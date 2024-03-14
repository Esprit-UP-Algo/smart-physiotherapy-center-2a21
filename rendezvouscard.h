#ifndef RENDEZVOUSCARD_H
#define RENDEZVOUSCARD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "rendezvous.h"

class RendezvousCard : public QWidget
{
    Q_OBJECT

public:
public:
    explicit RendezvousCard(const Rendezvous &rendezvous, QWidget *parent = nullptr);
signals:
    void rendezvousUpdated(const Rendezvous &rendezvous);
    void rendezvousDeleted(const QString &rendezvousId);

private slots:
    void handleEditButtonClicked();
    void handleDeleteButtonClicked();

private:
    QLabel *titleLabel;
    QLabel *dateTimeLabel;
    QLabel *statusLabel;
    QLabel *clientLabel;
    QLabel *notesLabel;
    QLabel *locationLabel;
    QPushButton *editButton;
    QPushButton *deleteButton;

    Rendezvous rendezvous;
};

#endif // RENDEZVOUSCARD_H
