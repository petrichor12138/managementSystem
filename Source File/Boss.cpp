#include "../Header File/Boss.h"

using namespace std;

Boss::Boss(int ID, std::string name, int deptID) {
    this->w_ID=ID;
    this->w_name=name;
    this->w_DeptID=deptID;

}

void Boss::show_info()
{
    cout<<"职工编号："<<this->w_ID
        <<"\t职工姓名："<<this->w_name
        <<"\t岗位："<<this->get_dept_name()
        <<"\t岗位职责：管理公司所有事物"<<endl;
}

std::string Boss::get_dept_name()
{
    return string("总裁");
}




