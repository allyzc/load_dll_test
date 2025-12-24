#include "mainwindow.h"

#include <QApplication>

#include "keystone_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    KeystoneManager::instance().init(
        "keystone.dll",
        KS_ARCH_X86,
        KS_MODE_64
    );

    MainWindow w;
    w.show();

    int ret = a.exec();

    KeystoneManager::instance().shutdown();

    return ret;
}
