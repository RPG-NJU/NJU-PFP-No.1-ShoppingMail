#include"head3.0.h"
#include<iostream>
#include<string>
#include<iomanip>


Admin::Admin()
{
	char the_store_list_filename[] = ".\\All_File\\Admin\\库存.txt";
	char the_store_sold_filename[] = ".\\All_File\\Admin\\已售清单.txt";
	char pass_check_filename[] = ".\\All_File\\Admin\\管理员账号.txt";
	admin_name = "NULL";
	admin_password = "NULL";//其实是无意义的赋值，最终就会改变
	the_store_list_file = the_store_list_filename;
	the_store_sold_file = the_store_sold_filename;
	pass_check_file = pass_check_filename;
	//这三个是对于文件路径的把握
}

Admin::~Admin()
{
	//std::cout << "clear" << std::endl;
}

bool Admin::Pass_Check()
{
	std::string name_input;
	std::string password_input;
	char name_in_file[THE_STR_LEN + 1];
	char password_in_file[THE_STR_LEN + 1];
	FILE *the_check_file;

	if (fopen_s(&the_check_file, pass_check_file.c_str(), "r"))
	{
		std::cout << "无法打开指定的管理员文件，请检查您的文件配置。" << std::endl;
		return false;
	}
	else
	{
		fscanf_s(the_check_file, "%s", name_in_file, THE_STR_LEN + 1);
		fscanf_s(the_check_file, "%s", password_in_file, THE_STR_LEN + 1);//将文件的头读出，不在列
		std::cout << "输入管理员账号：";
		std::cin >> name_input;//暂未考虑输出长度较长之后如何报错
		std::cout << "输入管理员密码：";
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
					admin_name = name_input;//将管理员名录入
					admin_password = password_input;
					fclose(the_check_file);
					std::cout << "登录成功！" << std::endl;
					return true;
				}
			}
		}
	}
	fclose(the_check_file);
	std::cout << "登陆失败，请检查您的管理员ID和密码。" << std::endl;
	return false;
}

//经过修改，把读取在循环中滞后，防止最后一组数据的多次重复读取引起的误差
void Admin::Init_The_Store_List()
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

void Admin::Print_List()
{
	std::cout.setf(std::ios::left);//左对齐
	std::cout << std::setw(THE_TAB) << "ID" << std::setw(THE_TAB) << "名称"
		<< std::setw(THE_TAB) << "品牌" << std::setw(THE_TAB) << "价格"
		<< std::setw(THE_TAB) << "数量" << std::endl;
	for (int i = 0; store_list[i].name != "NULL"; i++)
		std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
		<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
		<< std::setw(THE_TAB) << store_list[i].num << std::endl;
	return;
}

void Admin::Add_List()
{
	std::string name, brand;
	double price;
	int num;
	std::cout << "请输入商品的名称：";
	std::cin >> name;
	std::cout << "请输入商品的品牌：";
	std::cin >> brand;
	std::cout << "请输入商品的价格：";
	std::cin >> price;
	std::cout << "请输入商品的数量：";
	std::cin >> num;

	int i = 0;
	for (; store_list[i].ID != "NULL"; i++)
	{
		if (store_list[i].name == name && store_list[i].brand == brand && store_list[i].price == price)
		{
			store_list[i].num += num;
			std::cout << "该商品已经存在于库存，将数量修改为" << store_list[i].num << std::endl;
			this->Write_List_File();
			return;
		}
	}
	//以下是没有该商品的添加情况
	int n = 0;
	char add[10];
	n = atoi(&(store_list[i - 1].ID[1]));
	n++;
	if (n > 999)
		sprintf_s(add, 10, "F%d", n);
	else if (n > 99)
		sprintf_s(add, 10, "F0%d", n);
	else if (n > 9)
		sprintf_s(add, 10, "F00%d", n);
	else
		sprintf_s(add, 10, "F000%d", n);

	store_list[i].ID = add;
	store_list[i].name = name;
	store_list[i].brand = brand;
	store_list[i].price = price;
	store_list[i].num = num;
	std::cout << "增加了新进的商品：" << std::endl;
	std::cout << "ID：" << store_list[i].ID << "  名称：" << store_list[i].name << "  品牌："
		<< store_list[i].brand << "  价格：" << store_list[i].price << "  数量：" << store_list[i].num << std::endl;
	this->Write_List_File();
	return;
}

