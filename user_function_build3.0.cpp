#include"head3.0.h"
#include<string>
#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<algorithm>


User::User()
{
	char the_store_list_filename[] = ".\\All_File\\Admin\\库存.txt";
	char the_pass_check_filename[] = ".\\All_File\\User\\用户账号.txt";
	char the_store_sold_filename[] = ".\\All_File\\Admin\\已售清单.txt";

	user_name = "NULL";
	user_password = "NULL";//其实是无意义的赋值，最终就会改变
	the_store_list_file = the_store_list_filename;
	pass_check_file = the_pass_check_filename;
	the_store_sold_file = the_store_sold_filename;
}

User::~User()
{

}

void User::Init_Filename()
{
	std::string before_add = ".\\All_File\\User\\";//这是文件的统一路径
	std::string pay_after_add = "_pay.txt";
	std::string wish_after_add = "_wish.txt";//这三个是文件名的前后添加项
	wish_file = before_add + user_name + wish_after_add;
	pay_file = before_add + user_name + pay_after_add;
	return;
}

void User::New_User()
{
	std::string name;
	std::string password;
	char name_get[THE_STR_LEN + 1], password_get[THE_STR_LEN + 1];
	FILE *the_check_file;

	if (fopen_s(&the_check_file, pass_check_file.c_str(), "r+"))
	{
		std::cout << "请检查你的文件配置！" << std::endl;
		exit(-1);
	}
	else
	{
		std::cout << "请输入你的用户名：";
		std::cin >> name;
		if (name.size() > 20)
		{
			fclose(the_check_file);
			std::cout << "用户名请小于20个字符" << std::endl;
			return;
		}
		std::cout << "请输入你的密码：";
		std::cin >> password;
		if (password.size() > 20)
		{
			fclose(the_check_file);
			std::cout << "密码请小于20个字符" << std::endl;
			return;
		}

		fscanf_s(the_check_file, "%s%s", name_get, THE_STR_LEN + 1, password_get, THE_STR_LEN + 1);
		while (!feof(the_check_file))
		{
			if (name == name_get)
			{
				fclose(the_check_file);
				std::cout << "用户名重复！" << std::endl;
				return;
			}
			fscanf_s(the_check_file, "%s%s", name_get, THE_STR_LEN + 1, password_get, THE_STR_LEN + 1);
		}

		user_name = name;
		user_password = password;//这两个的初始化，使得后面的文件建立有据可依

		fprintf_s(the_check_file, "%-32s%-32s\n", name.c_str(), password.c_str());
		std::cout << "新用户创建成功" << std::endl;
		fclose(the_check_file);
	}

	//以上是用户的账户信息创建完毕，下面还需要创建用户的购物车文件。

	this->Init_Filename();//调用文件名初始化函数进行设定，用于第一次建立用户文件
	FILE *wish, *pay;
	if (fopen_s(&wish, wish_file.c_str(), "w") || fopen_s(&pay, pay_file.c_str(), "w"))
	{
		std::cout << "请检查文件配置！" << std::endl;
		exit(-1);
	}
	else
	{
		fprintf_s(wish, "%-16s%-16s%-16s%-16s%-16s\n", "ID", "名称", "品牌", "价格", "数量");
		fprintf_s(pay, "%-16s%-16s%-16s%-16s%-16s\n", "ID", "名称", "品牌", "价格", "数量");
	}
	fclose(wish);
	fclose(pay);

	std::cout << "用户文件建立完毕！" << std::endl;


	return;
}

