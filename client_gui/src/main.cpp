#include <QApplication>
#include <QCoreApplication>
#include "../include/client.hpp"
#include "../include/themes.hpp"
#include <cstdlib>
#include <fstream>
#include <stdexcept>

void loadEnvFile(const std::string& path) {
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        return; // silently ignore if .env is missing
    }

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        setenv(key.c_str(), value.c_str(), 1);
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QString envPath = QCoreApplication::applicationDirPath() + "/.env";
    loadEnvFile(envPath.toStdString());

    const char* envIp = std::getenv("CCHAT_SERVER_IP");
    if (!envIp) {
        throw std::runtime_error("CCHAT_SERVER_IP not set");
    }

    std::string SERVER_IP(envIp);
    const int SERVER_PORT = 5000;

    QString initialStyle = MAIN_QSS + "\n";

    if (THEME_MAP.contains("dark"))
        initialStyle += THEME_MAP.value("dark");

    app.setStyleSheet(initialStyle);

    Client client(SERVER_IP, SERVER_PORT);

    return app.exec();
}
