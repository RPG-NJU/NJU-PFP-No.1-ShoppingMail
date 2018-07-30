#include"outlook.h"
#include"head3.0.h"

using namespace std;

/*
在之前的1.X版本中已经逐步优化并且完成了基础版所要求的所有功能
所以，在之后的2.X版本中，将进行功能的小添加以及界面的优化
是为第二个大版本的更新
*/

/*
上交的第一次完整可执行代码是2.0版本
在2.0的代码中，增加了在付款的时候进行的金额的结算，并且询问是否进行付款，可以取消付款的功能



*/


/*
在之前的版本2.1中，已经给助教进行了演示，也修改了库存无法改变的bug，
在这次的3.X版本中，主要进行附加功能的编写，进行一些细节的修改，至此   2018.4.17
*/


int main()
{
	Outlook UI;
	string input;



	UI.print_start(1);

	UI.main_menu();//主菜单


	cin >> input;

	while (input != "0")
	{
		Admin the_admin;
		User the_user;
		if (input == "1")
		{
			if (the_user.Pass_Check())
			{
				//std::cout << "用户登录成功！" << std::endl;

				system("pause");
				system("CLS");

				the_user.Init_The_Store_List();
				the_user.Init_Wish_List();//商店的初始化一定要在最前面，因为之后的购物车有一个纠错板块需要调用
				the_user.Init_Pay_List();

				UI.user_menu();
				cout << "请输入您的操作：";
				cin >> input;
				while (input != "0")//0为注销操作
				{
					if (input == "1")
					{
						the_user.Print_List();
					}
					else if (input == "2")
					{
						the_user.Search();
					}
					else if (input == "3")
					{
						the_user.Add_Wish();
					}

					else if (input == "4")
					{
						the_user.Print_Wish_List();
					}
					else if (input == "5")
					{
						the_user.Change_Wish();
					}
					else if (input == "6")
					{
						the_user.Pay();
					}
					else if (input == "7")
					{
						the_user.Change_Password();
					}
					else
					{
						cout << "“" << input << "”为不合法的输入，请重新输入：";
					}
					UI.low();
					cin >> input;
					system("CLS");
					UI.user_menu();
				}
				cout << "您的账户已经注销！" << endl;
			}
		}
		else if (input == "2")
		{
			the_user.New_User();
		}
		else if (input == "3")
		{
			

			if (the_admin.Pass_Check())
			{
				system("pause");
				system("CLS");
				the_admin.Init_Sold_List();
				the_admin.Init_The_Store_List();//作为一开始储存信息的初始化
				
				UI.admin_menu();
				cout << "请输入操作：";
				cin >> input;
				//以下是二级目录的操作界面所带来的选择
				while (input != "0")
				{
					if (input == "1")//查询商品
					{
						the_admin.Print_List();
					}
					else if (input == "2")
					{
						the_admin.Add_List();
					}
					else if (input == "3")
					{
						the_admin.Delete_Thing();
					}
					else if (input == "4")
					{
						the_admin.Change_List();
					}
					else if (input == "5")
					{
						the_admin.Print_Sold_List();
					}
					else
					{
						cout << "“" << input << "”" << "为不合法的操作输入" << endl;
					}
					UI.low();
					cin >> input;
					system("CLS");
					UI.admin_menu();

				}
				cout << "您已经注销账号！" << endl;
			}
		}


		else
		{
			cout << "“" << input << "”为不合法的输入，请重新输入：";
		}

		the_admin.~Admin();//析构，结束寿命
		the_user.~User();
		system("pause");
		system("CLS");
		UI.main_menu();
		cin >> input;
	}

	system("CLS");
	UI.goodbye();
	std::cout << "系统关闭！" << std::endl;
	system("pause");

	return 0;
}