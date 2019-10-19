#include "client.h"

Client::Client(QString ipAddress, unsigned short ipPort, QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(print()));
    socket->connectToHost(ipAddress, ipPort);
}

void Client::writeOutData(int data[9][10][2])
{
    QByteArray dataArray;
    QDataStream stream(&dataArray, QIODevice::WriteOnly);

    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            stream << data[i][j][0];
        }
    }
    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            stream << data[i][j][1];
        }
    }

    socket->write(dataArray);
    //socket->flush();
}

void Client::print()
{
    QByteArray arr = socket->readAll();
    QDataStream stream(&arr, QIODevice::ReadOnly);
    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            stream >> status[i][j][0];
        }
    }
    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            stream >> status[i][j][1];
        }
    }
    emit dataRecieved();
}

void Client::P2LinkStart()
{
    qDebug() << "linking";
}
