#include "logger.h"

logger::logger()
{

}

void logger::logMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt, str;
    QByteArray localMsg = msg.toLocal8Bit();
    str = context.file;
      if (str.contains(".qml", Qt::CaseInsensitive)){
        switch (type) {
        case QtDebugMsg:
            //fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            //txt = QString(localMsg.constData());
            txt = QString("QML: ").append(" - [");
            txt.append(context.file).append(" - ").append(context.function).append("]: ").append(localMsg.constData());
            //LOG(INFO) << localMsg.constData();
            LOG(INFO) << txt.toStdString();
            break;
            fprintf(stderr, "Infeo: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            abort();
          }
        }
       /* else
            switch (type) {
            case QtDebugMsg:
                //fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
                //txt = QString(localMsg.constData());
                txt = QString("Debug: ").append(localMsg.constData()).append(" - [");
                txt.append(context.file).append("]: ").append(context.line).append(" - ").append(context.function);
                //LOG(INFO) << localMsg.constData();
                LOG(INFO) << txt.toStdString();
                break;
                fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
                break;
            case QtWarningMsg:
                fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
                break;
            case QtCriticalMsg:
                fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
                break;
            case QtFatalMsg:
                fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
                abort();
            }*/
        /*QFile outFile("logs/CAF6000_qmllog.txt");
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << txt << endl;*/
        //outFile.close();
}

