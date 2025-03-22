#ifndef UINOTIF_H
#define UINOTIF_H

#include <QMainWindow>

namespace Ui {
class UINotif;
}

class UINotif : public QMainWindow
{
    Q_OBJECT

public:
    explicit UINotif(QWidget *parent = nullptr);
    ~UINotif();

private:
    Ui::UINotif *ui;
};

#endif // UINOTIF_H
