project (KDo)
cmake_minimum_required(VERSION 2.6)
find_package( KDE4 REQUIRED )
include( KDE4Defaults )
include_directories( ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )

set( KDo_SRCS main.cpp
              doapp.cpp
              mainwindow.cpp
              systray.cpp
              todoobject.cpp
              settings.cpp
              editdialog.cpp
              model/treeitem.cpp
              model/treemodel.cpp
              model/tododelegate.cpp
              )
 

      

kde4_add_executable( kdo ${KDo_SRCS} )
target_link_libraries( kdo ${KDE4_KDEUI_LIBS} )

install(TARGETS kdo ${INSTALL_TARGETS_DEFAULT_ARGS} )
