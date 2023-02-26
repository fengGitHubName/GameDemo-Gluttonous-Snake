#include "CMap.h"

//功能函数:将光标移动到指定位置
void my_gotoxy_printf(int x, int y, char c) {
	COORD pos = { x,y };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hout, pos);//两个参数分别是指定哪个窗体，具体位置
	printf("%c", c);
}

CMap::CMap() {}

CMap::CMap(int _x, int _y) {
	this->map_x = _x;
	this->map_y = _y;
	this->map_data = vector<vector<char>>(_y, vector<char>(_x, ' '));
}

// 地图初始化
void CMap::init() {
	// 墙壁以 # 来表示
	// 初始化上下墙壁
	for (int i = 0; i < this->map_x; i++) {
		this->map_data[0][i] = '#';
		this->map_data[this->map_y-1][i] = '#';
	}
	// 初始化左右墙壁
	for (int i = 0; i < this->map_y; i++) {
		this->map_data[i][0] = '#';
		this->map_data[i][this->map_x-1] = '#';
	}
}

// 打印地图
void CMap::print() {
	for (vector<char> line : this->map_data) {
		for (char c : line) {
			cout << c << " ";
		}
		cout << endl;
	}
}

// 地图中添加蛇
void CMap::get_snake(deque<vector<int>> _snake_data) {
	// 蛇身以 O 表示
	for (vector<int> point : _snake_data) {
		this->map_data[point[1]][point[0]] = 'O';
	}
	// 蛇头以 @ 表示
	this->map_data[_snake_data.front()[1]][_snake_data.front()[0]] = '@';
}

// 地图中添加食物
void CMap::get_food(vector<int> _food_data) {
	// 食物以 * 来表示
	this->map_data[_food_data[1]][_food_data[0]] = '*';
}

void CMap::update_snake_old(vector<int> _head, vector<int> _head_pre, vector<int> _tail, bool grow) {
	this->map_data[_head[1]][_head[0]] = '@';
	this->map_data[_head_pre[1]][_head_pre[0]] = 'O';
	if (!grow) {
		this->map_data[_tail[1]][_tail[0]] = ' ';
	}
}

void CMap::update_snake(vector<int> _head, vector<int> _head_pre, vector<int> _tail, bool grow) {
	my_gotoxy_printf(_head[0] * 2, _head[1], '@');
	my_gotoxy_printf(_head_pre[0] * 2, _head_pre[1], 'O');
	if (!grow) {
		my_gotoxy_printf(_tail[0] * 2, _tail[1], ' ');
	}
}

void CMap::update_food(vector<int> _food_data) {
	my_gotoxy_printf(_food_data[0] * 2, _food_data[1], '*');
}