#include "gerantnotif.h"

GerantNotif::GerantNotif() : id(-1), referenceId(-1) {}

GerantNotif::GerantNotif(int id, QString role, QString typeNotif, int referenceId, QString message, QString date)
    : id(id), role(role), typeNotif(typeNotif), referenceId(referenceId), message(message), date(date) {}

int GerantNotif::getId() const { return id; }
QString GerantNotif::getRole() const { return role; }
QString GerantNotif::getTypeNotif() const { return typeNotif; }
int GerantNotif::getReferenceId() const { return referenceId; }
QString GerantNotif::getMessage() const { return message; }
QString GerantNotif::getDate() const { return date; }

void GerantNotif::setId(int id) { this->id = id; }
void GerantNotif::setRole(QString role) { this->role = role; }
void GerantNotif::setTypeNotif(QString typeNotif) { this->typeNotif = typeNotif; }
void GerantNotif::setReferenceId(int referenceId) { this->referenceId = referenceId; }
void GerantNotif::setMessage(QString message) { this->message = message; }
void GerantNotif::setDate(QString date) { this->date = date; }
