#include "../Header File/WorkerManager.h"
#include "../Header File/Worker.h"
#include "../Header File/Employee.h"
#include "../Header File/Manager.h"
#include "../Header File/Boss.h"
using namespace std;

WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    //file not exists
    if(!ifs.is_open())
    {
        cout<<"文件不存在"<<endl;
        this->hc = 0;
        this->w_EmpArray = NULL;
        this->w_FileEmpty = true;
        ifs.close();
        return;
    }

    //file existing without data
    char ch;
    if((ifs>>ch).eof())
    {
        cout<<"文件为空"<<endl;
        this->hc = 0;
        this->w_EmpArray = NULL;
        this->w_FileEmpty = true;
        ifs.close();
        return;
    }

    int w_hc = this->get_hc();
    cout<<"员工人数为："<<w_hc<<endl;
    this->hc = w_hc;

    this->w_EmpArray = new Worker * [this->hc];
    this->init_emp();

    for(int i=0;i<this->hc;++i)
    {
        cout<<"员工编号"<<this->w_EmpArray[i]->w_ID<<'\t'
            <<"员工姓名"<<this->w_EmpArray[i]->w_name<<'\t'
            <<"部门编号"<<this->w_EmpArray[i]->w_DeptID<<endl;
    }
}

void WorkerManager::show_menu()
{
    cout<<"-----------------------------------------"<<endl;
    cout<<"---------- 欢迎使用员工管理系统！ -----------"<<endl;
    cout<<"------------- 0.退出管理系统 --------------"<<endl;
    cout<<"------------- 1.增加职工信息 --------------"<<endl;
    cout<<"------------- 2.显示职工信息 --------------"<<endl;
    cout<<"------------- 3.删除离职职工 --------------"<<endl;
    cout<<"------------- 4.修改职工信息 --------------"<<endl;
    cout<<"------------- 5.查找职工信息 --------------"<<endl;
    cout<<"------------- 6.按照编号排序 --------------"<<endl;
    cout<<"------------- 7.清空所有文档 --------------"<<endl;
    cout<<"-----------------------------------------"<<endl;
    cout<<endl;
}

WorkerManager::~WorkerManager()
{
    if(this->w_EmpArray!=NULL)
    {
        for(int i=0;i<this->hc;++i)
        {
            if(this->w_EmpArray[i] != NULL)
            {
                delete this->w_EmpArray[i];
            }
        }
        delete [] this->w_EmpArray;
        this->w_EmpArray = NULL;
    }
}

void WorkerManager::upd_emp() {
    if(this->w_FileEmpty)
    {
        cout<<"文件不存在或记录为空！"<<endl;
    }
    else
    {
        cout<<"请输入需要修改的员工编号："<<endl;
        int ID;
        cin>>ID;

        int index = this->is_exist(ID);

        if(index != -1)
        {
            cout<<"查询到该员工数据！"<<endl;
            cout<<"该员工信息为："<<endl;
            this->w_EmpArray[index]->show_info();
            //cout<<&this->w_EmpArray[index]<<endl;
            delete this->w_EmpArray[index];

            int newID = 0;
            string newName = "";
            int newDept = 0;

            cout<<"请输入新的员工编号："<<endl;
            cin>>newID;

            cout<<"请输入新的员工姓名："<<endl;
            cin>>newName;

            cout<<"请选择该员工岗位"<<endl;
            cout<<"1. 普通员工"<<endl;
            cout<<"2. 经理"<<endl;
            cout<<"3. 总裁"<<endl;
            cin>>newDept;

            Worker * worker =NULL;
            switch (newDept) {
                case 1:
                    worker = new Employee(newID, newName, 1);
                    break;
                case 2:
                    worker = new Manager(newID, newName, 2);
                    break;
                case 3:
                    worker = new Boss(newID, newName, 3);
                default:
                    break;
            }

            this->w_EmpArray[index] = worker;
            cout<<"修改成功！"<<endl;

            this->save();

        }
        else
        {
            cout<<"修改失败！未找到此员工！"<<endl;
        }
    }

    system("pause");
    system("cls");

}

