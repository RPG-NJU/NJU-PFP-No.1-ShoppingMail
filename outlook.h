#pragma once

#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include<cstdlib>





class Outlook
{
private:
	std::string start_1[17];//第一种开机界面
	std::string start_2[10];

	std::string second[20];//作为欢迎界面

	std::string logo[20];//作为贯穿的logo设计
	std::string short_logo[10];

	std::string end[10];//作为最后的关机界面
public:
	Outlook();
	void print_start(int mode);
	void main_menu();
	void user_menu();
	void admin_menu();
	void low();
	void goodbye();
};