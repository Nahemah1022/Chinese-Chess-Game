#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

class myServer : public QObject
{
    Q_OBJECT
public:
    explicit myServer(unsigned short ipPort = 1234, QObject *parent = nullptr);
    void writeOutData(int data[9][10][2]);
    int status[9][10][2];
    unsigned short ipPort;
    QTcpServer *server;

signals:
    void dataRecieved();
    void Connected();

public slots:
    void onnewConnection();
    void print();

private:
    QTcpSocket *socket;
};

#endif // SERVER_H
