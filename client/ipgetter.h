// IPGETTER_H
#ifndef IPGETTER_H
#define IPGETTER_H

#include <QObject>
#include <QLineEdit>
#include <QPushButton>
#include "sockethandler.h"

class Ipgetter : public QObject
{
    Q_OBJECT

signals:
    void socketReady(SocketHandler* handler);

public:
    explicit Ipgetter(QLineEdit* ipLineEdit, QPushButton* connectButton, QObject *parent = nullptr);
    ~Ipgetter() override;

public slots:
    void getId();

private slots:
    void onConnected();
    void onMessageReceived(const QString& msg);
    void onErrorOccurred(const QString& errorString);
    void onDisconnected();

private:
    QLineEdit* m_ipLineEdit = nullptr;
    QPushButton* m_connectButton = nullptr;
    SocketHandler* m_socketHandler = nullptr;
};

#endif // IPGETTER_H
