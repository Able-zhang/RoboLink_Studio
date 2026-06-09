#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../backend/BackendTypes.h"

namespace RoboLink {
class IHardwareBackend;
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onConnectClicked();
    void onDisconnectClicked();
    void onSendTestFrameClicked();
    void onClearLogClicked();

    void onConnectionChanged(bool connected);
    void onCANFrameReceived(const RoboLink::CANFrame& frame);
    void onLogMessage(const QString& message);
    void onErrorOccurred(const QString& error);

private:
    void appendLog(const QString& message);
    void updateUIState(bool connected);

private:
    Ui::MainWindow *ui;
    RoboLink::IHardwareBackend* m_backend = nullptr;
};
#endif // MAINWINDOW_H
