#pragma once

#include "Worker.h"

class Employee : public Worker
{
public:
    Employee(int ID, std::string name, int deptID);

    void show_info();

    std::string get_dept_name();
};