bool User::Pass_Check()
{
	std::string name_input;
	std::string password_input;
	char name_in_file[THE_STR_LEN + 1];
	char password_in_file[THE_STR_LEN + 1];
	FILE *the_check_file;

	if (fopen_s(&the_check_file, pass_check_file.c_str(), "r"))
	{
		std::cout << "无法打开指定的用户文件，请检查您的文件配置。" << std::endl;
		return false;
	}
	else
	{
		fscanf_s(the_check_file, "%s", name_in_file, THE_STR_LEN + 1);
		fscanf_s(the_check_file, "%s", password_in_file, THE_STR_LEN + 1);//将文件的头读出，不在列
		std::cout << "输入用户名：";
		std::cin >> name_input;//暂未考虑输出长度较长之后如何报错
		std::cout << "输入用户密码：";
		std::cin >> password_input;
		//未更改可能的读取重复问题，因为是只读模式，对于其影响不大
		while (!feof(the_check_file))
		{
			fscanf_s(the_check_file, "%s", name_in_file, THE_STR_LEN + 1);
			fscanf_s(the_check_file, "%s", password_in_file, THE_STR_LEN + 1);
			if (strcmp(name_in_file, name_input.c_str()) == 0)
			{
				if (strcmp(password_in_file, password_input.c_str()) == 0)
				{
					user_name = name_input;//将用户名录入
					user_password = password_input;
					fclose(the_check_file);
					std::cout << "登录成功！" << std::endl;
					this->Init_Filename();//******必要的一步，进行用户文件名的初始化，便于之后的操作******
					return true;
				}
			}
		}
	}
	fclose(the_check_file);
	std::cout << "登陆失败，请检查您的用户名和密码。" << std::endl;
	return false;
}

