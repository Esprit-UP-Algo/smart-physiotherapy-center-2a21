#ifndef rendez_vous_H
#define rendez_vous_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>





class rendez_vous
{

public:
    rendez_vous();
    rendez_vous(int,QString,QString,QString,QString,QString);

    bool ajouter();
    int getID();
    QString getDate_and_time ();
    QString getattendees();
    QString getstatus();
    QString getnote();
    QString getlocationn();



    void setID(int );
    void setDate_and_time(QString );
    void setattendee(QString );
    void setstatus(QString );
    void setnote(QString );
    void setlocation(QString );




    QSqlQueryModel * afficher();
    bool supprimer(int);
private:
     int ID;
    QString DATE_AND_TIME, ATTENDEE,STATUS,NOTE,LOCATION;



};


#endif // RENDEZ_VOUS_H
