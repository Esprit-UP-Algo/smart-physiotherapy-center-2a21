#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include <QString>
#include <QDateTime>

class Rendezvous
{
public:

    Rendezvous();
    Rendezvous(const QDateTime& dateTime, const QString& status, const QString& client,
               const QString& notes, const QString& location);
    // Add this constructor
    Rendezvous(const QString& rendezvousId, const QDateTime& dateTime, const QString& status, const QString& client, const QString& notes, const QString& location);
    bool addRendezvousToDatabase();
    static QVector<Rendezvous> getAllRendezvousFromDatabase();
    bool updateRendezvousInDatabase() const;
    bool deleteRendezvousFromDatabase() const;

    // Getters
    QDateTime getDateTime() const;
    QString getStatus() const;
    QString getClient() const;
    QString getNotes() const;
    QString getLocation() const;

    // Setters
    void setDateTime(const QDateTime& dateTime);
    void setStatus(const QString& status);
    void setClient(const QString& client);
    void setNotes(const QString& notes);
    void setLocation(const QString& location);

    QString getRendezvousId() const;
    void setRendezvousId(QString id);

private:
    QDateTime dateTime;
    QString status;
    QString client;
    QString notes;
    QString location;
    QString rendezvousId;

};

#endif // RENDEZVOUS_H
