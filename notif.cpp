#include "notif.h"

Notif::Notif()
{

}

Notif::Notif(int _idClient,int _number, QString _typeNotif, QString _message, QString _date):
    idClient(_idClient),number(_number), typeNotif(_typeNotif), message(_message), date(_date)
{}

Notif::Notif(int _id, QString _typeNotif, QString _message, QString _date):
    id(_id), typeNotif(_typeNotif), message(_message), date(_date)
{}

Notif::Notif(int _id, int _idClient,int _number, QString _typeNotif, QString _message, QString _date):
    id(_id), idClient(_idClient),number(_number), typeNotif(_typeNotif), message(_message), date(_date)
{}


