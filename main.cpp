#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    if (qApp->arguments().size() >=2 )
    {
        QString potential_file_name = qApp->arguments().at(1);
        qDebug() << potential_file_name;
        /*
        if (!potential_file_name.isEmpty())
            w.openBinFile(potential_file_name);
        */
    }

    return a.exec();
}
