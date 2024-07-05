// ����ö�١�����˵�����ǳ��죬���Գ���һ�¡�

#define COMPILE_THIS_FILE
#ifdef COMPILE_THIS_FILE
#include <iostream>
#include <chrono>
#include <iomanip>


/// <summary>
/// ����������¸�ʽ��ʱ�䣨ȡ�������ϵͳʱ�䣩2023-03-21 12:34:56
/// </summary>
void PrintTime()
{
	static std::chrono::steady_clock::time_point begin_start = std::chrono::high_resolution_clock::now();
	static std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();

	std::string timing_unit = "(����)";
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto begin_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin_start);

	struct tm t;   //tm�ṹָ��
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);   //��ȡ�������ں�ʱ��

	//��ʽ���������ʱ��
	std::cout << t.tm_year + 1900 << "��";
	std::cout << std::setw(2) << t.tm_mon + 1 << "��";
	std::cout << std::setw(2) << t.tm_mday << "��";
	std::cout << t.tm_wday << "��";//�����Ǵ������տ�ʼ����������0
	std::cout << std::setw(3) << t.tm_yday << "��";
	std::cout << std::setw(2) << t.tm_hour << "ʱ";
	std::cout << std::setw(2) << t.tm_min << "��";
	std::cout << std::setw(2) << t.tm_sec << "��";
	std::cout << t.tm_isdst << "����ʱ";
	std::cout << std::setw(6) << elapsed.count() << "���κ�ʱ" << timing_unit;
	std::cout << std::setw(6) << begin_elapsed.count() << "�ܺ�ʱ" << timing_unit;

	start = std::chrono::high_resolution_clock::now();
}




bool SameNum(int(&enum_suduku)[9][9])
{
	// ��
	for (size_t i = 0; i < 9; i++)
	{
		bool same_num[10] = { false };
		for (size_t ii = 0; ii < 9; ii++)
		{
			int t = enum_suduku[i][ii];
			if (same_num[t])
			{
				return false;
			}
			else
			{
				same_num[t] = true;
			}
		}
	}

	// ��
	for (size_t i = 0; i < 9; i++)
	{
		bool same_num[10] = { false };
		for (size_t ii = 0; ii < 9; ii++)
		{
			int t = enum_suduku[ii][i];
			if (same_num[t])
			{
				return false;
			}
			else
			{
				same_num[t] = true;
			}
		}
	}

	// С����
	for (size_t r = 0; r < 9; r += 3)
	{
		for (size_t c = 0; c < 9; c += 3)
		{
			bool same_num[10] = { false };
			for (size_t rr = 0; rr < 3; rr++)
			{
				for (size_t cc = 0; cc < 3; cc++)
				{
					int t = enum_suduku[r + rr][c + cc];
					if (same_num[t])
					{
						return false;
					}
					else
					{
						same_num[t] = true;
					}
				}
			}
		}
	}

	return true;
}

void Print_suduku(int(&enum_suduku)[9][9])
{
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t ii = 0; ii < 9; ii++)
		{
			std::cout << enum_suduku[i][ii];
		}
		std::cout << std::endl;
	}
}

void EnumLoop(int(&enum_suduku)[9][9],int r,int c)
{
	for (size_t i = 1; i <= 9; i++)
	{
		enum_suduku[r][c] = i;
		if (SameNum(enum_suduku))
		{
			Print_suduku(enum_suduku);
		}
		else
		{
			
		}
	}
}

int main()
{
	std::cout << "Hello World!\n";


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

	// ÿһ����Ҫ����Ŀո��ò�ͬ�ĸ�����䡣
	int to_not_same = -1;
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t ii = 0; ii < 9; ii++)
		{
			if (enum_suduku[i][ii]==0)
			{
				enum_suduku[i][ii] = to_not_same;
				to_not_same--;
			}
		}
	}


	for (size_t i = 0; i < 9; i++)
	{
		for (size_t ii = 0; ii < 9; ii++)
		{

		}
	}























	PrintTime(); std::cout << "Hello World!" << std::endl;
	return 0;
}
#endif // COMPILE_THIS_FILE
