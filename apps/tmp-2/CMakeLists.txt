project(tmp-2 LANGUAGES CXX)
set(TargetAppName ${PROJECT_NAME})

add_executable(${TargetAppName}
        src/main.cpp
)

target_include_directories(${TargetAppName} PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${TargetAppName} PUBLIC ${tfl_INCLUDE_DIRS})

too_use_asio(${TargetAppName} ${CMAKE_SOURCE_DIR}/3rdparty/asio-1.12.2.tar.gz
        MD5=43c53b8d255edc385dc4e704e59b3641)
