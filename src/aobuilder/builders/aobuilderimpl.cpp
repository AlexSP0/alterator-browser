#include "../constants.h"

#include "../objects/category.h"
#include "aobuilderimpl.h"
#include "localapplicationobjectbuilder.h"
#include "objectbuilderfactory.h"
#include "objectbulderinterface.h"

#include "../datasource/datasourcedbusimpl.h"
#include "../datasource/datasourceinterface.h"

#include "../parsers/baseobjectparser.h"
#include <ostream>
#include <qdebug.h>

namespace ao_builder
{
class AOBuilderImplPrivate
{
public:
    AOBuilderImplPrivate()
        : m_localAppBuilder(new LocalApplicationObjectBuilder())
        , m_dataSource(new DataSourceDBusImpl(DBUS_SERVICE_NAME))
        , m_parser(new BaseObjectParser())
    {}

public:
    std::unique_ptr<ObjectBuilderInterface> m_localAppBuilder;
    std::unique_ptr<DataSourceInterface> m_dataSource;
    std::unique_ptr<ObjectParserInterface> m_parser;
};

AOBuilderImpl::AOBuilderImpl()
    : d(new AOBuilderImplPrivate())
{}

std::unique_ptr<Object> AOBuilderImpl::buildDefaultCategory()
{
    auto result           = std::make_unique<Category>();
    result->m_id          = DEFAULT_CATEGORY_NAME;
    result->m_displayName = DEFAULT_CATEGORY_NAME;

    result->m_nameLocaleStorage.insert("ru", "Без категории");
    result->m_nameLocaleStorage.insert("en", "Without category");

    result->m_comment = DEFAULT_CATEGORY_NAME;
    result->m_commentLocaleStorage.insert("ru", "Объекты не имеющие категории");
    result->m_commentLocaleStorage.insert("en", "Objects without category");

    result->m_icon = "groups/system";

    return result;
}

AOBuilderImpl::~AOBuilderImpl()
{
    delete d;
}

std::vector<std::unique_ptr<Object>> AOBuilderImpl::buildLocalApps()
{
    QStringList appsList = d->m_dataSource->getLocalAppPaths();

    std::vector<std::unique_ptr<Object>> result{};

    for (QString currentApp : appsList)
    {
        QString currentAppInfo                = d->m_dataSource->getLocalAppInfo(currentApp);
        std::unique_ptr<Object> currentObject = buildObject(currentAppInfo);

        if (!currentObject)
        {
            qWarning() << "Cannot build app" << currentApp;
            continue;
        }

        qInfo() << "Successfully built app" << currentApp;
        result.push_back(std::move(currentObject));
    }
    return result;
}

std::vector<std::unique_ptr<Object>> AOBuilderImpl::buildCategories()
{
    QStringList catList = d->m_dataSource->getCategoriesList();

    std::vector<std::unique_ptr<Object>> result;

    for (QString currentCategory : catList)
    {
        QString currentCatInfo                = d->m_dataSource->getCategoryInfo(currentCategory);
        std::unique_ptr<Object> currentObject = buildObject(currentCatInfo);

        if (currentObject)
        {
            qInfo() << "Successfully built category" << currentCategory;
            result.push_back(std::move(currentObject));
        }
    }

    result.push_back(std::move(buildDefaultCategory()));

    return result;
}

std::vector<std::unique_ptr<Object>> AOBuilderImpl::buildObjects(std::vector<QString> interfaces)
{
    std::vector<std::unique_ptr<Object>> result;

    for (auto interface : interfaces)
    {
        QStringList objectsList = d->m_dataSource->getObjectsPath(interface);

        for (QString currentObjectPath : objectsList)
        {
            QString currentObjectInfo             = d->m_dataSource->getObjectInfo(currentObjectPath, interface);
            std::unique_ptr<Object> currentObject = buildObject(currentObjectInfo);

            if (currentObject)
            {
                qInfo() << "Successfully built object" << currentObjectPath;
                currentObject->m_interface = interface;
                currentObject->m_dbus_path = currentObjectPath;
                result.push_back(std::move(currentObject));
            }
        }
    }

    return result;
}

std::unique_ptr<Object> AOBuilderImpl::buildObject(QString info)
{
    if (info.isEmpty())
    {
        qWarning() << "Cannot parse object: Info returned empty string";
        return {};
    }

    if (!d->m_parser->parse(info))
    {
        qWarning() << "Cannot parse object";
        return {};
    }

    ObjectBuilderFactory factory{};
    std::unique_ptr<ObjectBuilderInterface> objectBuilder = factory.getBuilder(d->m_parser.get());

    if (!objectBuilder)
    {
        qWarning() << "Cannot get builder for an object";
        return {};
    }

    return objectBuilder->buildObject(d->m_parser.get());
}
} // namespace ao_builder
