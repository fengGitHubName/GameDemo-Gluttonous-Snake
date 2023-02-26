#pragma once
#include<iostream>
#include <random>
#include<deque>
#include<vector>
using namespace std;

class CFood
{
	public:
		// ���캯��
		CFood();
		CFood(int _max_x, int _max_y);

		// ��Ա����
		int food_max_x;
		int food_max_y;
		vector<int> data;

		// ��Ա����
		void create(deque<vector<int>> _snake_data);
		vector<int> get_data();
};

