#ifndef UILISTVIREMENT_H
#define UILISTVIREMENT_H

#include <QMainWindow>
#include <uiabstractwindow.h>
#include <transactionmodel.h>

namespace Ui {
class UiListVirement;
}

class UiListVirement : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UiListVirement(QWidget *parent = nullptr);
    UiListVirement(QObject* controller);

    void setTableViewModel(TransactionModel* transactionModel);
    void updateTitle(QString suite);
    void updateTitle(QString suite, QString TransactionTitle);
    void top();

    ~UiListVirement();

private:
    Ui::UiListVirement *ui;
};

#endif // UILISTVIREMENT_H
