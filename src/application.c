#include "application.h"

#include <stdio.h>

#include "camera.h"
#include "config_manager.h"
#include "pipeline_manager.h"

#define CONFIG_FILE_PATH "config/streams.json"

static void
print_cameras(const GPtrArray *cameras)
{
    for (guint i = 0; i < cameras->len; i++)
    {
        Camera *camera;

        camera = g_ptr_array_index(cameras, i);

        printf(
            "Camera loaded: id=%u, name=%s, source=%s\n",
            camera->id,
            camera->name,
            camera->source
        );
    }
}

static gboolean
create_camera_pipelines(Application *application)
{
    for (guint i = 0; i < application->cameras->len; i++)
    {
        Camera *camera;

        camera = g_ptr_array_index(
            application->cameras,
            i
        );

        if (!pipeline_manager_add_camera(
                application->pipeline_manager,
                camera))
        {
            g_printerr(
                "Failed to create pipeline for camera: %s\n",
                camera->name
            );

            return FALSE;
        }
    }

    return TRUE;
}

gboolean
application_init(Application *application)
{
    if (application == NULL)
    {
        return FALSE;
    }

    application->cameras = config_manager_load_cameras(
        CONFIG_FILE_PATH
    );

    if (application->cameras == NULL)
    {
        g_printerr("Failed to load camera configuration.\n");
        return FALSE;
    }

    application->pipeline_manager = pipeline_manager_new();

    if (application->pipeline_manager == NULL)
    {
        g_printerr("Failed to create pipeline manager.\n");

        g_clear_pointer(
            &application->cameras,
            g_ptr_array_unref
        );

        return FALSE;
    }

    if (!create_camera_pipelines(application))
    {
        g_printerr("Failed to create camera pipelines.\n");

        g_clear_pointer(
            &application->pipeline_manager,
            pipeline_manager_free
        );

        g_clear_pointer(
            &application->cameras,
            g_ptr_array_unref
        );

        return FALSE;
    }

    printf(
        "Application initialized with %u camera(s).\n",
        application->cameras->len
    );

    return TRUE;
}

void
application_run(Application *application)
{
    if (application == NULL)
    {
        return;
    }

    print_cameras(application->cameras);
}

void
application_shutdown(Application *application)
{
    if (application == NULL)
    {
        return;
    }

    g_clear_pointer(
        &application->pipeline_manager,
        pipeline_manager_free
    );

    g_clear_pointer(
        &application->cameras,
        g_ptr_array_unref
    );

    printf("Application shutting down.\n");
}