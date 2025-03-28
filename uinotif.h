#ifndef UINOTIF_H
#define UINOTIF_H

#include <QMainWindow>
#include <uiabstractwindow.h>
#include <notifmodele.h>

namespace Ui {
class UINotif;
}

class UINotif : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UINotif(QWidget *parent = nullptr);
    UINotif(QObject* controller);
    void updateTitle(QString libelle) override;
    void setTableViewModel(NotifModele* notifModel);
    void top();
    ~UINotif();


private:
    Ui::UINotif *ui;
};

#endif // UINOTIF_H
