#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QVariant>

namespace Settings {

static const QString URL_KEY = "url";
static const QVariant URL_VALUE_DEFAULT = "http://jsonplaceholder.typicode.com/";
static const QString ORGANIZATION_NAME = "Reksio";
static const QString APPLICATION_NAME = "RFP v2.0";

}

#endif // SETTINGS_H
