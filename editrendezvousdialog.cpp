#include "editrendezvousdialog.h"
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

EditRendezvousDialog::EditRendezvousDialog(const Rendezvous &rendezvous, QWidget *parent)
    : QDialog(parent), originalRendezvous(rendezvous)
{
    setupUi();
}

void EditRendezvousDialog::setupUi()
{
    setWindowTitle(tr("Edit Rendezvous"));
    this->setFixedSize(500, 400);
    this->setStyleSheet("font-family: 'Arial'; font-size: 14px; color: #333; background-color: #ffffff;");

    dateTimeEdit = new QDateTimeEdit(originalRendezvous.getDateTime(), this);
    dateTimeEdit->setCalendarPopup(true);
    dateTimeEdit->setMinimumWidth(400);

    statusEdit = new QComboBox(this);
    statusEdit->addItem(tr("Pending"));
    statusEdit->addItem(tr("Approved"));
    statusEdit->addItem(tr("Rejected"));
    statusEdit->setCurrentText(originalRendezvous.getStatus());
    statusEdit->setMinimumWidth(400);

    clientEdit = new QLineEdit(originalRendezvous.getClient(), this);
    notesEdit = new QLineEdit(originalRendezvous.getNotes(), this);
    locationEdit = new QLineEdit(originalRendezvous.getLocation(), this);
    clientEdit->setMinimumWidth(400);
    notesEdit->setMinimumWidth(400);
    locationEdit->setMinimumWidth(400);
    QFormLayout *layout = new QFormLayout;
    layout->setRowWrapPolicy(QFormLayout::DontWrapRows);
    layout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    layout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
    layout->setLabelAlignment(Qt::AlignLeft);
    layout->addRow(tr("Date/Time"), dateTimeEdit);
    layout->addRow(tr("Status"), statusEdit);
    layout->addRow(tr("Client"), clientEdit);
    layout->addRow(tr("Notes"), notesEdit);
    layout->addRow(tr("Location"), locationEdit);

    QPushButton *saveButton = new QPushButton(tr("Save"), this);
    connect(saveButton, &QPushButton::clicked, this, [this]() {
           Rendezvous updatedRendezvous = getUpdatedRendezvous();
           emit rendezvousUpdated(updatedRendezvous);
           accept();
       });
    layout->addRow(saveButton);

    setLayout(layout);

    dateTimeEdit->setStyleSheet("QDateTimeEdit { padding: 6px; border: 1px solid gray; border-radius: 4px; }");
    statusEdit->setStyleSheet("QComboBox { padding: 6px; border: 1px solid gray; border-radius: 4px; }");
    clientEdit->setStyleSheet("QLineEdit { padding: 6px; border: 1px solid gray; border-radius: 4px; }");
    notesEdit->setStyleSheet("QLineEdit { padding: 6px; border: 1px solid gray; border-radius: 4px; }");
    locationEdit->setStyleSheet("QLineEdit { padding: 6px; border: 1px solid gray; border-radius: 4px; }");
    saveButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 6px 12px; border: none; border-radius: 4px; }");
}

Rendezvous EditRendezvousDialog::getUpdatedRendezvous() const
{
    return Rendezvous(

        dateTimeEdit->dateTime(),
        statusEdit->currentText(),
        clientEdit->text(),
        notesEdit->text(),
        locationEdit->text()
    );

}
