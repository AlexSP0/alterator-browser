#ifndef AB_LOCAL_APLLICATION_MODEL_BUILDER_H
#define AB_LOCAL_APLLICATION_MODEL_BUILDER_H

#include <memory>
#include <QDBusConnection>
#include <QString>

#include "localapplication.h"
#include "localapplicationmodel.h"

class LocalApllicationModelBuilder
{
public:
    LocalApllicationModelBuilder(QString serviceName,
                                   QString dbusPath,
                                   QString interfaceName,
                                   QString getListOfFilesMethod,
                                   QString getDesktopFileMethod);

    std::unique_ptr<LocalApplicationModel> buildModel();

private:
    QStringList getListOfDesktopFiles();

    std::vector<std::unique_ptr<LocalApplication>> parseDesktopFiles(QStringList files);

    QString getDesktopFile(QString file);

private:
    QDBusConnection m_dbusConnection;
    QString m_dbusServiceName;
    QString m_dbusPath;
    QString m_interface;
    QString m_getFilesMethodName;
    QString m_getDesktopFileMethodName;
};

#endif // AB_LOCAL_APLLICATION_MODEL_BUILDER_H
