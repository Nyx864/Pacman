#include "aftergamescene.h"
#include "resources.h"

AfterGameScene::AfterGameScene():
    m_image{ new QGraphicsPixmapItem() },
    m_score{ new QLabel() }
{

    QSize buttonToMenuSize { 200, 70 };
    QPoint buttonToMenuPosition { 0, 400};
    m_toMenu = new QPushButton("Back to menu");
    m_toMenu->setFixedSize(buttonToMenuSize);
    m_toMenu->move(buttonToMenuPosition);
    addWidget(m_toMenu);
    connect(m_toMenu, &QPushButton::clicked, this, &AfterGameScene::toMenu);

    QSize buttonRestartGameSize{ 200, 70 };
    QPoint buttonRestartGamePosition{ 400, 400 };
    m_restartGame = new QPushButton("Play again");
    m_restartGame->setFixedSize(buttonRestartGameSize);
    m_restartGame->move(buttonRestartGamePosition);
    addWidget(m_restartGame);
    connect(m_restartGame, &QPushButton::clicked, this, &AfterGameScene::restartGame);
}

AfterGameScene::~AfterGameScene()
{
    delete m_image;
    delete m_score;
    delete m_toMenu;
    delete m_restartGame;
}

void AfterGameScene::setData(const int lives, const int score)
{
    if(m_image != nullptr)
    {
        delete m_image;
    }

    if(m_score != nullptr)
    {
        delete m_score;
    }

    m_score = new QLabel(QString("Score: %1").arg(score));

    if(lives < 0)
    {
        m_image = new QGraphicsPixmapItem(Resources::PATH_TO_LOOSE_IMAGE);
    }
    else
    {
        m_image = new QGraphicsPixmapItem(Resources::PATH_TO_WIN_IMAGE);
    }

    QPoint scorePosition { 250, 200};
    m_score->move(scorePosition);

    QPoint imagePosition { 0, -150};
    m_image->moveBy(imagePosition.x(),imagePosition.y());

    addItem(m_image);
    addWidget(m_score);
}
