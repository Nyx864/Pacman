#include "gamescene.h"

#include "gamescene.h"
#include "resources.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QPainter>
#include <QDir>
#include <QFontDatabase>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent},
    m_map { new PacmanMap("map2.txt") },
    m_loopSpeed { int(1000.0f/Resources::FPS) },
    m_score { 0 },
    TOP_SPACE{ 65 },
    LEFT_SPACE ((Resources::WINDOW_SIZE.width() - m_map->getMapWidth()*Resources::MAP_TILE_SIZE)/2),
    m_scenePosition { 0, 0 }
{
    srand(time(0));
    loadPixmap();
    loadSFX();
    setSceneRect(m_scenePosition.x(), m_scenePosition.y(), Resources::WINDOW_SIZE.width(), Resources::WINDOW_SIZE.height());
    setBackgroundBrush(QBrush(Resources::BG_COLOR));
    initMap();
    initGUI();
    initFruit();
    initPackman();
    initGhosts();

    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    connect(m_pacman, &Pacman::deadAnimOver, this, &GameScene::restartPositions);
    connect(m_map, &PacmanMap::bigDotIsEaten, this, &GameScene::weakAllGhosts);
    connect(&m_weekTimer, &QTimer::timeout, this, &GameScene::normalAllGhost);
    stop();
}

GameScene::~GameScene()
{
    for(int i = 0; i < m_mapPixmapItems.size(); ++i)
    {
        for(int j = 0; j < m_mapPixmapItems[i].size(); ++j)
        {
            delete m_mapPixmapItems[i][j];
        }
    }
    delete m_pacman;
    delete m_blinky;
    delete m_inky;
    delete m_pinky;
    delete m_clyde;
    delete m_fruit;
    for(int i = 0; i < m_livesPixmapItem.size(); ++i)
    {
        delete m_livesPixmapItem[i];
    }
}

void GameScene::start()
{
    m_timer.start(m_loopSpeed);
    m_blinky->start();
    m_inky->start();
    m_pinky->start();
    m_clyde->start();
}

void GameScene::stop()
{
    m_timer.stop();
    m_blinky->stop();
    m_inky->stop();
    m_pinky->stop();
    m_clyde->stop();
}

void GameScene::loop()
{
    if (entityCanMove(m_pacman, m_pacman->getCurrentDirection()) && !m_pacman->isDead())
    {
        m_pacman->move();
    }
    else
    {
        m_pacman->stop();
    }

    if(entityCanMove(m_pacman, m_pacman->getNextDirection()))
    {
        m_pacman->setCurrentDirection(m_pacman->getNextDirection());
    }

    if(m_map->removeDot(m_pacman, m_score))
    {
        m_packman_chompSFX.play();
    }

    if (m_pacman->getCurrentDirection() != Resources::Direction::Unset)
    {
        m_blinky->findDestination(m_pacman);
        m_clyde->findDestination(m_pacman);
        m_inky->findDestination(m_pacman, m_blinky);
        m_pinky->findDestination(m_pacman, m_pacman->getCurrentDirection());
    }
    else
    {
        m_pacman->setCurrentDirection(m_pacman->getNextDirection());
    }
    renderMap(m_pacman->getPosition());

    ghostMovement(m_blinky);
    ghostMovement(m_inky);
    ghostMovement(m_pinky);
    ghostMovement(m_clyde);

    if(m_pacman->getDotsEaten() == 10)
    {
        m_inky->setAnimated(true);
        m_inky->setPosition(m_map->getBlinkyStartPosition());
    }
    if(m_pacman->getDotsEaten() == 25)
    {
        m_pinky->setAnimated(true);
        m_pinky->setPosition(m_map->getBlinkyStartPosition());
    }
    if(m_pacman->getDotsEaten() == 75)
    {
        m_clyde->setAnimated(true);
        m_clyde->setPosition(m_map->getBlinkyStartPosition());
    }


    for(int i = 40; i <= 240; i+=40)
    {
        if(m_pacman->getDotsEaten() == i)
        {
            m_fruit->create();
        }
    }

    pacmanCollizion();

    renderPacman();
    renderGhosts();
    updateGUI();

    if(m_pacman->getDotsEaten() == m_map->getAmountOfDots())
    {
        stop();
        emit gameOver(m_lives, m_score);
    }
}

