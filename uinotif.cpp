#include "uinotif.h"
#include "ui_uinotif.h"

UINotif::UINotif(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UINotif)
{
    ui->setupUi(this);
}

UINotif::~UINotif()
{
    delete ui;
}
