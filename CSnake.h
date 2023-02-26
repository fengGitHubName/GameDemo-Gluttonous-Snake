#pragma once
#include<iostream>
#include<deque>
#include<vector>
using namespace std;

class CSnake
{
	public:
		// 构造函数
		CSnake();
		CSnake(int _max_x, int _max_y);

		// 成员变量
		int max_x;
		int max_y;
		deque<vector<int>> data;
		vector<int> head;
		vector<int> head_pre;
		vector<int> tail_pre; // 这里的尾巴是指移动前的尾巴，不是当前的尾巴
		
		int speed = 4;
		char direct = 's';
		char direct_opposite = 'w';

		// 成员函数
		void init(int _start_x, int _start_y);
		void move();
		bool grow(vector<int> _food_data);
		bool alive();
		void update_direct(char _cmd);
		void set_speed(int _speed);

		deque<vector<int>> get_data();
		vector<int> get_head();
		vector<int> get_head_pre();
		vector<int> get_tail_pre();
		int get_speed();
};

