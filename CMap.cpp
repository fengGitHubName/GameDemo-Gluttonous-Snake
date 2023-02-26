#include "CMap.h"

//���ܺ���:������ƶ���ָ��λ��
void my_gotoxy_printf(int x, int y, char c) {
	COORD pos = { x,y };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hout, pos);//���������ֱ���ָ���ĸ����壬����λ��
	printf("%c", c);
}

CMap::CMap() {}

CMap::CMap(int _x, int _y) {
	this->map_x = _x;
	this->map_y = _y;
	this->map_data = vector<vector<char>>(_y, vector<char>(_x, ' '));
}

// ��ͼ��ʼ��
void CMap::init() {
	// ǽ���� # ����ʾ
	// ��ʼ������ǽ��
	for (int i = 0; i < this->map_x; i++) {
		this->map_data[0][i] = '#';
		this->map_data[this->map_y-1][i] = '#';
	}
	// ��ʼ������ǽ��
	for (int i = 0; i < this->map_y; i++) {
		this->map_data[i][0] = '#';
		this->map_data[i][this->map_x-1] = '#';
	}
}

// ��ӡ��ͼ
void CMap::print() {
	for (vector<char> line : this->map_data) {
		for (char c : line) {
			cout << c << " ";
		}
		cout << endl;
	}
}

// ��ͼ�������
void CMap::get_snake(deque<vector<int>> _snake_data) {
	// ������ O ��ʾ
	for (vector<int> point : _snake_data) {
		this->map_data[point[1]][point[0]] = 'O';
	}
	// ��ͷ�� @ ��ʾ
	this->map_data[_snake_data.front()[1]][_snake_data.front()[0]] = '@';
}

// ��ͼ�����ʳ��
void CMap::get_food(vector<int> _food_data) {
	// ʳ���� * ����ʾ
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