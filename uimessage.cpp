#include "uimessage.h"
#include "ui_uimessage.h"

UIMessage::UIMessage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIMessage)
{
    ui->setupUi(this);
}

UIMessage::~UIMessage()
{
    delete ui;
}
