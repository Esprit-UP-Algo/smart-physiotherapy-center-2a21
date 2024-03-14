

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfilesystemmodel.h"
#include "QMessageBox"
#include "QToolTip"
#include "QFileDialog"
#include "QTimer"
#include <fstream>
#include <QtSvg/QSvgRenderer>
#include <QUrl>
#include <QDesktopServices>
#include "rendezvouscard.h"
#include "rendezvous.h"
#include "addrendezvousdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patient.h"
#include <QMessageBox>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->tab_patient_3->setModel(P.afficher());

    auto *cardsContainer = new QWidget();
    auto *cardsLayout = new QGridLayout();
    cardsContainer->setLayout(cardsLayout);

    QVector<Rendezvous> rendezvousList = Rendezvous::getAllRendezvousFromDatabase();
    int row = 0, column = 0;
    int cardsPerRow = 2;

    for (const Rendezvous& rendezvous : rendezvousList) {
        auto *card = new RendezvousCard(rendezvous);
        cardsLayout->addWidget(card, row, column);
        connect(card, &RendezvousCard::rendezvousUpdated, this, &MainWindow::handleRendezvousUpdated);
     connect(card, &RendezvousCard::rendezvousDeleted, this, &MainWindow::handleRendezvousDeleted);
        column++;
        if (column >= cardsPerRow) {
            column = 0;
            row++;
        }
    }

    cardsLayout->setAlignment(Qt::AlignTop);
    cardsLayout->setHorizontalSpacing(10);
    cardsLayout->setVerticalSpacing(20);

    ui->scrollArea->setWidget(cardsContainer);
    ui->scrollArea->setWidgetResizable(true);
}

MainWindow::~MainWindow()
{
    delete ui;

}



void MainWindow::on_x_clicked()
{
    setWindowState(Qt::WindowMinimized);
}

void MainWindow::on_Close_clicked()
{
    close();
}


void MainWindow::on_gestion_employee_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}
void MainWindow::on_gestion_employee_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::updateRendezvousCards() {
    QVector<Rendezvous> rendezvousList = Rendezvous::getAllRendezvousFromDatabase();


    QWidget* cardsContainer = ui->scrollArea->takeWidget();

    if (cardsContainer) {
        QLayoutItem* item;
        while ((item = cardsContainer->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete cardsContainer;
    }

    cardsContainer = new QWidget();
    auto* cardsLayout = new QGridLayout();
    cardsContainer->setLayout(cardsLayout);

    int row = 0, column = 0;
    int cardsPerRow = 2;

    for (const Rendezvous& rendezvous : rendezvousList) {
        auto* card = new RendezvousCard(rendezvous);
        cardsLayout->addWidget(card, row, column);

        column++;
        if (column >= cardsPerRow) {
            column = 0;
            row++;
        }
    }

    cardsLayout->setAlignment(Qt::AlignTop);
    cardsLayout->setHorizontalSpacing(10);
    cardsLayout->setVerticalSpacing(20);

    ui->scrollArea->setWidget(cardsContainer);
    ui->scrollArea->setWidgetResizable(true);
}

void MainWindow::handleRendezvousAdded(const QDateTime& dateTime, const QString& status, const QString& client, const QString& notes, const QString& location) {
    Rendezvous rendezvous(dateTime, status, client, notes, location);
    if (rendezvous.addRendezvousToDatabase()) {
        QMessageBox::information(this, tr("Add Rendezvous"), tr("The rendezvous has been successfully added."));
        updateRendezvousCards();
    } else {
        QMessageBox::critical(this, tr("Add Rendezvous"), tr("Failed to add the rendezvous. Please check the details and try again."));
    }
}



void MainWindow::on_ajouter_client_clicked()
{
    AddRendezvousDialog dialog(this);
    connect(&dialog, &AddRendezvousDialog::rendezvousAdded, this, &MainWindow::handleRendezvousAdded);
    dialog.exec();
}


void MainWindow::handleRendezvousUpdated(const Rendezvous& updatedRendezvous) {
    if (updatedRendezvous.updateRendezvousInDatabase()) {

        QMessageBox::information(this, tr("Update Rendezvous"), tr("The rendezvous has been successfully updated."));
    } else {
        QMessageBox::critical(this, tr("Update Rendezvous"), tr("Failed to update the rendezvous. Please check the details and try again."));
    }
}


void MainWindow::handleRendezvousDeleted(const QString &rendezvousId) {
    Rendezvous rendezvous;
    rendezvous.setRendezvousId(rendezvousId);
    if (rendezvous.deleteRendezvousFromDatabase()) {
        QMessageBox::information(this, tr("Delete Rendezvous"), tr("The rendezvous has been successfully deleted."));
    } else {
        QMessageBox::critical(this, tr("Delete Rendezvous"), tr("Failed to delete the rendezvous. Please try again."));
    }
}



//


int MainWindow::controlSaisie()
{

    if (
            (ui->bid_4->text().isEmpty()) ||
            (ui->bid_4->text().toInt() == 0) ||
            (ui->bnom_3->text().isEmpty()) ||
            (ui->bnom_3->text().toInt() == 0) ||
            (ui->bprenom_3->text().isEmpty()) ||
            (ui->bprenom_3->text().toInt() == 0) ||
            (ui->b_genre_3->currentText().isEmpty()) ||
            (ui->b_genre_3->currentText().toInt() == 0) ||
            (ui->badresse_3->text().isEmpty()) ||
            (ui->badresse_3->text().toInt() == 0) ||
            (ui->bmail_3->text().isEmpty()) ||
            (ui->bmail_3->text().toInt() == 0) ||
            (ui->bnum_3->text().isEmpty()) ||
            (ui->bnum_3->text().toInt() == 0) ||
            (ui->b_date_4->text().isEmpty()) ||
            (ui->b_date_4->text().toInt() == 0))
        return 0;
    else
        return 1;

}


void MainWindow::on_ajouter_4_clicked()
{

    QString id =ui->bid_4->text();
    QString nom=ui->bnom_3->text();
    QString prenom=ui->bprenom_3->text();
    QString mail=ui->bmail_3->text();
    QString adresse=ui->badresse_3->text();
    int num=ui->bnum_3->text().toInt();
    QString genre=ui->b_genre_3->currentText();
    QDate datee = ui->b_date_4->date();

     patient  P(id,nom,prenom,genre,datee,adresse,mail,num);

    bool test = P.ajouter();
    if (test){
       QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Ajout effectué\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                            QObject::tr("Ajout non effetué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_patient_3->setModel(P.afficher());
}


void MainWindow::on_modifer_4_clicked()
{
    QString id =ui->bid_4->text();
    QString nom=ui->bnom_3->text();
    QString prenom=ui->bprenom_3->text();
    QString mail=ui->bmail_3->text();
    QString adresse=ui->badresse_3->text();
    int num=ui->bnum_3->text().toInt();
    QString genre=ui->b_genre_3->currentText();
    QDate datee = ui->b_date_4->date();

     patient  P(id,nom,prenom,genre,datee,adresse,mail,num);


     bool test = P.modifier(id);
     if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("ubdate effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_patient_3->setModel(P.afficher());

     }
     else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                             QObject::tr("ubdate non effetué.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_supp_4_clicked()
{
    QString id = ui->supp_4->text();
    bool test=P.supprimer(id);

    if(test)
    {

            QMessageBox::information(nullptr, QObject::tr("database is open"),
            QObject::tr("suppression successful.\n"
                    "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
            QObject::tr("suppression failed.\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);
    }

    ui->tab_patient_3->setModel(P.afficher());
    //ui->supp_4->clear();
}












