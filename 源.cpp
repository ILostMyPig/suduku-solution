// 暴力枚举。有人说这样非常快，所以尝试一下。

#define COMPILE_THIS_FILE
#ifdef COMPILE_THIS_FILE
#include <iostream>
#include <chrono>
#include <iomanip>


/// <summary>
/// 输出类似以下格式的时间（取决于你的系统时间）2023-03-21 12:34:56
/// </summary>
void PrintTime()
{
	static std::chrono::steady_clock::time_point begin_start = std::chrono::high_resolution_clock::now();
	static std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();

	std::string timing_unit = "(毫秒)";
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto begin_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin_start);

	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间

	//格式化输出本地时间
	std::cout << t.tm_year + 1900 << "年";
	std::cout << std::setw(2) << t.tm_mon + 1 << "月";
	std::cout << std::setw(2) << t.tm_mday << "日";
	std::cout << t.tm_wday << "周";//星期是从星期日开始，星期日是0
	std::cout << std::setw(3) << t.tm_yday << "天";
	std::cout << std::setw(2) << t.tm_hour << "时";
	std::cout << std::setw(2) << t.tm_min << "分";
	std::cout << std::setw(2) << t.tm_sec << "秒";
	std::cout << t.tm_isdst << "夏令时";
	std::cout << std::setw(6) << elapsed.count() << "单次耗时" << timing_unit;
	std::cout << std::setw(6) << begin_elapsed.count() << "总耗时" << timing_unit;

	start = std::chrono::high_resolution_clock::now();
}




bool SameNum(int(&enum_suduku)[9][9])
{
	// 行
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

	// 列
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

	// 小宫格
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
	// 题目。需要填写的位置就是0。
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

	// 答案。（用于测试）
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

	// 每一个需要填入的空格都用不同的负数填充。
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
