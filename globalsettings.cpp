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

    if(!cfg.contains(Settings::LOG_LEVEL_KEY)) {
        cfg.setValue(Settings::LOG_LEVEL_KEY, Settings::LOG_LEVEL_DEFAULT);
    }
}

void GlobalSettings::fillForm()
{
    QString url = cfg.value(Settings::URL_KEY).toString();
    int log_level= cfg.value(Settings::LOG_LEVEL_KEY).toInt();

    ui->urlEdit->setText(url);
    ui->logLevelBox->setCurrentIndex(log_level);
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

void GlobalSettings::on_logLevelBox_currentIndexChanged(int index)
{
    cfg.setValue(Settings::LOG_LEVEL_KEY, index);
}
