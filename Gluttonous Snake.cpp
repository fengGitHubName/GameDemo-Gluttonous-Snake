#include <iostream>
#include <Windows.h>
//#include<cstdlib>;
#include <chrono>
#include <thread>
#include "CMap.h"
#include "CSnake.h"
#include "CFood.h"

using namespace std;

int main() {
	int max_x = 30; // 尺寸
	int max_y = 30;
	int goal = 0;  // 分数
	bool start = false;
	bool snake_alive = true;
	bool snake_grow = false;
	
	// 实例化地图
	CMap map(max_x, max_y);
	map.init();

	// 实例化蛇
	CSnake snake(max_x, max_y);
	snake.init(5, 5);

	// 实例化食物
	CFood food(max_x, max_y);
	food.create(snake.get_data());

	// 将蛇和食物打印在地图上
	map.get_snake(snake.get_data());
	map.get_food(food.data);
	map.print();

	// 等待游戏开始
	my_gotoxy_printf(2 * max_x + 4, 4, ' ');
	cout << "游戏规则：    上-W    下-S    左-A    右-D" << endl;
	my_gotoxy_printf(2 * max_x + 4, 6, ' ');
	cout << "按下 G 键开始游戏！" << endl;

	while (!(GetAsyncKeyState('G') & 0x8000));
	my_gotoxy_printf(2 * max_x + 4, 8, ' ');
	cout << "Goal : " << goal << "    " << "Game in progress..." << endl;

	// 当蛇活着时游戏继续
	while (snake_alive) {
		// 检测键盘按键
		for (int i = 0; i < 100/snake.get_speed(); i++) {
			this_thread::sleep_for(std::chrono::milliseconds(5));
			if (GetAsyncKeyState('W') & 0x8000) //检测A键是否按下
			{
				snake.update_direct('w');
			}
			if (GetAsyncKeyState('S') & 0x8000) //检测S键是否按下
			{
				snake.update_direct('s');
			}
			if (GetAsyncKeyState('A') & 0x8000) //检测A键是否按下
			{
				snake.update_direct('a');
			}
			if (GetAsyncKeyState('D') & 0x8000) //检测D键是否按下
			{
				snake.update_direct('d');
			}
		}
		// 蛇移动并判断是否存活和成长
		snake.move();
		snake_alive = snake.alive();
		snake_grow = snake.grow(food.get_data());
		
		// 如果成长，则分数增加、加速、生成新的食物
		if (snake_grow) {
			goal++;
			snake.set_speed(4 + goal/5);  // 每五分加一次速
			food.create(snake.get_data());
			map.update_food(food.get_data());
			// 更新分数
			my_gotoxy_printf(2 * max_x + 4, 8, ' ');
			cout << "Goal : " << goal << "    " << "Game in progress..." << endl;
		}

		// 更新蛇的位置
		map.update_snake(snake.get_head(), snake.get_head_pre(), snake.get_tail_pre(), snake_grow);
		my_gotoxy_printf(2 * max_x + 1, max_y + 1, ' ');
	}

	// 游戏结束
	my_gotoxy_printf(2 *max_x + 4, 8, ' ');
	cout << "Goal : " << goal << "    " << "Game Over!!!             " << endl;

	my_gotoxy_printf(1, max_y + 2, ' ');
	system("pause");
	return 0;
}