#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>

void PrintTime(size_t ratio_second_lgX)
{
	static std::chrono::steady_clock::time_point begin_start = std::chrono::high_resolution_clock::now();
	static std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();

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
	switch (ratio_second_lgX)
	{
	case 0:
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::seconds>(end - start)).count() << "单次耗时(秒)";
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::seconds>(end - begin_start)).count() << "总耗时(秒)";
		break;
	case 3:
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count() << "单次耗时(毫秒)";
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin_start)).count() << "总耗时(毫秒)";
		break;
	case 6:
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::microseconds>(end - start)).count() << "单次耗时(微秒)";
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin_start)).count() << "总耗时(微秒)";
		break;
	case 9:
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)).count() << "单次耗时(纳秒)";
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin_start)).count() << "总耗时(纳秒)";
		break;
	default:
		std::cout << "时间单位错误。";
		break;
	}
	

	start = std::chrono::high_resolution_clock::now();
}