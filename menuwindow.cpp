#include "menuwindow.h"
#include "ui_menuwindow.h"

Menuwindow *Menuwindow::me;
MainWindow *Menuwindow::battleWindow;

Menuwindow::Menuwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menuwindow)
{
    ui->setupUi(this);
    Menuwindow::me = this;
    ui->comboBox->setEditable(false);
    loadExistingFiles();
}

Menuwindow::~Menuwindow()
{
    delete ui;
}

void Menuwindow::on_startButton_clicked()
{
    hide();
    battleWindow = new MainWindow(this);
    //battleWindow->server = nullptr
    MainWindow::turn = false;
    battleWindow->changeTurn();
    connect(battleWindow, SIGNAL(ending()), this, SLOT(returnToMenu()));
    connect(battleWindow, SIGNAL(save()), this, SLOT(saveFiles()));
    battleWindow->show();
}

void Menuwindow::on_editorButton_clicked()
{
    hide();
    editorWindow = new EditorWIndow(this);
    connect(editorWindow, SIGNAL(endingEdit()), this, SLOT(returnToMenu()));
    editorWindow->show();
}

void Menuwindow::returnToMenu()
{
    show();
}

void Menuwindow::saveFiles()
{
    QDir dir;
    if(!dir.exists("savefiles")){
        dir.mkdir("savefiles");
    }
    QString filepath = "savefiles/" + QDateTime::currentDateTime().toString();
    QFile *f = new QFile(filepath);
    f->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(f);
    int i, j;
    for(i=0; i<9; ++i){
        for(j=0; j<9; ++j){
            out << QString::number(MainWindow::lastStepNum[i][j][0]) << " ";
        }
        out << QString::number(MainWindow::lastStepNum[i][j][0]) << endl;
    }
    for(i=0; i<9; ++i){
        for(j=0; j<9; ++j){
            out << QString::number(MainWindow::lastStepNum[i][j][1]) << " ";
        }
        out << QString::number(MainWindow::lastStepNum[i][j][1]) << endl;
    }
    out << MainWindow::turn;

    files.push_back(f);
    f->close();
    battleWindow->hide();
    loadExistingFiles();
    show();
}

void Menuwindow::on_loadButton_clicked()
{
    if(files.size() == 0){
        return ;
    }
    QFile *in = files.at(ui->comboBox->currentIndex());
    in->open(QIODevice::ReadOnly);
    QTextStream sin(in);
    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            sin >> posToLoad[i][j][0];
        }
    }

    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            sin >> posToLoad[i][j][1];
        }
    }
    sin >> turnToLoad;

    in->close();
    hide();
    battleWindow = new MainWindow(posToLoad, turnToLoad);
    battleWindow->show();
    connect(battleWindow, SIGNAL(ending()), this, SLOT(returnToMenu()));
    connect(battleWindow, SIGNAL(save()), this, SLOT(saveFiles()));
}

void Menuwindow::on_loadButton_2_clicked()
{
    if(files.size() > 0){
        files.at(ui->comboBox->currentIndex())->remove();
        loadExistingFiles();
    }
}

void Menuwindow::loadExistingFiles()
{
    ui->comboBox->clear();
    files.clear();
    QDir dir("savefiles/");
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    for(int i=0; i<file_list.size(); ++i){
        QFileInfo fileInfo = file_list.at(i);
        files.push_back(new QFile(fileInfo.filePath()));
        ui->comboBox->addItem(fileInfo.fileName());
    }
}

void Menuwindow::on_OnlineButton_clicked()
{
    onlineWidget = new QWidget(this);
    onlineWidget->setGeometry(0, 0, this->geometry().width(), this->geometry().height());
    onlineWidget->show();
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    play_1 = new QPushButton(onlineWidget);
    play_1->setGeometry(20, 20, 115, 50);
    play_1->setText("Player 1");
    play_1->setFont(font);
    play_1->show();
    play_2 = new QPushButton(onlineWidget);
    play_2->setGeometry(150, 20, 115, 50);
    play_2->setText("Player 2");
    play_2->setFont(font);
    play_2->show();
    sendButton = new QPushButton(onlineWidget);
    sendButton->setGeometry(197, 265, 80, 30);
    sendButton->show();
    sendButton->setEnabled(false);
    sendButton->setText("Send");
    sendButton->setFont(font);
    quitButton = new QPushButton(onlineWidget);
    quitButton->setGeometry(197, 300, 80, 30);
    quitButton->setText("Quit");
    quitButton->setFont(font);
    quitButton->show();
    connect(quitButton, SIGNAL(clicked()), this, SLOT(onlineQuit()));
    connect(play_1, SIGNAL(clicked()), this, SLOT(showPlayer_1Detail()));
    connect(play_2, SIGNAL(clicked()), this, SLOT(showPlayer_2Detail()));
}

void Menuwindow::play_1Pressed()
{
    p1Window = new MainWindow(this);
    p1Window->server = new myServer((unsigned short)ipPort->text().toInt(), p1Window);
    connect(p1Window->server->server, SIGNAL(newConnection()), this, SLOT(play_1LinkStart()));
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeCount()));
    timer->start(1000);
    detail->setText("waiting for connection...\n");
    sendButton->setEnabled(false);
    play_2->setEnabled(false);
    ipAddress->setEnabled(false);
    ipPort->setEnabled(false);
}

