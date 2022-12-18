#pragma once    //防止头文件重复包含
#include <iostream>
#include <fstream>
#include "Worker.h"

#define FILENAME "worker.txt"

class WorkerManager{
public:
    bool w_FileEmpty;

    WorkerManager();

    void show_menu();//show

    void exit_system();//exit

    void save();

    void clear_file();

    //head count
    int hc;

    int get_hc();

    //职工数组指针
    Worker **w_EmpArray;

    void add_emp();

    void init_emp();

    void show_emp();

    void del_emp();
    int is_exist(int ID);

    void upd_emp();

    void find_emp();
    int is_exist(std::string name);

    void sort_emp();

    ~WorkerManager();




};