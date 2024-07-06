#include "pacman.h"
#include <QKeyEvent>
void Pacman::loadPixmap()
{
    m_upPixmap    = m_thingsPixmap.copy(Resources::PACMAN_UP.x(), Resources::PACMAN_UP.y(), Resources::ENTITY_TILE_SIZE*Resources::PACMAN_COUNT_ANIM_FRAMES, Resources::ENTITY_TILE_SIZE);
    m_downPixmap  = m_thingsPixmap.copy(Resources::PACMAN_DOWN.x(), Resources::PACMAN_DOWN.y(), Resources::ENTITY_TILE_SIZE*Resources::PACMAN_COUNT_ANIM_FRAMES, Resources::ENTITY_TILE_SIZE);
    m_leftPixmap  = m_thingsPixmap.copy(Resources::PACMAN_LEFT.x(), Resources::PACMAN_LEFT.y(), Resources::ENTITY_TILE_SIZE*Resources::PACMAN_COUNT_ANIM_FRAMES, Resources::ENTITY_TILE_SIZE);
    m_rightPixmap = m_thingsPixmap.copy(Resources::PACMAN_RIGHT.x(), Resources::PACMAN_RIGHT.y(), Resources::ENTITY_TILE_SIZE*Resources::PACMAN_COUNT_ANIM_FRAMES, Resources::ENTITY_TILE_SIZE);
    m_deadPixmap  = m_thingsPixmap.copy(Resources::DEAD_PACMAN.x(), Resources::DEAD_PACMAN.y(), Resources::ENTITY_TILE_SIZE*Resources::DEAD_PACMAN_COUNT_ANIM_FRAMES, Resources::ENTITY_TILE_SIZE);
}

Pacman::Pacman(QPoint startPosition)
    : Entity(startPosition.x(), startPosition.y()),
    m_eatenDots { 0 },
    m_dead { false },
    m_currentIndex { 0 },
    m_speed {Resources::PACMAN_SPEED},
    m_animationSpeed {Resources::PACMAN_ANIM_SPEED}
{
    loadPixmap();
    setPixmap(m_thingsPixmap.copy(0,0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
    setTransformOriginPoint(Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    connect(&m_timer, &QTimer::timeout, this, &Pacman::updatePixmap);
    m_timer.start(m_animationSpeed);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setActive(true);
}

void Pacman::updatePixmap()
{
    if(!m_dead)
    {
        if(m_currentDirection == Resources::Direction::Up)
        {
            setPixmap(m_upPixmap.copy(m_currentIndex*Resources::ENTITY_TILE_SIZE, 0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
        }
        else if(m_currentDirection == Resources::Direction::Right)
        {
            setPixmap(m_rightPixmap.copy(m_currentIndex*Resources::ENTITY_TILE_SIZE, 0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
        }
        else if(m_currentDirection == Resources::Direction::Down)
        {
            setPixmap(m_downPixmap.copy(m_currentIndex*Resources::ENTITY_TILE_SIZE, 0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
        }
        else if(m_currentDirection == Resources::Direction::Left)
        {
            setPixmap(m_leftPixmap.copy(m_currentIndex*Resources::ENTITY_TILE_SIZE, 0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
        }

        m_currentIndex += 1;
        m_currentIndex %= Resources::PACMAN_COUNT_ANIM_FRAMES;
    }
    else
    {
        setPixmap(m_deadPixmap.copy(m_currentIndex*Resources::ENTITY_TILE_SIZE, 0, Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE));
        m_currentIndex += 1;
        if(m_currentIndex == Resources::DEAD_PACMAN_COUNT_ANIM_FRAMES)
        {
            emit deadAnimOver();
        }
        m_currentIndex %= Resources::DEAD_PACMAN_COUNT_ANIM_FRAMES;
    }

}

void Pacman::move()
{
    switch (m_currentDirection)
    {
    case Resources::Direction::Up:
        Entity::move(0, -m_speed);
        break;
    case Resources::Direction::Down:
        Entity::move(0, m_speed);
        break;
    case Resources::Direction::Left:
        Entity::move(-m_speed, 0);
        break;
    case Resources::Direction::Right:
        Entity::move(m_speed, 0);
        break;
    case Resources::Direction::Unset:
        break;
    }
}

Resources::Direction Pacman::getCurrentDirection()
{
    return m_currentDirection;
}

void Pacman::setCurrentDirection(const Resources::Direction& direction)
{
    m_currentDirection = direction;
    setCenter();
}

Resources::Direction Pacman::getNextDirection()
{
    return m_nextDirection;
}

void Pacman::setNextDirection(const Resources::Direction& direction)
{
    m_nextDirection = direction;
}

void Pacman::stop()
{
    m_currentDirection = Resources::Unset;
}

void Pacman::eatDot()
{
    m_eatenDots++;
}

int Pacman::getDotsEaten()
{
    return m_eatenDots;
}

void Pacman::setCenter()
{

    if(m_currentDirection == Resources::Direction::Up)
    {
        m_screenPosition.setX((m_position.x() + 1.0f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE);
    }
    else if(m_currentDirection == Resources::Direction::Down)
    {
        m_screenPosition.setX((m_position.x() + 1.0f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE);
    }
    else if(m_currentDirection == Resources::Direction::Left)
    {
        m_screenPosition.setY((m_position.y() + 0.5f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE/2);
    }
    else if(m_currentDirection == Resources::Direction::Right)
    {
        m_screenPosition.setY((m_position.y() + 0.5f) * Resources::MAP_TILE_SIZE - Resources::ENTITY_TILE_SIZE/2);
    }

}

void Pacman::setDead(const bool& dead)
{
    m_dead = dead;
    m_active = !dead;
    m_currentIndex = 0;
}

bool Pacman::isDead()
{
    return m_dead;
}

void Pacman::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
    {
        return;
    }
    if(!isDead())
    {
        switch (event->key()) {
        case Qt::Key_Up:
            m_nextDirection = Resources::Direction::Up;
            break;
        case Qt::Key_Right:
            m_nextDirection = Resources::Direction::Right;
            break;
        case Qt::Key_Down:
            m_nextDirection = Resources::Direction::Down;
            break;
        case Qt::Key_Left:
            m_nextDirection = Resources::Direction::Left;
            break;
        }
    }

    QGraphicsPixmapItem::keyPressEvent(event);
}
