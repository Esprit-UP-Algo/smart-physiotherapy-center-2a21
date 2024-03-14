#include "addrendezvousdialog.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QMessageBox>

AddRendezvousDialog::AddRendezvousDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi();
}

void AddRendezvousDialog::setupUi() {
    this->setWindowTitle(tr("Add Rendezvous"));
    this->setFixedSize(500, 400);
    this->setStyleSheet("font-family: 'Arial'; font-size: 14px; color: #333;");

    dateTimeEdit = new QDateTimeEdit(this);
    dateTimeEdit->setCalendarPopup(true);
    dateTimeEdit->setMinimumWidth(400);

    statusEdit = new QComboBox(this);
    statusEdit->addItem(tr("Pending"));
    statusEdit->addItem(tr("Approved"));
    statusEdit->addItem(tr("Rejected"));
    statusEdit->setMinimumWidth(400);

    clientEdit = new QLineEdit(this);
    clientEdit->setMinimumWidth(400);

    notesEdit = new QLineEdit(this);
    notesEdit->setMinimumWidth(400);
    locationEdit = new QLineEdit(this);
    locationEdit->setText(tr("أريانة الصغرى W52Q+RF6, Cebalat Ben Ammar"));
    locationEdit->setReadOnly(true);
    locationEdit->setMinimumWidth(400);

    addButton = new QPushButton(tr("Add"), this);
    addButton->setStyleSheet("QPushButton { background-color: #5cb85c; color: white; border-radius: 5px; padding: 10px; }"
                             "QPushButton:hover { background-color: #4cae4c; }");

    QFormLayout *layout = new QFormLayout;
    layout->setRowWrapPolicy(QFormLayout::DontWrapRows);
    layout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    layout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
    layout->setLabelAlignment(Qt::AlignLeft);
    layout->setVerticalSpacing(25);
    layout->addRow(tr("Date/Time"), dateTimeEdit);
    layout->addRow(tr("Status"), statusEdit);
    layout->addRow(tr("Client"), clientEdit);
    layout->addRow(tr("Notes"), notesEdit);
    layout->addRow(tr("Location"), locationEdit);
    layout->addWidget(addButton);

    setLayout(layout);

    connect(addButton, &QPushButton::clicked, this, &AddRendezvousDialog::onAddButtonClicked);
}




void AddRendezvousDialog::onAddButtonClicked()
{
    QDateTime dateTime = dateTimeEdit->dateTime();
    QString status = statusEdit->currentText();
    QString client = clientEdit->text().trimmed();
    QString notes = notesEdit->text().trimmed();
    QString location = locationEdit->text().trimmed();

    if (!client.contains(" ") || client.isEmpty()) {
        QMessageBox::warning(this, tr("Input Validation"), tr("Please enter both first and last name for the client."));
        return;
    }

    if (notes.length() <= 10) {
        QMessageBox::warning(this, tr("Input Validation"), tr("Notes must be more than 10 characters long."));
        return;
    }

    if (client.isEmpty()) {
            QMessageBox::warning(this, tr("Input Validation"), tr("Client name cannot be empty."));
            return;
        }

        if (notes.isEmpty()) {
            QMessageBox::warning(this, tr("Input Validation"), tr("Notes cannot be empty."));
            return;
        }

    emit rendezvousAdded(dateTime, status, client, notes, location);

    accept();
}


