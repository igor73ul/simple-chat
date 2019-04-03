
set(SOURCES netservice.cpp asyncwork.cpp)
set(HEADERS netservice.h safelist.h asyncwork.h)
add_library(netservice SHARED ${SOURCES} ${HEADERS})
file(COPY ${HEADERS} DESTINATION ${PROJECT_SOURCE_DIR}/include/)
#add_custom_command(TARGET netservice POST_BUILD COMMAND cp ${HEADERS} ${PROJECT_SOURCE_DIR}/include/)
