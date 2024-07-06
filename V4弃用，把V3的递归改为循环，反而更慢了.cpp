// ����ö�١�
// �Ż����ݹ��ѭ����


//#define COMPILE_THIS_FILE
#ifdef COMPILE_THIS_FILE
#include <iostream>
#include <chrono>
#include <iomanip>

#include "other.h"



bool CheckSameNum(int(&enum_suduku)[9][9], int  r, int c)
{
	// ��
	for (size_t cc = 0; cc < c; cc++)
	{
		if (enum_suduku[r][cc] == enum_suduku[r][c])
		{
			return false;
		}
	}
	for (size_t cc = c + 1; cc < 9; cc++)
	{
		if (enum_suduku[r][cc] == enum_suduku[r][c])
		{
			return false;
		}
	}


	// ��
	for (size_t rr = 0; rr < r; rr++)
	{
		if (enum_suduku[rr][c] == enum_suduku[r][c])
		{
			return false;
		}
	}
	for (size_t rr = r + 1; rr < 9; rr++)
	{
		if (enum_suduku[rr][c] == enum_suduku[r][c])
		{
			return false;
		}
	}

	// С����
	//for (size_t i = 0; i < 9; i++)
	//{
	//	std::cout << i / 3 << std::endl;
	//} // 000111222
	int xr = r / 3; // ��Ҫ�ϲ����㣬�Ա���������Ż���Ҫ����С��ת���������ݶ�ʧ�ص㡣
	xr = xr * 3;
	int xc = c / 3;
	xc = xc * 3;
	for (size_t rr = 0; rr < 3; rr++)
	{
		for (size_t cc = 0; cc < 3; cc++)
		{
			if (xr + rr != r || xc + cc != c)
			{
				if (enum_suduku[xr + rr][xc + cc] == enum_suduku[r][c])
				{
					return false;
				}
			}
		}
	}

	return true;
}

int main()
{
	PrintTime(6); std::cout << "Hello World!\n";


#pragma region suduku
	// ��Ŀ����Ҫ��д��λ�þ���0��
	int suduku[9][9] = {
		{0,0,6,0,0,8,4,0,0},
		{0,0,0,9,0,0,0,0,0},
		{1,0,2,0,0,4,0,0,0},
		{5,0,8,0,0,3,0,0,0},
		{0,2,3,7,9,0,0,8,0},
		{0,7,0,0,0,0,0,6,0},
		{0,0,0,2,8,0,3,0,0},
		{0,0,0,4,0,1,0,5,6},
		{0,0,0,0,0,0,0,9,0}
	};

	//int suduku[9][9] = {
	//	{6,7,0,0,0,0,0,0,0},
	//	{0,0,0,0,0,0,3,8,0},
	//	{2,0,0,9,0,0,0,5,0},
	//	{0,0,0,0,0,4,9,0,0},
	//	{0,0,9,0,0,3,2,4,0},
	//	{0,8,0,5,0,0,0,0,0},
	//	{0,6,7,0,2,0,1,0,0},
	//	{0,0,0,0,9,0,0,0,7},
	//	{5,0,0,0,4,0,0,6,0}
	//};

	// �𰸡������ڲ��ԣ�
	//	int suduku[9][9] = {
	//{3,7,9,4,8,1,5,2,6},
	//{8,2,4,5,7,6,3,1,9},
	//{6,5,1,2,3,9,4,7,8},
	//{1,6,5,7,9,2,8,4,3},
	//{9,4,3,1,6,8,2,5,7},
	//{2,8,7,3,5,4,6,9,1},
	//{7,9,8,6,4,5,1,3,2},
	//{5,3,2,8,1,7,9,6,4},
	//{4,1,6,9,2,3,7,8,5}
	//	};


#pragma endregion

	int enum_suduku[9][9] = { 0 };
	memcpy(enum_suduku, suduku, sizeof(int) * 9 * 9);

	int r = 0;
	int c = 0;
	do
	{
		if (r == 9)
		{
			std::cout << "���ִ𰸣�" << std::endl;
			for (size_t i = 0; i < 9; i++)
			{
				for (size_t ii = 0; ii < 9; ii++)
				{
					std::cout << enum_suduku[i][ii];
				}
				std::cout << std::endl;
			}
			c--; if (c == -1) { c = 8; r--; }
		}
		else if (suduku[r][c] != 0)
		{
			c++; if (c == 9) { c = 0; r++; }
		}
		else
		{
			enum_suduku[r][c]++;
			if (enum_suduku[r][c] == 10)
			{
				enum_suduku[r][c] = 0;
				c--; if (c == -1) { c = 8; r--; }
				while (suduku[r][c] != 0)
				{
					c--; if (c == -1) { c = 8; r--; }
				}
			}
			else
			{
				if (CheckSameNum(enum_suduku, r, c))
				{
					c++; if (c == 9) { c = 0; r++; }
				}
			}
		}
	} while (r != -1);



	PrintTime(6); std::cout << "Hello World!" << std::endl;
	return 0;
}

//2024�� 7�� 6��6��187��20ʱ20��14��0����ʱ     0���κ�ʱ(΢��)     1�ܺ�ʱ(΢��)Hello World!
//���ִ𰸣�
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024�� 7�� 6��6��187��20ʱ20��14��0����ʱ 20134���κ�ʱ(΢��) 23427�ܺ�ʱ(΢��)Hello World!

#endif // COMPILE_THIS_FILE
