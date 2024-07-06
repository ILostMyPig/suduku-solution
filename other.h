#pragma once
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