#include "MockBackend.h"
#include <QDateTime>

namespace RoboLink {

MockBackend::MockBackend(QObject* parent)
    : IHardwareBackend(parent)
    , m_mockTimer(new QTimer(this))
{
    // 配置模拟定时器，每100ms产生一个模拟CAN帧
    m_mockTimer->setInterval(100);
    connect(m_mockTimer, &QTimer::timeout, this, &MockBackend::generateMockCANFrame);
}

MockBackend::~MockBackend()
{
    disconnectBackend();
}

BackendInfo MockBackend::getBackendInfo() const
{
    BackendInfo info;
    info.type = BackendType::Mock;
    info.name = "Mock Backend";
    info.version = "1.0.0";
    info.description = "模拟后端，用于测试和开发";

    info.capabilities.supportsCAN = true;
    info.capabilities.supportsRS485 = true;
    info.capabilities.supportsDeviceInfo = false;
    info.capabilities.supportsFirmwareUpgrade = false;
    info.capabilities.supportsCANFilter = false;

    return info;
}

BackendError MockBackend::connectBackend()
{
    if (m_connected) {
        return BackendError::error(1, "Already connected");
    }

    emit logMessage("MockBackend: 正在连接...");

    m_connected = true;
    m_frameCounter = 0;

    // 启动模拟数据生成
    m_mockTimer->start();

    emit logMessage("MockBackend: 连接成功");
    emit connectionChanged(true);

    return BackendError::success();
}

void MockBackend::disconnectBackend()
{
    if (!m_connected) {
        return;
    }

    emit logMessage("MockBackend: 正在断开连接...");

    // 停止模拟数据生成
    m_mockTimer->stop();

    m_connected = false;

    emit logMessage("MockBackend: 已断开连接");
    emit connectionChanged(false);
}

bool MockBackend::isConnected() const
{
    return m_connected;
}

BackendCapabilities MockBackend::capabilities() const
{
    return getBackendInfo().capabilities;
}

BackendError MockBackend::configureCAN(const CANChannelConfig& config)
{
    if (!m_connected) {
        return BackendError::error(2, "Not connected");
    }

    m_canConfig = config;
    emit logMessage(QString("MockBackend: CAN配置 - %1").arg(config.toString()));

    return BackendError::success();
}

BackendError MockBackend::sendCANFrame(const CANFrame& frame)
{
    if (!m_connected) {
        return BackendError::error(2, "Not connected");
    }

    emit logMessage(QString("MockBackend: 发送CAN帧 - %1").arg(frame.toString()));

    // 模拟回环：发送后也会收到该帧（延迟10ms）
    if (m_canConfig.loopback) {
        QTimer::singleShot(10, this, [this, frame]() {
            CANFrame loopbackFrame = frame;
            loopbackFrame.timestamp = QDateTime::currentMSecsSinceEpoch();
            emit canFrameReceived(loopbackFrame);
        });
    }

    return BackendError::success();
}

BackendError MockBackend::configureRS485(const RS485Config& config)
{
    if (!m_connected) {
        return BackendError::error(2, "Not connected");
    }

    m_rs485Config = config;
    emit logMessage(QString("MockBackend: RS485配置 - %1").arg(config.toString()));

    return BackendError::success();
}

BackendError MockBackend::sendRS485Data(const QByteArray& data)
{
    if (!m_connected) {
        return BackendError::error(2, "Not connected");
    }

    QString hexStr = data.toHex(' ').toUpper();
    emit logMessage(QString("MockBackend: 发送RS485数据 - [%1]").arg(hexStr));

    return BackendError::success();
}

void MockBackend::generateMockCANFrame()
{
    if (!m_connected) {
        return;
    }

    // 生成模拟CAN帧
    CANFrame frame;

    // 模拟电机反馈帧（ID: 0x201-0x204）
    static int motorId = 1;
    frame.id = 0x200 + motorId;
    frame.dlc = 8;
    frame.isExtended = false;
    frame.timestamp = QDateTime::currentMSecsSinceEpoch();

    // 模拟数据：角度、速度、电流、温度
    uint16_t angle = (m_frameCounter * 100) % 8192;  // 0-8191
    int16_t velocity = QRandomGenerator::global()->bounded(-3000, 3000);
    int16_t current = QRandomGenerator::global()->bounded(-10000, 10000);
    uint8_t temperature = 25 + QRandomGenerator::global()->bounded(0, 30);

    frame.data[0] = (angle >> 8) & 0xFF;
    frame.data[1] = angle & 0xFF;
    frame.data[2] = (velocity >> 8) & 0xFF;
    frame.data[3] = velocity & 0xFF;
    frame.data[4] = (current >> 8) & 0xFF;
    frame.data[5] = current & 0xFF;
    frame.data[6] = temperature;
    frame.data[7] = 0;

    emit canFrameReceived(frame);

    // 循环使用不同的电机ID
    motorId = (motorId % 4) + 1;
    m_frameCounter++;
}

} // namespace RoboLink
