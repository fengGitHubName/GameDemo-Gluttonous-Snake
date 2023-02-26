#include "CSnake.h"

CSnake::CSnake() {}

CSnake::CSnake( int _max_x, int _max_y) {
	// 初始化蛇的范围
	this->max_x = _max_x - 2;
	this->max_y = _max_y - 2;
}

// 蛇的初始化
void CSnake::init(int _start_x, int _start_y) {
	if (_start_x < this->max_x && _start_y < this->max_y) {
		// 初始化蛇的身体
		this->data.push_back({ _start_x, _start_y });
		this->data.push_back({ _start_x, _start_y - 1 });
		this->data.push_back({ _start_x, _start_y - 2 });
		// 初始化头部和尾部
		this->head = this->data.front();
		this->head_pre = this->head;
		this->tail_pre = this->data.back();

		// 初始化方向
		this->direct = 's';
		this->direct_opposite = 'w';
	}
	else {
		cout << "蛇的初始化失败！" << endl;
	}
}

// 蛇的移动
void CSnake::move() {
	// 存储一下原来的头部位置
	this->head_pre = this->head;
	// 根据指令更新现在的头部位置
	switch (this->direct) {
		case 'w':
			this->head[1]--;
			this->direct_opposite = 's';
			break;
		case 's':
			this->head[1]++;
			this->direct_opposite = 'w';
			break;
		case 'a':
			this->head[0]--;
			this->direct_opposite = 'd';
			break;
		case 'd':
			this->head[0]++;
			this->direct_opposite = 'a';
			break;
	}
	this->data.push_front(this->head);

	this->tail_pre = this->data.back();
	this->data.pop_back();
}

// 蛇的成长判定
bool CSnake::grow(vector<int> _food_data) {
	if (this->head[0] == _food_data[0]) {
		if (this->head[1] == _food_data[1]) {
			data.push_back(this->tail_pre);
			return true;
		}
	}
	return false;
}

// 蛇的死亡判定
bool CSnake::alive() {
	// 死亡判定：撞墙
	if (this->head[0] < 1 || this->head[0] > this->max_x) {
		return false;
	}
	if (this->head[1] < 1 || this->head[1] > this->max_y) {
		return false;
	}
	// 死亡判定：咬到自己
	for (int i = 4; i < this->data.size(); i++) { // 注意此处对比的是头部与第五个身体点开始的数据
		if (this->head[0] == this->data[i][0] && this->head[1] == this->data[i][1]) {
			return false;
		}
	}
	return true;
}

// 蛇的方向改变
void CSnake::update_direct(char _cmd) {
	// 不能朝反方向移动
	if (_cmd != this->direct_opposite) {
		this->direct = _cmd;
	}
}

// 蛇的速度设置
void CSnake::set_speed(int _speed) {
	// 速度范围4~15
	if (_speed > 4 && _speed < 15) {
		this->speed = _speed;
	}
}

deque<vector<int>> CSnake::get_data() {
	return this->data;
}

vector<int> CSnake::get_head() {
	return this->head;
}

vector<int> CSnake::get_head_pre() {
	return this->head_pre;
}

vector<int> CSnake::get_tail_pre() {
	return this->tail_pre;
}

int CSnake::get_speed() {
	return this->speed;
}