#ifndef CAMERA_PIPELINE_H
#define CAMERA_PIPELINE_H

#include <gst/gst.h>

#include "camera.h"

typedef struct
{
    Camera *camera;

    GstElement *pipeline;
    GstElement *source;
    GstElement *decoder;
    GstElement *video_convert;
    GstElement *video_sink;
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
 * Starts the camera pipeline.
 *
 * Returns TRUE on success, FALSE on failure.
 */
gboolean
camera_pipeline_start(CameraPipeline *camera_pipeline);

/**
 * Stops the camera pipeline.
 */
void
camera_pipeline_stop(CameraPipeline *camera_pipeline);

/**
 * Releases all resources owned by the camera pipeline.
 */
void
camera_pipeline_free(CameraPipeline *camera_pipeline);

#endif /* CAMERA_PIPELINE_H */