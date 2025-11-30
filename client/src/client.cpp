#include "../include/client.h"
#include <QMessageBox>

Client::Client(const QString &ip, quint16 port, QWidget *parent)
    : QMainWindow(parent), socket(new QTcpSocket(this))
{
    // Attempt connection immediately
    socket->connectToHost(ip, port);

    if (!socket->waitForConnected(3000)) {
        QMessageBox::critical(this, "Connection Error",
                              "Failed to connect to server.");
    }
}
