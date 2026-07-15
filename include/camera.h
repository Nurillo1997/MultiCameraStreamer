#ifndef CAMERA_H
#define CAMERA_H

#include <glib.h>

/**
 * Describes the type of camera source.
 */
typedef enum
{
    CAMERA_SOURCE_FILE,
    CAMERA_SOURCE_RTSP
} CameraSourceType;

/**
 * Represents a camera source and its RTSP output.
 */
typedef struct
{
    guint id;
    gchar *name;
    gchar *source;
    CameraSourceType source_type;
    gchar *rtsp_url;
} Camera;

/**
 * Creates a new camera.
 *
 * Returns a newly allocated Camera on success.
 */
Camera *
camera_new(
    guint id,
    const gchar *name,
    const gchar *source,
    CameraSourceType source_type,
    const gchar *rtsp_url
);

/**
 * Releases all resources owned by the camera.
 */
void
camera_free(Camera *camera);

#endif /* CAMERA_H */