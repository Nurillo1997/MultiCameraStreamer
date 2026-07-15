#include <gst/gst.h>

#include <stdio.h>

#include "application.h"

int
main(int argc, char *argv[])
{
    gst_init(&argc, &argv);

    if (!application_init())
    {
        fprintf(stderr, "Failed to initialize application.\n");
        return 1;
    }

    application_run();
    application_shutdown();

    return 0;
}