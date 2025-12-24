
INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/include/keystone/arm.h \
    $$PWD/include/keystone/arm64.h \
    $$PWD/include/keystone/evm.h \
    $$PWD/include/keystone/hexagon.h \
    $$PWD/include/keystone/keystone.h \
    $$PWD/include/keystone/mips.h \
    $$PWD/include/keystone/ppc.h \
    $$PWD/include/keystone/sparc.h \
    $$PWD/include/keystone/systemz.h \
    $$PWD/include/keystone/x86.h \
    $$PWD/keystone_dyn.h \
    $$PWD/keystone_manager.h

SOURCES += \
    $$PWD/keystone_dyn.c \
    $$PWD/keystone_manager.cpp
