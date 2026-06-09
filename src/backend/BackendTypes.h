#ifndef BACKENDTYPES_H
#define BACKENDTYPES_H

#include <QString>
#include <QStringList>
#include <QChar>
#include <QByteArray>
#include <cstdint>

namespace RoboLink {

// 后端类型枚举
enum class BackendType {
    Mock,           // 模拟后端
    RoboLink,       // RoboLink自有硬件
    ZlgCan          // ZLGCAN兼容后端
};

// 后端能力标志
struct BackendCapabilities {
    bool supportsCAN = false;
    bool supportsRS485 = false;
    bool supportsDeviceInfo = false;
    bool supportsFirmwareUpgrade = false;
    bool supportsCANFilter = false;

    QString toString() const {
        QStringList caps;
        if (supportsCAN) caps << "CAN";
        if (supportsRS485) caps << "RS485";
        if (supportsDeviceInfo) caps << "DeviceInfo";
        if (supportsFirmwareUpgrade) caps << "FirmwareUpgrade";
        if (supportsCANFilter) caps << "CANFilter";
        return caps.join(", ");
    }
};

// 后端信息
struct BackendInfo {
    BackendType type;
    QString name;
    QString version;
    QString description;
    BackendCapabilities capabilities;
};

// 后端错误
struct BackendError {
    int code = 0;
    QString message;

    bool isError() const { return code != 0; }

    static BackendError success() {
        return BackendError{0, "Success"};
    }

    static BackendError error(int code, const QString& message) {
        return BackendError{code, message};
    }
};

// CAN帧结构
struct CANFrame {
    uint32_t id = 0;
    uint8_t dlc = 0;
    uint8_t data[8] = {0};
    bool isExtended = false;
    uint32_t timestamp = 0;  // 时间戳（毫秒）

    QString toString() const {
        QString dataStr;
        for (int i = 0; i < dlc; ++i) {
            dataStr += QString("%1").arg(data[i], 2, 16, QChar('0')).toUpper();
            if (i < dlc - 1) dataStr += " ";
        }
        return QString("ID:0x%1 DLC:%2 Data:[%3]%4")
            .arg(id, isExtended ? 8 : 3, 16, QChar('0'))
            .arg(dlc)
            .arg(dataStr)
            .arg(isExtended ? " [EXT]" : "");
    }
};

// CAN通道配置
struct CANChannelConfig {
    uint32_t baudrate = 1000000;  // 默认1Mbps
    bool loopback = false;
    bool listenOnly = false;
    bool termination = false;     // 120Ω终端电阻

    QString toString() const {
        return QString("Baudrate:%1 Loopback:%2 ListenOnly:%3 Termination:%4")
            .arg(baudrate)
            .arg(loopback ? "On" : "Off")
            .arg(listenOnly ? "On" : "Off")
            .arg(termination ? "On" : "Off");
    }
};

// RS485配置
struct RS485Config {
    uint32_t baudrate = 115200;
    enum class Parity { None, Even, Odd } parity = Parity::None;
    uint8_t dataBits = 8;
    uint8_t stopBits = 1;

    QString toString() const {
        QString parityStr;
        switch (parity) {
            case Parity::None: parityStr = "None"; break;
            case Parity::Even: parityStr = "Even"; break;
            case Parity::Odd: parityStr = "Odd"; break;
        }
        return QString("Baudrate:%1 Parity:%2 DataBits:%3 StopBits:%4")
            .arg(baudrate)
            .arg(parityStr)
            .arg(dataBits)
            .arg(stopBits);
    }
};

// 后端类型转字符串
inline QString backendTypeToString(BackendType type) {
    switch (type) {
        case BackendType::Mock: return "MockBackend";
        case BackendType::RoboLink: return "RoboLinkBackend";
        case BackendType::ZlgCan: return "ZlgCanBackend";
        default: return "Unknown";
    }
}

} // namespace RoboLink

#endif // BACKENDTYPES_H
