#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::NoFocus);

    connect(&read_timer, &QTimer::timeout, this, &MainWindow::readBlock);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_file_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a binary file");
    openBinFile(file_name);
}

void MainWindow::readBlock()
{
    QByteArray data;
    char* rawdata = new char[block_length/sizeof(char)];

    qint64 read = current_file.read(rawdata, block_length);

    if (read < block_length)
    {
        read_timer.stop();
        current_file.close();
    }

    data.setRawData(rawdata,read);

    ui->textEdit->setPlainText(ui->textEdit->toPlainText()+data.toHex(' '));
}

void MainWindow::openBinFile(QString file_name)
{

    current_file.setFileName(file_name);
    if (!current_file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", current_file.errorString());
        return;
    }

    ui->actionDelete->setEnabled(true);
    ui->actionRename->setEnabled(true);
    ui->actionSave_as->setEnabled(true);

    QFileInfo current_info(current_file);
    ui->statusbar->showMessage("size: "+QVariant(current_file.size()).toString()+ "      "
                               "last modified: "+current_info.lastModified().toString());

    if (current_file.fileName().size()<=40)
        this->setWindowTitle(current_file.fileName());
    else
        this->setWindowTitle(current_info.fileName());

    readBlock();
    read_timer.start(900);

}

