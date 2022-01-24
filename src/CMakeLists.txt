add_executable(snake main.cpp)
target_include_directories(snake PRIVATE ../include)
target_link_libraries(
  snake
  PRIVATE project_options
          project_warnings)
