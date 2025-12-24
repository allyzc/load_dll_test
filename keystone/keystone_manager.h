#pragma once

extern "C" {
#include <keystone/keystone.h>
}

class KeystoneManager
{
public:
    static KeystoneManager& instance();

    bool init(const char* dllPath,
              ks_arch arch,
              ks_mode mode);

    void shutdown();

    ks_engine* engine() const;

private:
    KeystoneManager() = default;
    ~KeystoneManager() = default;

    KeystoneManager(const KeystoneManager&) = delete;
    KeystoneManager& operator=(const KeystoneManager&) = delete;

private:
    ks_engine* m_engine = nullptr;
    bool m_loaded = false;
};