void Menuwindow::play_1LinkStart()
{
    connect(p1Window->server, SIGNAL(dataRecieved()), p1Window, SLOT(restatusByData()));
    hide();
    p1Window->show();
    p1Window->resetButton->setEnabled(false);

}

void Menuwindow::timeCount()
{
    if(count < 10){
        detail->setText(detail->text() + ".");
        count++;
    }
    else{
        count = 0;
        detail->setText("waiting for connection...\n");
    }
}

void Menuwindow::onlineQuit()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(timeCount()));
    delete onlineWidget;
}

void Menuwindow::play_2Pressed()
{
    hide();
    p2Window = new MainWindow(this);
    QString ip = ipAddress->text();
    p2Window->client = new Client(ip, (unsigned short)ipPort->text().toInt() ,p2Window);
    connect(p2Window->client, SIGNAL(dataRecieved()), p2Window, SLOT(restatusByData()));
    p2Window->show();
    p2Window->resetButton->setEnabled(false);
}

void Menuwindow::showPlayer_1Detail()
{
    if(!ipAddress)
        delete ipAddress;
    if(!ipPort)
        delete ipPort;
    sendButton->setEnabled(true);
    play_1->setEnabled(false);
    play_2->setEnabled(true);
    QLabel *label = new QLabel(onlineWidget);
    label->setGeometry(10, 90, label->width()+50, label->height()+15);
    label->setText("Player 1 : ");
    label->show();
    QFont font;
    font.setPointSize(28);
    font.setItalic(true);
    label->setFont(font);
    ipAddress = new QLineEdit(onlineWidget);
    ipAddress->setGeometry(190, 150, ipAddress->width()-20, ipAddress->height());
    ipAddress->show();
    QLabel *ipAddressLabel = new QLabel(onlineWidget);
    ipAddressLabel->setGeometry(20, 140, label->width()+20, label->height());
    ipAddressLabel->setText("your IP address : ");
    ipAddressLabel->show();
    font.setPointSize(15);
    ipAddressLabel->setFont(font);
    QLabel *ipPortLabel = new QLabel(onlineWidget);
    ipPortLabel->setGeometry(20, 180, label->width()+20, label->height());
    ipPortLabel->setText("please take a port : ");
    ipPortLabel->show();
    font.setPointSize(15);
    ipPortLabel->setFont(font);
    ipPort = new QLineEdit(onlineWidget);
    ipPort->setGeometry(195, 190, 75, ipAddress->height());
    ipPort->show();
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            ipAddress->setText(address.toString());
    }
    detail = new QLabel(onlineWidget);
    detail->setGeometry(20, 270, detail->width()+150, detail->height()+20);
    detail->setText("send your data to\nwait for challenger");
    detail->show();
    sendButton->raise();
    font.setPointSize(15);
    font.setItalic(false);
    detail->setFont(font);
    QLabel *border = new QLabel(onlineWidget);
    border->setGeometry(5, 80, 272, 170);
    border->setStyleSheet("QLabel{border:3px solid}");
    border->lower();
    border->show();
    quitButton->raise();
    disconnect(sendButton, SIGNAL(clicked()), this, SLOT(play_2Pressed()));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(play_1Pressed()));
}

void Menuwindow::showPlayer_2Detail()
{
    if(!ipAddress)
        delete ipAddress;
    if(!ipPort)
        delete ipPort;
    sendButton->setEnabled(true);
    play_1->setEnabled(true);
    play_2->setEnabled(false);
    QLabel *label = new QLabel(onlineWidget);
    label->setGeometry(10, 90, label->width()+50, label->height()+15);
    label->setText("Player 2 : ");
    label->show();
    QFont font;
    font.setPointSize(28);
    font.setItalic(true);
    label->setFont(font);
    ipAddress = new QLineEdit(onlineWidget);
    ipAddress->setReadOnly(false);
    ipAddress->setGeometry(190, 150, ipAddress->width()-20, ipAddress->height());
    ipAddress->show();
    QLabel *ipAddressLabel = new QLabel(onlineWidget);
    ipAddressLabel->setGeometry(20, 140, label->width()+10, label->height());
    ipAddressLabel->setText("Player1 IP address : ");
    ipAddressLabel->show();
    font.setPointSize(15);
    ipAddressLabel->setFont(font);
    QLabel *ipPortLabel = new QLabel(onlineWidget);
    ipPortLabel->setGeometry(20, 180, label->width()+20, label->height());
    ipPortLabel->setText("please take a port : ");
    ipPortLabel->show();
    font.setPointSize(15);
    ipPortLabel->setFont(font);
    ipPort = new QLineEdit(onlineWidget);
    ipPort->setGeometry(195, 190, 75, ipAddress->height());
    ipPort->show();
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            ipAddress->setText(address.toString());
    }
    detail = new QLabel(onlineWidget);
    detail->setGeometry(20, 270, detail->width()+150, detail->height()+20);
    detail->setText("send your data to \nchallenge Player1");
    detail->show();
    sendButton->raise();
    font.setPointSize(15);
    font.setItalic(false);
    detail->setFont(font);
    QLabel *border = new QLabel(onlineWidget);
    border->setGeometry(5, 80, 272, 170);
    border->setStyleSheet("QLabel{border:3px solid}");
    border->lower();
    quitButton->raise();
    border->show();
    disconnect(sendButton, SIGNAL(clicked()), this, SLOT(play_1Pressed()));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(play_2Pressed()));
}


