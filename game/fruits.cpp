#include "fruits.h"

void Fruits::loadPixmap()
{
    m_fruitsPixmap[0] = m_thingsPixmap.copy(Resources::STRAWBERRY.x(),Resources::STRAWBERRY.y(),Resources::ENTITY_TILE_SIZE,Resources::ENTITY_TILE_SIZE);
    m_fruitsPixmap[1] = m_thingsPixmap.copy(Resources::CHERRY.x(),Resources::CHERRY.y(),Resources::ENTITY_TILE_SIZE,Resources::ENTITY_TILE_SIZE);
    m_fruitsPixmap[2] = m_thingsPixmap.copy(Resources::ORANGE.x(),Resources::ORANGE.y(),Resources::ENTITY_TILE_SIZE,Resources::ENTITY_TILE_SIZE);
}


Fruits::Fruits(float startPositionX, float startPositionY):
    Entity(startPositionX, startPositionY),
    m_existanceTime { Resources::FRUITS_EXISTANCE_TIME }
{
    loadPixmap();
    connect(&m_timer, &QTimer::timeout, this, &Fruits::existanceTimeOut);
}

void Fruits::create()
{
    if(!m_active)
    {
        m_active = true;
        setPixmap(m_fruitsPixmap[rand()%Resources::COUNT_OF_FRUITS]);
        m_timer.start(m_existanceTime);
    }
}

void Fruits::remove()
{
    m_timer.stop();
    m_active = false;
    setPixmap(QPixmap());
}

void Fruits::existanceTimeOut()
{
    m_active = false;
    setPixmap(QPixmap());
}

