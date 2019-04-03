
set(SOURCES alivematrix.cpp servercontroller.cpp serverservice.cpp server_path.cpp)
set(HEADERS alivematrix.h servercontroller.h serverservice.h server_path.h)

add_library(server_path SHARED ${SOURCES} ${HEADERS} ${FORMS})
target_link_libraries(server_path netservice configreader)
file(COPY server_path.h DESTINATION ${PROJECT_SOURCE_DIR}/include/)
