#include "ipgetter.h"
#include <QMessageBox>
#include <QDebug>

Ipgetter::Ipgetter(QLineEdit* ipLineEdit, QPushButton* connectButton, QObject *parent)
    : QObject(parent)
    , m_ipLineEdit(ipLineEdit)
    , m_connectButton(connectButton)
    , m_socketHandler(nullptr)
{
    if (m_connectButton) {
        connect(m_connectButton, &QPushButton::clicked,
                this, &Ipgetter::getId);
    }
}

Ipgetter::~Ipgetter()
{
    delete m_socketHandler;
    m_socketHandler = nullptr;
}

void Ipgetter::getId()
{
    if (!m_ipLineEdit)
        return;
    QString ipAddress = m_ipLineEdit->text().trimmed();

    if (ipAddress.isEmpty()) {
        QMessageBox::warning(nullptr, tr("Invalid IP"), tr("Please enter an IP address!"));
        return;
    }

    if (m_socketHandler) {
        disconnect(m_socketHandler, &SocketHandler::connected, this, &Ipgetter::onConnected);
        disconnect(m_socketHandler, &SocketHandler::messageReceived, this, &Ipgetter::onMessageReceived);
        disconnect(m_socketHandler, &SocketHandler::errorOccurred, this, &Ipgetter::onErrorOccurred);
        disconnect(m_socketHandler, &SocketHandler::disconnected, this, &Ipgetter::onDisconnected);
        delete m_socketHandler;
        m_socketHandler = nullptr;
    }

    m_socketHandler = new SocketHandler(ipAddress, 1234, this);
    qDebug() << "Attempting to connect to IP:" << ipAddress << "Port:" << 1234;
    connect(m_socketHandler, &SocketHandler::connected,      this, &Ipgetter::onConnected);
    connect(m_socketHandler, &SocketHandler::messageReceived,this, &Ipgetter::onMessageReceived);
    connect(m_socketHandler, &SocketHandler::errorOccurred,  this, &Ipgetter::onErrorOccurred);
    connect(m_socketHandler, &SocketHandler::disconnected,   this, &Ipgetter::onDisconnected);
    m_socketHandler->connectToServer();
}

void Ipgetter::onConnected()
{
    QMessageBox::information(nullptr, tr("Successful connection"), tr("Server was connected."));
    qDebug() << "Socket connected.";
    emit socketReady(m_socketHandler);
}

void Ipgetter::onMessageReceived(const QString& msg)
{
    QMessageBox::information(nullptr, tr("Message from server"), tr("Received:\n%1").arg(msg));
    qDebug() << "Message received:" << msg;
}

void Ipgetter::onErrorOccurred(const QString& errorString)
{
    QMessageBox::critical(nullptr, tr("Network error"), errorString);
    qDebug() << "Socket error:" << errorString;
}

void Ipgetter::onDisconnected()
{
    QMessageBox::information(nullptr, tr("Connection error"), tr("Disconnected from server."));
    qDebug() << "Socket disconnected.";
}
