#ifndef LOGGER_H
#define LOGGER_H

#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QtMessageHandler>
#include "DefaultLogManager.h"

class logger
{
public:
    logger();

    static void logMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:

public slots:
};

#endif // LOGGER_H
