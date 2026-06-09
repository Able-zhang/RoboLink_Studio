include("E:/RoboLink/RoboLinkStudio/RoboLinkStudio/build/Desktop_Qt_6_9_3_MSVC2022_64bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/RoboLinkStudio-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "E:/RoboLink/RoboLinkStudio/RoboLinkStudio/build/Desktop_Qt_6_9_3_MSVC2022_64bit-Debug/bin/RoboLinkStudio.exe"
    GENERATE_QT_CONF
)
