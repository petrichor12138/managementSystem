#include <iostream>
#include "../Header File/WorkerManager.h"
#include "../Header File/Worker.h"
#include "../Header File/Employee.h"
using namespace std;


int main() {

    WorkerManager wm;

    int user_choice = 0;

    while(true)
    {
        wm.show_menu();

        cout<<"请输入您的选择："<<endl;
        cin>>user_choice;

        switch (user_choice) {
            case 0://exit
                wm.exit_system();
                break;
            case 1://add
                wm.add_emp();
                break;
            case 2://show
                wm.show_emp();
                break;
            case 3://delete
                wm.del_emp();
                break;
            case 4://upd_emp
                wm.upd_emp();
                break;
            case 5://search
                wm.find_emp();
                break;
            case 6://sort
                wm.sort_emp();
                break;
            case 7://clear
                wm.clear_file();
                break;
            default:
                system("cls");
        }
    }




    //system("pause");

    return 0;
}
