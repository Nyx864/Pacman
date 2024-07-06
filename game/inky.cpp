#include "inky.h"

void Inky::loadPixmap()
{
    m_upPixmap = m_thingsPixmap.copy(Resources::INKY_UP.x(), Resources::INKY_UP.y(), Resources::INKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_rightPixmap = m_thingsPixmap.copy(Resources::INKY_RIGHT.x(), Resources::INKY_RIGHT.y(), Resources::INKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_downPixmap = m_thingsPixmap.copy(Resources::INKY_DOWN.x(), Resources::INKY_DOWN.y(), Resources::INKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_leftPixmap = m_thingsPixmap.copy(Resources::INKY_LEFT.x(), Resources::INKY_LEFT.y(), Resources::INKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
}

Inky::Inky(QPoint startPosition):
    Ghost(startPosition.x(), startPosition.y()),
    m_currentIndex(0)
{
    m_speed = Resources::INKY_SPEED;
    m_animationSpeed = Resources::INKY_ANIM_SPEED;

    setPixmap(m_thingsPixmap.copy(Resources::INKY_DOWN.x(),Resources::INKY_DOWN.y(), Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
    loadPixmap();

    setTransformOriginPoint(Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    connect(&m_timer, &QTimer::timeout, this, &Inky::updatePixmap);
}

void Inky::updatePixmap()
{
    if(getDirection() == Resources::Direction::Unset || !m_isAnimated)
    {
        setPixmap(m_thingsPixmap.copy(Resources::INKY_DOWN.x(),Resources::INKY_DOWN.y(), Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
        return;
    }

    if(!isWeak())
    {
        if(getDirection() == Resources::Direction::Up)
        {
            setPixmap(m_upPixmap.copy(m_currentIndex*Resources::ENTITY_TILE_SIZE, 0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
        }
        else if(getDirection() == Resources::Direction::Right)
        {
            setPixmap(m_rightPixmap.copy(m_currentIndex*Resources::ENTITY_TILE_SIZE, 0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
        }
        else if(getDirection() == Resources::Direction::Down)
        {
            setPixmap(m_downPixmap.copy(m_currentIndex*Resources::ENTITY_TILE_SIZE, 0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
        }
        else if(getDirection() == Resources::Direction::Left)
        {
            setPixmap(m_leftPixmap.copy(m_currentIndex*Resources::ENTITY_TILE_SIZE, 0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
        }
    }
    else
    {
        setPixmap(m_weakPixmap.copy(m_currentIndex*Resources::ENTITY_TILE_SIZE, 0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
    }


    m_currentIndex += 1;
    m_currentIndex %= Resources::INKY_COUNT_ANIM_FRAMES;

}

void Inky::findDestination(Entity *entity, Ghost* blinky)
{
    if(!isScattering())
    {
        setDestination(entity->getTileX() + (blinky->getTileX() - entity->getTileX()), entity->getTileY() + (blinky->getTileY() - entity->getTileY()));
    }
}
