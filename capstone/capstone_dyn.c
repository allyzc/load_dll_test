// capstone_dyn.c
#include "capstone_dyn.h"
#include <windows.h>
#include <capstone/capstone.h>

static HMODULE g_capstone = NULL;

/* ---- Capstone API 函数指针 ---- */
static cs_err (*fp_cs_open)(cs_arch, cs_mode, csh*) = NULL;
static cs_err (*fp_cs_close)(csh*) = NULL;
static size_t (*fp_cs_disasm)(
    csh, const uint8_t*, size_t, uint64_t, size_t, cs_insn**) = NULL;
static void (*fp_cs_free)(cs_insn*, size_t) = NULL;
static int (*fp_cs_option)(csh, cs_opt_type, size_t) = NULL;
static const char* (*fp_cs_strerror)(cs_err) = NULL;

int capstone_is_loaded(void)
{
    return g_capstone != NULL;
}

int capstone_load_library(const char* dll_path)
{
    if (g_capstone)
        return 1;

    g_capstone = LoadLibraryA(dll_path);
    if (!g_capstone)
        return 0;

#define RESOLVE(name) \
    fp_##name = (void*)GetProcAddress(g_capstone, #name)

    RESOLVE(cs_open);
    RESOLVE(cs_close);
    RESOLVE(cs_disasm);
    RESOLVE(cs_free);
    RESOLVE(cs_option);
    RESOLVE(cs_strerror);

#undef RESOLVE

    if (!fp_cs_open || !fp_cs_close ||
        !fp_cs_disasm || !fp_cs_free)
    {
        capstone_unload_library();
        return 0;
    }

    return 1;
}

void capstone_unload_library(void)
{
    if (g_capstone) {
        FreeLibrary(g_capstone);
        g_capstone = NULL;
    }
}

/* ---- 对外暴露的“官方 API” ---- */

cs_err cs_open(cs_arch arch, cs_mode mode, csh* handle)
{
    if (!fp_cs_open) return CS_ERR_HANDLE;
    return fp_cs_open(arch, mode, handle);
}

cs_err cs_close(csh* handle)
{
    if (!fp_cs_close) return CS_ERR_HANDLE;
    return fp_cs_close(handle);
}

size_t cs_disasm(
    csh handle,
    const uint8_t* code,
    size_t code_size,
    uint64_t address,
    size_t count,
    cs_insn** insn)
{
    if (!fp_cs_disasm) return 0;
    return fp_cs_disasm(handle, code, code_size, address, count, insn);
}

void cs_free(cs_insn* insn, size_t count)
{
    if (fp_cs_free)
        fp_cs_free(insn, count);
}

//int cs_option(csh handle, cs_opt_type type, size_t value)
cs_err CAPSTONE_API cs_option(csh handle, cs_opt_type type, size_t value)
{
    if (!fp_cs_option) return CS_ERR_HANDLE;
    return fp_cs_option(handle, type, value);
}

const char* cs_strerror(cs_err code)
{
    if (!fp_cs_strerror) return "Unknown";
    return fp_cs_strerror(code);
}