void WorkerManager::exit_system() {
    cout<<"欢迎下次使用此系统！"<<endl;
    std::system("pause");
    exit(0);

}

void WorkerManager::add_emp() {
    cout<<"请输入添加职工数量："<<endl;

    int add_hc = 0;
    cin>>add_hc;

    if(add_hc > 0)
    {
        int newSize = this->hc + add_hc;
        Worker ** newSpace = new Worker*[newSize];

        if(this->w_EmpArray != NULL)
        {
            for(int i=0;i<this->hc;++i)
            {
                newSpace[i] = this->w_EmpArray[i];
            }
        }

        for(int i=0;i<add_hc;++i)
        {
            int ID;
            string name;
            int deptSelect;

            cout<<"请输入第"<<i+1<<"个新员工编号："<<endl;
            cin>>ID;

            cout<<"请输入第"<<i+1<<"个新员工姓名："<<endl;
            cin>>name;

            cout<<"请选择该员工岗位"<<endl;
            cout<<"1. 普通员工"<<endl;
            cout<<"2. 经理"<<endl;
            cout<<"3. 总裁"<<endl;
            cin>>deptSelect;

            Worker * worker =NULL;
            switch (deptSelect) {
                case 1:
                    worker = new Employee(ID, name, 1);
                    break;
                case 2:
                    worker = new Manager(ID, name, 2);
                    break;
                case 3:
                    worker = new Boss(ID, name, 3);
                default:
                    break;
            }

            newSpace[this->hc + i] = worker;
        }

        delete [] this->w_EmpArray;

        this->w_EmpArray = newSpace;
        this->hc = newSize;

        this->w_FileEmpty = false;
        cout<<"成功添加"<<add_hc<<"名员工"<<endl;
        this->save();
    }
    else
    {
        cout<<"您输入的人数有误："<<endl;
    }


}

void WorkerManager::save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for(int i=0;i<this->hc;++i)
    {
        ofs<<this->w_EmpArray[i]->w_ID<<'\t'
           <<this->w_EmpArray[i]->w_name<<'\t'
           <<this->w_EmpArray[i]->w_DeptID<<endl;
    }

    ofs.close();

}

int WorkerManager::get_hc() {
    int w_hc;
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int ID;
    string name;
    int deptID;

    while(ifs>>ID && ifs>>name && ifs>>deptID)
    {
        ++w_hc;
    }
    return w_hc;
}

void WorkerManager::init_emp() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int ID;
    string name;
    int deptID;

    int index = 0;
    while(ifs>>ID && ifs>>name && ifs>>deptID)
    {
        Worker *worker = NULL;
        if (deptID == 1)
        {
            worker = new Employee(ID, name, deptID);
        }
        if(deptID == 2)
        {
            worker = new Manager(ID, name, deptID);
        }
        if(deptID == 3)
        {
            worker = new Boss(ID, name, deptID);
        }

        this->w_EmpArray[index++] = worker;
    }
    ifs.close();
}

void WorkerManager::show_emp() {
    if(this->w_FileEmpty)
    {
        cout<<"文件不存在或记录为空"<<endl;
    }
    else
    {
        for(int i=0;i<this->hc;++i)
        {
            this->w_EmpArray[i]->show_info();
        }
    }

    system("pause");
    system("cls");
}

void WorkerManager::del_emp() {
    if(this->w_FileEmpty)
    {
        cout<<"文件不存在"<<endl;
    }
    else
    {
        cout<<"请输入想要删除员工编号："<<endl;
        int ID = 0;
        cin>>ID;

        int index = is_exist(ID);

        if(index != -1)
        {
            for(int i=index;i<this->hc;++i)
            {
                this->w_EmpArray[i] = this->w_EmpArray[i+1];
            }
            --this->hc;
            this->save();

            cout<<"删除成功"<<endl;
        }
        else
        {
            cout<<"删除失败，未找到该员工！"<<endl;
        }

    }

    system("pause");
    system("cls");
}

