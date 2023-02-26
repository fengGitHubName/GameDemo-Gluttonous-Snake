#pragma once
#include<iostream>
#include <random>
#include<deque>
#include<vector>
using namespace std;

class CFood
{
	public:
		// 构造函数
		CFood();
		CFood(int _max_x, int _max_y);

		// 成员变量
		int food_max_x;
		int food_max_y;
		vector<int> data;

		// 成员函数
		void create(deque<vector<int>> _snake_data);
		vector<int> get_data();
};

