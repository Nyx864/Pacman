#ifndef FRUITS_H
#define FRUITS_H

#include <QTimer>
#include "entity.h"
#include "resources.h"

class Fruits: public Entity
{
    Q_OBJECT
public:
    Fruits(float startPositionX, float startPositionY);

    void create();

    void remove();

private slots:
    void existanceTimeOut();

private:
    int m_existanceTime;

    QTimer m_timer;

    QPixmap m_fruitsPixmap[Resources::COUNT_OF_FRUITS];

    void loadPixmap();
};

#endif // FRUITS_H
