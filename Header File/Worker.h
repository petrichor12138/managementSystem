#pragma once

#include <iostream>
#include <string>

class Worker
{
public:
    int w_ID;
    std::string w_name;
    int w_DeptID;


    virtual void show_info() = 0;

    virtual std::string get_dept_name() = 0;

    virtual ~Worker(){}
};

