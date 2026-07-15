#include "camera_pipeline.h"

static void
on_pad_added(
    GstElement *decoder,
    GstPad *new_pad,
    gpointer user_data
)
{
    CameraPipeline *camera_pipeline;
    GstPad *sink_pad;
    GstCaps *caps;
    const GstStructure *structure;
    const gchar *media_type;

    camera_pipeline = user_data;

    sink_pad = gst_element_get_static_pad(
        camera_pipeline->video_convert,
        "sink"
    );

    if (gst_pad_is_linked(sink_pad))
    {
        gst_object_unref(sink_pad);
        return;
    }

    caps = gst_pad_get_current_caps(new_pad);

    if (caps == NULL)
    {
        caps = gst_pad_query_caps(new_pad, NULL);
    }

    structure = gst_caps_get_structure(caps, 0);
    media_type = gst_structure_get_name(structure);

    if (g_str_has_prefix(media_type, "video/"))
    {
        if (gst_pad_link(new_pad, sink_pad) != GST_PAD_LINK_OK)
        {
            g_printerr(
                "Failed to link video pad for camera: %s\n",
                camera_pipeline->camera->name
            );
        }
    }

    gst_caps_unref(caps);
    gst_object_unref(sink_pad);
}

CameraPipeline *
camera_pipeline_new(Camera *camera)
{
    CameraPipeline *camera_pipeline;

    if (camera == NULL)
    {
        return NULL;
    }

    camera_pipeline = g_new0(CameraPipeline, 1);

    camera_pipeline->camera = camera;

    camera_pipeline->pipeline = gst_pipeline_new(camera->name);
    camera_pipeline->source = gst_element_factory_make(
        "filesrc",
        NULL
    );
    camera_pipeline->decoder = gst_element_factory_make(
        "decodebin",
        NULL
    );
    camera_pipeline->video_convert = gst_element_factory_make(
        "videoconvert",
        NULL
    );
    camera_pipeline->video_sink = gst_element_factory_make(
        "fakesink",
        NULL
    );

    if (camera_pipeline->pipeline == NULL ||
        camera_pipeline->source == NULL ||
        camera_pipeline->decoder == NULL ||
        camera_pipeline->video_convert == NULL ||
        camera_pipeline->video_sink == NULL)
    {
        g_printerr(
            "Failed to create GStreamer elements for camera: %s\n",
            camera->name
        );

        camera_pipeline_free(camera_pipeline);
        return NULL;
    }

    g_object_set(
        camera_pipeline->source,
        "location",
        camera->source,
        NULL
    );

    gst_bin_add_many(
        GST_BIN(camera_pipeline->pipeline),
        camera_pipeline->source,
        camera_pipeline->decoder,
        camera_pipeline->video_convert,
        camera_pipeline->video_sink,
        NULL
    );

    if (!gst_element_link(
            camera_pipeline->source,
            camera_pipeline->decoder))
    {
        g_printerr(
            "Failed to link source and decoder for camera: %s\n",
            camera->name
        );

        camera_pipeline_free(camera_pipeline);
        return NULL;
    }

    if (!gst_element_link(
            camera_pipeline->video_convert,
            camera_pipeline->video_sink))
    {
        g_printerr(
            "Failed to link video converter and sink for camera: %s\n",
            camera->name
        );

        camera_pipeline_free(camera_pipeline);
        return NULL;
    }

    g_signal_connect(
        camera_pipeline->decoder,
        "pad-added",
        G_CALLBACK(on_pad_added),
        camera_pipeline
    );

    return camera_pipeline;
}

gboolean
camera_pipeline_start(CameraPipeline *camera_pipeline)
{
    GstStateChangeReturn result;

    if (camera_pipeline == NULL ||
        camera_pipeline->pipeline == NULL)
    {
        return FALSE;
    }

    result = gst_element_set_state(
        camera_pipeline->pipeline,
        GST_STATE_PLAYING
    );

    if (result == GST_STATE_CHANGE_FAILURE)
    {
        g_printerr(
            "Failed to start pipeline for camera: %s\n",
            camera_pipeline->camera->name
        );

        return FALSE;
    }

    return TRUE;
}

void
camera_pipeline_stop(CameraPipeline *camera_pipeline)
{
    if (camera_pipeline == NULL ||
        camera_pipeline->pipeline == NULL)
    {
        return;
    }

    gst_element_set_state(
        camera_pipeline->pipeline,
        GST_STATE_NULL
    );
}

void
camera_pipeline_free(CameraPipeline *camera_pipeline)
{
    if (camera_pipeline == NULL)
    {
        return;
    }

    if (camera_pipeline->pipeline != NULL)
    {
        camera_pipeline_stop(camera_pipeline);
        gst_object_unref(camera_pipeline->pipeline);
    }

    g_free(camera_pipeline);
}