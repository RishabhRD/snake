file(GLOB_RECURSE src_list "**.cpp")
add_executable(snake ${src_list})
target_include_directories(snake PRIVATE ../include)
target_link_libraries(snake PUBLIC CONAN_PKG::boost CONAN_PKG::sfml)
target_link_libraries(snake PRIVATE project_options project_warnings)
add_custom_command(
    TARGET snake
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../data/title.png ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/data/title.png
    )
