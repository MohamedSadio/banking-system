#ifndef UIADMINNOTIF_H
#define UIADMINNOTIF_H

#include <QMainWindow>
#include <uiabstractwindow.h>
#include <adminnotifmodel.h>

namespace Ui {
class UIAdminNotif;
}

class UIAdminNotif : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UIAdminNotif(QWidget *parent = nullptr);
    UIAdminNotif(QObject* controller);
    void updateTitle(QString libelle);
    void setTableViewModel(AdminNotifModel* adminNotifModel);
    void top();
    ~UIAdminNotif();

private:
    Ui::UIAdminNotif *ui;
};

#endif // UIADMINNOTIF_H
