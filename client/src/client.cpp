#include "../include/client.hpp"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

Client::Client(const std::string& ip, int port, QWidget *parent) : QMainWindow(parent) {
    sockfd = socket_create();
    if (sockfd < 0) {
        QMessageBox::critical(this, "Error", "Failed to create socket.");
        return;
    }

    if (!socket_connect(sockfd, ip.c_str(), port)) {
        QMessageBox::critical(this, "Error", "Failed to connect to server.");
        socket_close(sockfd);
        return;
    }

    // Start receiver thread
    recvThread = thread_create(Client::recv_loop, this);
    thread_detach(recvThread);

    //=======================================================
    // QT STRUCTURE
    //=======================================================
    resize(800, 600);

    // Central widget
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    // OUTER layout (handles centering)
    QVBoxLayout* outer = new QVBoxLayout(central);

    // push content toward center
    outer->addStretch(1);

    // INNER layout (your actual UI block)
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignCenter);

    // --- Site Label ---
    QLabel* label = new QLabel("SECURE CHATROOM");
    label->setObjectName("site-label");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    // --- Username input ---
    QLineEdit* usernameInput = new QLineEdit();
    usernameInput->setObjectName("username-input");
    usernameInput->setPlaceholderText("Enter username");
    usernameInput->setFixedWidth(300);
    layout->addWidget(usernameInput, 0, Qt::AlignCenter);

    // --- Connect button ---
    QPushButton* connectBtn = new QPushButton("Connect");
    connectBtn->setObjectName("connect-button");
    connectBtn->setFixedWidth(100);
    layout->addWidget(connectBtn, 0, Qt::AlignCenter);

    // Add your actual UI to outer layout
    outer->addLayout(layout);

    // push content toward center (bottom)
    outer->addStretch(1);
}

Client::~Client() {
    socket_close(sockfd);
    socket_cleanup();
}

// Loop to listen for server updates (mostly just messages)
void* Client::recv_loop(void* arg) {
    Client* self = (Client*)arg;

    char buffer[1024];

    while (true) {
        int bytes = socket_recv(self->sockfd, buffer, sizeof(buffer));

        if (bytes <= 0) {
            std::cout << "[CLIENT] Server disconnected\n";
            break;
        }

        buffer[bytes] = '\0';
        std::cout << "[SERVER] " << buffer << std::endl;

        // If needed, emit signals to update Qt UI
        // emit self->messageReceived(QString::fromUtf8(buffer));
    }

    return nullptr;
}
