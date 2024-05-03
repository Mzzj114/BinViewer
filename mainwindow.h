#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openBinFile(QString file_name);

private slots:
    void on_actionOpen_file_triggered();

private:
    Ui::MainWindow *ui;

    //each time 4kb to read
    const qint64 block_length = 1024*4;

    QFile current_file;
    QTimer read_timer;

    void readBlock();

};
#endif // MAINWINDOW_H
