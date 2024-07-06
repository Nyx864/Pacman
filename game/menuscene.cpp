#include "menuscene.h"

MenuScene::MenuScene(QObject* parent):
    QGraphicsScene(parent)
{
    QSize logoSize { 624, 250 };
    QPoint logoPosition { -logoSize.width()/2, 0};
    m_logo = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(":/res/resource/logo.png").scaled(logoSize)));
    m_logo->moveBy(logoPosition.x(), logoPosition.y());
    addItem(m_logo);

    QSize buttonPlaySize { 170, 45 };
    QPoint buttonPlayPosition { -buttonPlaySize.width()/2, 400};
    m_play = new QPushButton("PLAY");
    m_play->setFixedSize(buttonPlaySize);
    m_play->move(buttonPlayPosition);
    addWidget(m_play);
    connect(m_play, &QPushButton::clicked, this, &MenuScene::buttonPlayClicked);

    QSize buttonCloseSize { 170, 45 };
    QPoint buttonClosePosition { -buttonCloseSize.width()/2, 500};
    m_close = new QPushButton("close");
    m_close->setFixedSize(buttonCloseSize);
    m_close->move(buttonClosePosition);
    addWidget(m_close);
    connect(m_close, &QPushButton::clicked, this, &MenuScene::buttonCloseClicked);
}

MenuScene::~MenuScene()
{
    delete m_logo;
    delete m_play;
    // delete m_settings;
    delete m_close;
}