//以下两个函数的所有代码与Admin类中的该函数一样，修改时应该同步修改
void User::Init_The_Store_List()
{
	FILE *the_list_file;//文件名
	char get1[THE_STR_LEN + 1], get2[THE_STR_LEN + 1], get3[THE_STR_LEN + 1];
	double get4;
	int get5;

	if (fopen_s(&the_list_file, the_store_list_file.c_str(), "r"))
	{
		std::cout << "无法打开指定的仓库文件，请检查您的文件配置。" << std::endl;
		exit(-1);
	}
	else
	{
		for (int i = 0; i < 5; i++)
			fscanf_s(the_list_file, "%s", get1, THE_STR_LEN + 1);
		int i = 0;
		fscanf_s(the_list_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		while (!feof(the_list_file))
		{
			store_list[i].ID = get1;
			store_list[i].name = get2;
			store_list[i].brand = get3;
			store_list[i].price = get4;
			store_list[i].num = get5;
			i++;
			fscanf_s(the_list_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		}
	}

	fclose(the_list_file);
	return;
}

void User::Print_List()
{
	std::cout.setf(std::ios::left);//左对齐
	std::cout << std::setw(THE_TAB) << "ID" << std::setw(THE_TAB) << "名称"
		<< std::setw(THE_TAB) << "品牌" << std::setw(THE_TAB) << "价格"
		<< std::setw(THE_TAB) << "数量" << std::endl;
	for (int i = 0; store_list[i].name != "NULL"; i++)
	{
		if (store_list[i].num > 0)//避免输出已经下架或者数量为0的商品
		{
			std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
				<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
				<< std::setw(THE_TAB) << store_list[i].num << std::endl;
		}
	}
	return;
}

//以下两个代码为Admin移植而来的代码
void User::Init_Wish_List()
{
	FILE *the_wish_file;//文件名
	char get1[THE_STR_LEN + 1], get2[THE_STR_LEN + 1], get3[THE_STR_LEN + 1];
	double get4;
	int get5;
	std::string input;

	if (fopen_s(&the_wish_file, wish_file.c_str(), "r"))
	{
		std::cout << "无法打开指定的仓库文件，请检查您的文件配置。" << std::endl;
		exit(-1);
	}
	else
	{
		for (int i = 0; i < 5; i++)
			fscanf_s(the_wish_file, "%s", get1, THE_STR_LEN + 1);
		int i = 0;
		fscanf_s(the_wish_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		while (!feof(the_wish_file))
		{
			wish_list[i].ID = get1;
			wish_list[i].name = get2;
			wish_list[i].brand = get3;
			wish_list[i].price = get4;
			wish_list[i].num = get5;
			i++;
			fscanf_s(the_wish_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		}
	}

	fclose(the_wish_file);

	//下面是一个纠正板块，用于纠正在下线期间可能导致的数量改变

	//2018.4.10 进行拟定优化，也就是在删除购物车中物品的时候询问用户，是否删除以及相关的操作

	//进行如上类似的操作优化，也就是在购物车的商品数量大于库存的时候所可能导致的问题，进行2.1版本的优化

	//拟采用
	bool correct = false;
	bool flag = false;

	for (int i = 0; wish_list[i].ID != "NULL"; i++)
	{
		for (int j = 0; store_list[j].ID != "NULL"; j++)
		{
			if (wish_list[i].ID == store_list[j].ID)
			{

				if (wish_list[i].price != store_list[j].price)
				{
					flag = true;
					std::cout << "你选中的商品" << wish_list[i].ID << "-" << wish_list[i].name << "-" << wish_list[i].brand << "价格变动为：" << store_list[j].price << "元" << std::endl;
					//增加了对于问题商品的信息的详细描述
					//不需要对商品的异常处理
					wish_list[i].price = store_list[j].price;
					correct = true;

				}

				if (wish_list[i].num > store_list[j].num)
				{
					flag = true;
					if (store_list[j].num > 0)
					{
						std::cout << "商品" << wish_list[i].ID << "-" << wish_list[i].name << "-" << wish_list[i].brand << "库存不足" << std::endl;
						//对于商品信息显示的优化，对于用户友好
						std::cout << "您可以选择：1.修改至最大库存\t2.保留原数量" << std::endl;
						do
						{
							std::cin >> input;
							if (input == "1")
							{
								wish_list[i].num = store_list[j].num;
								std::cout << "商品的数量修改为" << wish_list[i].num << std::endl;
							}

							else if (input == "2")
							{
								wish_list[i].owner = "NOTENOUGH";//作为商品不足的表示，异常显示
							}

							else
								std::cout<<"“" << input << "”" << "为非法输入，请重新输入：";
						} while (input != "1"&&input != "2");
					}
					else
					{
						//2.0版本所做的修改：*******************************************************************************************


						std::cout << "商品" << wish_list[i].ID << "-" << wish_list[i].name << "-" << wish_list[i].brand << "的库存不足或者已经下架，您可以选择：" << std::endl;
						std::cout << "1.删除该商品\t2.保留该商品" << std::endl;
						std::cout << "请您做出决定：";

						do {
							std::cin >> input;
							if (input == "1")
							{
								int ii = i;
								for (; wish_list[ii].ID != "NULL"; ii++)
									wish_list[ii] = wish_list[ii + 1];
								std::cout << "该商品已从购物车删除！" << std::endl;
								correct = true;
								i--;
							}

							else if (input == "2")
							{
								wish_list[i].owner = "DOWN";//作为商品下架的标志
							}

							else
								std::cout << "“" << input << "”" << "为非法输入，请重新输入：";
						} while (input != "1"&&input != "2");

						//2.0版本的更新结束***********************************************************************************************

					}

				}
				break;
			}
			//以上的纠错模块是对于数量的不足

			//以下的纠错模块是对于价格的变动
		}
	}
	if (correct)
		this->Write_Wish_File();
	if (flag)
	{
		system("pause");
		system("CLS");//进行等待清屏操作，优化观瞻
	}
	//上面是一个纠正板块

	return;
}
void User::Init_Pay_List()
{
	FILE *the_pay_file;//文件名
	char get1[THE_STR_LEN + 1], get2[THE_STR_LEN + 1], get3[THE_STR_LEN + 1];
	double get4;
	int get5;

	if (fopen_s(&the_pay_file, pay_file.c_str(), "r"))
	{
		std::cout << "无法打开指定的仓库文件，请检查您的文件配置。" << std::endl;
		exit(-1);
	}
	else
	{
		for (int i = 0; i < 5; i++)
			fscanf_s(the_pay_file, "%s", get1, THE_STR_LEN + 1);
		int i = 0;
		fscanf_s(the_pay_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		while (!feof(the_pay_file))
		{
			pay_list[i].ID = get1;
			pay_list[i].name = get2;
			pay_list[i].brand = get3;
			pay_list[i].price = get4;
			pay_list[i].num = get5;
			i++;
			fscanf_s(the_pay_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		}
	}

	fclose(the_pay_file);
	return;
}

void User::Write_List_File() const
{
	FILE *list_file;
	if (fopen_s(&list_file, the_store_list_file.c_str(), "w"))
	{
		std::cout << "请检查你的文件配置！" << std::endl;
		exit(-1);
	}
	else
	{
		fprintf_s(list_file, "%-16s%-16s%-16s%-16s%-16s", "ID", "名称", "品牌", "价格", "数量");
		for (int i = 0; store_list[i].ID != "NULL"; i++)
		{
			fprintf_s(list_file, "\n%-16s%-16s%-16s%-16.1f%-16d", store_list[i].ID.c_str(), store_list[i].name.c_str(), store_list[i].brand.c_str(), store_list[i].price, store_list[i].num);
		}
	}
	fclose(list_file);
	std::cout << "库存文件写入完成！" << std::endl;
	return;
}
void User::Write_Wish_File() const
{
	FILE *wish;
	if (fopen_s(&wish, wish_file.c_str(), "w"))
	{
		std::cout << "请检查你的文件配置！" << std::endl;
		exit(-1);
	}
	else
	{
		fprintf_s(wish, "%-16s%-16s%-16s%-16s%-16s", "ID", "名称", "品牌", "价格", "数量");
		for (int i = 0; wish_list[i].ID != "NULL"; i++)
		{
			fprintf_s(wish, "\n%-16s%-16s%-16s%-16.1f%-16d", wish_list[i].ID.c_str(), wish_list[i].name.c_str(), wish_list[i].brand.c_str(), wish_list[i].price, wish_list[i].num);
		}
	}
	fclose(wish);
	std::cout << "购物车文件写入完成！" << std::endl;
	return;
}
void User::Write_Pay_File() const
{
	FILE *pay;
	if (fopen_s(&pay, pay_file.c_str(), "w"))
	{
		std::cout << "请检查你的文件配置！" << std::endl;
		exit(-1);
	}
	else
	{
		fprintf_s(pay, "%-16s%-16s%-16s%-16s%-16s", "ID", "名称", "品牌", "价格", "数量");
		for (int i = 0; pay_list[i].ID != "NULL"; i++)
		{
			fprintf_s(pay, "\n%-16s%-16s%-16s%-16.1f%-16d", pay_list[i].ID.c_str(), pay_list[i].name.c_str(), pay_list[i].brand.c_str(), pay_list[i].price, pay_list[i].num);
		}
	}
	fclose(pay);
	std::cout << "待收货文件写入完成！" << std::endl;
	return;
}

void User::Search()
{
	std::cout.setf(std::ios::left);//左对齐定义
	std::string kind;
	std::string input;
	bool x = false;




	//3.0拟进行模糊查询的支持***************************************************************************************



	bool list[200] = { false };//用这个来决定发现了哪一个符合条件，并且最终输出


	/*std::cout << "ID/名称/品牌" << std::endl;
	std::cout << "请输入你要搜索的方式：";
	std::cin >> kind;
	if (kind == "ID")
	{
		std::cout << "请输入商品的ID：";
		std::cin >> input;
		std::cout << "ID\t\t名称\t\t品牌\t\t价格\t\t数量\n";
		for (int i = 0; store_list[i].ID != "NULL"; i++)
		{
			if (store_list[i].ID == input && store_list[i].num > 0)
			{
				x = true;
				std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
					<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
					<< std::setw(THE_TAB) << store_list[i].num << std::endl;
			}
		}
		if (!x)
			std::cout << "\n未找到指定ID商品！\n";
	}
	else if (kind == "名称")
	{
		std::cout << "请输入商品的名称：";
		std::cin >> input;
		std::cout << "ID\t\t名称\t\t品牌\t\t价格\t\t数量\n";
		for (int i = 0; store_list[i].ID != "NULL"; i++)
		{
			if (store_list[i].name == input && store_list[i].num > 0)
			{
				x = true;
				std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
					<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
					<< std::setw(THE_TAB) << store_list[i].num << std::endl;
			}
		}
		if (!x)
			std::cout << "\n未找到指定名称商品！\n";
	}
	else if (kind == "品牌")
	{
		std::cout << "请输入商品的品牌：";
		std::cin >> input;
		std::cout << "ID\t\t名称\t\t品牌\t\t价格\t\t数量\n";
		for (int i = 0; store_list[i].ID != "NULL"; i++)
		{
			if (store_list[i].brand == input && store_list[i].num > 0)
			{
				x = true;
				std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
					<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
					<< std::setw(THE_TAB) << store_list[i].num << std::endl;
			}
		}
		if (!x)
			std::cout << "\n未找到指定品牌商品！\n";
	}*/

	std::cout << "请输入您要搜索的关键词：";
	std::cin >> input;
	transform(input.begin(), input.end(), input.begin(), toupper);

	int len = input.length();//作为模糊搜索关键词的长度

	for (int i = 0; store_list[i].ID != "NULL"; i++)
	{
		if (store_list[i].num <= 0)
			continue;
		for (int j = 0; j < (int)store_list[i].ID.length() - len + 1; j++)
		{
			std::string a = store_list[i].ID;
			transform(a.begin(), a.end(), a.begin(), toupper);
			if (strncmp(input.c_str(), (&a[0] + j), len) == 0)
			{
				list[i] = true;
				x = true;
				break;
			}
		}

		for (int j = 0; j < (int)store_list[i].name.length() - len + 1; j++)
		{
			std::string a = store_list[i].name;
			transform(a.begin(), a.end(), a.begin(), toupper);
			if (strncmp(input.c_str(), (&a[0] + j), len) == 0)
			{
				list[i] = true;
				x = true;
				break;
			}
		}

		for (int j = 0; j < (int)store_list[i].brand.length() - len + 1; j++)
		{
			std::string a = store_list[i].brand;
			transform(a.begin(), a.end(), a.begin(), toupper);
			if (strncmp(input.c_str(), (&a[0] + j), len) == 0)
			{
				list[i] = true;
				x = true;
				break;
			}
		}
	}

	if (!x)
		std::cout << "\n未找到商品！\n";
	else
	{
		std::cout << "ID\t\t名称\t\t品牌\t\t价格\t\t数量\n";//表头
		for (int i = 0; i < 200; i++)
		{
			if (list[i])
			{
				std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
					<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
					<< std::setw(THE_TAB) << store_list[i].num << std::endl;
			}
		}
	}

	return;
}

void User::Add_Wish()
{
	std::string ID;//作为添加的商品的唯一标识
	int num = 0;//作为添加的数量

	std::cout << std::endl;
	this->Print_List();
	std::cout << std::endl;


	std::cout << "请输入你要添加的商品的ID：";
	std::cin >> ID;
	std::cout << "请输入商品的数量：";
	std::cin >> num;
	int i = 0;
	for (; wish_list[i].ID != "NULL"; i++)//遍历是否在购物车中已经有了该商品
	{
		if (wish_list[i].ID == ID)//说明在原来的购物车文件中已经有了这一个商品
			break;

	}

	for (int j = 0; store_list[j].ID != "NULL"; j++)//在库存中寻找这一个商品
	{
		if (store_list[j].ID == ID)//找到了这个商品
		{
			wish_list[i].ID = ID;//将购物车ID进行赋值
			if (store_list[j].num <= 0)
			{
				wish_list[i] = store_list[j];
				std::cout << "该商品由于下架或者数量问题不能添加至您的购物车" << std::endl;
				for (; i < THE_STORE_MAX - 1; i++)//将这一项之后的所有购物车向前重置
				{
					wish_list[i] = wish_list[i + 1];
				}
			}
			else if (wish_list[i].num + num > store_list[j].num)
			{
				wish_list[i] = store_list[j];
				std::cout << "商品数量超过限制，已经将数量修改为：" << store_list[j].num << std::endl;
				wish_list[i].num = store_list[j].num;
			}
			else
			{
				int save_num = 0;
				save_num = wish_list[i].num;
				wish_list[i] = store_list[j];
				wish_list[i].num = save_num + num;
			}
			this->Write_Wish_File();
			return;
		}
	}
	std::cout << "无此商品！" << std::endl;
	return;
}

void User::Print_Wish_List()
{
	std::cout.setf(std::ios::left);//左对齐
	std::cout << std::setw(THE_TAB) << "ID" << std::setw(THE_TAB) << "名称"
		<< std::setw(THE_TAB) << "品牌" << std::setw(THE_TAB) << "价格"
		<< std::setw(THE_TAB) << "数量" << std::endl;
	for (int i = 0; wish_list[i].name != "NULL"; i++)
	{
		if (wish_list[i].owner == "NOTENOUGH" || wish_list[i].owner == "DOWN")
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
		std::cout << std::setw(THE_TAB) << wish_list[i].ID << std::setw(THE_TAB) << wish_list[i].name
			<< std::setw(THE_TAB) << wish_list[i].brand << std::setw(THE_TAB) << wish_list[i].price
			<< std::setw(THE_TAB) << wish_list[i].num;//<< std::endl;
		if (wish_list[i].owner == "NOTENOUGH")
			std::cout << std::setw(THE_TAB) << "该商品库存数量不足";
		else if (wish_list[i].owner == "DOWN")
			std::cout << std::setw(THE_TAB) << "该商品的库存为0或者已经下架";
		std::cout << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}
	//std::cout << std::endl;
	//std::cout.setf(std::ios::right);
	return;
}

void User::Change_Wish()//目前只有删除功能，后续可能进行添加
{
	std::string ID;
	int num = 0;

	std::cout << std::endl;
	this->Print_Wish_List();
	std::cout << std::endl;

	//在3.0的版本中希望可以不止删除这一个商品，还可以进行其他的操作
	std::cout << "请输入商品的ID：";
	std::cin >> ID;

	for (int i = 0; wish_list[i].ID != "NULL"; i++)
	{
		if (wish_list[i].ID == ID)
			//找到了这一个商品在购物车中
		{
			int j = 0;
			for (; store_list[j].ID != "NULL"; j++)
				if (store_list[j].ID == ID)//在库存中也找到了这一个商品
					break;
			//如上的代码三句话就已经在商店中找到了这一个要修改的购物车里的商品，方便之后对于数据的比对和修改

			std::cout << "*********************************************************************" << std::endl;
			std::cout << "您的购物车中为：" << wish_list[i].name << "-" << wish_list[i].brand << "有" << wish_list[i].num << "件" << std::endl;
			std::cout << "库存中有" << store_list[j].num << "件" << std::endl;
			std::cout << "*********************************************************************" << std::endl;

			std::cout << "请您输入您期望的修改后的数量（若为0则删除该货品）：";
			std::cin >> num;


			if (num < 0)
			{
				std::cout << "输入的数据不能为负数，操作失败！" << std::endl;
				return;
			}
			else if (num == 0)
			{
				for (; i < THE_STORE_MAX - 1; i++)
					wish_list[i] = wish_list[i + 1];
				std::cout << "商品" << ID << "已经移除" << std::endl;
			}
			else
			{
				if (store_list[j].num <= 0)
				{
					wish_list[i].num = num;
					wish_list[i].owner = "DOWN";
				}
				else if (num > store_list[j].num)//如果修改之后的数量大于库存
				{
					wish_list[i].num = num;
					wish_list[i].owner = "NOTENOUGH";
				}

				std::cout << "已经成功修改该商品的数量！" << std::endl;
			}
			this->Write_Wish_File();
			return;
		}
	}
	std::cout << "您的购物车中没有这个商品！" << std::endl;



	return;
}

void User::Pay()
{
	//目前只能实现全部购买的操作，后续进行弥补*************************************
	//bool x = false;
	//bool flag = false;//2.0版本更新所加的新变量
	FILE *file;
	if (fopen_s(&file, the_store_sold_file.c_str(), "a"))
	{
		std::cout << "请联系管理员检查文件配置" << std::endl;
		exit(-1);
	}

	//2.0版本更新，对于与之前的删除商品由用户决定，则对应的购买时需要检测，是否有库存以及是否下架，即确定可否购买：*******************
	int which_pay[200] = { 0 };//标记哪些商品是进行付款的
	int which_pay_i = 0;
	double tot_money = 0;//计算总价
	std::string input;
	/*
	for (int i = 0; wish_list[i].ID != "NULL"; i++)
	{
	int j = 0;
	/*
	for (; pay_list[j].ID != "NULL"; j++)
	{

	if (pay_list[j].ID == wish_list[i].ID)//在已售中已经有了这一件商品
	{
	x = true;
	for (int k = 0; store_list[k].ID != "NULL"; k++)//进行库存的遍历
	{
	if (store_list[k].ID == wish_list[i].ID)
	{
	if (store_list[k].num < wish_list[i].num)
	{
	std::cout << "商品" << store_list[k].ID << "的库存不足，请你修改购物车之后再进行付款" << std::endl;
	break;//跳出循环，结束这一商品的付款
	}
	else
	{
	tot_money += wish_list[i].price*wish_list[i].num;
	which_pay[which_pay_i] = i;
	which_pay_i++;
	//pay_list[j].num += wish_list[i].num;
	//store_list[k].num -= wish_list[i].num;//库存的修改
	flag = true;//付款成功的时候进行翻转
	break;
	}
	}
	}
	}


	}

	//取消了待收货清单的合并，毕竟购买时间不一样
	//if (!x)//如果是一个新的商品的话

	for (int k = 0; store_list[k].ID != "NULL"; k++)//进行库存的遍历
	{
	if (store_list[k].ID == wish_list[i].ID)
	{
	if (store_list[k].num < wish_list[i].num)
	{
	std::cout << "商品" << store_list[k].ID << "的库存不足，请你修改购物车之后再进行付款" << std::endl;
	break;//跳出循环，结束这一商品的付款
	}
	else
	{
	tot_money += wish_list[i].num*wish_list[i].price;
	which_pay[which_pay_i] = i;//记录下可以付款的对象
	which_pay_i++;

	//pay_list[j] = wish_list[i];//滞后会比较好
	//store_list[k].num -= wish_list[i].num;//库存的修改
	//flag = true;//付款成功的时候进行翻转
	//break;
	}
	}
	}
	//i--;
	//x = false;



	/*
	if (flag)
	{
	fprintf_s(file, "%-16s%-16s%-16s%-16.1f%-16d%-16s\n", wish_list[i].ID.c_str(), wish_list[i].name.c_str(), wish_list[i].brand.c_str(), wish_list[i].price, wish_list[i].num, user_name.c_str());
	for (int ii = i; wish_list[ii].ID != "NULL"; ii++)//这段代码完成了下面注释掉的代码的功能，但是为了契合2.0的修改，所以代码进行了变动
	{
	wish_list[ii] = wish_list[ii + 1];
	}
	}
	//wish_list[i] = { "NULL","NULL","NULL",0.0,0 };//恢复购物车的这一位置

	flag = false;


	}

	*/

	//下面是3.0的修改，采用的是标志位来判定是否可以进行付款

	for (int i = 0; wish_list[i].ID != "NULL"; i++)//只对购物车进行遍历，减少了很多的工作量
	{
		if (wish_list[i].owner == "NOTENOUGH")
		{
			std::cout << "商品" << wish_list[i].ID << "的库存不足，请你修改购物车之后再进行付款" << std::endl;
		}
		else if (wish_list[i].owner == "DOWN")
		{
			std::cout << "商品" << wish_list[i].ID << "的库存不足，请你修改购物车之后再进行付款" << std::endl;
		}
		else//这种情况就是可以进行结算的时候
		{
			which_pay[which_pay_i] = i;//标价下哪一个可以进行付款
			tot_money += wish_list[i].num*wish_list[i].price;//进行总款的表示
			which_pay_i++;//+1不解释
		}

	}



	std::cout << "总价格是" << tot_money << "元" << std::endl;
	std::cout << "1.确认付款\t2.取消付款" << std::endl;
	do
	{
		std::cin >> input;
		if (input == "2")
		{
			fclose(file);
			return;
		}

	} while (input != "1"&&input != "2");

	int pay_i = 0;
	for (; pay_list[pay_i].ID != "NULL"; pay_i++);
	for (int i = which_pay_i - 1; i >= 0; i--)//进行付款的操作
	{
		fprintf_s(file, "%-16s%-16s%-16s%-16.1f%-16d%-16s\n", wish_list[which_pay[i]].ID.c_str(), wish_list[which_pay[i]].name.c_str(), wish_list[which_pay[i]].brand.c_str(), wish_list[which_pay[i]].price, wish_list[which_pay[i]].num, user_name.c_str());
		pay_list[pay_i] = wish_list[which_pay[i]];
		for (int k = 0; store_list[k].ID != "NULL"; k++)
		{
			if (store_list[k].ID == wish_list[which_pay[i]].ID)
				store_list[k].num -= wish_list[which_pay[i]].num;
		}
		pay_i++;
		for (int ii = which_pay[i]; wish_list[ii].ID != "NULL"; ii++)//这段代码完成了下面注释掉的代码的功能，但是为了契合2.0的修改，所以代码进行了变动
		{
			wish_list[ii] = wish_list[ii + 1];
		}
	}

	//2.0版本这一段的修改结束*********************************************************************************************************

	fclose(file);

	this->Write_List_File();
	this->Write_Pay_File();
	this->Write_Wish_File();
	std::cout << "已经上传商家" << std::endl;
	std::cout << "购物车清空完毕！" << std::endl;

	return;
}

void User::Change_Password()
{
	FILE *file;
	int i = 2;

	if (fopen_s(&file, pass_check_file.c_str(), "r"))
	{
		std::cout << "无法打开指定的用户文件，请检查您的文件配置。" << std::endl;
		exit(-1);
	}
	else
	{

		fscanf_s(file, "%s", user[0][0], THE_STR_LEN + 1);
		fscanf_s(file, "%s", user[0][1], THE_STR_LEN + 1);//读出表头

		fscanf_s(file, "%s", user[1][0], THE_STR_LEN + 1);
		fscanf_s(file, "%s", user[1][1], THE_STR_LEN + 1);//读第一个


		while (!feof(file))
		{
			fscanf_s(file, "%s", user[i][0], THE_STR_LEN + 1);
			fscanf_s(file, "%s", user[i][1], THE_STR_LEN + 1);
			i++;
		}

		std::string old_password;
		std::string new_password;

		std::string a;
		int j = 0;
		for (; j < i; j++)
		{
			a = user[j][0];
			if (user_name == a)//找到这个用户
				break;
		}
		a = user[j][1];

		std::cout << "请输入旧密码：";
		std::cin >> old_password;
		if (old_password == a)
		{
			std::cout << "请输入新密码：";
			do
			{
				std::cin >> new_password;
				if (new_password.length() > 20)
					std::cout << "密码长度不能大于20，请重新输入：";
			} while (new_password.length() > 20);

			strcpy_s(user[j][1], 21, new_password.c_str());//进行密码的书写
			fclose(file);

		}

		else
		{
			std::cout << "密码错误！" << std::endl;
			fclose(file);
			return;
		}
	}

	//下面需要进行密码的写入文件

	if (fopen_s(&file, pass_check_file.c_str(), "w"))
	{
		std::cout << "无法打开指定的用户文件，请检查您的文件配置。" << std::endl;
		exit(-1);
	}
	else
	{
		for (int j = 0; j < i - 1; j++)
		{
			fprintf_s(file, "%-32s%-32s\n", user[j][0], user[j][1]);
		}
	}

	fclose(file);

	std::cout << "密码修改成功！" << std::endl;

	return;
}