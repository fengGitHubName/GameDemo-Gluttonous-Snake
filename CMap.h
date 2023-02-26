#pragma once
#include<iostream>
#include<deque>
#include<vector>
#include <windows.h>
#include <stdio.h>

using namespace std;

class CMap
{
	public:
		// 构造函数
		CMap();
		CMap(int _x, int _y);

		// 成员变量
		int map_x = 50;
		int map_y = 50;
		vector<vector<char>> map_data;

		// 成员函数
		void init();
		void print();
		void get_snake(deque<vector<int>> _snake_data);
		void get_food(vector<int> _food_data);
		void update_snake_old(vector<int> _head, vector<int> _head_pre, vector<int> _tail, bool grow);
		void update_snake(vector<int> _head, vector<int> _head_pre, vector<int> _tail, bool grow);
		void update_food(vector<int> _food_data);
};

void my_gotoxy_printf(int x, int y, char c);