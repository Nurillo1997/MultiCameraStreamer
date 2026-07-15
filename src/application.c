#include "application.h"

#include <stdio.h>

#include "camera.h"
#include "config_manager.h"

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
        &application->cameras,
        g_ptr_array_unref
    );

    printf("Application shutting down.\n");
}