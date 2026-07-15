#include "camera_pipeline.h"

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

    if (camera_pipeline->pipeline == NULL)
    {
        g_free(camera_pipeline);
        return NULL;
    }

    return camera_pipeline;
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
        gst_element_set_state(
            camera_pipeline->pipeline,
            GST_STATE_NULL
        );

        gst_object_unref(camera_pipeline->pipeline);
    }

    g_free(camera_pipeline);
}