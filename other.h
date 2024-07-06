#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>

void PrintTime(size_t ratio_second_lgX)
{
	static std::chrono::steady_clock::time_point begin_start = std::chrono::high_resolution_clock::now();
	static std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();

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
	switch (ratio_second_lgX)
	{
	case 0:
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::seconds>(end - start)).count() << "���κ�ʱ(��)";
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::seconds>(end - begin_start)).count() << "�ܺ�ʱ(��)";
		break;
	case 3:
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count() << "���κ�ʱ(����)";
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin_start)).count() << "�ܺ�ʱ(����)";
		break;
	case 6:
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::microseconds>(end - start)).count() << "���κ�ʱ(΢��)";
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin_start)).count() << "�ܺ�ʱ(΢��)";
		break;
	case 9:
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)).count() << "���κ�ʱ(����)";
		std::cout << std::setw(6) << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin_start)).count() << "�ܺ�ʱ(����)";
		break;
	default:
		std::cout << "ʱ�䵥λ����";
		break;
	}
	

	start = std::chrono::high_resolution_clock::now();
}