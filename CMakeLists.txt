project (DoBeeDo)
cmake_minimum_required(VERSION 2.6)
find_package( KDE4 REQUIRED )
include( KDE4Defaults )
include_directories( ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )

add_subdirectory( icons )

set( DoBeeDo_SRCS main.cpp
              doapp.cpp
              mainwindow.cpp
              systray.cpp
              todoobject.cpp
              settings.cpp
              editdialog.cpp
              model/treeitem.cpp
              model/treemodel.cpp
              model/tododelegate.cpp
              model/filtermodel.cpp
              config/configdialog.cpp
              config/categorywidget.cpp
              config/prioritywidget.cpp
              )
  

      

kde4_add_executable( dobeedo ${DoBeeDo_SRCS} )
kde4_add_app_icon(DoBeeDo_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/icons/hi*-app-dobeedo.png")
target_link_libraries( dobeedo ${KDE4_KDEUI_LIBS} )

install(TARGETS dobeedo ${INSTALL_TARGETS_DEFAULT_ARGS} )
install(FILES dobeedoui.rc DESTINATION  ${DATA_INSTALL_DIR}/dobeedo)
install( FILES dobeedo.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )

