#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <glib.h>

/**
 * Loads cameras from a JSON configuration file.
 *
 * Returns a GPtrArray containing Camera objects on success.
 * The returned array must be freed with g_ptr_array_unref().
 */
GPtrArray *
config_manager_load_cameras(const gchar *config_path);

#endif /* CONFIG_MANAGER_H */