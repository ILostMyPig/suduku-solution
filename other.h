#pragma once
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