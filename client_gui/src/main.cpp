#include "../include/client.hpp"
#include "../include/themes.hpp"
#include <QApplication>
#include <QCoreApplication>
#include <cstdlib>
#include <fstream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    if (argc != 3)
    {
        qCritical() << "Usage:" << argv[0] << "<server-ip> <server-port>";
        return EXIT_FAILURE;
    }

    const std::string SERVER_IP = argv[1];

    bool ok = false;
    const int SERVER_PORT = QString(argv[2]).toInt(&ok);

    if (!ok || SERVER_PORT <= 0 || SERVER_PORT > 65535)
    {
        qCritical() << "Invalid server port:" << argv[2];
        return EXIT_FAILURE;
    }

    QString initialStyle = MAIN_QSS + "\n";

    if (THEME_MAP.contains("dark"))
    {
        initialStyle += THEME_MAP.value("dark");
    }

    app.setStyleSheet(initialStyle);

    Client client(SERVER_IP, SERVER_PORT);

    return app.exec();
}
