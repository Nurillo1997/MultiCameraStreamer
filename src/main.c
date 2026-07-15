#include <gst/gst.h>

#include <stdio.h>

int
main(int argc, char *argv[])
{
    gst_init(&argc, &argv);

    printf("MultiCameraStreamer started.\n");

    return 0;
}