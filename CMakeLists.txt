cmake_minimum_required(VERSION 3.15)
project(ConfigurationManager)

set(CMAKE_CXX_STANDARD 23) # Habilita o std::expected (C++23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include lib) # Onde estão os .hpp

add_executable(config_manager_exe 
    src/main.cpp 
    src/ConfigurationManager.cpp 
    src/IniParser.cpp
)