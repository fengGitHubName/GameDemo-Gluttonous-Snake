#include "CFood.h"

CFood::CFood() {

}

CFood::CFood(int _max_x, int _max_y) {
	this->food_max_x = _max_x - 2;
	this->food_max_y = _max_y - 2;
	this->data = { 1, 1 };
}

// 食物的随机产生
void CFood::create(deque<vector<int>> _snake_data) {
	random_device rd;  // 用于获取随机种子
	mt19937 gen(rd());  // 用于生成随机数的引擎
	gen.seed(time(0));  // 设置种子值为当前时间

	bool has_create = false;
	int random_x = 1;
	int random_y = 1;
	while (!has_create) {
		// 获取随机的 x 值
		uniform_int_distribution<> dis_x(1, this->food_max_x);  // 生成[1, food_max_x]之间的整数
		random_x = dis_x(gen);  // 生成随机数

		// 获取随机的 y 值
		uniform_int_distribution<> dis_y(1, this->food_max_y);  // 生成[1, 100]之间的整数
		random_y = dis_y(gen);  // 生成随机数

		has_create = true;

		// 判断是否与蛇身重合
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
