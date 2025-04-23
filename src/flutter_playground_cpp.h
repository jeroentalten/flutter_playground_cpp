
#if _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

#if _WIN32
#define FFI_PLUGIN_EXPORT __declspec(dllexport)
#else
#define FFI_PLUGIN_EXPORT
#endif

extern "C"{
    FFI_PLUGIN_EXPORT const char *send_message(const char *username, const char *message, const char *encodedImage);
    FFI_PLUGIN_EXPORT const char *get_messages();
}

