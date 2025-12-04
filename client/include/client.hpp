#include <iostream>
#include <string>

#include <QMainWindow>
#include <QStackedWidget>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "../../common/include/socket_handler.hpp"
#include "../../common/include/thread_handler.hpp"

class Client : public QMainWindow {

public:
    Client(const std::string& ip, int port, QWidget *parent = nullptr);
    ~Client();

private:
    SocketType sockfd;
    ThreadType recvThread;

    static void* recv_loop(void* arg);  // background thread for receiving server updates

    QStackedWidget* stack;
    QWidget* loginScreen;
    QWidget* chatScreen;
    QWidget* shopScreen;
};
