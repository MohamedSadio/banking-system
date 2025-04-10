#include "adminnotif.h"

AdminNotif::AdminNotif()
{

}

AdminNotif::AdminNotif(QString _typeNotif, QString _message, QString _date):
    typeNotif(_typeNotif), message(_message), date(_date)
{
}

AdminNotif::AdminNotif(int _id, QString _typeNotif, QString _message, QString _date):
    id(_id), typeNotif(_typeNotif), message(_message), date(_date)
{
}
