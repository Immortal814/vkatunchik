cmake_minimum_required(VERSION 3.19)
project(balancer_que LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

qt_add_executable(balancer_que
    #WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.hpp
    mainwindow.ui
    producer_cl.hpp producer_cl.cpp
    data_types.hpp
    consumer.hpp consumer.cpp
    storage_class.hpp storage_class.cpp


)

target_link_libraries(balancer_que
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

include(GNUInstallDirs)

install(TARGETS balancer_que
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET balancer_que
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
