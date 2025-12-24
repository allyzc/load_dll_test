#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "keystone_manager.h"
#include "contx.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ks_engine* ks = KeystoneManager::instance().engine();
    if (!ks) return;

    unsigned char* code;
    size_t size, count;

    if (ks_asm(ks, "mov eax, ebx", 0, &code, &size, &count) >= 0) {
        // use code
        for (size_t i = 0; i < size; i++) {
            qDebug("%02x ", code[i]);
        }

        ks_free(code);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_keystone_asm_clicked()
{
    ks_engine* ks = KeystoneManager::instance().engine();
    if (!ks) return;

    QString s_asm = ui->te_input_asm->toPlainText();
    QByteArray ba_asm = s_asm.toLatin1();
    uint64_t address = Contx::strToHexAddress(ui->edit_asm_addr->text());

    unsigned char* code;
    size_t size, count;

    if (ks_asm(ks, ba_asm.data(), address, &code, &size, &count) >= 0) {
        // use code
        // for (size_t i = 0; i < size; i++) {
        //     qDebug("%02x ", code[i]);
        // }
        QString s_out = Contx::bytesToStr(code, size);
        ui->tb_output_asm->clear();
        ui->tb_output_asm->append(s_out);

        ks_free(code);
    }
}


void MainWindow::on_btn_capstone_dsm_clicked()
{

}

