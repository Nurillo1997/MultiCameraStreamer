#ifndef PIPELINE_MANAGER_H
#define PIPELINE_MANAGER_H

#include <glib.h>

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
 * Releases all resources owned by the pipeline manager.
 */
void
pipeline_manager_free(PipelineManager *manager);

#endif /* PIPELINE_MANAGER_H */