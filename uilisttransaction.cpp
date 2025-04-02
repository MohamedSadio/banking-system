#include "uilisttransaction.h"
#include "ui_uilisttransaction.h"
#include <QInputDialog>
#include <QLineEdit>

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
    
    connect(ui->pushButtonOnGoing, SIGNAL(clicked()), controller, SLOT(onGoing_UIListTransaction()));
	connect(ui->pushButtonClose, SIGNAL(clicked()), controller, SLOT(onClose_UIListTransaction()));
}

void UIListTransaction::setTableViewModel(TransactionModel* transactionModel)
{
    sourceModel = transactionModel;

    // Création d'un modèle proxy standard
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(sourceModel);

    // Configuration pour rendre le filtre insensible à la casse
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // Configure la table pour utiliser le modèle proxy
    ui->tableViewTransactions->setModel(proxyModel);
    ui->tableViewTransactions->setSortingEnabled(true);

    // Connexion au clic sur l'en-tête
    connect(ui->tableViewTransactions->horizontalHeader(),
            SIGNAL(sectionClicked(int)),
            this,
            SLOT(onHeaderClicked(int)));

    ui->tableViewTransactions->show();
}

void UIListTransaction::onHeaderClicked(int logicalIndex)
{
    if(logicalIndex==2 || logicalIndex==5 || logicalIndex==6){
        switch (logicalIndex) {
        case 2: {
            Qt::SortOrder currentOrder = ui->tableViewTransactions->horizontalHeader()->sortIndicatorOrder();
            Qt::SortOrder newOrder = (currentOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
            ui->tableViewTransactions->sortByColumn(2, newOrder);
            break;
        }
        case 5: // Tri par montant (descendant)
            ui->tableViewTransactions->sortByColumn(5, Qt::DescendingOrder);
            break;
        case 6: // Tri par date (le plus récent d'abord)
            ui->tableViewTransactions->sortByColumn(6, Qt::DescendingOrder);
            break;
        default:
            // Pour les autres colonnes, tri ascendant par défaut
            ui->tableViewTransactions->setModel(nullptr);
            ui->tableViewTransactions->setModel(sourceModel);
            break;
        }
    }
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
