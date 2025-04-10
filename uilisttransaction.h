#ifndef UILISTTRANSACTION_H
#define UILISTTRANSACTION_H

#include <QMainWindow>
#include <uiabstractwindow.h>
#include <transactionmodel.h>
#include <QSortFilterProxyModel>

namespace Ui {
class UIListTransaction;
}

class UIListTransaction : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UIListTransaction(QWidget *parent = nullptr);
    UIListTransaction(QObject* controller);
    void setTableViewModel(TransactionModel* transactionModel);
    void updateTitle(QString suite);
    void updateTitle(QString suite, QString TransactionTitle);
    void hideButton();
    void showButton();
    void showEvent(QShowEvent *event);
    void top();
    ~UIListTransaction();

private slots:
    // Nouveau slot pour gérer le clic sur l'en-tête
    void onHeaderClicked(int logicalIndex);

private:
    Ui::UIListTransaction *ui;
    QSortFilterProxyModel *proxyModel;
    TransactionModel *sourceModel;
    QObject *m_controller;
    int currentFilterColumn;
};

#endif // UILISTTRANSACTION_H