void Admin::Write_List_File() const
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

void Admin::Delete_Thing()
{
	std::string ID;
	bool x = false;

	this->Print_List();//输出所有的商品

	std::cout << "请输入你要下架的商品ID：";
	std::cin >> ID;

	for (int i = 0; store_list[i].ID != "NULL"; i++)
	{
		if (store_list[i].ID == ID)
		{
			store_list[i].num = -1;
			std::cout << "商品 " << store_list[i].name << "-" << store_list[i].brand << " 下架" << std::endl;
			x = true;
			break;
		}
	}
	if (x)
		this->Write_List_File();
	return;
}

void Admin::Change_List()
{
	std::string ID, input;

	this->Print_List();
	std::cout << "请输入你要修改的商品ID：";
	std::cin >> ID;

	for (int i = 0; store_list[i].ID != "NULL"; i++)
	{
		if (store_list[i].ID == ID)
		{
			std::cout << "商品 " << store_list[i].name << "的价格为：" << store_list[i].price
				<< "元，修改为：";
			std::cin >> input;
			store_list[i].price = atof(input.c_str());//使用atof将string变为float型
			std::cout << "商品 " << store_list[i].name << "的数量为：" << store_list[i].num
				<< "，修改为：";
			std::cin >> input;
			store_list[i].num = atoi(input.c_str());
			this->Write_List_File();
			return;
		}
	}

	std::cout << "你所要修改的商品不存在！" << std::endl;

	return;
}

void Admin::Init_Sold_List()
{
	FILE *file;
	char get1[THE_STR_LEN + 1], get2[THE_STR_LEN + 1], get3[THE_STR_LEN + 1], get6[THE_STR_LEN + 1];
	double get4;
	int get5;

	if (fopen_s(&file, the_store_sold_file.c_str(), "r"))
	{
		std::cout << "请检查你的文件配置！" << std::endl;
		exit(-1);
	}
	else
	{
		for (int i = 0; i < 6; i++)
			fscanf_s(file, "%s", get1, THE_STR_LEN + 1);
		int i = 0;
		fscanf_s(file, "%s%s%s%lf%d%s", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5, get6, THE_STR_LEN + 1);
		while (!feof(file))
		{
			list[i].ID = get1;
			list[i].name = get2;
			list[i].brand = get3;
			list[i].price = get4;
			list[i].num = get5;
			list[i].owner = get6;//这是一个全新的数据，但是在这里并没有作用，只是加一个接口，以便之后的附加功能
			i++;
			fscanf_s(file, "%s%s%s%lf%d%s", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5, get6, THE_STR_LEN + 1);
		}
	}

	fclose(file);
	return;
}

void Admin::Print_Sold_List() const
{
	std::cout.setf(std::ios::left);//左对齐
	std::cout << std::setw(THE_TAB) << "ID" << std::setw(THE_TAB) << "名称"
		<< std::setw(THE_TAB) << "品牌" << std::setw(THE_TAB) << "价格"
		<< std::setw(THE_TAB) << "数量" << std::endl;//打印头***********************
	for (int i = 0; store_list[i].ID != "NULL"; i++)//以store_list作为升序的基础
	{
		double price_list[200][2] = { 0 };
		for (int j = 0; list[j].ID != "NULL"; j++)//4.7增加功能，输出不同价格的同商品的售出
		{
			bool px = false;

			if (list[j].ID == store_list[i].ID)
			{
				int pi = 0;
				for (; price_list[pi][0] != 0; pi++)
				{
					if (list[j].price == price_list[pi][0])
					{
						px = true;
						price_list[pi][1] += list[j].num;
					}
				}
				if (!px)
				{
					price_list[pi][0] = list[j].price;
					price_list[pi][1] = list[j].num;
				}
			}
			px = false;
		}
		for (int pi = 0; price_list[pi][0] != 0; pi++)
		{
			if (price_list[pi][1] != 0)
			{
				std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
					<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << price_list[pi][0]
					<< std::setw(THE_TAB) << price_list[pi][1] << std::endl;
			}
		}
	}
	return;
}
//以上是管理员功能的函数构造，以下是用户的函数构造

