#pragma once

extern "C" {
#include <capstone/capstone.h>
}

class CapstoneManager
{
public:
    static CapstoneManager& instance();

    bool init(const char* dllPath,
              cs_arch arch,
              cs_mode mode);

    void shutdown();

    csh handle() const;

private:
    CapstoneManager() = default;
    ~CapstoneManager() = default;

    CapstoneManager(const CapstoneManager&) = delete;
    CapstoneManager& operator=(const CapstoneManager&) = delete;

private:
    csh m_handle = 0;
    bool m_loaded = false;
};
