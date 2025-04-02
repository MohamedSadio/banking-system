#include "uilistvirement.h"
#include "ui_uilistvirement.h"

UiListVirement::UiListVirement(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiListVirement)
{
    ui->setupUi(this);
}
UiListVirement::UiListVirement(QObject* controller) :
    ui(new Ui::UiListVirement)
{
    qDebug("Contruction/Initialisation de la fenêtre UiListVirement ...");
    ui->setupUi(this);

    connect(ui->pushButtonInspecter, SIGNAL(clicked()), controller, SLOT(onInspecter_UIListVirement()));
    connect(ui->pushButtonClose, SIGNAL(clicked()), controller, SLOT(onClose_UIListVirement()));
}

void UiListVirement::setTableViewModel(TransactionModel* transactionModel)
{
    ui->tableViewTransactions->setModel(dynamic_cast<QAbstractItemModel*> (transactionModel));
    ui->tableViewTransactions->setSelectionModel(transactionModel->getSelectionModel());

    ui->tableViewTransactions->show();
}

void UiListVirement::top()
{
    ui->tableViewTransactions->setCurrentIndex(ui->tableViewTransactions->model()->index(0, 0));
}

void UiListVirement::updateTitle(QString suite)
{
    this->setWindowTitle("Virement en cours de : " + suite);
}

void UiListVirement::updateTitle(QString suite, QString transactionTitle)
{
    updateTitle(suite);
    ui->labelTitle->setText(transactionTitle);
}

UiListVirement::~UiListVirement()
{
    delete ui;
}
