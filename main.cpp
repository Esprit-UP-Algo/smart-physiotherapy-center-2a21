#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "connection.h"
#include <QMessageBox>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Connection c;
    bool test=c.createconnect();


     MainWindow w;
    if(test)
    {
        w.show();

        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}

