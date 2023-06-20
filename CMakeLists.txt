cmake_minimum_required(VERSION 3.21.1)
project(home_money)

set(CMAKE_CXX_STANDARD 11)

add_executable(home_money main.cpp base.hpp baseData.hpp DataSource.cpp DataSource.hpp IterImpl.hpp ListImpl.h Cmd.h Cmd.cpp StringUtils.h StringUtils.cpp CommandImpl.cpp CommandImpl.h)
