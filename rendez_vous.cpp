#include "rendez_vous.h"




rendez_vous::rendez_vous()
{
    ID=0;
    DATE_AND_TIME="";
    ATTENDEE="";
    STATUS="";
    NOTE="";
    LOCATION
            ="";
}

rendez_vous::rendez_vous(int id,QString date_and_time,QString attendee,QString status,QString note,QString location)
{
    this->ID=id;
    this->DATE_AND_TIME=date_and_time;
    this->ATTENDEE=attendee;
    this->STATUS=status;
    this->NOTE=note;
    this->LOCATION=location;
}
  int rendez_vous::getID()
  {
      return ID;
  }
  void rendez_vous::setID(int id)
  {this->ID=id;}
  QString rendez_vous::getDate_and_time()
  {
      return DATE_AND_TIME;
  }
  void rendez_vous::setDate_and_time(QString Date_and_time)
  {this->DATE_AND_TIME=Date_and_time;}

 QString rendez_vous::getattendees()
  {
      return ATTENDEE;
  }
  void rendez_vous::setattendee(QString attendees)
  {this->ATTENDEE=attendees;}

  QString rendez_vous::getstatus()
   {
       return STATUS;
   }
   void rendez_vous::setstatus(QString status)
   {this->STATUS=status;}
   QString rendez_vous::getnote()
    {
        return NOTE;
    }
    void rendez_vous::setnote(QString note)
    {this->NOTE=note;}
    QString rendez_vous::getlocationn()
     {
         return LOCATION;
     }
     void rendez_vous::setlocation(QString location)
     {this->LOCATION=location;}









bool rendez_vous::ajouter()
{
   QSqlQuery query;
   QString res = QString::number(ID);
   query.prepare("INSERT INTO RENDEZ_VOUS(ID, DATE_AND_TIME, ATTENDEE, STATUS, NOTE, LOCATION)" "VALUES(:id,:date and time,:attendee,:status,:note,:location)");
   query.bindValue(":id",ID);
   query.bindValue(":date_and_time",DATE_AND_TIME);
   query.bindValue(":attendee",ATTENDEE);
   query.bindValue(":status",STATUS);
   query.bindValue(":note",NOTE);
   query.bindValue(":location",LOCATION);
   bool inserted =query.exec();


}
QSqlQueryModel* rendez_vous ::afficher()
 {

   QSqlQueryModel* model=new QSqlQueryModel();


      model->setQuery("SELECT * FROM rendez_vous");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_and_time"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("attendee"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("status"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("note"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("location"));
   return model;

 }

bool rendez_vous::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("delete from rendez vous where ID=id");
    query.bindValue(":id",res);
    return query.exec();
