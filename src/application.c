#include "application.h"

#include <stdio.h>

gboolean
application_init(void)
{
    printf("Application initialized.\n");

    return TRUE;
}

void
application_run(void)
{
    printf("Application running.\n");
}

void
application_shutdown(void)
{
    printf("Application shutting down.\n");
}