#ifndef UISETTINGS_H
#define UISETTINGS_H

#include <QMainWindow>
#include <uiabstractwindow.h>

namespace Ui {
class UISettings;
}

class UISettings : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UISettings(QWidget *parent = nullptr);
    UISettings(QObject* controller);
    void updateTitle (QString libelle);
    ~UISettings();

    int getTransactionLimit();
    int getMinimumAmount();
    int getMaximumAmount();
    bool getNotifications();

    void setTransactionLimit(int limit);
    void setMinimumAmount(int min);
    void setMaximumAmount(int max);
    void setNotifications(bool enabled);

    void populateSettings(int transactionLimit, int minimumAmount, int maximumAmount, bool notifications);

private:
    Ui::UISettings *ui;
};

#endif // UISETTINGS_H
