#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QVariant>

namespace Settings {

static const QString URL_KEY = "url";
static const QVariant URL_VALUE_DEFAULT = "http://jsonplaceholder.typicode.com/";
static const QString ORGANIZATION_NAME = "Reksio";
static const QString APPLICATION_NAME = "RFP v2.0";

static const QString LOG_LEVEL_KEY = "loglevel";
static const QVariant LOG_LEVEL_DEFAULT = 3;
}

#endif // SETTINGS_H
