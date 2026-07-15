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

gboolean
pipeline_manager_start(PipelineManager *manager)
{
    if (manager == NULL)
    {
        return FALSE;
    }

    for (guint i = 0; i < manager->pipelines->len; i++)
    {
        CameraPipeline *camera_pipeline;

        camera_pipeline = g_ptr_array_index(
            manager->pipelines,
            i
        );

        if (!camera_pipeline_start(camera_pipeline))
        {
            g_printerr(
                "Failed to start one of the camera pipelines.\n"
            );

            pipeline_manager_stop(manager);

            return FALSE;
        }
    }

    return TRUE;
}

void
pipeline_manager_stop(PipelineManager *manager)
{
    if (manager == NULL)
    {
        return;
    }

    for (guint i = 0; i < manager->pipelines->len; i++)
    {
        CameraPipeline *camera_pipeline;

        camera_pipeline = g_ptr_array_index(
            manager->pipelines,
            i
        );

        camera_pipeline_stop(camera_pipeline);
    }
}

void
pipeline_manager_free(PipelineManager *manager)
{
    if (manager == NULL)
    {
        return;
    }

    pipeline_manager_stop(manager);

    g_clear_pointer(
        &manager->pipelines,
        g_ptr_array_unref
    );

    g_free(manager);
}