void GameScene::restartPositions()
{
    if (m_blinky->isOutOfCage())
    {
        m_blinky->setPosition(m_map->getBlinkyStartPosition());
        m_blinky->setPos(m_blinky->getScreenPosition());
    }
    if (m_inky->isOutOfCage())
    {
        m_inky->setPosition(m_map->getBlinkyStartPosition());
        m_inky->setPos(m_inky->getScreenPosition());
    }
    if (m_pinky->isOutOfCage())
    {
        m_pinky->setPosition(m_map->getBlinkyStartPosition());
        m_pinky->setPos(m_pinky->getScreenPosition());
    }
    if (m_clyde->isOutOfCage())
    {
        m_clyde->setPosition(m_map->getBlinkyStartPosition());
        m_clyde->setPos(m_clyde->getScreenPosition());
    }
    m_pacman->setPosition(m_map->getPacmanStartPosition());
    m_pacman->setPos(m_pacman->getPosition().x()*Resources::MAP_TILE_SIZE - Resources::MAP_TILE_SIZE/2 + LEFT_SPACE, m_pacman->getPosition().y()*Resources::MAP_TILE_SIZE+TOP_SPACE);
    m_pacman->setDead(false);
    m_lives--;
    if(m_lives < 0)
    {
        stop();
        emit gameOver(m_lives, m_score);
    }
}

void GameScene::weakAllGhosts()
{
    m_blinky->startWeakMode();
    m_inky->startWeakMode();
    m_pinky->startWeakMode();
    m_clyde->startWeakMode();
    m_weekTimer.start(Resources::SCARED_GHOST_DURATION);
}

void GameScene::normalAllGhost()
{
    m_blinky->stopWeakMode();
    m_inky->stopWeakMode();
    m_pinky->stopWeakMode();
    m_clyde->stopWeakMode();
    m_weekTimer.stop();
}

void GameScene::loadPixmap()
{
    if( m_mapPixmap.load(Resources::PATH_TO_MAP_PIXMAP) )
    {
        qDebug() << "map is loaded SUCCESSFULLY";
    }
    else
    {
        qFatal("map is NOT loaded");
    }

    QPixmap thingsPixmap;
    if( thingsPixmap.load(Resources::PATH_TO_ENTITY_PIXMAP) )
    {
        m_lifePacmanPixmap = thingsPixmap.copy(Resources::LIFE_PACKMAN.x(), Resources::LIFE_PACKMAN.y(), Resources::ENTITY_TILE_SIZE, Resources::ENTITY_TILE_SIZE);
    }
}

void GameScene::loadSFX()
{
    m_packman_chompSFX.setSource(Resources::PACMAN_CHOMP_SFX);
    m_packman_chompSFX.setVolume(0.5f);
    m_packman_deathSFX.setSource(Resources::PACMAN_DEATH_SFX);
    m_packman_eatfruitSFX.setSource(Resources::PACMAN_EATFRUIT_SFX);
    m_packman_eatghostSFX.setSource(Resources::PACMAN_EATGHOST_SFX);
}

void GameScene::initMap()
{
    m_mapPixmaps[0] = QPixmap();
    m_mapPixmaps[1] = m_mapPixmap.copy(0 * Resources::MAP_TILE_SIZE, 0, Resources::MAP_TILE_SIZE, Resources::MAP_TILE_SIZE);
    m_mapPixmaps[2] = m_mapPixmap.copy(2 * Resources::MAP_TILE_SIZE, 0, Resources::MAP_TILE_SIZE, Resources::MAP_TILE_SIZE);
    m_mapPixmaps[3] = m_mapPixmap.copy(1 * Resources::MAP_TILE_SIZE, 0, Resources::MAP_TILE_SIZE, Resources::MAP_TILE_SIZE);

    for (int i = 0; i < m_map->getMapHeight(); i++)
    {
        QVector<QGraphicsPixmapItem*> row;
        for (int j = 0; j < m_map->getMapWidth(); j++)
        {
            row.push_back(new QGraphicsPixmapItem(m_mapPixmaps[m_map->tiles(i, j)]));
            row[j]->setPos(i*Resources::MAP_TILE_SIZE + LEFT_SPACE, j*Resources::MAP_TILE_SIZE + TOP_SPACE);
            addItem(row[j]);
        }
        m_mapPixmapItems.push_back(row);
    }
}

void GameScene::initPackman()
{
    m_pacman = new Pacman(m_map->getPacmanStartPosition());
    m_pacman->setFocus();
    m_pacman->setPos(m_pacman->getPosition().x()*Resources::MAP_TILE_SIZE - Resources::MAP_TILE_SIZE/2 + LEFT_SPACE, m_pacman->getPosition().y()*Resources::MAP_TILE_SIZE + TOP_SPACE);
    addItem(m_pacman);
}

