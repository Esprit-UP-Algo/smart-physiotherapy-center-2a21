#ifndef ADDRENDEZVOUSDIALOG_H
#define ADDRENDEZVOUSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>

class AddRendezvousDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRendezvousDialog(QWidget *parent = nullptr);
    QDateTime getDateTime() const;
    QString getStatus() const;
    QString getClient() const;
    QString getNotes() const;
    QString getLocation() const;

private slots:
    void onAddButtonClicked();

private:
    QDateTimeEdit *dateTimeEdit;
    QComboBox *statusEdit;
    QLineEdit *clientEdit;
    QLineEdit *notesEdit;
    QLineEdit *locationEdit;
    QPushButton *addButton;

    void setupUi();

signals:
    void rendezvousAdded(const QDateTime& dateTime, const QString& status, const QString& client, const QString& notes, const QString& location);

};

#endif // ADDRENDEZVOUSDIALOG_H
