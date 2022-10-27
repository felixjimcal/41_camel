#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setupSecureSocket();
  secureConnect();
  sendData();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::secureConnect() {
  // socket->connectToHostEncrypted("eu.datapublisher.alkamelcloud.com", 11001);
    socket->connectToHostEncrypted("gmail.com", 443);
  if (socket->waitForConnected()) {
    qDebug() << "Connected!";
  } else {
    qDebug() << "NOPE";
  }
}

void MainWindow::sendData() {
  socket->waitForBytesWritten(1000);
  const QString input = "LOGIN:::{}";
  socket->write(input.toUtf8() + "\r\n");

  socket->waitForReadyRead(3000);
}

void MainWindow::socketReadyRead() {
  appendString(QString::fromUtf8(socket->readAll()));
}

void MainWindow::setupSecureSocket() {
  if (socket)
    return;

  socket = new QSslSocket(this);
  socket->ignoreSslErrors();

  /*
  QSslConfiguration sslConfig = socket->sslConfiguration();
  sslConfig.setSslOption(QSsl::SslOptionDisableSessionTickets, true);
  sslConfig.setProtocol(QSsl::AnyProtocol);
  socket->setSslConfiguration(sslConfig);
  */
  connect(socket, &QSslSocket::readyRead, this, &MainWindow::socketReadyRead);
}

void MainWindow::appendString(const QString &line) {
  qDebug() << "Message: \n" << line;
}
