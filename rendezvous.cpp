#include "rendezvous.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

Rendezvous::Rendezvous()
    : dateTime(QDateTime::currentDateTime()), status("Pending"), client(""), notes(""), location("") {}

Rendezvous::Rendezvous( const QDateTime& dateTime, const QString& status, const QString& client, const QString& notes, const QString& location)
    : dateTime(dateTime), status(status), client(client), notes(notes), location(location) {}

Rendezvous::Rendezvous(const QString& rendezvousId, const QDateTime& dateTime, const QString& status, const QString& client, const QString& notes, const QString& location)
    : rendezvousId(rendezvousId), dateTime(dateTime), status(status), client(client), notes(notes), location(location)
{
}



QDateTime Rendezvous::getDateTime() const {
    return dateTime;
}

QString Rendezvous::getRendezvousId() const {
    return rendezvousId;
}

void Rendezvous::setRendezvousId(QString id) {
    rendezvousId = id;
}


QString Rendezvous::getStatus() const {
    return status;
}

QString Rendezvous::getClient() const {
    return client;
}

QString Rendezvous::getNotes() const {
    return notes;
}

QString Rendezvous::getLocation() const {
    return location;
}


void Rendezvous::setDateTime(const QDateTime& dateTime) {
    this->dateTime = dateTime;
}

void Rendezvous::setStatus(const QString& status) {
    this->status = status;
}

void Rendezvous::setClient(const QString& client) {
    this->client = client;
}

void Rendezvous::setNotes(const QString& notes) {
    this->notes = notes;
}

void Rendezvous::setLocation(const QString& location) {
    this->location = location;
}


bool Rendezvous::addRendezvousToDatabase() {
    QSqlQuery query;
    query.prepare("INSERT INTO Rendezvous (DateTime, Status, Client, Notes, Location) "
                  "VALUES (:DateTime, :Status, :Client, :Notes, :Location)");
    query.bindValue(":DateTime", this->dateTime);
    query.bindValue(":Status", this->status);
    query.bindValue(":Client", this->client);
    query.bindValue(":Notes", this->notes);
    query.bindValue(":Location", this->location);

    if (!query.exec()) {
        qDebug() << "addRendezvousToDatabase error:" << query.lastError().text();
        return false;
    }
    return true;
}

QVector<Rendezvous> Rendezvous::getAllRendezvousFromDatabase() {
    QVector<Rendezvous> rendezvousList;
    QSqlQuery query("SELECT * FROM Rendezvous");

    while (query.next()) {
        QString rendezvousId = query.value("RendezvousId").toString();
        QDateTime dateTime = query.value("DateTime").toDateTime();
        QString status = query.value("Status").toString();
        QString client = query.value("Client").toString();
        QString notes = query.value("Notes").toString();
        QString location = query.value("Location").toString();

        Rendezvous rendezvous(rendezvousId, dateTime, status, client, notes, location);
        rendezvousList.append(rendezvous);
    }

    return rendezvousList;
}

bool Rendezvous::updateRendezvousInDatabase() const {

    if (rendezvousId <= 0) {
        qDebug() << "updateRendezvousInDatabase error: Invalid ID, rendezvousId=" << rendezvousId;
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE Rendezvous SET DateTime = :DateTime, Status = :Status, Client = :Client, "
                  "Notes = :Notes, Location = :Location WHERE Rendezvousid = :RendezvousId");

    query.bindValue(":DateTime", this->dateTime);
    query.bindValue(":Status", this->status);
    query.bindValue(":Client", this->client);
    query.bindValue(":Notes", this->notes);
    query.bindValue(":Location", this->location);
    query.bindValue(":RendezvousId",(this->rendezvousId));

    qDebug() << "Executing query:" << query.lastQuery();
    qDebug() << "With values: DateTime =" << this->dateTime
             << ", Status =" << this->status
             << ", Client =" << this->client
             << ", Notes =" << this->notes
             << ", Location =" << this->location
             << ", RendezvousId =" << this->rendezvousId;

    if (!query.exec()) {
        qDebug() << "updateRendezvousInDatabase error:" << query.lastError().text();
        return false;
    }

    if(query.numRowsAffected() <= 0) {
        qDebug() << "No rows updated. Possible reasons: No record with the provided ID exists.";
        return false;
    }
    qDebug() << "RendezvousId to bind:" <<(this->rendezvousId);


    qDebug() << "Rendezvous record updated successfully.";
    return true;
}

bool Rendezvous::deleteRendezvousFromDatabase() const {
    if (rendezvousId.isEmpty()) {
        qDebug() << "deleteRendezvousFromDatabase error: Invalid ID, rendezvousId is empty";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM Rendezvous WHERE RendezvousId = :RendezvousId");
    query.bindValue(":RendezvousId", rendezvousId);

    if (!query.exec()) {
        qDebug() << "deleteRendezvousFromDatabase error:" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() <= 0) {
        qDebug() << "No rows deleted. Possible reasons: No record with the provided ID exists.";
        return false;
    }

    qDebug() << "Rendezvous record deleted successfully.";
    return true;
}
