#pragma once
#include<iostream>
#include<string>

#define THE_STORE_MAX 200
#define THE_STR_LEN 20
#define THE_TAB 16

struct LIST
{
	std::string ID = "NULL";
	std::string name = "NULL";
	std::string brand = "NULL";
	double price = 0.0;
	int num = 0;//一般是大于0，-1为错误标记，表示该商品已经下架
	std::string owner = "NULL";//一般指向用户，在商品的读取的时候不进行使用
							   //在2.1的版本中，除了对于上述本来的作用之外，可以作为一个备用的接口，在wish_list中，拟作为一个标志，显示该商品是否异常
};

class Admin
{
private:
	std::string admin_name;
	std::string admin_password;
	std::string the_store_list_file;//作为所有的商品的储存目录
	std::string the_store_sold_file;//作为所有的已售商品的目录
	std::string pass_check_file;//作为登录信息的检测
	LIST store_list[THE_STORE_MAX];
	LIST list[10 * THE_STORE_MAX];//做为已售清单的列表
public:
	Admin();
	~Admin();
	bool Pass_Check();
	void Init_The_Store_List();
	void Print_List();
	void Add_List();
	void Write_List_File() const;
	void Delete_Thing();
	void Change_List();
	void Init_Sold_List();
	void Print_Sold_List() const;
};

class User
{
private:
	std::string user_name;
	std::string user_password;
	std::string the_store_list_file;
	std::string pass_check_file;
	std::string wish_file;
	std::string pay_file;
	std::string the_store_sold_file;
	LIST store_list[THE_STORE_MAX];
	LIST wish_list[THE_STORE_MAX];
	LIST pay_list[THE_STORE_MAX];
	char user[101][2][21];
public:
	User();
	~User();
	void New_User();
	void Init_Filename();
	bool Pass_Check();
	void Init_The_Store_List();
	void Init_Wish_List();
	void Init_Pay_List();
	void Print_List();//打印商品的所有清单
	void Print_Wish_List();
	void Write_List_File() const;
	void Write_Wish_File() const;
	void Write_Pay_File() const;
	void Search();
	void Add_Wish();
	void Change_Wish();
	void Pay();
	void Change_Password();
};


