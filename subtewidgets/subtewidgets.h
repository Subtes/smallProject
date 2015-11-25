#ifndef SUBTEWIDGETS_H
#define SUBTEWIDGETS_H

#include <QtDeclarative/qdeclarativeitem.h>

class SubteWidgets : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(SubteWidgets)

public:
    SubteWidgets(QDeclarativeItem *parent = 0);
    ~SubteWidgets();
};

QML_DECLARE_TYPE(SubteWidgets)

#endif // SUBTEWIDGETS_H
