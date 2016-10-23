#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class GlobalSettings;
}

class GlobalSettings : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSettings(QWidget *parent = 0);
    ~GlobalSettings();

private slots:
    void on_saveButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::GlobalSettings *ui;
    QSettings cfg;
    void setupSettings();
    void fillForm();
};

#endif // GLOBALSETTINGS_H
