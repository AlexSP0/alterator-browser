#include "objectitem.h"

namespace ab
{
namespace model
{
ObjectItem::ObjectItem()
    : m_itemType(ItemType::category)
{}

int ObjectItem::type() const
{
    return static_cast<int>(m_itemType);
}

std::variant<Object, Category> *ObjectItem::getObject()
{
    return m_object.get(); // NOTE(uyraq2001): is it the best way?
}
} // namespace model
} // namespace ab
