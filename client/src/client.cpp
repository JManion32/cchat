#include "../include/client.hpp"

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

    resize(800, 600);

    loginScreen = buildLoginScreen();
    chatScreen  = buildChatScreen();
    shopScreen  = buildShopScreen();

    stack->addWidget(loginScreen);
    stack->addWidget(chatScreen);
    stack->addWidget(shopScreen);

    setCentralWidget(stack);

    show(); // show the GUI
}

Client::~Client() {
    socket_close(sockfd);
}

// Receive updates from the server
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

//===================================
// Login Screen
//===================================
QWidget* Client::buildLoginScreen() {
    QWidget* loginScreen = new QWidget();

    QVBoxLayout* outer = new QVBoxLayout(loginScreen);
    outer->addStretch(1);

    QVBoxLayout* loginLayout = new QVBoxLayout();
    loginLayout->setAlignment(Qt::AlignCenter);

    QLabel* label = new QLabel("SECURE CHATROOM");
    label->setObjectName("site-label");
    label->setAlignment(Qt::AlignCenter);

    QLineEdit* usernameInput = new QLineEdit();
    usernameInput->setObjectName("username-input");
    usernameInput->setPlaceholderText("Enter username");
    usernameInput->setFixedWidth(300);

    QPushButton* connectButton = new QPushButton("Connect");
    connectButton->setObjectName("connect-button");
    connectButton->setFixedWidth(100);
    connect(connectButton, &QPushButton::clicked, [this]() {
        stack->setCurrentIndex(1);
    });

    loginLayout->addWidget(label);
    loginLayout->addWidget(usernameInput, 0, Qt::AlignCenter);
    loginLayout->addWidget(connectButton, 0, Qt::AlignCenter);

    outer->addLayout(loginLayout);
    outer->addStretch(1);

    return loginScreen;
}

//===================================
// Chatroom Screen
//===================================
QWidget* Client::buildChatScreen() {
    QWidget* chatScreen = new QWidget();

    QVBoxLayout* outer = new QVBoxLayout(chatScreen);
    outer->addStretch(1);

    QVBoxLayout* chatLayout = new QVBoxLayout();

    QHBoxLayout* messageNav = new QHBoxLayout();
    QLabel* nameLabel = new QLabel("Justin");
    nameLabel->setObjectName("name-label");
    messageNav->addWidget(nameLabel);

    QPushButton* shopButton = new QPushButton("Theme Shop");
    shopButton->setObjectName("shop-button");
    shopButton->setFixedWidth(100);
    connect(shopButton, &QPushButton::clicked, [this]() {
        stack->setCurrentIndex(2);
    });
    messageNav->addWidget(shopButton);

    QVBoxLayout* messageDisplay = new QVBoxLayout();
    messageDisplay->setAlignment(Qt::AlignCenter);

    QHBoxLayout* messageType = new QHBoxLayout();
    messageType->setAlignment(Qt::AlignCenter);

    chatLayout->addLayout(messageNav);
    chatLayout->addLayout(messageDisplay);
    chatLayout->addLayout(messageType);

    outer->addLayout(chatLayout);
    outer->addStretch(1);

    return chatScreen;
}

//===================================
// Theme Shop Screen
//===================================
QWidget* Client::buildShopScreen() {
    QWidget* shopScreen = new QWidget();

    QVBoxLayout* outer = new QVBoxLayout(shopScreen);
    outer->addStretch(1);

    QVBoxLayout* shopLayout = new QVBoxLayout();

    QHBoxLayout* shopNav = new QHBoxLayout();
    QPushButton* returnButton = new QPushButton("Return");
    returnButton->setObjectName("return-button");
    returnButton->setFixedWidth(100);
    connect(returnButton, &QPushButton::clicked, [this]() {
        stack->setCurrentIndex(1);
    });
    shopNav->addWidget(returnButton);
    QLabel* creditLabel = new QLabel("Credits: 100");
    creditLabel->setObjectName("credit-label");
    shopNav->addWidget(creditLabel);

    QVBoxLayout* shopDisplay = new QVBoxLayout();
    shopDisplay->setAlignment(Qt::AlignCenter);

    shopLayout->addLayout(shopNav);
    shopLayout->addLayout(shopDisplay);

    outer->addLayout(shopLayout);
    outer->addStretch(1);

    return shopScreen;
}