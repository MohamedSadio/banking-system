#include "uimessagegestionnaire.h"
#include "ui_uimessagegestionnaire.h"
#include <QMessageBox>
#include <QSqlError>

UIMessageGestionnaire::UIMessageGestionnaire(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIMessageGestionnaire)
{
    ui->setupUi(this);
}

UIMessageGestionnaire::UIMessageGestionnaire(QObject* controller) :
    ui(new Ui::UIMessageGestionnaire)
{
    qDebug("Construction/Initialisation de la fenêtre UIMessageGestionnaire ...");
    ui->setupUi(this);

    // Connecter les signaux aux slots du contrôleur
    connect(ui->pushButtonSend, SIGNAL(clicked()), controller, SLOT(onSend_UIMessageGestionnaire()));
    connect(ui->pushButtonQuit, SIGNAL(clicked()), controller, SLOT(onQuit_UIMessageGestionnaire()));

    // Connecter le changement d'onglet
    connect(ui->tabWidgetMessages, SIGNAL(currentChanged(int)), controller, SLOT(onTabChanged_UIMessageGestionnaire(int)));

    // Connecter le double-clic sur les messages pour les ouvrir
    connect(ui->tableViewReceived, SIGNAL(doubleClicked(QModelIndex)), controller, SLOT(onOpenMessage_UIMessageGestionnaire(QModelIndex)));
    connect(ui->tableViewSent, SIGNAL(doubleClicked(QModelIndex)), controller, SLOT(onOpenMessage_UIMessageGestionnaire(QModelIndex)));
}

void UIMessageGestionnaire::updateTitle(QString libelle)
{
    this->setWindowTitle(libelle);
}

QString UIMessageGestionnaire::getMessageContent()
{
    return ui->textEditMessageContent->toPlainText();
}

QString UIMessageGestionnaire::getSelectedReceiverId()
{
    return ui->comboBoxReceiver->currentText();
}

QString UIMessageGestionnaire::getSelectedReceiverName()
{
    return ui->comboBoxReceiver->currentText();
}

QString UIMessageGestionnaire::getMessageSubject()
{
    return ui->lineEditSubject->text();
}

void UIMessageGestionnaire::setComboxReceiver(QStringList liste)
{
    ui->comboBoxReceiver->addItems(liste);
}

void UIMessageGestionnaire::addReceiver(int userId, QString username, QString role)
{
    // Ajouter l'utilisateur avec son rôle dans la liste déroulante
    QString displayText = username + " (" + role + ")";
    ui->comboBoxReceiver->addItem(displayText, userId);
}

void UIMessageGestionnaire::clearRecipients()
{
    ui->comboBoxReceiver->clear();
}

QTableView* UIMessageGestionnaire::getReceivedMessagesView()
{
    return ui->tableViewReceived;
}

QTableView* UIMessageGestionnaire::getSentMessagesView()
{
    return ui->tableViewSent;
}

int UIMessageGestionnaire::getSelectedMessageId()
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

void UIMessageGestionnaire::clearMessageForm()
{
    ui->lineEditSubject->clear();
    ui->textEditMessageContent->clear();
}

void UIMessageGestionnaire::viewMessageDetails(QString sender, QString subject,
                                 QString content, QString date)
{
    ui->labelSenderValue->setText(sender);
    ui->labelDateValue->setText(date);
    ui->labelSubjectValue->setText(subject);
    ui->textBrowserContent->setText(content);

    ui->tabWidgetMessages->setCurrentIndex(3);
}


UIMessageGestionnaire::~UIMessageGestionnaire()
{
    delete ui;
}
