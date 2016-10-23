#include "globalsettings.h"
#include "ui_globalsettings.h"
#include "settings.h"

#include <QMessageBox>

GlobalSettings::GlobalSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlobalSettings)
{
    ui->setupUi(this);

    setupSettings();
    fillForm();
}

GlobalSettings::~GlobalSettings()
{
    delete ui;
}

void GlobalSettings::setupSettings()
{
    if(!cfg.contains(Settings::URL_KEY)) {
        cfg.setValue(Settings::URL_KEY, Settings::URL_VALUE_DEFAULT);
    }
}

void GlobalSettings::fillForm()
{
    QString url = cfg.value(Settings::URL_KEY).toString();

    ui->urlEdit->setText(url);
}

void GlobalSettings::on_saveButton_clicked()
{
    int ret = QMessageBox::question(this, "Global settings save", "Save changes?");
    if(ret == QMessageBox::No)
        return;

    cfg.setValue(Settings::URL_KEY, ui->urlEdit->text());
}

void GlobalSettings::on_resetButton_clicked()
{
    int ret = QMessageBox::question(this, "Global settings reset", "Are you sure?");
    if(ret == QMessageBox::No)
        return;

    cfg.clear();
    setupSettings();
    fillForm();
}
