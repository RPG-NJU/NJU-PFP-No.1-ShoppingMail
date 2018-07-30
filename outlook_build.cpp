#include"outlook.h"



#define THE_SCREEN_LEN 100

Outlook::Outlook()
{
	//第一种开机界面的初始化
	start_1[0] = "HHHHHHHHH     HHHHHHHHH                   lllllll lllllll                   !!!";
	start_1[1] = "H:::::::H     H:::::::H                   l:::::l l:::::l                  !!:!!";
	start_1[2] = "H:::::::H     H:::::::H                   l:::::l l:::::l                  !:::!";
	start_1[3] = "HH::::::H     H::::::HH                   l:::::l l:::::l                  !:::!";
	start_1[4] = "  H:::::H     H:::::H      eeeeeeeeeeee    l::::l  l::::l    ooooooooooo   !:::!";
	start_1[5] = "  H:::::H     H:::::H    ee::::::::::::ee  l::::l  l::::l  oo:::::::::::oo !:::!";
	start_1[6] = "  H::::::HHHHH::::::H   e::::::eeeee:::::eel::::l  l::::l o:::::::::::::::o!:::!";
	start_1[7] = "  H:::::::::::::::::H  e::::::e     e:::::el::::l  l::::l o:::::ooooo:::::o!:::!";
	start_1[8] = "  H:::::::::::::::::H  e:::::::eeeee::::::el::::l  l::::l o::::o     o::::o!:::!";
	start_1[9] = "  H::::::HHHHH::::::H  e:::::::::::::::::e l::::l  l::::l o::::o     o::::o!:::!";
	start_1[10] = "  H:::::H     H:::::H  e::::::eeeeeeeeeee  l::::l  l::::l o::::o     o::::o!!:!!";
	start_1[11] = "  H:::::H     H:::::H  e:::::::e           l::::l  l::::l o::::o     o::::o !!!";
	start_1[12] = "HH::::::H     H::::::HHe::::::::e         l::::::ll::::::lo:::::ooooo:::::o";
	start_1[13] = "H:::::::H     H:::::::H e::::::::eeeeeeee l::::::ll::::::lo:::::::::::::::o !!!";
	start_1[14] = "H:::::: H     H:::::::H  ee:::::::::::::e l::::::ll::::::l oo:::::::::::oo !!:!!";
	start_1[15] = "HHHHHHHHH     HHHHHHHHH    eeeeeeeeeeeeee llllllllllllllll   ooooooooooo    !!!";
	start_1[16] = "END";


	//第二种开机界面的初始化
	start_2[0] = " (`-').-> (`-')  _                            ,---. ";
	start_2[1] = " (OO )__  ( OO).-/  <-.      <-.        .->   |   | ";
	start_2[2] = ",--. ,'-'(,------.,--. )   ,--. )  (`-')----. |   |";
	start_2[3] = "|  | |  | |  .---'|  (`-') |  (`-')( OO).-.  '|   |";
	start_2[4] = "|  `-'  |(|  '--. |  |OO ) |  |OO )( _) | |  ||  .'";
	start_2[5] = "|  .-.  | |  .--'(|  '__ |(|  '__ |  \\|  |)|  |`--' ";//相比原文增加了一个空格
	start_2[6] = "|  | |  | |  `---.|     |' |     |'  '  '-'  '.--. ";
	start_2[7] = "`--' `--' `------'`-----'  `-----'    `-----' `--'";
	start_2[8] = "END";





	//欢迎界面的初始化
	second[0] = " _ _ _     _                   ";
	second[1] = "| | | |___| |___ ___ _____ ___ ";
	second[2] = "| | | | -_| |  _| . |     | -_|";
	second[3] = "|_____|___|_|___|___|_|_|_|___|";

	//logo的初始化
	logo[0] = "  ooooooo8 oooooooooo  oooooooooo          oooo     oooo      o      ooooo       ooooo       ";
	logo[1] = "o888    88  888    888  888    888          8888o   888      888      888         888        ";
	logo[2] = "888    oooo 888oooo88   888oooo88 ooooooooo 88 888o8 88     8  88     888         888        ";
	logo[3] = "888o    88  888  88o    888                 88  888  88    8oooo88    888      o  888      o ";
	logo[4] = " 888ooo888 o888o  88o8 o888o               o88o  8  o88o o88o  o888o o888ooooo88 o888ooooo88 ";


	//short_logo
	short_logo[0] = "  ooooooo8 oooooooooo  oooooooooo ";
	short_logo[1] = "o888    88  888    888  888    888";
	short_logo[2] = "888    oooo 888oooo88   888oooo88 ";
	short_logo[3] = "888o    88  888  88o    888       ";
	short_logo[4] = " 888ooo888 o888o  88o8 o888o      ";



	end[0] = ":'######::::'#######:::'#######::'########::'########::'##:::'##:'########:";
	end[1] = "'##... ##::'##.... ##:'##.... ##: ##.... ##: ##.... ##:. ##:'##:: ##.....::";
	end[2] = " ##:::..::: ##:::: ##: ##:::: ##: ##:::: ##: ##:::: ##::. ####::: ##:::::::";
	end[3] = " ##::'####: ##:::: ##: ##:::: ##: ##:::: ##: ########::::. ##:::: ######:::";
	end[4] = " ##::: ##:: ##:::: ##: ##:::: ##: ##:::: ##: ##.... ##:::: ##:::: ##...::::";
	end[5] = " ##::: ##:: ##:::: ##: ##:::: ##: ##:::: ##: ##:::: ##:::: ##:::: ##:::::::";
	end[6] = ". ######:::. #######::. #######:: ########:: ########::::: ##:::: ########:";
	end[7] = ":......:::::.......::::.......:::........:::........::::::..:::::........::";

	return;
}