void GameScene::initGhosts()
{
    m_blinky = new Blinky(m_map->getBlinkyStartPosition());
    m_blinky->setPos(m_blinky->getScreenPosition().x() + LEFT_SPACE, m_blinky->getScreenPosition().y() + TOP_SPACE);
    m_blinky->setAnimated(true);

    m_inky = new Inky(m_map->getInkyStartPosition());
    m_inky->setPos(m_inky->getScreenPosition().x() + LEFT_SPACE, m_inky->getScreenPosition().y() + TOP_SPACE);
    m_inky->setAnimated(false);

    m_pinky = new Pinky(m_map->getPinkyStartPosition());
    m_pinky->setPos(m_pinky->getScreenPosition().x() + LEFT_SPACE, m_pinky->getScreenPosition().y() + TOP_SPACE);
    m_pinky->setAnimated(false);

    m_clyde = new Clyde(m_map->getClydeStartPosition());
    m_clyde->setPos(m_clyde->getScreenPosition().x() + LEFT_SPACE, m_clyde->getScreenPosition().y() + TOP_SPACE);
    m_clyde->setAnimated(false);

    addItem(m_blinky);
    addItem(m_inky);
    addItem(m_pinky);
    addItem(m_clyde);
}

void GameScene::initFruit()
{
    m_fruit = new Fruits(m_map->getFruitPosition().x(),m_map->getFruitPosition().y());
    m_fruit->setPos(m_fruit->getScreenPosition().x() + LEFT_SPACE, m_fruit->getScreenPosition().y() + TOP_SPACE);
    m_fruit->setPixmap(QPixmap());
    addItem(m_fruit);
}

void GameScene::initGUI()
{
    int id = QFontDatabase::addApplicationFont(Resources::PATH_TO_FONT);
    m_basicFont = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 22, 0);

    QPoint scorePosition{ 750, 30 };
    m_scoreTextItem = new QGraphicsSimpleTextItem();
    m_scoreTextItem->setBrush(QBrush(Resources::FONT_COLOR));
    m_scoreTextItem->setPen(QPen(Resources::FONT_COLOR));
    m_scoreTextItem->setPos(scorePosition);
    m_scoreTextItem->setFont(m_basicFont);
    m_scoreTextItem->setText("Score: " + QString::number(m_score).right(5));
    addItem(m_scoreTextItem);

    m_lives = Resources::AMOUNT_OF_LIVES;
    QPoint livesPosition{ 100, 30 };
    for(int i = 0; i < Resources::AMOUNT_OF_LIVES; ++i)
    {
        QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem();
        pixmapItem->setPixmap(m_lifePacmanPixmap);
        pixmapItem->setPos(i * Resources::ENTITY_TILE_SIZE + livesPosition.x(), livesPosition.y());
        m_livesPixmapItem.append(pixmapItem);
        addItem(m_livesPixmapItem[i]);
    }

}

void GameScene::renderMap(const QPoint& pacmanPosition)
{
    m_mapPixmapItems[pacmanPosition.x()][pacmanPosition.y()]->setPixmap(m_mapPixmaps[ m_map->tiles(pacmanPosition.x(), pacmanPosition.y()) ]);
}

void GameScene::renderPacman()
{
    m_pacman->setPos(m_pacman->getScreenPosition().x() + LEFT_SPACE, m_pacman->getScreenPosition().y() + TOP_SPACE);
}

void GameScene::renderGhosts()
{
    m_blinky->setPos(m_blinky->getScreenPosition().x() + LEFT_SPACE, m_blinky->getScreenPosition().y() + TOP_SPACE);
    m_inky->setPos(m_inky->getScreenPosition().x() + LEFT_SPACE, m_inky->getScreenPosition().y() + TOP_SPACE);
    m_pinky->setPos(m_pinky->getScreenPosition().x() + LEFT_SPACE, m_pinky->getScreenPosition().y() + TOP_SPACE);
    m_clyde->setPos(m_clyde->getScreenPosition().x() + LEFT_SPACE, m_clyde->getScreenPosition().y() + TOP_SPACE);
}

void GameScene::pacmanCollizion()
{
    if(m_pacman->collisionWithEntity(m_fruit))
    {
        fruitAndPacmanCollision();
    }

    if(m_pacman->collisionWithEntity(m_blinky))
    {
        ghostAndPacmanCollision(m_blinky);
    }

    if(m_pacman->collisionWithEntity(m_inky))
    {
        ghostAndPacmanCollision(m_inky);
    }

    if(m_pacman->collisionWithEntity(m_pinky))
    {
        ghostAndPacmanCollision(m_pinky);
    }

    if(m_pacman->collisionWithEntity(m_clyde))
    {
        ghostAndPacmanCollision(m_clyde);
    }
}

