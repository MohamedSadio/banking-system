#include "uimessage.h"
#include "ui_uimessage.h"
#include <QMessageBox>
#include <QSqlError>


UIMessage::UIMessage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIMessage)
{
    ui->setupUi(this);
}

UIMessage::UIMessage(QObject* controller) :
    ui(new Ui::UIMessage)
{
    qDebug("Construction/Initialisation de la fenêtre UIMessage ...");
    ui->setupUi(this);

    // Connecter les signaux aux slots du contrôleur
    connect(ui->pushButtonSend, SIGNAL(clicked()), controller, SLOT(onSend_UIMessage()));
    connect(ui->pushButtonQuit, SIGNAL(clicked()), controller, SLOT(onQuit_UIMessage()));

    // Connecter le changement d'onglet
    connect(ui->tabWidgetMessages, SIGNAL(currentChanged(int)), controller, SLOT(onTabChanged_UIMessage(int)));

    // Connecter le double-clic sur les messages pour les ouvrir
    connect(ui->tableViewReceived, SIGNAL(doubleClicked(QModelIndex)), controller, SLOT(onOpenMessage_UIMessage(QModelIndex)));
    connect(ui->tableViewSent, SIGNAL(doubleClicked(QModelIndex)), controller, SLOT(onOpenMessage_UIMessage(QModelIndex)));
}

void UIMessage::updateTitle(QString libelle)
{
    this->setWindowTitle(libelle);
}

QString UIMessage::getMessageContent()
{
    return ui->textEditMessageContent->toPlainText();
}

QString UIMessage::getSelectedReceiverId()
{
    return ui->comboBoxReceiver->currentText();
}

QString UIMessage::getSelectedReceiverName()
{
    return ui->comboBoxReceiver->currentText();
}

QString UIMessage::getMessageSubject()
{
    return ui->lineEditSubject->text();
}

void UIMessage::setComboxReceiver(QStringList liste)
{
    ui->comboBoxReceiver->addItems(liste);
}

void UIMessage::addReceiver(int userId, QString username, QString role)
{
    // Ajouter l'utilisateur avec son rôle dans la liste déroulante
    QString displayText = username + " (" + role + ")";
    ui->comboBoxReceiver->addItem(displayText, userId);
}

void UIMessage::clearRecipients()
{
    ui->comboBoxReceiver->clear();
}

QTableView* UIMessage::getReceivedMessagesView()
{
    return ui->tableViewReceived;
}

QTableView* UIMessage::getSentMessagesView()
{
    return ui->tableViewSent;
}

int UIMessage::getSelectedMessageId()
{
    int activeTab = ui->tabWidgetMessages->currentIndex();

    if (activeTab == 1) {
        QModelIndex currentIndex = ui->tableViewReceived->currentIndex();
        if (currentIndex.isValid()) {
            return ui->tableViewReceived->model()->data(
                ui->tableViewReceived->model()->index(currentIndex.row(), 0)
            ).toInt();
        }
    }
    else if (activeTab == 2) {
        QModelIndex currentIndex = ui->tableViewSent->currentIndex();
        if (currentIndex.isValid()) {
            return ui->tableViewSent->model()->data(
                ui->tableViewSent->model()->index(currentIndex.row(), 0)
            ).toInt();
        }
    }

    return -1;
}

void UIMessage::clearMessageForm()
{
    ui->lineEditSubject->clear();
    ui->textEditMessageContent->clear();
}

void UIMessage::viewMessageDetails(QString sender, QString subject,
                                 QString content, QString date)
{
    ui->labelSenderValue->setText(sender);
    ui->labelDateValue->setText(date);
    ui->labelSubjectValue->setText(subject);
    ui->textBrowserContent->setText(content);

    ui->tabWidgetMessages->setCurrentIndex(3);
}

UIMessage::~UIMessage()
{
    delete ui;
}
