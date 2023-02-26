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
	int max_x = 30; // �ߴ�
	int max_y = 30;
	int goal = 0;  // ����
	bool start = false;
	bool snake_alive = true;
	bool snake_grow = false;
	
	// ʵ������ͼ
	CMap map(max_x, max_y);
	map.init();

	// ʵ������
	CSnake snake(max_x, max_y);
	snake.init(5, 5);

	// ʵ����ʳ��
	CFood food(max_x, max_y);
	food.create(snake.get_data());

	// ���ߺ�ʳ���ӡ�ڵ�ͼ��
	map.get_snake(snake.get_data());
	map.get_food(food.data);
	map.print();

	// �ȴ���Ϸ��ʼ
	my_gotoxy_printf(2 * max_x + 4, 4, ' ');
	cout << "��Ϸ����    ��-W    ��-S    ��-A    ��-D" << endl;
	my_gotoxy_printf(2 * max_x + 4, 6, ' ');
	cout << "���� G ����ʼ��Ϸ��" << endl;

	while (!(GetAsyncKeyState('G') & 0x8000));
	my_gotoxy_printf(2 * max_x + 4, 8, ' ');
	cout << "Goal : " << goal << "    " << "Game in progress..." << endl;

	// ���߻���ʱ��Ϸ����
	while (snake_alive) {
		// �����̰���
		for (int i = 0; i < 100/snake.get_speed(); i++) {
			this_thread::sleep_for(std::chrono::milliseconds(5));
			if (GetAsyncKeyState('W') & 0x8000) //���A���Ƿ���
			{
				snake.update_direct('w');
			}
			if (GetAsyncKeyState('S') & 0x8000) //���S���Ƿ���
			{
				snake.update_direct('s');
			}
			if (GetAsyncKeyState('A') & 0x8000) //���A���Ƿ���
			{
				snake.update_direct('a');
			}
			if (GetAsyncKeyState('D') & 0x8000) //���D���Ƿ���
			{
				snake.update_direct('d');
			}
		}
		// ���ƶ����ж��Ƿ���ͳɳ�
		snake.move();
		snake_alive = snake.alive();
		snake_grow = snake.grow(food.get_data());
		
		// ����ɳ�����������ӡ����١������µ�ʳ��
		if (snake_grow) {
			goal++;
			snake.set_speed(4 + goal/5);  // ÿ��ּ�һ����
			food.create(snake.get_data());
			map.update_food(food.get_data());
			// ���·���
			my_gotoxy_printf(2 * max_x + 4, 8, ' ');
			cout << "Goal : " << goal << "    " << "Game in progress..." << endl;
		}

		// �����ߵ�λ��
		map.update_snake(snake.get_head(), snake.get_head_pre(), snake.get_tail_pre(), snake_grow);
		my_gotoxy_printf(2 * max_x + 1, max_y + 1, ' ');
	}

	// ��Ϸ����
	my_gotoxy_printf(2 *max_x + 4, 8, ' ');
	cout << "Goal : " << goal << "    " << "Game Over!!!             " << endl;

	my_gotoxy_printf(1, max_y + 2, ' ');
	system("pause");
	return 0;
}