#ifndef UIGERANTNOTIF_H
#define UIGERANTNOTIF_H

#include <QMainWindow>
#include <uiabstractwindow.h>
#include <gerantnotifmodel.h>

namespace Ui {
class UIGerantNotif;
}

class UIGerantNotif : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UIGerantNotif(QWidget *parent = nullptr);
    UIGerantNotif(QObject* controller);
    void updateTitle(QString libelle);
    void setTableViewModel(GerantNotifModel* gerantNotifModel);
    void top();

    ~UIGerantNotif();

private:
    Ui::UIGerantNotif *ui;
};

#endif // UIGERANTNOTIF_H
