#include "logger.h"

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
    emit logSig(QString(LogLevelToQString(lvl)+msg));
}
