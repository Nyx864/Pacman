#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QApplication>
#include "menuscene.h"
#include "gamescene.h"
#include "aftergamescene.h"

class View: public QGraphicsView
{
    Q_OBJECT
public:
    View();

    ~View();

public slots:
    void openGame();

    void openMainMenu();

    void closeApp();

    void gameOver(const int lives, const int score);

private:
    MenuScene* m_mainMenu;

    GameScene* m_game;

    AfterGameScene* m_afterGame;
};

#endif // VIEW_H
