// keystone_wrapper.c
#include <windows.h>
#include <keystone/keystone.h>

// -----------------------------------------------------------------------------
//  全局函数指针定义（你感兴趣的最常用 API）
// -----------------------------------------------------------------------------
static ks_err   (*fp_ks_open)(ks_arch, ks_mode, ks_engine**) = NULL;
static ks_err   (*fp_ks_close)(ks_engine*)                = NULL;
static int      (*fp_ks_asm)(ks_engine*, const char*, uint64_t,
                     unsigned char**, size_t*, size_t*)   = NULL;
static void     (*fp_ks_free)(void*)                      = NULL;
static ks_err   (*fp_ks_option)(ks_engine*, ks_opt_type, size_t) = NULL;
static ks_err   (*fp_ks_errno)(ks_engine*)                = NULL;
static const char* (*fp_ks_strerror)(ks_err)              = NULL;

// -----------------------------------------------------------------------------
//  动态加载库和函数指针
// -----------------------------------------------------------------------------
static HMODULE g_keystone_lib = NULL;

int keystone_load_library(const char* dll_path)
{
    if (g_keystone_lib)
        return 1; // 已加载

    g_keystone_lib = LoadLibraryA(dll_path);
    if (!g_keystone_lib)
        return 0;

    fp_ks_open      = (void*)GetProcAddress(g_keystone_lib, "ks_open");
    fp_ks_close     = (void*)GetProcAddress(g_keystone_lib, "ks_close");
    fp_ks_asm       = (void*)GetProcAddress(g_keystone_lib, "ks_asm");
    fp_ks_free      = (void*)GetProcAddress(g_keystone_lib, "ks_free");
    fp_ks_option    = (void*)GetProcAddress(g_keystone_lib, "ks_option");
    fp_ks_errno     = (void*)GetProcAddress(g_keystone_lib, "ks_errno");
    fp_ks_strerror  = (void*)GetProcAddress(g_keystone_lib, "ks_strerror");

    // 你可以检测你想要的每个函数是否存在
    if (!fp_ks_open || !fp_ks_close || !fp_ks_asm || !fp_ks_free)
        return 0; // 很关键

    return 1;
}

void keystone_unload_library()
{
    if (g_keystone_lib) {
        FreeLibrary(g_keystone_lib);
        g_keystone_lib = NULL;
    }
}

// -----------------------------------------------------------------------------
//  对外 API：按官方签名对外转发
// -----------------------------------------------------------------------------
//ks_err ks_open(ks_arch arch, ks_mode mode, ks_engine** ks)
ks_err ks_open(ks_arch arch, int mode, ks_engine **ks)
{
    if (!fp_ks_open) return KS_ERR_HANDLE;
    return fp_ks_open(arch, mode, ks);
}

ks_err ks_close(ks_engine* ks)
{
    if (!fp_ks_close) return KS_ERR_HANDLE;
    return fp_ks_close(ks);
}

int ks_asm(ks_engine* ks, const char* assembly,
           uint64_t address,
           unsigned char** encoding,
           size_t* size,
           size_t* count)
{
    if (!fp_ks_asm) return -1;
    return fp_ks_asm(ks, assembly, address, encoding, size, count);
}

//void ks_free(void* p)
void ks_free(unsigned char *p)
{
    if (!fp_ks_free) return;
    fp_ks_free(p);
}

ks_err ks_option(ks_engine* ks, ks_opt_type type, size_t value)
{
    if (!fp_ks_option) return KS_ERR_HANDLE;
    return fp_ks_option(ks, type, value);
}

ks_err ks_errno(ks_engine* ks)
{
    if (!fp_ks_errno) return KS_ERR_HANDLE;
    return fp_ks_errno(ks);
}

const char* ks_strerror(ks_err code)
{
    if (!fp_ks_strerror) return "Unknown";
    return fp_ks_strerror(code);
}
