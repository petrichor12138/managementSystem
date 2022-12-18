#include "../Header File/Employee.h"
using  namespace std;
Employee::Employee(int ID, std::string name, int deptID)
{
    this->w_ID=ID;
    this->w_name=name;
    this->w_DeptID=deptID;
}

void Employee::show_info()
{
    cout<<"职工编号："<<this->w_ID
        <<"\t职工姓名："<<this->w_name
        <<"\t岗位："<<this->get_dept_name()
        <<"\t岗位职责：完成经理交给的任务"<<endl;
}

std::string Employee::get_dept_name()
{
    return string("员工");
}