void Outlook::print_start(int mode)
{
	/*if (mode == 1)
	{
	for (int i = 0; start_1[i] != "END"; i++)
	{
	std::cout << start_1[i].c_str() << std::endl;
	}
	}

	else if (mode == 2)
	{
	for (int i = 0; start_2[i] != "END"; i++)
	{
	std::cout << start_2[i].c_str() << std::endl;
	}
	}*/




	//system("pause");//进行停顿进入下一个动作
	//system("CLS");



	system("color F0");//白色背景黑色字体


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	for (int i = 0; i < 4; i++)
	{
		//Sleep(100);
		std::cout << second[i].c_str() << std::endl;
	}
	std::cout << std::endl;


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
	std::cout << "	      TO------" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < 5; i++)

		//for (int j = 0; j < 96; j++)
	{
		//int i = 0;
		std::cout << "             ";
		for (int j = 0; j < logo[i].length(); j++)//想做一个RGB随机色的输出
												  //for (; i < 5; i++)
		{
			/*switch (rand() % (6 - 1 + 1) + 1)
			{
			case 1:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE); std::cout << logo[i][j]; break;
			case 2:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN); std::cout << logo[i][j]; break;
			case 3:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED); std::cout << logo[i][j]; break;
			case 4:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED); std::cout << logo[i][j]; break;
			case 5:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN); std::cout << logo[i][j]; break;
			case 6:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED); std::cout << logo[i][j]; break;
			}*/


			if (logo[i][j] != ' ')
				Sleep(5);

			if (j < 16 - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
				std::cout << logo[i][j];
			}
			else if (j < 32 - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
				std::cout << logo[i][j];
			}
			else if (j < 48 - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
				std::cout << logo[i][j];
			}
			else if (j < 64 - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
				std::cout << logo[i][j];
			}
			else if (j < 80 - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
				std::cout << logo[i][j];
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
				std::cout << logo[i][j];
			}
			//else
			//std::cout << std::endl;

		}
		std::cout << std::endl;
		//std::cout << logo[i].c_str() << std::endl;

	}

	std::cout << std::endl;

	std::cout << "                                                                                                         V3.0 HD" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;


	system("pause");
	system("CLS");
	system("color F0");//进行初始的恢复


	return;
}

