#ifndef MANUALSERIALCONTROLLER_H
#define MANUALSERIALCONTROLLER_H

#include <QWidget>

namespace Ui {
class ManualSerialController;
}

class ManualSerialController : public QWidget
{
    Q_OBJECT

public:
    explicit ManualSerialController(QWidget *parent = 0);
    ~ManualSerialController();

private:
    Ui::ManualSerialController *ui;
};

#endif // MANUALSERIALCONTROLLER_H
