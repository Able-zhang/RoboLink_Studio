#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../backend/mock/MockBackend.h"
#include <QDateTime>
#include <QPushButton>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建MockBackend实例
    m_backend = new RoboLink::MockBackend(this);

    // 连接信号槽
    connect(ui->btnConnect, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(ui->btnDisconnect, &QPushButton::clicked, this, &MainWindow::onDisconnectClicked);
    connect(ui->btnSendTestFrame, &QPushButton::clicked, this, &MainWindow::onSendTestFrameClicked);
    connect(ui->btnClearLog, &QPushButton::clicked, this, &MainWindow::onClearLogClicked);

    // 连接后端信号
    connect(m_backend, &RoboLink::IHardwareBackend::connectionChanged,
            this, &MainWindow::onConnectionChanged);
    connect(m_backend, &RoboLink::IHardwareBackend::canFrameReceived,
            this, &MainWindow::onCANFrameReceived);
    connect(m_backend, &RoboLink::IHardwareBackend::logMessage,
            this, &MainWindow::onLogMessage);
    connect(m_backend, &RoboLink::IHardwareBackend::errorOccurred,
            this, &MainWindow::onErrorOccurred);

    // 显示后端信息
    auto info = m_backend->getBackendInfo();
    ui->labelBackendName->setText(QString("%1 v%2")
        .arg(RoboLink::backendTypeToString(info.type))
        .arg(info.version));

    appendLog("=== RoboLinkStudio 启动 ===");
    appendLog(QString("后端: %1").arg(info.name));
    appendLog(QString("版本: %1").arg(info.version));
    appendLog(QString("能力: %1").arg(info.capabilities.toString()));
    appendLog("准备就绪");
}

MainWindow::~MainWindow()
{
    if (m_backend && m_backend->isConnected()) {
        m_backend->disconnectBackend();
    }
    delete ui;
}

void MainWindow::onConnectClicked()
{
    appendLog("--- 开始连接后端 ---");
    auto error = m_backend->connectBackend();
    if (error.isError()) {
        appendLog(QString("错误: %1").arg(error.message));
    }
}

void MainWindow::onDisconnectClicked()
{
    appendLog("--- 断开后端连接 ---");
    m_backend->disconnectBackend();
}

void MainWindow::onSendTestFrameClicked()
{
    // 发送一个测试CAN帧
    RoboLink::CANFrame frame;
    frame.id = 0x200;
    frame.dlc = 8;
    frame.isExtended = false;

    // 填充测试数据
    for (int i = 0; i < 8; ++i) {
        frame.data[i] = 0x10 + i;
    }

    appendLog("--- 发送测试CAN帧 ---");
    auto error = m_backend->sendCANFrame(frame);
    if (error.isError()) {
        appendLog(QString("错误: %1").arg(error.message));
    }
}

void MainWindow::onClearLogClicked()
{
    ui->textEditLog->clear();
}

void MainWindow::onConnectionChanged(bool connected)
{
    updateUIState(connected);

    if (connected) {
        appendLog(">>> 后端已连接");
    } else {
        appendLog(">>> 后端已断开");
    }
}

void MainWindow::onCANFrameReceived(const RoboLink::CANFrame& frame)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    appendLog(QString("[%1] 接收CAN: %2").arg(timestamp).arg(frame.toString()));
}

void MainWindow::onLogMessage(const QString& message)
{
    appendLog(message);
}

void MainWindow::onErrorOccurred(const QString& error)
{
    appendLog(QString("!!! 错误: %1").arg(error));
}

void MainWindow::appendLog(const QString& message)
{
    ui->textEditLog->append(message);

    // 自动滚动到底部
    QTextCursor cursor = ui->textEditLog->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEditLog->setTextCursor(cursor);
}

void MainWindow::updateUIState(bool connected)
{
    ui->btnConnect->setEnabled(!connected);
    ui->btnDisconnect->setEnabled(connected);
    ui->btnSendTestFrame->setEnabled(connected);
}
