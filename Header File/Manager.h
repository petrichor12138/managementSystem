#pragma once
#include "Worker.h"

class Manager : public Worker
{
public:
    Manager(int ID, std::string name, int deptID);

    void show_info();
    std::string get_dept_name();
};