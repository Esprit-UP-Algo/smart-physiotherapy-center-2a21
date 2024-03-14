#include "rendezvouscard.h"
#include "editrendezvousdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>
#include <QHBoxLayout>

#include <QGraphicsDropShadowEffect>

RendezvousCard::RendezvousCard(const Rendezvous &rendezvous, QWidget *parent) : QWidget(parent), rendezvous(rendezvous) {
    auto *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    setObjectName("card");

    setStyleSheet("#card { background-color: #ffffff; border-radius: 20px; }");
    auto *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(15);
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(4);
    shadowEffect->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(shadowEffect);

    auto *topBar = new QWidget(this);
    auto *topBarLayout = new QHBoxLayout(topBar);
    topBar->setObjectName("topBar");
    topBar->setStyleSheet("#topBar { background-color: #6876e1; color: white; border-top-left-radius: 20px; border-top-right-radius: 20px; padding: 10px 20px; }");

    titleLabel = new QLabel(rendezvous.getClient(), topBar);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 18px; color: white;");

    statusLabel = new QLabel(rendezvous.getStatus(), topBar);
    statusLabel->setStyleSheet("font-size: 18px; color: white; margin-left: 10px;");

    topBarLayout->addWidget(titleLabel);
    topBarLayout->addStretch();
    topBarLayout->addWidget(statusLabel);

    auto *contentArea = new QWidget(this);
    auto *contentLayout = new QVBoxLayout(contentArea);
    contentArea->setObjectName("contentArea");
    contentArea->setStyleSheet("#contentArea { padding: 20px; background-color: #ffffff; border-bottom-left-radius: 20px; border-bottom-right-radius: 20px; }");

    dateTimeLabel = new QLabel(rendezvous.getDateTime().toString("dd/MM/yyyy hh:mm ap"), contentArea);
    dateTimeLabel->setStyleSheet("font-size: 14px; color: #333;");

    notesLabel = new QLabel(rendezvous.getNotes(), contentArea);
    notesLabel->setWordWrap(true);
    notesLabel->setStyleSheet("font-size: 14px; color: #555; margin-top: 15px;");

    locationLabel = new QLabel(rendezvous.getLocation(), contentArea);
    locationLabel->setWordWrap(true);
    locationLabel->setStyleSheet("font-size: 14px; color: #555; margin-top: 15px;");

    contentLayout->addWidget(dateTimeLabel);
    contentLayout->addWidget(notesLabel);
    contentLayout->addWidget(locationLabel);

    auto *buttonLayout = new QHBoxLayout();

    editButton = new QPushButton("Edit", this);
    editButton->setObjectName("editButton");
    editButton->setStyleSheet("#editButton { background-color: #6876e1; color: white; border-radius: 10px; padding: 8px 16px; margin-top: 15px; font-size: 16px; } #editButton:hover { background-color: #0069D9; }");
    buttonLayout->addWidget(editButton);

    deleteButton = new QPushButton("Delete", this);
    deleteButton->setObjectName("deleteButton");
    deleteButton->setStyleSheet("#deleteButton { background-color: #e15f76; color: white; border-radius: 10px; padding: 8px 16px; margin-top: 15px; font-size: 16px; } #deleteButton:hover { background-color: #d9534f; }");
    buttonLayout->addWidget(deleteButton);

    mainLayout->addWidget(topBar);
    mainLayout->addWidget(contentArea);
    mainLayout->addLayout(buttonLayout);

    connect(editButton, &QPushButton::clicked, this, &RendezvousCard::handleEditButtonClicked);
    connect(deleteButton, &QPushButton::clicked, this, &RendezvousCard::handleDeleteButtonClicked);
}

void RendezvousCard::handleEditButtonClicked() {
    EditRendezvousDialog dialog(this->rendezvous, this);
    if (dialog.exec() == QDialog::Accepted) {
        Rendezvous updatedRendezvous = dialog.getUpdatedRendezvous();
        updatedRendezvous.setRendezvousId(this->rendezvous.getRendezvousId());
        this->rendezvous = updatedRendezvous;
        emit rendezvousUpdated(updatedRendezvous);
    }
}

void RendezvousCard::handleDeleteButtonClicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Rendezvous", "Are you sure you want to delete this rendezvous?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        emit rendezvousDeleted(rendezvous.getRendezvousId());
    }
}
