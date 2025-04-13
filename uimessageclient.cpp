#include "uimessageclient.h"
#include "ui_uimessageclient.h"
#include <QMessageBox>
#include <QSqlError>

UIMessageClient::UIMessageClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIMessageClient)
{
    ui->setupUi(this);
}

UIMessageClient::UIMessageClient(QObject* controller) :
    ui(new Ui::UIMessageClient)
{
    qDebug("Construction/Initialisation de la fenêtre UIMessage ...");
    ui->setupUi(this);

    // Connecter les signaux aux slots du contrôleur
    connect(ui->pushButtonSend, SIGNAL(clicked()), controller, SLOT(onSend_UIMessage()));
    connect(ui->pushButtonRefresh, SIGNAL(clicked()), controller, SLOT(onRefresh_UIMessage()));
    connect(ui->pushButtonDelete, SIGNAL(clicked()), controller, SLOT(onDelete_UIMessage()));
    connect(ui->pushButtonQuit, SIGNAL(clicked()), controller, SLOT(onQuit_UIMessage()));

    // Connecter le changement d'onglet
    connect(ui->tabWidgetMessages, SIGNAL(currentChanged(int)), controller, SLOT(onTabChanged_UIMessage(int)));

    // Connecter le double-clic sur les messages pour les ouvrir
    connect(ui->tableViewReceived, SIGNAL(doubleClicked(QModelIndex)), controller, SLOT(onOpenMessage_UIMessage(QModelIndex)));
    connect(ui->tableViewSent, SIGNAL(doubleClicked(QModelIndex)), controller, SLOT(onOpenMessage_UIMessage(QModelIndex)));
}

void UIMessageClient::updateTitle(QString libelle)
{
    this->setWindowTitle(libelle);
}

QString UIMessageClient::getMessageContent()
{
    return ui->textEditMessageContent->toPlainText();
}

QString UIMessageClient::getSelectedReceiverId()
{
    return ui->comboBoxReceiver->currentText();
}

QString UIMessageClient::getSelectedReceiverName()
{
    return ui->comboBoxReceiver->currentText();
}

QString UIMessageClient::getMessageSubject()
{
    return ui->lineEditSubject->text();
}

void UIMessageClient::setComboxReceiver(QStringList liste)
{
    ui->comboBoxReceiver->addItems(liste);
}

void UIMessageClient::setComboReceiverClient(QString email){
    ui->comboBoxReceiver->setCurrentText(email);
}

void UIMessageClient::addReceiver(int userId, QString username, QString role)
{
    // Ajouter l'utilisateur avec son rôle dans la liste déroulante
    QString displayText = username + " (" + role + ")";
    ui->comboBoxReceiver->addItem(displayText, userId);
}

void UIMessageClient::clearRecipients()
{
    ui->comboBoxReceiver->clear();
}

QTableView* UIMessageClient::getReceivedMessagesView()
{
    return ui->tableViewReceived;
}

QTableView* UIMessageClient::getSentMessagesView()
{
    return ui->tableViewSent;
}

int UIMessageClient::getSelectedMessageId()
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

void UIMessageClient::clearMessageForm()
{
    ui->lineEditSubject->clear();
    ui->textEditMessageContent->clear();
}

void UIMessageClient::viewMessageDetails(QString sender, QString subject,
                                 QString content, QString date)
{
    ui->labelSenderValue->setText(sender);
    ui->labelDateValue->setText(date);
    ui->labelSubjectValue->setText(subject);
    ui->textBrowserContent->setText(content);

    ui->tabWidgetMessages->setCurrentIndex(3);
}

void UIMessageClient::loadUsers()
{
    // Vider le comboBox et la map
    ui->comboBoxReceiver->clear();
    m_userMap.clear();

    // Connexion à la base de données (supposée déjà établie)
    dbManager->open();
    QSqlQuery query(dbManager->database());
    query.prepare("SELECT id, nom, FROM t_users");

    if (query.exec()) {
        // Parcourir les résultats et remplir le comboBox
        while (query.next()) {
            int id = query.value("id").toInt();
            QString nom = query.value("nom").toString();
            QString prenom = query.value("login").toString();

            QString displayName = nom.toUpper();

            m_userMap[id] = displayName;

            ui->comboBoxReceiver->addItem(displayName, id);
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de charger la liste des utilisateurs: "
                              + query.lastError().text());
    }
}

UIMessageClient::~UIMessageClient()
{
    delete ui;
}
