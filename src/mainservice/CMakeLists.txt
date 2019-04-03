  
set(SOURCES main.cpp widget.cpp)
set(HEADERS widget.h )
qt5_wrap_ui(FORMS widget.ui)
qt5_add_resources(RESOURCES mainservice.qrc)
add_executable(mainservice ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})
target_link_libraries(mainservice Qt5::Widgets client_path server_path)
#add_custom_command(TARGET netservice POST_BUILD COMMAND cp ${HEADERS} ${PROJECT_SOURCE_DIR}/include/)
