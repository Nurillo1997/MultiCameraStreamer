#include "config_manager.h"

#include <json-glib/json-glib.h>

#include "camera.h"

static CameraSourceType
parse_source_type(const gchar *type)
{
    if (g_strcmp0(type, "rtsp") == 0)
    {
        return CAMERA_SOURCE_RTSP;
    }

    return CAMERA_SOURCE_FILE;
}

GPtrArray *
config_manager_load_cameras(const gchar *config_path)
{
    JsonParser *parser;
    JsonObject *root_object;
    JsonArray *cameras_array;
    GPtrArray *cameras;
    GError *error = NULL;
    guint camera_count;

    if (config_path == NULL)
    {
        return NULL;
    }

    parser = json_parser_new();

    if (!json_parser_load_from_file(parser, config_path, &error))
    {
        g_printerr(
            "Failed to load config file: %s\n",
            error->message
        );

        g_clear_error(&error);
        g_object_unref(parser);

        return NULL;
    }

    root_object = json_node_get_object(
        json_parser_get_root(parser)
    );

    cameras_array = json_object_get_array_member(
        root_object,
        "cameras"
    );

    cameras = g_ptr_array_new_with_free_func(
        (GDestroyNotify)camera_free
    );

    camera_count = json_array_get_length(cameras_array);

    for (guint i = 0; i < camera_count; i++)
    {
        JsonObject *camera_object;
        Camera *camera;
        guint id;
        const gchar *name;
        const gchar *source;
        const gchar *type;

        camera_object = json_array_get_object_element(
            cameras_array,
            i
        );

        id = json_object_get_int_member(camera_object, "id");
        name = json_object_get_string_member(camera_object, "name");
        source = json_object_get_string_member(camera_object, "source");
        type = json_object_get_string_member(camera_object, "type");

        camera = camera_new(
            id,
            name,
            source,
            parse_source_type(type)
        );

        if (camera != NULL)
        {
            g_ptr_array_add(cameras, camera);
        }
    }

    g_object_unref(parser);

    return cameras;
}