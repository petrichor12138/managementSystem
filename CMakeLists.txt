cmake_minimum_required(VERSION 3.24)
project(managementSystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(managementSystem "Source File/ManagementSystem.cpp" "Source File/WorkerManager.cpp" "Header File/Worker.h" "Header File/Employee.h" "Source File/Employee.cpp" "Header File/Manager.h" "Source File/Manager.cpp" "Header File/Boss.h" "Source File/Boss.cpp")
