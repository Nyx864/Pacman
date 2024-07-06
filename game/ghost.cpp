#include "ghost.h"



Ghost::Ghost(int startPositionX, int startPositionY):
    Entity(startPositionX, startPositionY),
    m_scattering { false },
    m_weak { false },
    m_outOfCage { false },
    m_decision{ true },
    m_isAnimated{ false }
{
    setDestination(startPositionX, startPositionY);
    setDirection(Resources::Direction::Unset);
    m_weakPixmap = m_thingsPixmap.copy(Resources::SCARED_GHOST.x(), Resources::SCARED_GHOST.y(), Resources::ENTITY_TILE_SIZE*Resources::SCARED_GHOST_COUNT_ANIM_FRAMES, Resources::ENTITY_TILE_SIZE);
}

void Ghost::setDestination(const float &destinationX, const float &destinationY)
{
    m_destination = QPoint(destinationX, destinationY);
}

void Ghost::setDestination(const QPoint &destination)
{
    m_destination = destination;
}

void Ghost::setScattering(const bool &scattering)
{
    m_scattering = scattering;
}

void Ghost::startWeakMode()
{
    m_weak = true;
}

void Ghost::stopWeakMode()
{
    m_weak = false;
}

void Ghost::setWeak(const bool &weak)
{
    m_weak = weak;
}

void Ghost::setAnimated(const bool &animated)
{
    m_isAnimated = animated;
    m_outOfCage = animated;
    setActive(true);
}

void Ghost::setSpeed(const float &speed)
{
    m_speed = speed;
}

void Ghost::setDirection(const Resources::Direction &direction)
{
    m_direction = direction;
    setCenter();
}

void Ghost::move()
{
    if(m_direction == Resources::Direction::Up)
    {
        Entity::move(0, -m_speed);
    }
    else if(m_direction == Resources::Direction::Down)
    {
        Entity::move(0, m_speed);
    }
    else if(m_direction == Resources::Direction::Left)
    {
        Entity::move(-m_speed, 0);
    }
    else if(m_direction == Resources::Direction::Right)
    {
        Entity::move(m_speed, 0);
    }
}

void Ghost::start()
{
    m_timer.start(m_animationSpeed);
}

void Ghost::setCenter()
{
    if(m_direction == Resources::Direction::Up)
    {
        m_screenPosition.setX((m_position.x() + 1.0f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE);
    }
    else if(m_direction == Resources::Direction::Down)
    {
        m_screenPosition.setX((m_position.x() + 1.0f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE);
    }
    else if(m_direction == Resources::Direction::Left)
    {
        m_screenPosition.setY((m_position.y() + 0.5f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE/2);
    }
    else if(m_direction == Resources::Direction::Right)
    {
        m_screenPosition.setY((m_position.y() + 0.5f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE/2);
    }
}

void Ghost::setTakeDecision(bool d)
{
    m_decision = d;
}

void Ghost::stop()
{
    m_timer.stop();
}

QPoint Ghost::getDestination()
{
    return m_destination;
}

bool Ghost::isOutOfCage()
{
    return m_outOfCage;
}

bool Ghost::isScattering()
{
    return m_scattering;
}

bool Ghost::isWeak()
{
    return m_weak;
}

bool Ghost::shouldTakeDecision()
{
    return m_decision;
}

bool Ghost::isAnimated()
{
    return m_isAnimated;
}

float Ghost::getSpeed()
{
    return m_speed;
}

float Ghost::getDistanceToDestination(const float &addX, const float &addY)
{
    return  sqrt(pow(getDestination().x() - getTileX() - addX, 2) + pow(getDestination().y() - getTileY() - addY, 2));
}

Resources::Direction Ghost::getDirection()
{
    return m_direction;
}
