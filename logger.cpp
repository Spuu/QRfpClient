#include "logger.h"
#include "settings.h"

Logger::Logger()
{
}

QString Logger::LogLevelToQString(LogLevel e) {
    switch(e) {
    case LogLevel::INFO:
        return "INFO: ";

    case LogLevel::DEBUG:
        return "DEBUG: ";

    case LogLevel::WARNING:
        return "WARNING: ";

    case LogLevel::ERROR:
        return "ERROR: ";

    case LogLevel::TRACE:
        return "TRACE: ";
    }

    return "";
}

void Logger::log(LogLevel lvl, QString msg)
{
    if(cfg.value(Settings::LOG_LEVEL_KEY).toInt() >= (int)lvl)
        emit logSig(QString(LogLevelToQString(lvl)+msg));
}
