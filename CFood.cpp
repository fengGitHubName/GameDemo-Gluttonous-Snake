#include "CFood.h"

CFood::CFood() {

}

CFood::CFood(int _max_x, int _max_y) {
	this->food_max_x = _max_x - 2;
	this->food_max_y = _max_y - 2;
	this->data = { 1, 1 };
}

// ʳ����������
void CFood::create(deque<vector<int>> _snake_data) {
	random_device rd;  // ���ڻ�ȡ�������
	mt19937 gen(rd());  // �������������������
	gen.seed(time(0));  // ��������ֵΪ��ǰʱ��

	bool has_create = false;
	int random_x = 1;
	int random_y = 1;
	while (!has_create) {
		// ��ȡ����� x ֵ
		uniform_int_distribution<> dis_x(1, this->food_max_x);  // ����[1, food_max_x]֮�������
		random_x = dis_x(gen);  // ���������

		// ��ȡ����� y ֵ
		uniform_int_distribution<> dis_y(1, this->food_max_y);  // ����[1, 100]֮�������
		random_y = dis_y(gen);  // ���������

		has_create = true;

		// �ж��Ƿ��������غ�
		for (vector<int> point : _snake_data) {
			if (random_x == point[0] && random_y == point[1]) {
				has_create = false;
				break;
			}
			else {
				continue;
			}
		}
	}
	this->data = { random_x, random_y };
}

vector<int> CFood::get_data() {
	return this->data;
}
