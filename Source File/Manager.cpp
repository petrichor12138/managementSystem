#include "../Header File/Manager.h"

using namespace std;

Manager::Manager(int ID, std::string name, int deptID) {
    this->w_ID=ID;
    this->w_name=name;
    this->w_DeptID=deptID;

}

void Manager::show_info()
{
    cout<<"职工编号："<<this->w_ID
        <<"\t职工姓名："<<this->w_name
        <<"\t岗位："<<this->get_dept_name()
        <<"\t岗位职责：完成老板交给的任务，并下发任务给员工"<<endl;
}

std::string Manager::get_dept_name()
{
    return string("经理");
}




