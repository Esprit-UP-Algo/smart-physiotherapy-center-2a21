#ifndef EDITRENDEZVOUSDIALOG_H
#define EDITRENDEZVOUSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QPushButton>
#include "rendezvous.h"

class EditRendezvousDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditRendezvousDialog(const Rendezvous &rendezvous, QWidget *parent = nullptr);

    Rendezvous getUpdatedRendezvous() const;

private:
    QDateTimeEdit *dateTimeEdit;
    QComboBox *statusEdit;
    QLineEdit *clientEdit;
    QLineEdit *notesEdit;
    QLineEdit *locationEdit;
    QPushButton *saveButton;

    Rendezvous originalRendezvous;

    void setupUi();

signals:
    void rendezvousUpdated(const Rendezvous &rendezvous);

};

#endif // EDITRENDEZVOUSDIALOG_H
