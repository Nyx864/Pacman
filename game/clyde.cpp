#include "clyde.h"

void Clyde::loadPixmap()
{
    m_upPixmap = m_thingsPixmap.copy(Resources::CLYDE_UP.x(), Resources::CLYDE_UP.y(), Resources::CLYDE_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_rightPixmap = m_thingsPixmap.copy(Resources::CLYDE_RIGHT.x(), Resources::CLYDE_RIGHT.y(), Resources::CLYDE_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_downPixmap = m_thingsPixmap.copy(Resources::CLYDE_DOWN.x(), Resources::CLYDE_DOWN.y(), Resources::CLYDE_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_leftPixmap = m_thingsPixmap.copy(Resources::CLYDE_LEFT.x(), Resources::CLYDE_LEFT.y(), Resources::CLYDE_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
}

Clyde::Clyde(QPoint startPosition):
    Ghost(startPosition.x(), startPosition.y()),
    m_currentIndex(0)
{
    m_speed = Resources::CLYDE_SPEED;
    m_animationSpeed = Resources::CLYDE_ANIM_SPEED;

    setPixmap(m_thingsPixmap.copy(Resources::CLYDE_DOWN.x(),Resources::CLYDE_DOWN.y(), Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
    loadPixmap();

    setTransformOriginPoint(Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    connect(&m_timer, &QTimer::timeout, this, &Clyde::updatePixmap);
}

void Clyde::updatePixmap()
{
    if(getDirection() == Resources::Direction::Unset || !m_isAnimated)
    {
        setPixmap(m_thingsPixmap.copy(Resources::CLYDE_DOWN.x(),Resources::CLYDE_DOWN.y(), Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
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
    m_currentIndex %= Resources::CLYDE_COUNT_ANIM_FRAMES;

}

void Clyde::findDestination(Entity *entitity)
{
    if (!isScattering())
    {
        if (sqrt(pow(getTileX() - entitity->getTileX(), 2) + pow(getTileY() - entitity->getTileY(), 2)) < 9)
        {
            setDestination(entitity->getTileX(), entitity->getTileY());
        }
        else
        {
            setDestination(0, 0);
        }
    }
}
