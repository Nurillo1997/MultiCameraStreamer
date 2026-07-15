#ifndef PIPELINE_MANAGER_H
#define PIPELINE_MANAGER_H

#include <glib.h>

#include "camera.h"

typedef struct
{
    GPtrArray *pipelines;
} PipelineManager;

/**
 * Creates a new pipeline manager.
 *
 * Returns a newly allocated PipelineManager on success.
 */
PipelineManager *
pipeline_manager_new(void);

/**
 * Creates and adds a pipeline for the given camera.
 *
 * Returns TRUE on success, FALSE on failure.
 */
gboolean
pipeline_manager_add_camera(
    PipelineManager *manager,
    Camera *camera
);

/**
 * Starts all camera pipelines.
 *
 * Returns TRUE on success, FALSE on failure.
 */
gboolean
pipeline_manager_start(PipelineManager *manager);

/**
 * Stops all camera pipelines.
 */
void
pipeline_manager_stop(PipelineManager *manager);

/**
 * Releases all resources owned by the pipeline manager.
 */
void
pipeline_manager_free(PipelineManager *manager);

#endif /* PIPELINE_MANAGER_H */