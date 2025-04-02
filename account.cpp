#include "account.h"

Account::Account(int _id, int _idClient, QString _number, QString _type) :
    Account (_id, _idClient, _number, _type, 0.00, "")
{}

Account::Account(int _idClient, QString _number, QString _type) :
    Account (_idClient, _number, _type, 0.00, "")
{}

Account::Account(int _idClient, QString _number, QString _type, double _balance, QString _statut) :
    idClient(_idClient), number(_number), type(_type), balance(_balance), statut(_statut)
{}

Account::Account(int id, int idClient, QString number, QString type, double balance, QString statut) :
    Account (idClient, number, type, balance, statut)
{
    this->id = id;
}

Account::Account()
{}
