#ifndef RESOURCES_H
#define RESOURCES_H

#include <QString>
#include <QPoint>
#include <QSize>
#include <QColor>
#include <QUrl>

class Resources
{
public:
    enum Direction
    {
        Up          = 1,
        Down        = -1,
        Left        = 2,
        Right       = -2,
        Unset       = 0
    };

    enum Tiles
    {
        Empty                   = 0,
        Wall                    = 1,
        SmallDot                = 2,
        BigDot                  = 3,
        PacmanStartPosition     = 4,
        BlinkyStartPosition     = 5,
        ClydeStartPosition      = 6,
        InkyStartPosition       = 7,
        PinkyStartPosition      = 8,
        Fruit                   = 9
    };

    constexpr static const QSize WINDOW_SIZE { 1200, 700 };
    constexpr static const QColor BG_COLOR { 0, 0, 0 };
    constexpr static const QColor FONT_COLOR { 255, 255, 255 };
    constexpr static const QColor BASE_COLOR { 0, 0, 0 };

    static const QString PATH_TO_MAP_PIXMAP;
    constexpr static const unsigned int MAP_TILE_SIZE { 27 };

    static const QString PATH_TO_ENTITY_PIXMAP;
    constexpr static const unsigned int ENTITY_TILE_SIZE { 32 };

    static const QString PATH_TO_FONT;

    constexpr static const unsigned int AMOUNT_OF_LIVES { 2 };
    constexpr static const unsigned int PACMAN_COUNT_ANIM_FRAMES { 5 };
    constexpr static const QPoint PACMAN_UP { 0, 0 };
    constexpr static const QPoint PACMAN_DOWN { 160, 0 } ;
    constexpr static const QPoint PACMAN_LEFT { 320, 0 };
    constexpr static const QPoint PACMAN_RIGHT { 480, 0 };
    constexpr static const float PACMAN_SPEED = 1.3f;
    constexpr static const int PACMAN_ANIM_SPEED = 125;

    constexpr static const unsigned int BLINKY_COUNT_ANIM_FRAMES { 2 };
    constexpr static const QPoint BLINKY_UP{ 0, 32 };
    constexpr static const QPoint BLINKY_DOWN { 64, 32 };
    constexpr static const QPoint BLINKY_LEFT { 128, 32 };
    constexpr static const QPoint BLINKY_RIGHT { 192, 32 };
    constexpr static const float BLINKY_SPEED = 1.35f;
    constexpr static const int BLINKY_ANIM_SPEED = 125;

    constexpr static const unsigned int PINKY_COUNT_ANIM_FRAMES { 2 };
    constexpr static const QPoint PINKY_UP { 0, 64 };
    constexpr static const QPoint PINKY_DOWN { 64, 64 };
    constexpr static const QPoint PINKY_LEFT { 128, 64 };
    constexpr static const QPoint PINKY_RIGHT { 192, 64 };
    constexpr static const float PINKY_SPEED = 1.35f;
    constexpr static const int PINKY_ANIM_SPEED = 125;

    constexpr static const unsigned int INKY_COUNT_ANIM_FRAMES { 2 };
    constexpr static const QPoint INKY_UP { 0, 96 };
    constexpr static const QPoint INKY_DOWN { 64, 96 };
    constexpr static const QPoint INKY_LEFT { 128, 96 };
    constexpr static const QPoint INKY_RIGHT { 192, 96 };
    constexpr static const float INKY_SPEED = 1.35f;
    constexpr static const int INKY_ANIM_SPEED = 125;

    constexpr static const unsigned int CLYDE_COUNT_ANIM_FRAMES { 2 };
    constexpr static const QPoint CLYDE_UP { 0, 128 };
    constexpr static const QPoint CLYDE_DOWN { 64, 128 };
    constexpr static const QPoint CLYDE_LEFT { 128, 128 };
    constexpr static const QPoint CLYDE_RIGHT { 192, 128 };
    constexpr static const float CLYDE_SPEED = 1.35f;
    constexpr static const int CLYDE_ANIM_SPEED = 125;

    constexpr static const unsigned int SCARED_GHOST_COUNT_ANIM_FRAMES { 2 };
    constexpr static const QPoint SCARED_GHOST { 256, 32 };

    constexpr static const unsigned int SCARED_GHOST_DURATION { 10000 };

    constexpr static const unsigned int DEAD_PACMAN_COUNT_ANIM_FRAMES { 12 };
    constexpr static const QPoint DEAD_PACMAN { 0, 160 };

    constexpr static const QPoint LIFE_PACKMAN { 576, 0 };

    constexpr static int FPS { 144 };

    constexpr static const QPoint STRAWBERRY { 256, 64 };
    constexpr static const QPoint CHERRY  { 256, 92 };
    constexpr static const QPoint ORANGE { 256, 128 };
    constexpr static int FRUITS_EXISTANCE_TIME { 9000 };
    constexpr static int COUNT_OF_FRUITS = 3;

    static const QUrl PACMAN_CHOMP_SFX;
    static const QUrl PACMAN_DEATH_SFX;
    static const QUrl PACMAN_EATFRUIT_SFX;
    static const QUrl PACMAN_EATGHOST_SFX;

    static const QString PATH_TO_STYLE_SHEET;

    static const QString PATH_TO_LOOSE_IMAGE;
    static const QString PATH_TO_WIN_IMAGE;
};




#endif // RESOURCES_H
