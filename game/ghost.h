#ifndef GHOST_H
#define GHOST_H

#include <QPixmap>
#include <QTimer>
#include "entity.h"
#include "resources.h"

class Ghost : public Entity
{
public:

    Ghost(int startPositionX, int startPositionY);

    //Setters

    void setDestination(const float& destinationY, const float& destinationX);

    void setDestination(const QPoint& destination);

    void setScattering(const bool& scattering);

    void startWeakMode();

    void stopWeakMode();

    void setWeak(const bool& weak);

    void setAnimated(const bool& animated);

    void setSpeed(const float& speed);

    void setDirection(const Resources::Direction& direction);

    void move();

    void start();

    void setCenter();

    void setTakeDecision(bool d);

    void stop();

    //Getters

    QPoint getDestination();

    bool isOutOfCage();

    bool isScattering();

    bool isWeak();

    bool shouldTakeDecision();

    bool isAnimated();

    float getSpeed();

    float getDistanceToDestination(const float& addX = 0, const float& addY = 0);

    Resources::Direction getDirection();

protected:    
    QTimer m_timer;

    QPoint m_destination;

    bool m_scattering;

    bool m_weak;

    bool m_outOfCage;

    bool m_decision;

    bool m_isAnimated;

    QPixmap m_weakPixmap;

    float m_speed;

    int m_animationSpeed;

    Resources::Direction m_direction;
};

#endif // GHOST_H
