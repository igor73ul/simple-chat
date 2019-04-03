  
set(SOURCES chatwindow.cpp client_path.cpp loginform.cpp netmessageconverter.cpp)
set(HEADERS chatwindow.h client_path.h loginform.h netmessageconverter.h)
qt5_wrap_ui(FORMS chatwindow.ui loginform.ui)
qt5_add_resources(RESOURCES client_path.qrc)
add_library(client_path SHARED ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})
target_link_libraries(client_path Qt5::Widgets netservice configreader)
file(COPY client_path.h DESTINATION ${PROJECT_SOURCE_DIR}/include/)
