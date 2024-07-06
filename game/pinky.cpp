#include "pinky.h"

void Pinky::loadPixmap()
{
    m_upPixmap = m_thingsPixmap.copy(Resources::PINKY_UP.x(), Resources::PINKY_UP.y(), Resources::PINKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_rightPixmap = m_thingsPixmap.copy(Resources::PINKY_RIGHT.x(), Resources::PINKY_RIGHT.y(), Resources::PINKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_downPixmap = m_thingsPixmap.copy(Resources::PINKY_DOWN.x(), Resources::PINKY_DOWN.y(), Resources::PINKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    m_leftPixmap = m_thingsPixmap.copy(Resources::PINKY_LEFT.x(), Resources::PINKY_LEFT.y(), Resources::PINKY_COUNT_ANIM_FRAMES*Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
}

Pinky::Pinky(QPoint startPosition):
    Ghost(startPosition.x(), startPosition.y()),
    m_currentIndex(0)
{
    m_speed = Resources::PINKY_SPEED;
    m_animationSpeed = Resources::PINKY_ANIM_SPEED;

    setPixmap(m_thingsPixmap.copy(Resources::PINKY_DOWN.x(),Resources::PINKY_DOWN.y(), Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
    loadPixmap();

    setTransformOriginPoint(Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    connect(&m_timer, &QTimer::timeout, this, &Pinky::updatePixmap);
}

void Pinky::updatePixmap()
{
    if(getDirection() == Resources::Direction::Unset || !m_isAnimated)
    {
        setPixmap(m_thingsPixmap.copy(Resources::PINKY_DOWN.x(),Resources::PINKY_DOWN.y(), Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
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
    m_currentIndex %= Resources::PINKY_COUNT_ANIM_FRAMES;

}

void Pinky::findDestination(Entity *entity, const Resources::Direction& entityDirection)
{
    if (!isScattering())
    {
        if(entityDirection == Resources::Direction::Up)
        {
            setDestination(entity->getTileX() - 4, entity->getTileY());
        }
        else if(entityDirection == Resources::Direction::Right)
        {
            setDestination(entity->getTileX(), entity->getTileY() + 4);
        }
        else if(entityDirection == Resources::Direction::Down)
        {
            setDestination(entity->getTileX() + 4, entity->getTileY());
        }
        else if(entityDirection == Resources::Direction::Left)
        {
            setDestination(entity->getTileX(), entity->getTileY() - 4);
        }
    }
}
