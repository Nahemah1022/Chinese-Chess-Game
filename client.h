#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString ipAddress = "127.0.0.1" ,unsigned short ipPort = 1234, QObject *parent = nullptr);
    void writeOutData(int data[9][10][2]);
    int status[9][10][2];

signals:
    void dataRecieved();

public slots:
    void print();
    void P2LinkStart();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
