
INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/capstone_dyn.h \
    $$PWD/capstone_manager.h \
    $$PWD/include/capstone/arm.h \
    $$PWD/include/capstone/arm64.h \
    $$PWD/include/capstone/bpf.h \
    $$PWD/include/capstone/capstone.h \
    $$PWD/include/capstone/evm.h \
    $$PWD/include/capstone/m680x.h \
    $$PWD/include/capstone/m68k.h \
    $$PWD/include/capstone/mips.h \
    $$PWD/include/capstone/mos65xx.h \
    $$PWD/include/capstone/platform.h \
    $$PWD/include/capstone/ppc.h \
    $$PWD/include/capstone/riscv.h \
    $$PWD/include/capstone/sh.h \
    $$PWD/include/capstone/sparc.h \
    $$PWD/include/capstone/systemz.h \
    $$PWD/include/capstone/tms320c64x.h \
    $$PWD/include/capstone/tricore.h \
    $$PWD/include/capstone/wasm.h \
    $$PWD/include/capstone/x86.h \
    $$PWD/include/capstone/xcore.h

SOURCES += \
    $$PWD/capstone_dyn.c \
    $$PWD/capstone_manager.cpp


