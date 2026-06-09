# RoboLinkStudio 阶段1：硬件后端抽象与MockBackend

## 项目概述

本阶段完成了RoboLinkStudio的基础架构搭建，包括：
- 项目目录结构整理
- 硬件后端抽象层定义
- MockBackend模拟后端实现
- 基础UI演示界面

## 目录结构

```
RoboLinkStudio/
├── CMakeLists.txt              # 构建配置
├── README.md                   # 本文件
├── src/
│   ├── main.cpp                # 主入口
│   ├── ui/                     # UI相关
│   │   ├── mainwindow.h
│   │   ├── mainwindow.cpp
│   │   └── mainwindow.ui
│   ├── backend/                # 硬件后端
│   │   ├── BackendTypes.h      # 基础类型定义
│   │   ├── IHardwareBackend.h  # 后端接口
│   │   ├── mock/               # 模拟后端
│   │   │   ├── MockBackend.h
│   │   │   └── MockBackend.cpp
│   │   ├── robolink/           # RoboLink后端（待实现）
│   │   └── zlgcan/             # ZLGCAN后端（待实现）
│   ├── can/                    # CAN相关（待实现）
│   ├── rs485/                  # RS485相关（待实现）
│   ├── protocol/               # 协议引擎（待实现）
│   ├── logging/                # 日志（待实现）
│   └── utils/                  # 工具类（待实现）
├── docs/                       # 文档
├── protocols/                  # 协议文件
└── tests/                      # 测试
```

## 核心架构

### 1. 基础类型 (BackendTypes.h)

定义了系统的基础数据类型：
- `BackendType`: 后端类型枚举（Mock, RoboLink, ZlgCan）
- `BackendInfo`: 后端信息结构
- `BackendCapabilities`: 后端能力描述
- `BackendError`: 统一错误处理
- `CANFrame`: CAN帧结构
- `CANChannelConfig`: CAN通道配置
- `RS485Config`: RS485配置

### 2. 硬件后端接口 (IHardwareBackend.h)

所有硬件后端必须实现的接口：
```cpp
class IHardwareBackend : public QObject {
    // 连接管理
    virtual BackendError connectBackend() = 0;
    virtual void disconnectBackend() = 0;
    virtual bool isConnected() const = 0;
    
    // CAN操作
    virtual BackendError configureCAN(const CANChannelConfig& config) = 0;
    virtual BackendError sendCANFrame(const CANFrame& frame) = 0;
    
    // RS485操作
    virtual BackendError configureRS485(const RS485Config& config) = 0;
    virtual BackendError sendRS485Data(const QByteArray& data) = 0;
    
    // 信号
    signals:
        void connectionChanged(bool connected);
        void canFrameReceived(const CANFrame& frame);
        void rs485DataReceived(const QByteArray& data);
        void errorOccurred(const QString& error);
        void logMessage(const QString& message);
};
```

### 3. MockBackend实现

模拟后端用于无硬件开发：
- 实现所有IHardwareBackend接口
- 周期性产生模拟CAN帧（每100ms）
- 模拟电机反馈数据（ID 0x201-0x204）
- 支持CAN回环模式
- 所有操作通过日志显示

### 4. MainWindow UI

基础演示界面包含：
- 后端信息显示（MockBackend v1.0.0）
- 连接/断开按钮
- 发送测试CAN帧按钮
- 日志显示区域（实时显示所有操作）
- 清空日志按钮

## 构建方法

### 方法1：使用Qt Creator（推荐）

1. 打开Qt Creator
2. 菜单 -> 文件 -> 打开文件或项目
3. 选择 `CMakeLists.txt`
4. 配置Kit：选择 `Desktop Qt 6.9.3 MSVC 2022 64-bit`
5. 点击左下角的"构建"按钮（锤子图标）
6. 点击"运行"按钮（绿色三角形）

### 方法2：命令行构建

```bash
# 进入项目目录
cd E:\RoboLink\RoboLinkStudio\RoboLinkStudio

# 配置（确保CMake和Ninja在PATH中）
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug

# 编译
cmake --build build

# 运行
build/bin/RoboLinkStudio.exe
```

## 验收标准测试

启动程序后，应该能够：

### ✅ 1. 打开主窗口
- 窗口标题显示"RoboLinkStudio"
- 显示当前后端：MockBackend v1.0.0
- 日志区显示启动信息和后端能力

### ✅ 2. 连接MockBackend
1. 点击"连接 (Connect)"按钮
2. 日志显示：
   - "MockBackend: 正在连接..."
   - "MockBackend: 连接成功"
   - ">>> 后端已连接"
3. 按钮状态变化：
   - "连接"按钮禁用
   - "断开"按钮启用
   - "发送测试CAN帧"按钮启用

### ✅ 3. 接收模拟CAN帧
连接后，日志每100ms显示接收到的CAN帧：
```
[14:23:45.123] 接收CAN: ID:0x201 DLC:8 Data:[00 64 F5 12 D8 F0 1E 00]
[14:23:45.223] 接收CAN: ID:0x202 DLC:8 Data:[00 C8 03 E8 E8 03 20 00]
...
```

### ✅ 4. 发送测试CAN帧
1. 点击"发送测试CAN帧"按钮
2. 日志显示：
   - "--- 发送测试CAN帧 ---"
   - "MockBackend: 发送CAN帧 - ID:0x200 DLC:8 Data:[10 11 12 13 14 15 16 17]"

### ✅ 5. 断开连接
1. 点击"断开 (Disconnect)"按钮
2. 日志显示：
   - "--- 断开后端连接 ---"
   - "MockBackend: 正在断开连接..."
   - "MockBackend: 已断开连接"
   - ">>> 后端已断开"
3. 模拟CAN帧停止接收
4. 按钮状态恢复初始状态

### ✅ 6. 清空日志
点击"清空日志"按钮，日志区被清空

## 架构要点

### ✅ 后端抽象正确
- UI层（MainWindow）只依赖IHardwareBackend接口
- 不直接引用MockBackend、RoboLinkBackend或ZlgCanBackend的具体实现
- 后续添加新后端时，UI层无需修改

### ✅ ZLGCAN定位明确
- ZLGCAN只是IHardwareBackend的一个实现
- 与MockBackend、RoboLinkBackend平级
- 不能污染上层业务逻辑

### ✅ 信号槽架构
- 后端通过Qt信号通知UI
- 异步、解耦、线程安全
- 便于后续扩展

## 技术栈

- Qt 6.9.3
- C++17
- CMake 3.19+
- MSVC 2022 64-bit
- Ninja构建系统

## 下一步

阶段2将实现：
- ZLGCAN兼容后端（接入ZLGCAN SDK）
- 阶段3将实现基础CAN/RS485调试面板
- 阶段4将实现RoboLink自有硬件后端

## 注意事项

1. 当前MockBackend的CAN帧是模拟大疆M3508电机反馈格式
2. 时间戳显示使用系统本地时间
3. 日志会自动滚动到底部
4. 连接状态下，模拟CAN帧会持续产生，可能导致日志快速增长

## 故障排查

### 编译错误
- 确保Qt 6.9.3已正确安装
- 确保Kit配置正确（MSVC 2022 64-bit）
- 检查CMakeLists.txt中的路径

### 运行时错误
- 检查Qt DLL是否在PATH中
- 使用Qt Creator的"运行"功能会自动配置环境

### UI显示问题
- 确保mainwindow.ui被正确编译
- 检查uic生成的ui_mainwindow.h文件

## 许可证

本项目为RoboLink系统的一部分。

---

**版本**: V1.0  
**日期**: 2026-06-09  
**状态**: 阶段1完成
