#include "entity.h"
#include "resources.h"

Entity::Entity()
{
}

Entity::Entity(int startPositionX, int startPositionY):
    m_thingsPixmap { Resources::PATH_TO_ENTITY_PIXMAP },
    m_position { startPositionX, startPositionY },
    m_active{ false }
{
    this->pixmap().rect().moveCenter(QPoint(Resources::ENTITY_TILE_SIZE/2, Resources::ENTITY_TILE_SIZE/2));
    m_screenPosition.setX((m_position.x() + 1.0f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE);
    m_screenPosition.setY((m_position.y() + 0.5f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE/2);
}

int Entity::getTileX()
{
    return m_position.x();
}

int Entity::getTileY()
{
    return m_position.y();
}

QPoint Entity::getPosition()
{
    return m_position;
}

bool Entity::isActive()
{
    return m_active;
}

QPointF Entity::getScreenPosition()
{
    return m_screenPosition;
}

void Entity::move(const float& x,const float& y)
{
    m_screenPosition = QPointF(m_screenPosition.x()+x,m_screenPosition.y()+y);
    m_position = QPoint( round(m_screenPosition.x() / Resources::MAP_TILE_SIZE),  roundf(m_screenPosition.y() / Resources::MAP_TILE_SIZE));
}

void Entity::setPosition(const float& x,const float& y)
{
    m_position = QPoint(x + Resources::MAP_TILE_SIZE/2, y + Resources::MAP_TILE_SIZE/2);
    m_screenPosition.setX((m_position.x() + 1.0f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE/2);
    m_screenPosition.setY((m_position.y() + 0.5f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE/2);
}

void Entity::setPosition(const QPoint& point)
{
    m_position = point;
    m_screenPosition.setX((m_position.x() + 1.0f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE/2);
    m_screenPosition.setY((m_position.y() + 0.5f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE/2);
}

void Entity::setActive(const bool &active)
{
    m_active = active;
}

bool Entity::collisionWithEntity(Entity *entity)
{
    return isActive() && entity->isActive() && entity->getTileX() == getTileX() && entity->getTileY() == getTileY();
}
