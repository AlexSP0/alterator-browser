#include "mainwindow.h"
#include "modelbuilder.h"

#include <QApplication>
#include <QStandardItemModel>
#include <QTranslator>

#include <model/acmodel.h>
#include <model/acobjectsmodelbuilder.h>

const QString DBUS_SERVICE_NAME                 = "ru.basealt.alterator";
const QString DBUS_PATH                         = "/ru/basealt/alterator";
const QString DBUS_FIND_INTERFACE_NAME          = "ru.basealt.alterator.application";
const QString DBUS_MANAGER_INTERFACE_NAME       = "ru.basealt.alterator.manager";
const QString GET_OBJECTS_METHOD_NAME           = "get_objects";
const QString INFO_METHOD_NAME_FOR_ACOBJECT     = "info";
const QString CATEGORY_METHOD_NAME_FOR_ACOBJECT = "category";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLocale locale;
    QTranslator translator;
    QString language = locale.system().name().split("_").at(0);
    translator.load(language, ".");
    a.installTranslator(&translator);

    //    QStandardItemModel *model = new QStandardItemModel(&a);
    //    ModelBuilder builder;
    //    builder.build(model);

    ACObjectsModelBuilder objectModelBuilder(DBUS_SERVICE_NAME,
                                             DBUS_PATH,
                                             DBUS_MANAGER_INTERFACE_NAME,
                                             DBUS_FIND_INTERFACE_NAME,
                                             GET_OBJECTS_METHOD_NAME,
                                             INFO_METHOD_NAME_FOR_ACOBJECT,
                                             CATEGORY_METHOD_NAME_FOR_ACOBJECT);

    std::unique_ptr<ACModel> model = objectModelBuilder.buildModel();

    ACModel *m1 = model.get();

    model->translateModel(QString("ru"));
    ACModel *m2 = model.get();

    MainWindow w(model.get());
    w.show();
    return a.exec();
}
