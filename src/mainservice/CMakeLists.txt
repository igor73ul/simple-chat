  
set(SOURCES main.cpp widget.cpp chatwindow.cpp loginform.cpp servercontroller.cpp)
set(HEADERS widget.h chatwindow.h loginform.h servercontroller.h)
qt5_wrap_ui(FORMS widget.ui chatwindow.ui loginform.ui)
qt5_add_resources(RESOURCES mainservice.qrc)
add_executable(mainservice ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})
target_link_libraries(mainservice Qt5::Widgets)
#add_custom_command(TARGET netservice POST_BUILD COMMAND cp ${HEADERS} ${PROJECT_SOURCE_DIR}/include/)
