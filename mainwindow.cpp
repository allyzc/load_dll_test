#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "keystone_manager.h"
#include "capstone_manager.h"
#include "contx.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    csh cs = CapstoneManager::instance().handle();
    if (!cs) return;

    QString s_dsm = ui->te_input_dsm->toPlainText();
    auto code = Contx::strToBytes(s_dsm);
    uint64_t address = Contx::strToHexAddress(ui->edit_dsm_addr->text());

    cs_insn* insn;
    size_t count = cs_disasm(
        cs,
        code.data(),
        code.size(),
        address,
        0,
        &insn
    );

    QString s_intput = Contx::bytesToStr(code.data(), code.size());
    qDebug()<<"input:"<<s_intput;
    qDebug()<<"count:"<<count;

    ui->tb_output_dsm->clear();

    QString s_out = "";

    for (size_t i = 0; i < count; i++) {
        s_out += QString::asprintf("%016llX,%s,%s\r\n", insn[i].address, insn[i].mnemonic, insn[i].op_str);
        // qDebug() << QString("%1 %2")
        // .arg(insn[i].mnemonic)
        //     .arg(insn[i].op_str);
    }

    ui->tb_output_dsm->append(s_out);

    cs_free(insn, count);
}

