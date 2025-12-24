#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int  capstone_load_library(const char* dll_path);
void capstone_unload_library(void);
int  capstone_is_loaded(void);

#ifdef __cplusplus
}
#endif
