#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>

class Client : public QMainWindow {

public:
    Client(const QString &ip, quint16 port, QWidget *parent = nullptr);

private:
    QTcpSocket *socket;
};

#endif