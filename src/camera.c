#include "camera.h"

Camera *
camera_new(
    guint id,
    const gchar *name,
    const gchar *source,
    CameraSourceType source_type,
    const gchar *rtsp_url
)
{
    Camera *camera;

    if (name == NULL ||
        source == NULL ||
        rtsp_url == NULL)
    {
        return NULL;
    }

    camera = g_new0(Camera, 1);

    camera->id = id;
    camera->name = g_strdup(name);
    camera->source = g_strdup(source);
    camera->source_type = source_type;
    camera->rtsp_url = g_strdup(rtsp_url);

    return camera;
}

void
camera_free(Camera *camera)
{
    if (camera == NULL)
    {
        return;
    }

    g_free(camera->name);
    g_free(camera->source);
    g_free(camera->rtsp_url);

    g_free(camera);
}