#include "pipeline_manager.h"

#include "camera_pipeline.h"

PipelineManager *
pipeline_manager_new(void)
{
    PipelineManager *manager;

    manager = g_new0(PipelineManager, 1);

    manager->pipelines = g_ptr_array_new_with_free_func(
        (GDestroyNotify)camera_pipeline_free
    );

    return manager;
}

gboolean
pipeline_manager_add_camera(
    PipelineManager *manager,
    Camera *camera
)
{
    CameraPipeline *camera_pipeline;

    if (manager == NULL || camera == NULL)
    {
        return FALSE;
    }

    camera_pipeline = camera_pipeline_new(camera);

    if (camera_pipeline == NULL)
    {
        return FALSE;
    }

    g_ptr_array_add(
        manager->pipelines,
        camera_pipeline
    );

    return TRUE;
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