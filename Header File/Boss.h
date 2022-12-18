#pragma once
#include "Worker.h"

class Boss : public Worker
{
public:
    Boss(int ID, std::string name, int deptID);

    void show_info();
    std::string get_dept_name();
};