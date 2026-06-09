#ifndef MOCKBACKEND_H
#define MOCKBACKEND_H

#include "../IHardwareBackend.h"
#include <QTimer>
#include <QRandomGenerator>

namespace RoboLink {

// 模拟后端实现
class MockBackend : public IHardwareBackend {
    Q_OBJECT

public:
    explicit MockBackend(QObject* parent = nullptr);
    ~MockBackend() override;

    // IHardwareBackend接口实现
    BackendInfo getBackendInfo() const override;
    BackendError connectBackend() override;
    void disconnectBackend() override;
    bool isConnected() const override;
    BackendCapabilities capabilities() const override;

    BackendError configureCAN(const CANChannelConfig& config) override;
    BackendError sendCANFrame(const CANFrame& frame) override;

    BackendError configureRS485(const RS485Config& config) override;
    BackendError sendRS485Data(const QByteArray& data) override;

private slots:
    void generateMockCANFrame();

private:
    bool m_connected = false;
    CANChannelConfig m_canConfig;
    RS485Config m_rs485Config;
    QTimer* m_mockTimer = nullptr;
    uint32_t m_frameCounter = 0;
};

} // namespace RoboLink

#endif // MOCKBACKEND_H
