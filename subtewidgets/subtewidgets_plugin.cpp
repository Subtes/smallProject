#include "subtewidgets_plugin.h"
#include "subtewidgets.h"

//#include <qdeclarative.h>
#include <QtDeclarative/qdeclarative.h>

void SubteWidgetsPlugin::registerTypes(const char *uri)
{
    // @uri com.pladema.proyectoSubtes
    qmlRegisterType<SubteWidgets>(uri, 1, 0, "SubteWidgets");
}
