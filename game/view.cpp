#include "view.h"

View::View()
    :QGraphicsView(),
    m_mainMenu { new MenuScene(this) },
    m_game { new GameScene(this) },
    m_afterGame{ new AfterGameScene() }
{
    setFixedSize(Resources::WINDOW_SIZE);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(m_mainMenu, &MenuScene::buttonPlayClicked, this, &View::openGame);
    connect(m_mainMenu, &MenuScene::buttonCloseClicked, this, &View::closeApp);

    connect(m_game, &GameScene::gameClosed, this, &View::openMainMenu);
    connect(m_game, &GameScene::gameOver, this, &View::gameOver);

    connect(m_afterGame, &AfterGameScene::toMenu, this, &View::openMainMenu);
    connect(m_afterGame, &AfterGameScene::restartGame, this, &View::openGame);
    setScene(m_mainMenu);
}

View::~View()
{
    delete m_mainMenu;
    delete m_game;
}

void View::openGame()
{
    setScene(m_game);
    m_game->start();
}

void View::openMainMenu()
{
    setScene(m_mainMenu);
}

void View::closeApp()
{
     QApplication::instance()->quit();
}

void View::gameOver(const int lives, const int score)
{
    if(m_game != nullptr)
    {
        delete m_game;
    }
    m_game = new GameScene;
    connect(m_game, &GameScene::gameClosed, this, &View::openMainMenu);
    connect(m_game, &GameScene::gameOver, this, &View::gameOver);

    m_afterGame->setData(lives,score);
    setScene(m_afterGame);
}
