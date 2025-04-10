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

void UIAdminNotif::updateTitle(QString libelle)
{
    this->setWindowTitle(libelle);
}

UIAdminNotif::~UIAdminNotif()
{
    delete ui;
}
