#ifndef UIMESSAGE_H
#define UIMESSAGE_H

#include <QMainWindow>

namespace Ui {
class UIMessage;
}

class UIMessage : public QMainWindow
{
    Q_OBJECT

public:
    explicit UIMessage(QWidget *parent = nullptr);
    ~UIMessage();

private:
    Ui::UIMessage *ui;
};

#endif // UIMESSAGE_H
