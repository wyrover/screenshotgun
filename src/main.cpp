#include <QApplication>
#include "App.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setOrganizationName("Screenshotgun");
    app.setOrganizationDomain("screenshotgun.com");
    app.setApplicationName("Screenshotgun");

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString style = QLatin1String(file.readAll());
    file.close();

    app.setQuitOnLastWindowClosed(false);
    app.setStyleSheet(style);

    App application;
    return app.exec();
}
