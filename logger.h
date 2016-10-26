#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QSettings>

enum class LogLevel {
    ERROR,
    INFO,
    WARNING,
    DEBUG,
    TRACE
};

class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger &instance()
    {
        static Logger loggerInstance;
        return loggerInstance;
    }

    Logger(Logger const&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger const&) = delete;
    Logger& operator=(Logger &&) = delete;

    void log(LogLevel lvl = LogLevel::INFO, QString msg = "-- default info --");
    QString LogLevelToQString(LogLevel e = LogLevel::INFO);

signals:
    void logSig(QString msg);

protected:
    Logger();
    virtual ~Logger() {}

private:
    QSettings cfg;
};

#endif // LOGGER_H
