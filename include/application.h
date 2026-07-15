#ifndef APPLICATION_H
#define APPLICATION_H

#include <glib.h>

/**
 * Initializes the application.
 *
 * Returns TRUE on success, FALSE on failure.
 */
gboolean
application_init(void);

/**
 * Runs the application.
 */
void
application_run(void);

/**
 * Shuts down the application and releases resources.
 */
void
application_shutdown(void);

#endif /* APPLICATION_H */