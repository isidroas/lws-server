project(lws-minimal-ws-server C)
cmake_minimum_required(VERSION 2.8)
find_package(Libwebsockets CONFIG REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${LWS_CMAKE_DIR})

set(SAMP lws-minimal-ws-server)
set(SRCS minimal-ws-server.c)

add_executable(${SAMP} ${SRCS})
target_link_libraries(${SAMP} websockets_shared ${LIBWEBSOCKETS_DEP_LIBS})
add_dependencies(${SAMP} websockets_shared)
install(TARGETS ${SAMP} RUNTIME DESTINATION bin)
install(DIRECTORY mount-origin TYPE SYSCONF)
