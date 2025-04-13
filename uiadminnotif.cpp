#include "uiadminnotif.h"
#include "ui_uiadminnotif.h"

UIAdminNotif::UIAdminNotif(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIAdminNotif)
{
    ui->setupUi(this);
}

UIAdminNotif::UIAdminNotif(QObject* controller) :
    ui(new Ui::UIAdminNotif)
{
    qDebug("Contruction/Initialisation de la fenêtre UINotift ...");
    ui->setupUi(this);

    connect(ui->pushButtonExit, SIGNAL(clicked()), controller, SLOT(onQuit_UIAdminNotif()));

}

void UIAdminNotif::setTableViewModel(AdminNotifModel *adminNotifModel)
{
    ui->tableViewNotif->setModel(dynamic_cast<QAbstractItemModel*> (adminNotifModel));
    ui->tableViewNotif->setSelectionModel(adminNotifModel->getSelectionModel());

    ui->tableViewNotif->show();
}

void UIAdminNotif::top()
{
    ui->tableViewNotif->setCurrentIndex(ui->tableViewNotif->model()->index(0, 0));
}

void UIAdminNotif::updateTitle(QString libelle)
{
    this->setWindowTitle("Centre de notifications - Administrateur : " + libelle);
}

UIAdminNotif::~UIAdminNotif()
{
    delete ui;
}
