#include "uinotif.h"
#include "ui_uinotif.h"

UINotif::UINotif(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UINotif)
{
    ui->setupUi(this);
}

UINotif::UINotif(QObject* controller) :
    ui(new Ui::UINotif){
    qDebug("Contruction/Initialisation de la fenêtre UINotift ...");
    ui->setupUi(this);
    connect(ui->closeButton, SIGNAL(clicked()), controller, SLOT(onClose_UINotif()));

}

void UINotif::setTableViewModel(NotifModele* notifModel){
    ui->tableViewNotif->setModel(dynamic_cast<QAbstractItemModel*> (notifModel));
    ui->tableViewNotif->setSelectionModel(notifModel->getSelectionModel());

    ui->tableViewNotif->show();
}

void UINotif::updateTitle(QString libelle)
{
    this->setWindowTitle("Gestion des comptes client - Gestionnaire : " + libelle);
}

void UINotif::top(){
    QAbstractItemModel *model = ui->tableViewNotif->model();
    if (model && model->rowCount() > 0) {
            int lastRow = model->rowCount() - 1;
            ui->tableViewNotif->setCurrentIndex(model->index(lastRow, 0));
        }
}

UINotif::~UINotif()
{
    delete ui;
}
