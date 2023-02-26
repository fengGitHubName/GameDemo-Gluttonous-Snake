#include "CSnake.h"

CSnake::CSnake() {}

CSnake::CSnake( int _max_x, int _max_y) {
	// ��ʼ���ߵķ�Χ
	this->max_x = _max_x - 2;
	this->max_y = _max_y - 2;
}

// �ߵĳ�ʼ��
void CSnake::init(int _start_x, int _start_y) {
	if (_start_x < this->max_x && _start_y < this->max_y) {
		// ��ʼ���ߵ�����
		this->data.push_back({ _start_x, _start_y });
		this->data.push_back({ _start_x, _start_y - 1 });
		this->data.push_back({ _start_x, _start_y - 2 });
		// ��ʼ��ͷ����β��
		this->head = this->data.front();
		this->head_pre = this->head;
		this->tail_pre = this->data.back();

		// ��ʼ������
		this->direct = 's';
		this->direct_opposite = 'w';
	}
	else {
		cout << "�ߵĳ�ʼ��ʧ�ܣ�" << endl;
	}
}

// �ߵ��ƶ�
void CSnake::move() {
	// �洢һ��ԭ����ͷ��λ��
	this->head_pre = this->head;
	// ����ָ��������ڵ�ͷ��λ��
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

// �ߵĳɳ��ж�
bool CSnake::grow(vector<int> _food_data) {
	if (this->head[0] == _food_data[0]) {
		if (this->head[1] == _food_data[1]) {
			data.push_back(this->tail_pre);
			return true;
		}
	}
	return false;
}

// �ߵ������ж�
bool CSnake::alive() {
	// �����ж���ײǽ
	if (this->head[0] < 1 || this->head[0] > this->max_x) {
		return false;
	}
	if (this->head[1] < 1 || this->head[1] > this->max_y) {
		return false;
	}
	// �����ж���ҧ���Լ�
	for (int i = 4; i < this->data.size(); i++) { // ע��˴��Աȵ���ͷ������������㿪ʼ������
		if (this->head[0] == this->data[i][0] && this->head[1] == this->data[i][1]) {
			return false;
		}
	}
	return true;
}

// �ߵķ���ı�
void CSnake::update_direct(char _cmd) {
	// ���ܳ��������ƶ�
	if (_cmd != this->direct_opposite) {
		this->direct = _cmd;
	}
}

// �ߵ��ٶ�����
void CSnake::set_speed(int _speed) {
	// �ٶȷ�Χ4~15
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