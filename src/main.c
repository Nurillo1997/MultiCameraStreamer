#include <gst/gst.h>

#include <stdio.h>

#include "application.h"

int
main(int argc, char *argv[])
{
    Application application = {0};

    gst_init(&argc, &argv);

    if (!application_init(&application))
    {
        fprintf(stderr, "Failed to initialize application.\n");
        return 1;
    }

    application_run(&application);
    application_shutdown(&application);

    return 0;
}