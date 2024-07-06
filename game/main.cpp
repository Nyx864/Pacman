#include "view.h"
#include "resources.h"
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, Resources::BG_COLOR);
    darkPalette.setColor(QPalette::WindowText, Resources::FONT_COLOR);
    darkPalette.setColor(QPalette::Base, Resources::BASE_COLOR);
    app.setPalette(darkPalette);

    QFile styleSheetFile(Resources::PATH_TO_STYLE_SHEET);
    if(styleSheetFile.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        app.setStyleSheet(styleSheet);
    }

    View view;
    view.show();

    return app.exec();
}
