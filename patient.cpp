#include "patient.h"


patient::patient()
{
    id="";
    nom="";
    prenom="";
    genre="";
    datee= QDate(01,12,2023);
    adresse="";
    mail="";
    num=0;
}

patient::patient(QString a,QString b,QString c,QString d,QDate e,QString f,QString g,int i)
{
    this->id=a;
    this->nom=b;
    this->prenom=c;
    this->genre=d;
    this->datee=e;
    this->adresse=f;
    this->mail=g;
    this->num=i;
}

void patient::setid(QString n) { this->id = n; }
void patient::setnom(QString n) { this->nom = n; }
void patient::setprenom(QString n) { this->prenom = n; }
void patient::setgenre(QString n) { this->genre = n; }
void patient::setadresse(QString n) { this->adresse = n; }
void patient::setmail(QString n) { this->mail = n; }
void patient::setdatee(QDate n) { this->datee = n; }
void patient::setnum(int n) { this->num = n; }

QString patient::get_id()  { return id; }
QString patient::get_nom()  { return nom; }
QString patient::get_prenom()  { return prenom; }
QString patient::get_genre()  { return genre; }
QString patient::get_adresse()  { return adresse; }
QString patient::get_mail()  { return mail; }
QDate patient::get_date()  { return datee; }
int patient::get_num()  { return num; }

bool patient::ajouter()
{

    QSqlQuery query;


    QString num_string=QString::number(num);

    query.prepare("INSERT INTO patient (id,nom,prenom,genre,datee,adresse,mail,num ) " "VALUES (:id,:nom,:prenom,:genre,:datee,:adresse,:mail,:num)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":genre", genre);
    query.bindValue(":datee", datee);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mail", mail);
    query.bindValue(":num", num);
    return query.exec();
}


QSqlQueryModel*  patient::afficher()
{

    QSqlQueryModel* model = new QSqlQueryModel();
   model->setQuery("SELECT * FROM patient");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Genre"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de Naissance"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mail"));
   model->setHeaderData(7, Qt::Horizontal, QObject::tr("Numéro"));


    return model;
}


bool patient::supprimer(QString id)
{

    QSqlQuery query;
   query.prepare("DELETE FROM patient WHERE id=:id");
   query.bindValue(":id", id);
   return query.exec();


}


bool patient::modifier(QString id)
{
         QSqlQuery query;
        QString num_string = QString::number(num);
        query.prepare("UPDATE patient SET id=:id, nom=:nom, prenom=:prenom, genre=:genre, datee=:datee, adresse=:adresse, mail=:mail, num=:num WHERE id=:id");
        query.bindValue(":id", id);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":genre", genre);
        query.bindValue(":datee", datee);
        query.bindValue(":adresse", adresse);
        query.bindValue(":mail", mail);

        query.bindValue(":num", num);

        return query.exec();
}
