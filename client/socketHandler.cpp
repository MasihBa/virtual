#include "sockethandler.h"
#include <QHostAddress>

SocketHandler::SocketHandler(const QString& host,
                             quint16 port,
                             QObject *parent): QObject(parent),m_host(host),m_port(port)
{
    m_socket = new QTcpSocket(this);
    disconnect(m_socket, &QTcpSocket::connected, nullptr, nullptr);
    connect(m_socket, &QTcpSocket::connected,this, &SocketHandler::onSocketConnected);
    disconnect(m_socket, &QTcpSocket::readyRead, nullptr, nullptr);
    connect(m_socket, &QTcpSocket::readyRead,this, &SocketHandler::onSocketReadyRead);
    disconnect(m_socket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred), nullptr, nullptr);
    connect(m_socket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),this, &SocketHandler::onSocketError);
    disconnect(m_socket, &QTcpSocket::disconnected, nullptr, nullptr);
    connect(m_socket, &QTcpSocket::disconnected,this, &SocketHandler::onSocketDisconnected);
}

SocketHandler::~SocketHandler(){}

void SocketHandler::connectToServer()
{
    m_socket->connectToHost(m_host, m_port);
}

void SocketHandler::sendMessage(const QString& msg)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write(msg.toUtf8());
        m_socket->flush();
    }
    else {
        connectToServer();
        connect(this, &SocketHandler::connected,this, [this, msg]() {m_socket->write(msg.toUtf8());m_socket->flush();},Qt::SingleShotConnection);
    }
}


void SocketHandler::onSocketConnected()
{
    emit connected();
}

void SocketHandler::onSocketReadyRead()
{
    const QByteArray data = m_socket->readAll();
    const QString msg    = QString::fromUtf8(data).trimmed();
    emit messageReceived(msg);
}

void SocketHandler::onSocketError(QAbstractSocket::SocketError /*err*/)
{
    emit errorOccurred(m_socket->errorString());
}

void SocketHandler::onSocketDisconnected()
{
    emit disconnected();
}

QAbstractSocket::SocketState SocketHandler::state() const
{
    return m_socket->state();
}
