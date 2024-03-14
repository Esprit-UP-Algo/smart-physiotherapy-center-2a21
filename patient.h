#ifndef PATIENT_H
#define PATIENT_H
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

class patient
{
public:
    patient();
    patient(QString,QString,QString,QString,QDate,QString, QString,int);

    void setid(QString n);
    void setnom(QString n);
    void setprenom(QString n);
    void setgenre(QString n);
    void setadresse(QString n);
    void setmail(QString n);
    void setdatee(QDate n);
    void setnum(int n);

    QString get_id();
    QString get_nom();
    QString get_prenom();
    QString get_genre();
    QString get_adresse();
    QString get_mail();
    QString get_poste();
    QDate get_date();
    int get_num();

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool modifier(QString);

private:
    int num;
    QString id,nom,prenom,genre,adresse,mail;
    QDate datee;
};

#endif // PATIENT_H
