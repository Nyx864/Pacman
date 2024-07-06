#ifndef ENTITY_H
#define ENTITY_H

#include <QPointF>
#include <QGraphicsPixmapItem>

class Entity: public QGraphicsPixmapItem, public QObject
{
public:
    Entity();

    Entity(int startPositionX, int startPositionY);

    //Setters

    void move(const float& x,const float& y);

    void setPosition(const float& x,const float& y);

    void setPosition(const QPoint& point);

    void setSpeed(const float& speed);

    void setActive(const bool& active);

    //Getters

    int getTileX();

    int getTileY();

    QPoint getPosition();

    int getSpeed();

    bool isActive();

    QPointF getScreenPosition();

    bool collisionWithEntity(Entity* entity);

protected:
    const QPixmap m_thingsPixmap;

    QPoint m_position;

    QPointF m_screenPosition;

    bool m_active;
};

#endif // ENTITY_H
