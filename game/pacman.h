#ifndef PACMAN_H
#define PACMAN_H

#include <QTimer>
#include "resources.h"
#include "entity.h"

class Pacman: public Entity
{
    Q_OBJECT
public:
    Pacman(QPoint startPosition);

    void move();

    Resources::Direction getCurrentDirection();

    void setCurrentDirection(const Resources::Direction& direction);

    Resources::Direction getNextDirection();

    void setNextDirection(const Resources::Direction& direction);

    void stop();

    void eatDot();

    int getDotsEaten();

    void setCenter();

    void setDead(const bool& dead);

    bool isDead();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

signals:
    void deadAnimOver();

public slots:
    void updatePixmap();

private:
    void loadPixmap();

    Resources::Direction m_currentDirection;

    Resources::Direction m_nextDirection;

    int m_eatenDots;

    bool m_dead;

    QPixmap m_upPixmap, m_downPixmap, m_leftPixmap, m_rightPixmap;

    QPixmap m_deadPixmap;

    int m_currentIndex;

    QTimer m_timer;

    float m_speed;

    int m_animationSpeed;
};

#endif // PACMAN_H
