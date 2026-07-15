#ifndef APPLICATION_H
#define APPLICATION_H

#include <glib.h>

typedef struct
{
    GPtrArray *cameras;
} Application;

/**
 * Initializes the application.
 *
 * Returns TRUE on success, FALSE on failure.
 */
gboolean
application_init(Application *application);

/**
 * Runs the application.
 */
void
application_run(Application *application);

/**
 * Shuts down the application and releases resources.
 */
void
application_shutdown(Application *application);

#endif /* APPLICATION_H */