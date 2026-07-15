#include "config_manager.h"

#include <json-glib/json-glib.h>

#include "camera.h"

static gboolean
is_valid_source_type(const gchar *type)
{
    return g_strcmp0(type, "file") == 0 ||
           g_strcmp0(type, "rtsp") == 0;
}

static CameraSourceType
parse_source_type(const gchar *type)
{
    if (g_strcmp0(type, "rtsp") == 0)
    {
        return CAMERA_SOURCE_RTSP;
    }

    return CAMERA_SOURCE_FILE;
}

static gboolean
validate_camera_object(
    JsonObject *camera_object,
    guint index
)
{
    const gchar *required_members[] = {
        "id",
        "name",
        "source",
        "type",
        "rtsp_url"
    };

    guint member_count = G_N_ELEMENTS(
        required_members
    );

    for (guint i = 0; i < member_count; i++)
    {
        if (!json_object_has_member(
                camera_object,
                required_members[i]))
        {
            g_printerr(
                "Camera configuration at index %u "
                "is missing required field '%s'.\n",
                index,
                required_members[i]
            );

            return FALSE;
        }
    }

    return TRUE;
}

GPtrArray *
config_manager_load_cameras(const gchar *config_path)
{
    JsonParser *parser;
    JsonNode *root_node;
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

    if (!json_parser_load_from_file(
            parser,
            config_path,
            &error))
    {
        g_printerr(
            "Failed to load config file: %s\n",
            error->message
        );

        g_clear_error(&error);
        g_object_unref(parser);

        return NULL;
    }

    root_node = json_parser_get_root(
        parser
    );

    if (root_node == NULL ||
        !JSON_NODE_HOLDS_OBJECT(root_node))
    {
        g_printerr(
            "Invalid configuration: root must be a JSON object.\n"
        );

        g_object_unref(parser);
        return NULL;
    }

    root_object = json_node_get_object(
        root_node
    );

    if (!json_object_has_member(
            root_object,
            "cameras"))
    {
        g_printerr(
            "Invalid configuration: missing 'cameras' field.\n"
        );

        g_object_unref(parser);
        return NULL;
    }

    cameras_array = json_object_get_array_member(
        root_object,
        "cameras"
    );

    if (cameras_array == NULL)
    {
        g_printerr(
            "Invalid configuration: 'cameras' must be an array.\n"
        );

        g_object_unref(parser);
        return NULL;
    }

    cameras = g_ptr_array_new_with_free_func(
        (GDestroyNotify)camera_free
    );

    camera_count = json_array_get_length(
        cameras_array
    );

    for (guint i = 0; i < camera_count; i++)
    {
        JsonObject *camera_object;
        Camera *camera;

        guint id;
        const gchar *name;
        const gchar *source;
        const gchar *type;
        const gchar *rtsp_url;

        camera_object = json_array_get_object_element(
            cameras_array,
            i
        );

        if (camera_object == NULL)
        {
            g_printerr(
                "Invalid camera configuration at index %u.\n",
                i
            );

            continue;
        }

        if (!validate_camera_object(
                camera_object,
                i))
        {
            continue;
        }

        id = json_object_get_int_member(
            camera_object,
            "id"
        );

        name = json_object_get_string_member(
            camera_object,
            "name"
        );

        source = json_object_get_string_member(
            camera_object,
            "source"
        );

        type = json_object_get_string_member(
            camera_object,
            "type"
        );

        rtsp_url = json_object_get_string_member(
            camera_object,
            "rtsp_url"
        );

        if (!is_valid_source_type(type))
        {
            g_printerr(
                "Camera '%s' has unsupported source type '%s'.\n",
                name,
                type
            );

            continue;
        }

        camera = camera_new(
            id,
            name,
            source,
            parse_source_type(type),
            rtsp_url
        );

        if (camera == NULL)
        {
            g_printerr(
                "Failed to create camera at index %u.\n",
                i
            );

            continue;
        }

        g_ptr_array_add(
            cameras,
            camera
        );
    }

    g_object_unref(parser);

    return cameras;
}