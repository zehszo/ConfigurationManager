cmake_minimum_required(VERSION 3.15)
project(ConfigurationManager)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include lib) 

add_executable(config_manager_exe 
    src/main.cpp 
    src/ConfigurationManager.cpp 
    src/IniParser.cpp
)

set_target_properties(config_manager_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/examples"
)