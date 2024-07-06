#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPushButton>

class MenuScene: public QGraphicsScene
{
    Q_OBJECT
public:
    MenuScene(QObject* parent = nullptr);

    ~MenuScene();

signals:
    void buttonPlayClicked();

    // void buttonSettingsClicked();

    void buttonCloseClicked();

private:
    QGraphicsPixmapItem* m_logo;

    QPushButton* m_play;

    // QPushButton* m_settings;

    QPushButton* m_close;
};

#endif // MENUSCENE_H
