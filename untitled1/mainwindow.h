#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void secureConnect();

  void socketReadyRead();
  void sendData();

private:
  Ui::MainWindow *ui;
  void setupSecureSocket();
  void appendString(const QString &line);

  QSslSocket *socket = nullptr;
};
#endif // MAINWINDOW_H
