#ifndef IHARDWAREBACKEND_H
#define IHARDWAREBACKEND_H

#include "BackendTypes.h"
#include <QObject>

namespace RoboLink {

// 硬件后端接口
class IHardwareBackend : public QObject {
    Q_OBJECT

public:
    explicit IHardwareBackend(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~IHardwareBackend() = default;

    // 获取后端信息
    virtual BackendInfo getBackendInfo() const = 0;

    // 连接后端
    virtual BackendError connectBackend() = 0;

    // 断开后端
    virtual void disconnectBackend() = 0;

    // 检查连接状态
    virtual bool isConnected() const = 0;

    // 获取能力
    virtual BackendCapabilities capabilities() const = 0;

    // CAN相关
    virtual BackendError configureCAN(const CANChannelConfig& config) = 0;
    virtual BackendError sendCANFrame(const CANFrame& frame) = 0;

    // RS485相关
    virtual BackendError configureRS485(const RS485Config& config) = 0;
    virtual BackendError sendRS485Data(const QByteArray& data) = 0;

signals:
    // 连接状态变化
    void connectionChanged(bool connected);

    // CAN帧接收
    void canFrameReceived(const CANFrame& frame);

    // RS485数据接收
    void rs485DataReceived(const QByteArray& data);

    // 错误信号
    void errorOccurred(const QString& error);

    // 日志信号
    void logMessage(const QString& message);
};

} // namespace RoboLink

#endif // IHARDWAREBACKEND_H
