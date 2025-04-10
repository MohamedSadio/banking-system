#include "uisettings.h"
#include "ui_uisettings.h"

UISettings::UISettings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UISettings)
{
    ui->setupUi(this);
}

UISettings::UISettings(QObject* controller) :
    ui(new Ui::UISettings)
{
    qDebug("Contruction/Initialisation de la fenêtre UISettings ...");
    ui->setupUi(this);

    connect(ui->pushButtonSave, SIGNAL(clicked()), controller, SLOT(onSave_UISettings()));
    connect(ui->pushButtonQuit, SIGNAL(clicked()), controller, SLOT(onQuit_UISettings()));
}

void UISettings::updateTitle(QString libelle)
{
    this->setWindowTitle(libelle);
}

int UISettings::getTransactionLimit()
{
    return ui->spinBoxTransactionLimit->value();
}

int UISettings::getMinimumAmount()
{
    return ui->spinBoxMinAmount->value();
}

int UISettings::getMaximumAmount()
{
    return ui->spinBoxMaxAmount->value();
}

bool UISettings::getNotifications()
{
    return ui->checkBoxNotifications->isChecked();
}

void UISettings::setTransactionLimit(int limit)
{
    ui->spinBoxTransactionLimit->setValue(limit);
}

void UISettings::setMinimumAmount(int min)
{
    ui->spinBoxMinAmount->setValue(min);
}

void UISettings::setMaximumAmount(int max)
{
    ui->spinBoxMaxAmount->setValue(max);
}

void UISettings::setNotifications(bool enabled)
{
    ui->checkBoxNotifications->setChecked(enabled);
}

void UISettings::populateSettings(int transactionLimit, int minimumAmount, int maximumAmount, bool notifications)
{
    ui->spinBoxTransactionLimit->setValue(transactionLimit);
    ui->spinBoxMinAmount->setValue(minimumAmount);
    ui->spinBoxMaxAmount->setValue(maximumAmount);
    ui->checkBoxNotifications->setTristate(notifications);
}

UISettings::~UISettings()
{
    delete ui;
}