int WorkerManager::is_exist(int ID) {
    int index = -1;

    for(int i=0;i<this->hc;++i)
    {
        if(this->w_EmpArray[i]->w_ID == ID)
        {
            index = i;
            break;
        }
    }

    return index;

}

int WorkerManager::is_exist(string name)
{
    int index = -1;

    for(int i=0;i<this->hc;++i)
    {
        if(this->w_EmpArray[i]->w_name == name)
        {
            index = i;
            break;
        }
    }

    return index;
}


void WorkerManager::find_emp() {
    if(this->w_FileEmpty)
    {
        cout<<"文件不存在"<<endl;
    }
    else
    {
        cout<<"请选择查找方式！"<<endl;
        cout<<"1. 按照员工编号查找"<<endl;
        cout<<"2. 按照员工姓名查找"<<endl;
        int choice = 0;
        cin>>choice;

        if(choice == 1)
        {
            cout<<"请输入需要查找的员工编号："<<endl;
            int ID;
            cin>>ID;

            int index = is_exist(ID);
            if(index != -1)
            {
                cout<<"查询到该员工"<<endl;
                cout<<"该员工信息为："<<endl;
                this->w_EmpArray[index]->show_info();
            }
            else
            {
                cout<<"查询不到此员工!"<<endl;
            }

        }
        else if(choice == 2)
        {
            cout<<"请输入需要查找的员工姓名："<<endl;
            string name;
            cin>>name;

            int index = is_exist(name);
            if(index != -1)
            {
                cout<<"查询到该员工"<<endl;
                cout<<"该员工信息为："<<endl;
                this->w_EmpArray[index]->show_info();
            }
            else
            {
                cout<<"查询不到此员工!"<<endl;
            }
        }
        else
        {
            cout<<"您输入的数字有误！"<<endl;
        }
    }


}

void WorkerManager::sort_emp()
{
    cout<<"请选择排序方式！"<<endl;
    cout<<"1. 按照编号升序排列"<<endl;
    cout<<"2. 按照编号降序排列"<<endl;
    int choice = 1;
    cin>>choice;

    if(choice == 1)
    {
        Worker *temp = NULL;
        for(int i=0;i<this->hc-1;++i)
        {
            for(int j=i+1;j<this->hc;++j)
            {
                if(this->w_EmpArray[i]->w_ID > this->w_EmpArray[j]->w_ID)
                {

                    temp = w_EmpArray[i];
                    w_EmpArray[i] = w_EmpArray[j];
                    w_EmpArray[j] = temp;
                    //delete temp;
                }
            }

        }
        temp = NULL;
    }
    else if(choice == 2)
    {
        Worker *temp = NULL;
        for(int i=0;i<this->hc-1;++i)
        {
            for(int j=i+1;j<this->hc;++j)
            {
                if(this->w_EmpArray[i]->w_ID < this->w_EmpArray[j]->w_ID)
                {

                    temp = w_EmpArray[i];
                    w_EmpArray[i] = w_EmpArray[j];
                    w_EmpArray[j] = temp;
                }
            }

        }
        temp = NULL;
    }
    else
    {
        cout<<"您输入的数字有误！"<<endl;
    }


}

void WorkerManager::clear_file() {
    cout<<"确认清空吗？"<<endl;
    cout<<"1. 确认"<<endl;
    cout<<"2. 取消"<<endl;

    int choice = 0;
    cin>>choice;

    if(choice == 1)
    {
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        if(this->w_EmpArray != NULL)
        {
            for(int i = 0;i<this->hc;++i)
            {
                delete this->w_EmpArray[i];
                this->w_EmpArray[i] = NULL;
            }
            delete [] this->w_EmpArray;
            this->w_EmpArray = NULL;
            this->hc = 0;
            this->w_FileEmpty = true;
        }

        cout<<"清空成功！"<<endl;
    }
}




