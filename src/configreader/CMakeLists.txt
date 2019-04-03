
set(SOURCES configreader.cpp)
set(HEADERS configreader.h)

add_library(configreader SHARED ${SOURCES} ${HEADERS} ${FORMS})
target_link_libraries(configreader Qt5::Core)
file(COPY configreader.h DESTINATION ${PROJECT_SOURCE_DIR}/include/)
