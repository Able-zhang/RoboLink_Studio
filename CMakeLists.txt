cmake_minimum_required(VERSION 3.19)
project(RoboLinkStudio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# 收集源文件
set(PROJECT_SOURCES
    src/main.cpp
    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.ui
    src/backend/BackendTypes.h
    src/backend/IHardwareBackend.h
    src/backend/mock/MockBackend.h
    src/backend/mock/MockBackend.cpp
)

qt_add_executable(RoboLinkStudio
    WIN32 MACOSX_BUNDLE
    ${PROJECT_SOURCES}
)

# 包含目录
target_include_directories(RoboLinkStudio PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(RoboLinkStudio
    PRIVATE
        Qt::Core
        Qt::Widgets
)

# 设置输出目录
set_target_properties(RoboLinkStudio PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS RoboLinkStudio
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET RoboLinkStudio
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
