#include "tearserver.h"
#include "ui_tearserver.h"

static TearServer* tearInstance;

TearServer::TearServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TearServer)
{
    //Set up the GUI first
    ui->setupUi(this);

    connect(ui->quitBtn,SIGNAL(released()),SLOT(close()));

    //Initialize logging
    tearInstance = this;
    qInstallMessageHandler(&defaultMessageHandler);

    QJsonDocument doc;
    QFile docdat("test-config.json");
    docdat.open(QIODevice::ReadOnly);
    doc = QJsonDocument::fromJson(docdat.readAll());

    initInputHandler(doc.object().toVariantMap());

    QThread *capthread = new QThread(this);
    screencap = new TearScreenCapture(0);
    screencap->moveToThread(capthread);
    connect(capthread,SIGNAL(started()),screencap,SLOT(run()),Qt::QueuedConnection);
    connect(capthread,SIGNAL(finished()),screencap,SLOT(deleteLater()),Qt::QueuedConnection);
    capthread->start();

    connect(this,SIGNAL(startScreencap()),screencap,SLOT(start()),Qt::QueuedConnection);
    connect(this,SIGNAL(stopScreencap()),screencap,SLOT(stop()),Qt::QueuedConnection);

    //Initialize networking
    netman = new TearNetworkManager(this);
    netman->setInterface(QNetworkInterface::interfaceFromName("eth0"));

    qDebug("Main thread: %p",this->thread());
    qDebug("Network interface: %s",netman->getInterface().humanReadableName().toStdString().c_str());

    connect(netman,&TearNetworkManager::newConnection,[=](TearTCPSocket* socket,QHostAddress host,quint16 port){
        if(port==inputPort){
            socket->sendData(TearClientHandler::generateWelcomePacket(socket->getLocalAddress().toString(),avPort));
            connect(socket,&TearTCPSocket::packetReceived,[=](QByteArray* data){
                QVariantMap d = QJsonDocument::fromJson(*data).object().toVariantMap();
                switch(d.value("t").toInt()){
                case StreamerSharedProperties::SD_InputSignal:{
                    QVariantList i = d.value("v").toList();
                    if(i.size()!=3)
                        break;
                    inputHandler->interpretSignalDirect(
                                i.at(0).toInt(),
                                i.at(1).toLongLong(),
                                i.at(2).toLongLong());
                    break;
                }
                }
            });
        }else if(port==avPort){
            socket->setParent(0);
            socket->moveToThread(capthread);
            connect(screencap,SIGNAL(newFrame(QByteArray*)),socket,SLOT(sendData(QByteArray*)));
            qDebug() << "Starting screen capturing";
            startScreencap();
            connect(socket,&TearTCPSocket::socketClosing,[=](){
                qDebug() << "Stopping screen capturing";
                stopScreencap();
            });
        }
    });

    netman->registerNewListeningPort(inputPort);
    netman->registerNewListeningPort(avPort);

    //The basics on using a TearTCPSocket, not much more than this
//    netman->registerNewConnection(&test,QHostAddress("127.0.0.1"),46600);
//    connect(test,&TearTCPSocket::packetReceived,[=](QByteArray* data){
//        qDebug() << *data;
//        delete data;
//    });
//    test->socketConnect();
}

TearServer::~TearServer()
{
    delete ui;
}

void TearServer::appendLog(const QString &message)
{
    ui->logView->appendPlainText(message);
}

void TearServer::defaultMessageHandler(QtMsgType t, const QMessageLogContext &context, const QString &msg)
{
    QByteArray m_msg = msg.toLocal8Bit();
    QString out;
    switch(t){
    case QtDebugMsg:
        out = QString("DEBUG:%1:%2: %3")
                .arg(context.function)
                .arg(context.line)
                .arg(m_msg.constData());
        break;
    case QtWarningMsg:
        out = QString("WARN:%1:%2: %3")
                .arg(context.function)
                .arg(context.line)
                .arg(m_msg.constData());
        break;
    case QtCriticalMsg:
        out = QString("CRITICAL:%1:%2: %3")
                .arg(context.function)
                .arg(context.line)
                .arg(m_msg.constData());
        break;
    case QtFatalMsg:
        out = QString("FATAL:%1:%2: %3")
                .arg(context.function)
                .arg(context.line)
                .arg(m_msg.constData());
        break;
    default:
        out = QString("????:%1:%2: %3")
                .arg(context.function)
                .arg(context.line)
                .arg(m_msg.constData());
    }
    tearInstance->appendLog(out);
    fprintf(stderr,"%s\n",out.toStdString().c_str());
}

void TearServer::on_disconnectBtn_clicked()
{
    stopScreencap();
}

void TearServer::initInputHandler(QVariantMap data)
{
    inputHandler = new TearInputHandler(this);
    for(QString key : data.keys()){
        if(key=="input-handlers")
            for(QVariant el : data.value(key).toList()){
                InputHandlerObjectInterface* handler = TearInputHandler::loadInputHandler(
                            el.toMap().value("library").toString(),inputHandler);
                for(QVariant map : el.toMap().value("mapping").toList()){
                    if(map.type()==QVariant::String&&map.toString()=="default-mouse")
                        inputHandler->setMouseMapping(handler);
                    else if(map.type()==QVariant::String&&map.toString()=="default-keyboard")
                        inputHandler->setKeyboardMapping(handler);
                }
            }
    }
}
