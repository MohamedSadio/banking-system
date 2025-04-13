#ifndef GERANTNOTIF_H
#define GERANTNOTIF_H

#include <QString>
#include <QDateTime>

class GerantNotif
{
public:
    GerantNotif();
    GerantNotif(int id, QString role, QString typeNotif, int referenceId, QString message, QString date);

    int getId() const;
    QString getRole() const;
    QString getTypeNotif() const;
    int getReferenceId() const;
    QString getMessage() const;
    QString getDate() const;

    void setId(int id);
    void setRole(QString role);
    void setTypeNotif(QString typeNotif);
    void setReferenceId(int referenceId);
    void setMessage(QString message);
    void setDate(QString date);

private:
    int id;
    QString role;
    QString typeNotif;
    int referenceId;
    QString message;
    QString date;
};

#endif // GERANTNOTIF_H
