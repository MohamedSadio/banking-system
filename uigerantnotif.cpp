#include "uigerantnotif.h"
#include "ui_uigerantnotif.h"

UIGerantNotif::UIGerantNotif(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIGerantNotif)
{
    ui->setupUi(this);
}

UIGerantNotif::UIGerantNotif(QObject* controller) :
    ui(new Ui::UIGerantNotif)
{
    qDebug("Contruction/Initialisation de la fenêtre UIGerantNotif ...");
    ui->setupUi(this);

    connect(ui->pushButtonClose, SIGNAL(clicked()), controller, SLOT(onQuit_UIGerantNotif()));
}

void UIGerantNotif::setTableViewModel(GerantNotifModel* gerantNotifModel)
{
    ui->tableViewNotif->setModel(dynamic_cast<QAbstractItemModel*> (gerantNotifModel));
    ui->tableViewNotif->setSelectionModel(gerantNotifModel->getSelectionModel());

    ui->tableViewNotif->show();
}

void UIGerantNotif::top()
{
    ui->tableViewNotif->setCurrentIndex(ui->tableViewNotif->model()->index(0, 0));
}

void UIGerantNotif::updateTitle(QString libelle)
{
    this->setWindowTitle("Centre de notifications - Gérant : " + libelle);
}

UIGerantNotif::~UIGerantNotif()
{
    delete ui;
}
