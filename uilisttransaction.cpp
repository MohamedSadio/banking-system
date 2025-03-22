#include "uilisttransaction.h"
#include "ui_uilisttransaction.h"

UIListTransaction::UIListTransaction(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIListTransaction)
{
    ui->setupUi(this);
}

UIListTransaction::UIListTransaction(QObject* controller) :
    ui(new Ui::UIListTransaction)
{
    qDebug("Contruction/Initialisation de la fenêtre UIListTransaction ...");
    ui->setupUi(this);
    
	connect(ui->pushButtonClose, SIGNAL(clicked()), controller, SLOT(onClose_UIListTransaction()));
}

void UIListTransaction::setTableViewModel(TransactionModel* transactionModel)
{
    ui->tableViewTransactions->setModel(dynamic_cast<QAbstractItemModel*> (transactionModel));
    ui->tableViewTransactions->setSelectionModel(transactionModel->getSelectionModel());

    ui->tableViewTransactions->show();
}

void UIListTransaction::top()
{
    ui->tableViewTransactions->setCurrentIndex(ui->tableViewTransactions->model()->index(0, 0));
}

void UIListTransaction::updateTitle(QString suite)
{
    this->setWindowTitle("Historique des transactions de : " + suite);
}

void UIListTransaction::updateTitle(QString suite, QString transactionTitle)
{
    updateTitle(suite);
    ui->labelTitle->setText(transactionTitle);
}

UIListTransaction::~UIListTransaction()
{
    delete ui;
}
