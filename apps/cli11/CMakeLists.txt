project(cli11-playground)

mb_ul_include(cli11.cmake)
mb_ul_include(consoletable.cmake)

add_executable(${PROJECT_NAME} src/args.h src/console_table.h src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${ConsoleTable_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE CLI11::CLI11 ConsoleTableLib)
