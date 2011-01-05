project(kbitcoin)
 
find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})
 
set(kbitcoin_SRCS 
  main.cpp
  mainwindow.cpp
)
 
kde4_add_executable(kbitcoin ${kbitcoin_SRCS})
 
target_link_libraries(kbitcoin ${KDE4_KDEUI_LIBS} qjson)
 
install(TARGETS kbitcoin DESTINATION ${BIN_INSTALL_DIR})
install(FILES kbitcoinui.rc 
        DESTINATION  ${DATA_INSTALL_DIR}/kbitcoin)
