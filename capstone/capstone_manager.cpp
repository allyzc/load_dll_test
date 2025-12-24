#include "capstone_manager.h"
#include "capstone_dyn.h"
#include <QDebug>

CapstoneManager& CapstoneManager::instance()
{
    static CapstoneManager inst;
    return inst;
}

bool CapstoneManager::init(const char* dllPath,
                           cs_arch arch,
                           cs_mode mode)
{
    if (m_handle)
        return true;

    if (!capstone_load_library(dllPath)) {
        qWarning() << "Failed to load Capstone DLL";
        return false;
    }

    if (cs_open(arch, mode, &m_handle) != CS_ERR_OK) {
        qWarning() << "cs_open failed";
        capstone_unload_library();
        return false;
    }

    // 常用选项
    //cs_option(m_handle, CS_OPT_DETAIL, CS_OPT_ON);
    cs_option(m_handle, CS_OPT_DETAIL, CS_OPT_ON);
    cs_option(m_handle, CS_OPT_SKIPDATA, CS_OPT_OFF);
    cs_option(m_handle, CS_OPT_SYNTAX, CS_OPT_SYNTAX_INTEL);

    m_loaded = true;
    return true;
}

void CapstoneManager::shutdown()
{
    if (m_handle) {
        cs_close(&m_handle);
        m_handle = 0;
    }

    if (m_loaded) {
        capstone_unload_library();
        m_loaded = false;
    }
}

csh CapstoneManager::handle() const
{
    return m_handle;
}