void GameScene::ghostMovement(Ghost* ghost)
{
    if (ghost->isScattering())
    {
        if (ghost->getTileX() == ghost->getDestination().x() && ghost->getTileY() == ghost->getDestination().y())
        {
            ghost->setScattering(false);
        }
    }

    if (m_map->isIntersection(ghost->getTileX(), ghost->getTileY()) || !entityCanMove(ghost, ghost->getDirection()))
    {
        if (ghost->shouldTakeDecision())
        {
            float dRight = calculateDistance(ghost, 1, 0);
            float dLeft = calculateDistance(ghost, -1, 0);
            float dUp = calculateDistance(ghost, 0, -1);
            float dDown = calculateDistance(ghost, 0, 1);

            if (dRight < dLeft && dRight < dUp && dRight < dDown)
                ghost->setDirection(Resources::Direction::Right);
            else if (dLeft < dRight && dLeft < dUp && dLeft < dDown)
                ghost->setDirection(Resources::Direction::Left);
            else if (dUp < dLeft && dUp < dRight && dUp < dDown)
                ghost->setDirection(Resources::Direction::Up);
            else if (dDown < dLeft && dDown < dUp && dDown < dRight)
                ghost->setDirection(Resources::Direction::Down);
        }
        ghost->setTakeDecision(false);
    }
    else
    {
        ghost->setTakeDecision(true);
    }

    if (entityCanMove(ghost, ghost->getDirection()) && ghost->isOutOfCage())
    {
        ghost->move();
    }
    else
    {
        ghost->setTakeDecision(true);
    }
}

float GameScene::calculateDistance(Ghost *ghost, int addX, int addY)
{
    float distance { 100000.f };
    if (!m_map->tileBlocksEntity(ghost->getTileX() + addX, ghost->getTileY() + addY))
    {
        distance = ghost->getDistanceToDestination(addX, addY);
    }
    return distance;
}

bool GameScene::entityCanMove(Entity *entity, const Resources::Direction& entityDirection)
{
    if (entityDirection == Resources::Direction::Up)
    {
        return !m_map->tileBlocksEntity(entity->getTileX(), entity->getTileY() - 1);
    }
    else if (entityDirection == Resources::Direction::Down)
    {
        return !m_map->tileBlocksEntity(entity->getTileX(), entity->getTileY() + 1);
    }
    else if (entityDirection == Resources::Direction::Left)
    {
        return !m_map->tileBlocksEntity(entity->getTileX() - 1, entity->getTileY());
    }
    else if (entityDirection == Resources::Direction::Right)
    {
        return !m_map->tileBlocksEntity(entity->getTileX() + 1, entity->getTileY());
    }
    return false;
}

void GameScene::ghostAndPacmanCollision(Ghost* ghost)
{
    if (ghost->isWeak())
    {
        ghost->setPosition(m_map->getBlinkyStartPosition());
        ghost->stopWeakMode();
        addPoints(100);
        m_packman_eatghostSFX.play();
    }
    else if(!m_pacman->isDead())
    {
        m_pacman->setDead(true);
        m_packman_deathSFX.play();
    }
}

void GameScene::fruitAndPacmanCollision()
{
    m_packman_eatfruitSFX.play();
    m_fruit->remove();
    addPoints(50);
}

void GameScene::addPoints(int n)
{
    m_score += n;
}

void GameScene::updateGUI()
{
    m_scoreTextItem->setText(QString("Score: %1").arg(m_score));

    for(int i = 0; i < Resources::AMOUNT_OF_LIVES; ++i)
    {
        m_livesPixmapItem[i]->hide();
    }
    for(int i = 0; i < m_lives; ++i)
    {
        m_livesPixmapItem[i]->show();
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        stop();
        emit gameClosed();
        break;
    case Qt::Key_W:
        m_scenePosition.setY(m_scenePosition.y()-50);
        setSceneRect(m_scenePosition.x(), m_scenePosition.y(), Resources::WINDOW_SIZE.width(), Resources::WINDOW_SIZE.height());
        break;
    case Qt::Key_A:
        m_scenePosition.setX(m_scenePosition.x()-50);
        setSceneRect(m_scenePosition.x(), m_scenePosition.y(), Resources::WINDOW_SIZE.width(), Resources::WINDOW_SIZE.height());
        break;
    case Qt::Key_S:
        m_scenePosition.setY(m_scenePosition.y()+50);
        setSceneRect(m_scenePosition.x(), m_scenePosition.y(), Resources::WINDOW_SIZE.width(), Resources::WINDOW_SIZE.height());
        break;
    case Qt::Key_D:
        m_scenePosition.setX(m_scenePosition.x()+50);
        setSceneRect(m_scenePosition.x(), m_scenePosition.y(), Resources::WINDOW_SIZE.width(), Resources::WINDOW_SIZE.height());
        break;
    }


    QGraphicsScene::keyPressEvent(event);
}
