#ifndef CAMERA_PIPELINE_H
#define CAMERA_PIPELINE_H

#include <gst/gst.h>

#include "camera.h"

typedef struct
{
    Camera *camera;
    GstElement *pipeline;
} CameraPipeline;

/**
 * Creates a new camera pipeline.
 *
 * The Camera object is borrowed and remains owned by the caller.
 *
 * Returns a newly allocated CameraPipeline on success.
 */
CameraPipeline *
camera_pipeline_new(Camera *camera);

/**
 * Releases all resources owned by the camera pipeline.
 */
void
camera_pipeline_free(CameraPipeline *camera_pipeline);

#endif /* CAMERA_PIPELINE_H */