#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QAbstractSocket>
class SocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit SocketHandler(const QString& host = "127.0.0.1", quint16 port = 10200, QObject* parent = nullptr);
    ~SocketHandler() override;
    QAbstractSocket::SocketState state() const;

    void connectToServer();
    void sendMessage(const QString& msg);

signals:
    void connected();
    void errorOccurred(const QString& errorString);
    void messageReceived(const QString& msg);
    void disconnected();

private slots:
    void onSocketConnected();
    void onSocketReadyRead();
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onSocketDisconnected();

private:
    QString m_host;
    quint16 m_port;
    QTcpSocket* m_socket = nullptr;
};

#endif // SOCKETHANDLER_H
