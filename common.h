#include <gtk/gtk.h>

#if GLIB_CHECK_VERSION(2, 74, 0)
    constexpr GApplicationFlags app_flags = G_APPLICATION_DEFAULT_FLAGS;
#else
    constexpr GApplicationFlags app_flags = G_APPLICATION_FLAGS_NONE;
#endif
