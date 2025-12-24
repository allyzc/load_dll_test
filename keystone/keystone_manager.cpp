#include "keystone_manager.h"
#include "keystone_dyn.h"
#include <QDebug>

KeystoneManager& KeystoneManager::instance()
{
    static KeystoneManager inst;
    return inst;
}

bool KeystoneManager::init(const char* dllPath,
                           ks_arch arch,
                           ks_mode mode)
{
    if (m_engine)
        return true; // 已初始化

    if (!keystone_load_library(dllPath)) {
        qWarning() << "Failed to load Keystone DLL";
        return false;
    }

    if (ks_open(arch, mode, &m_engine) != KS_ERR_OK) {
        qWarning() << "ks_open failed";
        keystone_unload_library();
        return false;
    }

    m_loaded = true;
    return true;
}

void KeystoneManager::shutdown()
{
    if (m_engine) {
        ks_close(m_engine);
        m_engine = nullptr;
    }

    if (m_loaded) {
        keystone_unload_library();
        m_loaded = false;
    }
}

ks_engine* KeystoneManager::engine() const
{
    return m_engine;
}
