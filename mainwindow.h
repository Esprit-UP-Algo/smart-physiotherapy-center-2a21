#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"QListView"
#include"QStringListModel"
#include"QGraphicsTextItem"
#include"QGraphicsView"
#include <QCompleter>
#include <QDateTime>
#include <QGridLayout>
#include"rendezvous.h"
#include <QMainWindow>

#include <QChartView>
#include "patient.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_x_clicked();

    void on_Close_clicked();
    void handleRendezvousAdded(const QDateTime& dateTime, const QString& status, const QString& client, const QString& notes, const QString& location);
    void updateRendezvousCards();

    void on_gestion_employee_2_clicked();

    void on_gestion_employee_clicked();

    void on_ajouter_client_clicked();
    void handleRendezvousUpdated(const Rendezvous &rendezvous);
    void handleRendezvousDeleted(const QString &rendezvousId);
//

        int controlSaisie();
        void clear();
       void on_ajouter_4_clicked();

         void on_modifer_4_clicked();

        void on_supp_4_clicked();











private:
    Ui::MainWindow *ui;
       QGraphicsView *mView;
       QGraphicsScene *mScene;
       QGraphicsTextItem *mText;
       QStringListModel *model;
       QCompleter *stringCompleter;
       QCompleter *ModelCompleter;
       QGridLayout *cardsLayout;

       //

           patient P;



};

#endif // MAINWINDOW_H
