#include "server.h"

myServer::myServer(unsigned short ipPort, QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(onnewConnection()));

    this->ipPort = ipPort;
    if(!server->listen(QHostAddress::Any, ipPort)){
        qDebug() << "Server could not start";
    }
    else {
        qDebug() << "Server start";
    }
}

void myServer::writeOutData(int data[9][10][2])
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
    socket->flush();

}

void myServer::onnewConnection()
{
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(print()));
    qDebug() << "Connected!";
}

void myServer::print()
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
