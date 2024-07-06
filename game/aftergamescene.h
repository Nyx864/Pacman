#ifndef AFTERGAMESCENE_H
#define AFTERGAMESCENE_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QLabel>
#include <QFont>

class AfterGameScene: public QGraphicsScene
{
    Q_OBJECT
public:
    AfterGameScene();

    ~AfterGameScene();

public slots:
    void setData(const int lives, const int score);

signals:
    void toMenu();

    void restartGame();

private:
    QGraphicsPixmapItem* m_image;

    QLabel* m_score;

    QPushButton* m_toMenu;

    QPushButton* m_restartGame;
};

#endif // AFTERGAMESCENE_H