void Outlook::main_menu()
{

	system("color F0");

	//拟在主菜单的前面加上一个GRP的logo
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);//进行蓝色字体的设定

																																						   //也许做一个颜色渐变会更好
	for (int i = 0; i < 5; i++)
	{

		std::cout << "                                  ";
		//std::cout << short_logo[i].c_str() << std::endl;
		for (int j = 0; j < 35; j++)
		{
			if (j < 13 - 2 * i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);

			}
			else if (j < 26 - 2 * i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
			}
			std::cout << short_logo[i][j];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	for (int i = 0; i < THE_SCREEN_LEN; i++)
		std::cout << "=";
	std::cout << std::endl << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
	std::cout << "                                             0.退出系统" << std::endl << std::endl;
	std::cout << "                                             1.用户登录" << std::endl << std::endl;
	std::cout << "                                             2.用户注册" << std::endl << std::endl;
	std::cout << "                                             3.管理员的登录" << std::endl << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	for (int i = 0; i < THE_SCREEN_LEN; i++)
		std::cout << "=";
	std::cout << std::endl;
	std::cout << "请输入操作：";




	return;
}

void Outlook::user_menu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	for (int i = 0; i < THE_SCREEN_LEN; i++)
		std::cout << "=";
	std::cout << std::endl << std::endl;
	std::cout << "0.注销登录 1.查看商品 2.商品搜索 3.添加商品至购物车 4.查看购物车 5.修改购物车商品数量 6.结账 7.修改密码";
	
	std::cout << std::endl << std::endl;
	for (int i = 0; i < THE_SCREEN_LEN; i++)
		std::cout << "=";
	std::cout << std::endl;
	return;
}

void Outlook::admin_menu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	for (int i = 0; i < THE_SCREEN_LEN; i++)
		std::cout << "=";
	std::cout << std::endl << std::endl;
	std::cout << "0.注销账号   1.查询商品   2.增加商品   3.删除商品   4.修改商品信息   5.查看已售清单";
	
	std::cout << std::endl << std::endl;
	for (int i = 0; i < THE_SCREEN_LEN; i++)
		std::cout << "=";
	std::cout << std::endl;
	return;
}

void Outlook::low()
{
	std::cout << std::endl;
	for (int i = 0; i < THE_SCREEN_LEN; i++)
		std::cout << "=";
	//cout << "=====================================================================================================";
	std::cout << std::endl << std::endl;
	std::cout << "请您的输入操作：";
	return;
}

void Outlook::goodbye()
{
	for (int i = 0; i < 8; i++)

		//for (int j = 0; j < 96; j++)
	{
		//int i = 0;
		std::cout << "                  ";
		for (int j = 0; j < end[i].length(); j++)//想做一个RGB随机色的输出
												  //for (; i < 5; i++)
		{
			/*switch (rand() % (6 - 1 + 1) + 1)
			{
			case 1:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE); std::cout << logo[i][j]; break;
			case 2:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN); std::cout << logo[i][j]; break;
			case 3:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED); std::cout << logo[i][j]; break;
			case 4:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED); std::cout << logo[i][j]; break;
			case 5:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN); std::cout << logo[i][j]; break;
			case 6:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED); std::cout << logo[i][j]; break;
			}*/


			if (end[i][j] != ' ')
				Sleep(2);

			if (j < 16 - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
				std::cout << end[i][j];
			}
			else if (j < 32 - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
				std::cout << end[i][j];
			}
			else if (j < 48 - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
				std::cout << end[i][j];
			}
			else if (j < 64 - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
				std::cout << end[i][j];
			}
			else if (j < 80 - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
				std::cout << end[i][j];
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
				std::cout << end[i][j];
			}
			//else
			//std::cout << std::endl;

		}
		std::cout << std::endl;
		//std::cout << logo[i].c_str() << std::endl;

	}

	std::cout << std::endl;

	std::cout << "                                                                                                         BY GRP" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;


	system("pause");
	return;
}