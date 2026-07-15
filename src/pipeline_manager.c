#include "pipeline_manager.h"

PipelineManager *
pipeline_manager_new(void)
{
    PipelineManager *manager;

    manager = g_new0(PipelineManager, 1);

    manager->pipelines = g_ptr_array_new();

    return manager;
}

void
pipeline_manager_free(PipelineManager *manager)
{
    if (manager == NULL)
    {
        return;
    }

    g_clear_pointer(
        &manager->pipelines,
        g_ptr_array_unref
    );

    g_free(manager);
}