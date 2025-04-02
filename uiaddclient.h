#ifndef UIADDCLIENT_H
#define UIADDCLIENT_H

#include <QMainWindow>
#include <uiabstractwindow.h>

namespace Ui {
class UIAddClient;
}

class UIAddClient : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UIAddClient(QWidget *parent = nullptr);
    /*
     * Ce second constructeur permet de connecter le contrÃ´leur Ã  la
     * fenÃªtre */
    UIAddClient(QObject* controller);

    QString getNom();
    QString getPassword();
    QString getCountry();
    QString getBirthdate();
    QString getEmail();
    QString getStatut();
    // QString getRole();
    QString getLogin();

    void reinit();
    void updateTitle (QString libelle);
    void populate (QString identifiant, QString nom, QString country, QString birthdate, QString login, QString password, QString email, QString statut);
    void setIdEditableFalse();

    ~UIAddClient();

private:
    Ui::UIAddClient *ui;
};

#endif // UIADDCLIENT_H
