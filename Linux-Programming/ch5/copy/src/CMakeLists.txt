include_directories(${PROJECT_SOURCE_DIR}/libcopy)
set(APP_SRC main.c)
add_executable(cp ${APP_SRC})
target_link_libraries(cp libcopy)
