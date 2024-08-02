#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QElapsedTimer>
#include <QSoundEffect>
#include <QVector>
#include "pacman.h"
#include "pacmanmap.h"
#include "blinky.h"
#include "pinky.h"
#include "inky.h"
#include "clyde.h"
#include "fruits.h"

class GameScene: public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QObject *parent = nullptr);

    ~GameScene();

    void start();

    void stop();

public slots:
    void loop();

    void restartPositions();

    void weakAllGhosts();

    void normalAllGhost();

signals:
    void gameClosed();

    void gameOver(const int lives, const int score);

private:

    //Initialization

    void loadPixmap();

    void loadSFX();

    void initMap();

    void initPackman();

    void initGhosts();

    void initFruit();

    void initGUI();

    //GUI update

    void renderMap(const QPoint& pacmanPosition);

    void renderPacman();

    void renderGhosts();

    bool pacmanCanMove();

    void pacmanCollizion();

    bool entityCanMove(Entity* entity, const Resources::Direction& entityDirection);

    void ghostMovement(Ghost* ghost);

    void ghostAndPacmanCollision(Ghost* ghost);

    float calculateDistance(Ghost* ghost, int addX, int addY);

    void fruitAndPacmanCollision();

    void addPoints(int n);

    void updateGUI();

    //Map

    QPixmap m_mapPixmap;

    QPixmap m_mapPixmaps[4];

    QVector<QVector<QGraphicsPixmapItem*>> m_mapPixmapItems;

    PacmanMap* m_map;

    //Entity

    Pacman* m_pacman;

    Blinky* m_blinky;

    Inky* m_inky;

    Pinky* m_pinky;

    Clyde* m_clyde;

    Fruits* m_fruit;

    QTimer m_timer, m_weekTimer;

    const float m_loopSpeed;

    //GUI

    QFont m_basicFont;

    QGraphicsSimpleTextItem *m_scoreTextItem;

    QPixmap m_lifePacmanPixmap;

    int m_lives, m_score;

    QList<QGraphicsPixmapItem*> m_livesPixmapItem;

    const int TOP_SPACE;

    const int LEFT_SPACE;

    QPoint m_scenePosition;

    QSoundEffect m_packman_chompSFX, m_packman_deathSFX, m_packman_eatfruitSFX, m_packman_eatghostSFX;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
