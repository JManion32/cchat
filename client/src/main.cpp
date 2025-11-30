// Establish a connection to the server
// Initialize the GUI

#include <QApplication>
#include "client.h"   // your client logic class

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Hardcode the server IP + port for now
    const QString SERVER_IP = "165.227.182.111";
    const quint16 SERVER_PORT = 5000;

    Client client(SERVER_IP, SERVER_PORT);
    client.show();   // show the main window

    return app.exec();
}
