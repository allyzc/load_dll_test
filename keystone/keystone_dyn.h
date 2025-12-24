#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// 动态库加载 / 卸载
int  keystone_load_library(const char* dll_path);
void keystone_unload_library(void);

// 可选：查询是否已加载
int  keystone_is_loaded(void);

#ifdef __cplusplus
}
#endif
