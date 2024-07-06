#include "blinky.h"

void Blinky::loadPixmap()
{
    m_upPixmap = m_thingsPixmap.copy(Resources::BLINKY_UP.x(), Resources::BLINKY_UP.y(), Resources::BLINKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_rightPixmap = m_thingsPixmap.copy(Resources::BLINKY_RIGHT.x(), Resources::BLINKY_RIGHT.y(), Resources::BLINKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_downPixmap = m_thingsPixmap.copy(Resources::BLINKY_DOWN.x(), Resources::BLINKY_DOWN.y(), Resources::BLINKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_leftPixmap = m_thingsPixmap.copy(Resources::BLINKY_LEFT.x(), Resources::BLINKY_LEFT.y(), Resources::BLINKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
}

Blinky::Blinky(QPoint startPosition):
    Ghost(startPosition.x(), startPosition.y()),
    m_currentIndex(0)
{
    m_speed = Resources::BLINKY_SPEED;
    m_animationSpeed = Resources::BLINKY_ANIM_SPEED;

    setPixmap(m_thingsPixmap.copy(Resources::BLINKY_DOWN.x(),Resources::BLINKY_DOWN.y(), Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
    loadPixmap();

    setTransformOriginPoint(Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    connect(&m_timer, &QTimer::timeout, this, &Blinky::updatePixmap);
}

void Blinky::updatePixmap()
{
    if(getDirection() == Resources::Direction::Unset || !m_isAnimated)
    {
        setPixmap(m_thingsPixmap.copy(Resources::BLINKY_DOWN.x(),Resources::BLINKY_DOWN.y(), Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
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
    m_currentIndex %= Resources::BLINKY_COUNT_ANIM_FRAMES;

}

void Blinky::findDestination(Entity* entity)
{
    if(!isScattering())
    {
        setDestination(entity->getTileY(), entity->getTileX());
    }
}
