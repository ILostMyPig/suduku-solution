// ÿ�ж���1-9�����У�����������ö�٣��Ͳ����������ˡ��Դ�������ö�ٵ��ٶȡ�
// vector.erase��ɾ��ĩβԪ��ʱ���ٶȺܿ죬��ɾ���м�Ԫ����̫����
// �ݲ飬����ΪҪ��ɾ��λ��֮���Ԫ��ȫ��ǰ�ơ�
// �ʣ����������Ա���˲�����

#ifdef COMPILE_THIS_FILE
// suduku solution.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <iomanip>

#include "other.h"


// DeleteWrong�Ķ����㷨����ȫ�����ã���Ϊ����vector,��ɾ��̫������
#pragma region DeleteWrong

// �ȣ�DeleteWrong��Ũ��if����0�루AMD Ryzen 5 4600G with Radeon Graphics��
//int suduku[9][9] = {
//{3,7,9,4,8,1,5,2,6},
//{8,2,4,5,7,6,3,1,9},
//{6,5,1,2,3,9,4,7,8},
//{1,6,5,7,9,2,8,4,3},
//{9,4,3,1,6,8,2,5,7},
//{2,8,7,3,5,4,6,9,1},
//{7,9,8,6,4,5,1,3,2},
//{5,3,2,8,1,7,9,6,4},
//{4,1,6,9,2,3,7,8,5}
//};
///// <summary>
///// ������֪���֣��޳�����Ҫ�ı仯����DeleteWrong����֧if��
///// </summary>
///// <param name="rows_copy">���б仯</param>
///// <param name="r">����ָ����</param>
///// <param name="suduku">��֪����</param>
//void DeleteWrong(std::vector<std::vector<int*>>& rows_copy, size_t& r, int(&suduku)[9][9])
//{
//	for (size_t c = 0; c < 9; c++)
//	{
//		if (suduku[r][c] != 0) // ��֪���ֵ��к��У���r��c
//		{
//			for (size_t rs = 0; rs < 9; rs++) // ���������У���ǰ����������rs
//			{
//				for (int index = (int)rows_copy[rs].size() - 1; index >= 0; index--) // ������ǰ�е����б仯����ǰ�仯��������index
//				{
//					for (size_t rs_c = 0; rs_c < 9; rs_c++) // ������ǰ�仯��ÿһ�У���ǰ����rs_c
//					{
//						if (r == rs)
//						{
//							if (rs_c == c)
//							{
//								if (rows_copy[rs][index][rs_c] != suduku[r][c])
//								{
//									rows_copy[rs].erase(rows_copy[rs].begin() + index); // �����ԣ���ɾ���������������е����б仯�����ɾ��������1�롣
//									break;
//								}
//							}
//							else
//							{
//								if (rows_copy[rs][index][rs_c] == suduku[r][c])
//								{
//									rows_copy[rs].erase(rows_copy[rs].begin() + index); // �����ԣ���ɾ���������������е����б仯�����ɾ��������1�롣
//									break;
//								}
//							}
//						}
//						else
//						{
//							if (rs_c == c && rows_copy[rs][index][rs_c] == suduku[r][c])
//							{
//								rows_copy[rs].erase(rows_copy[rs].begin() + index); // �����ԣ���ɾ���������������е����б仯�����ɾ��������1�롣
//								break;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}


// �ȣ�DeleteWrong��Ũ��if����2�루AMD Ryzen 5 4600G with Radeon Graphics��
//int suduku[9][9] = {
//{3,7,9,4,8,1,5,2,6},
//{8,2,4,5,7,6,3,1,9},
//{6,5,1,2,3,9,4,7,8},
//{1,6,5,7,9,2,8,4,3},
//{9,4,3,1,6,8,2,5,7},
//{2,8,7,3,5,4,6,9,1},
//{7,9,8,6,4,5,1,3,2},
//{5,3,2,8,1,7,9,6,4},
//{4,1,6,9,2,3,7,8,5}
//};
///// <summary>
///// ������֪���֣��޳�����Ҫ�ı仯
///// </summary>
///// <param name="rows_copy">���б仯</param>
///// <param name="r">����ָ����</param>
///// <param name="suduku">��֪����</param>
//void DeleteWrong(std::vector<std::vector<int*>>& rows_copy, size_t& r, int(&suduku)[9][9])
//{
//	int* same_int = (int*)malloc(4);
//	if (same_int == nullptr) { return; } // 85
//	for (size_t c = 0; c < 9; c++)
//	{
//		if (suduku[r][c] != 0) // ��֪���ֵ��к��У���r��c
//		{
//			for (size_t rs = 0; rs < 9; rs++) // ���������У���ǰ����������rs
//			{
//				for (int index = (int)rows_copy[rs].size() - 1; index >= 0; index--) // ������ǰ�е����б仯����ǰ�仯��������index
//				{
//					for (size_t rs_c = 0; rs_c < 9; rs_c++) // ������ǰ�仯��ÿһ�У���ǰ����rs_c
//					{
//						char* same_int_one = (char*)same_int;
//						same_int_one++;
//						*same_int_one = (char)r == rs;
//						same_int_one++;
//						*same_int_one = (char)rs_c == c;
//						same_int_one++;
//						*same_int_one = (char)rows_copy[rs][index][rs_c] == suduku[r][c];
//						if (*same_int == 65997 || *same_int == 16842957 || *same_int == 16777677) // 65997�ԶԴ�16842957��Զԣ�16777677�Դ��
//						{
//							rows_copy[rs].erase(rows_copy[rs].begin() + index); // �����ԣ���ɾ���������������е����б仯�����ɾ��������1�롣
//							break;
//						}
//					}
//				}
//			}
//		}
//	}
//	free(same_int);
//}


// �ȣ�DeleteWrong��Ũ��if����3�루AMD Ryzen 5 4600G with Radeon Graphics��
//int suduku[9][9] = {
//{3,7,9,4,8,1,5,2,6},
//{8,2,4,5,7,6,3,1,9},
//{6,5,1,2,3,9,4,7,8},
//{1,6,5,7,9,2,8,4,3},
//{9,4,3,1,6,8,2,5,7},
//{2,8,7,3,5,4,6,9,1},
//{7,9,8,6,4,5,1,3,2},
//{5,3,2,8,1,7,9,6,4},
//{4,1,6,9,2,3,7,8,5}
//};
///// <summary>
///// ������֪���֣��޳�����Ҫ�ı仯
///// </summary>
///// <param name="rows_copy">���б仯</param>
///// <param name="r">����ָ����</param>
///// <param name="suduku">��֪����</param>
//void DeleteWrong(std::vector<std::vector<int*>>& rows_copy, size_t& r, int(&suduku)[9][9])
//{
//	int* same_int = (int*)calloc(1,4);
//	if (same_int == nullptr) { return; } // 85
//	for (size_t c = 0; c < 9; c++)
//	{
//		if (suduku[r][c] != 0) // ��֪���ֵ��к��У���r��c
//		{
//			for (size_t rs = 0; rs < 9; rs++) // ���������У���ǰ����������rs
//			{
//				for (int index = (int)rows_copy[rs].size() - 1; index >= 0; index--) // ������ǰ�е����б仯����ǰ�仯��������index
//				{
//					for (size_t rs_c = 0; rs_c < 9; rs_c++) // ������ǰ�仯��ÿһ�У���ǰ����rs_c
//					{
//						// ��DeleteWrong����֧if���������ζԱȣ����˴���6�ζԱȡ�
//						// ������ֵ��ǣ�ʱ�����Լ4%��
//						// ��ֻ��if����ת�����ˣ���֧����ת�����ͶԱȵĿ�����ͬ��
//						bool* same_int_one = (bool*)same_int;
//						same_int_one[1] = r == rs;
//						same_int_one[2] = rs_c == c;
//						same_int_one[3] = rows_copy[rs][index][rs_c] == suduku[r][c];
//						if (*same_int == 65792 || *same_int == 16842752 || *same_int == 16777472)
//						{
//							rows_copy[rs].erase(rows_copy[rs].begin() + index);
//							break;
//						}
//
//						// ��if (*same_int== ......)������ifԼ98888ms��switchԼ99205ms��
//						//switch (*same_int)// 65792�ԶԴ�16842752��Զԣ�16777472�Դ��
//						//{
//						//case 16842957:
//						//	rows_copy[rs].erase(rows_copy[rs].begin() + index); // �����ԣ���ɾ���������������е����б仯�����ɾ��������1�롣
//						//	goto end_goto;
//						//case 16777677:
//						//	rows_copy[rs].erase(rows_copy[rs].begin() + index); // �����ԣ���ɾ���������������е����б仯�����ɾ��������1�롣
//						//	goto end_goto;
//						//case 65997:
//						//	rows_copy[rs].erase(rows_copy[rs].begin() + index); // �����ԣ���ɾ���������������е����б仯�����ɾ��������1�롣
//						//	goto end_goto;
//						//}
//					}
//				end_goto:;
//				}
//			}
//		}
//	}
//	free(same_int);
//}


//// �ȣ�DeleteWrong��Ũ��if����1�루AMD Ryzen 5 4600G with Radeon Graphics��
////int suduku[9][9] = {
////{3,7,9,4,8,1,5,2,6},
////{8,2,4,5,7,6,3,1,9},
////{6,5,1,2,3,9,4,7,8},
////{1,6,5,7,9,2,8,4,3},
////{9,4,3,1,6,8,2,5,7},
////{2,8,7,3,5,4,6,9,1},
////{7,9,8,6,4,5,1,3,2},
////{5,3,2,8,1,7,9,6,4},
////{4,1,6,9,2,3,7,8,5}
////};
///// <summary>
///// ������֪���֣��޳�����Ҫ�ı仯
///// </summary>
///// <param name="rows_copy">���б仯</param>
///// <param name="r">����ָ����</param>
///// <param name="suduku">��֪����</param>
//void DeleteWrong(std::vector<std::vector<int*>>& rows_copy, size_t& r, int(&suduku)[9][9])
//{
//	int* same_int = (int*)calloc(9, 4);	
//	if (same_int == nullptr) { return; } // 85
//	bool* same_int_one = (bool*)same_int;
//	int tt[3] = { 0 };
//	for (size_t c = 0; c < 9; c++)
//	{
//		if (suduku[r][c] != 0) // ��֪���ֵ��к��У���r��c
//		{
//			for (size_t rs = 0; rs < 9; rs++) // ���������У���ǰ����������rs
//			{
//				for (int index = (int)rows_copy[rs].size() - 1; index >= 0; index--) // ������ǰ�е����б仯����ǰ�仯��������index
//				{
//					for (size_t rs_c = 0; rs_c < 9; rs_c++) // ������ǰ�仯��ÿһ�У���ǰ����rs_c
//					{
//						same_int[0] = r ^ rs;
//						same_int[1] = rs_c ^ c;
//						same_int[2] = rows_copy[rs][index][rs_c] ^ suduku[r][c];
//						tt[0] = same_int[0] + same_int[1];
//						tt[1] = same_int[0] + same_int[2];
//						tt[2] = same_int[1] + same_int[2];
//						if ((tt[0] == 0 && same_int[2] != 0)
//							|| (tt[1] == 0 && same_int[2] != 0)
//							|| (tt[2] == 0 && same_int[0] != 0)
//							)
//						{
//							rows_copy[rs].erase(rows_copy[rs].begin() + index);
//							break;
//						}
//					}
//				}
//			}
//		}
//	}
//	free(same_int);
//}


// ��ʱ121�루AMD Ryzen 5 4600G with Radeon Graphics��
//int suduku[9][9] = {
//{3,7,9,4,8,1,5,2,6},
//{8,2,4,5,7,6,3,1,9},
//{6,5,1,2,3,9,4,7,8},
//{1,6,5,7,9,2,8,4,3},
//{9,4,3,1,6,8,2,5,7},
//{2,8,7,3,5,4,6,9,1},
//{7,9,8,6,4,5,1,3,2},
//{5,3,2,8,1,7,9,6,4},
//{4,1,6,9,2,3,7,8,5}
//};
/// <summary>
/// ������֪���֣��޳�����Ҫ�ı仯����DeleteWrong��Ũ��if��
/// </summary>
/// <param name="rows_copy">���б仯</param>
/// <param name="r">����ָ����</param>
/// <param name="suduku">��֪����</param>
void DeleteWrong(std::vector<std::vector<int*>>& rows_copy, size_t& r, int(&suduku)[9][9])
{
	for (size_t c = 0; c < 9; c++)
	{
		if (suduku[r][c] != 0) // ��֪���ֵ��к��У���r��c
		{
			for (size_t rs = 0; rs < 9; rs++) // ���������У���ǰ����������rs
			{
				for (int index = (int)rows_copy[rs].size() - 1; index >= 0; index--) // ������ǰ�е����б仯����ǰ�仯��������index
				{
					for (size_t rs_c = 0; rs_c < 9; rs_c++) // ������ǰ�仯��ÿһ�У���ǰ����rs_c
					{
						// �����ԣ�if�ж��ٶȺܿ졣
						if ((r == rs && rs_c == c && rows_copy[rs][index][rs_c] != suduku[r][c]) /* ����֪����ͬ��ͬ�С����ֲ�ͬ�����޳� */
							|| (r == rs && rs_c != c && rows_copy[rs][index][rs_c] == suduku[r][c]) /* ����֪����ͬ�С���ͬ�С�������ͬ�����޳� */
							|| (r != rs && rs_c == c && rows_copy[rs][index][rs_c] == suduku[r][c]) /* ����֪���ֲ�ͬ�С�ͬ�С�������ͬ�����޳� */
							)
						{
							// �����ԣ����������Ϣ��
							// vector��ɾ���������Ὣ��������нڵ���ǰ�ơ�
							// ��ˣ�ɾ�����һ���Ĳ�����죬ɾ���м�ڵ����������
							// �����ԣ�ɾ�������е����б仯�������һ����ʼɾ��������һ�룬�����м�ɾ����Ҫ�ܾá�
							rows_copy[rs].erase(rows_copy[rs].begin() + index);
							break;
						}
					}
				}
			}
		}
	}
}

#pragma endregion








int main()
{
	std::cout << "Hello World!\n";
	std::cout << sizeof(nullptr) << std::endl;	// 8
	std::cout << sizeof(int) << std::endl;		// 4
	std::cout << sizeof(bool) << std::endl;		// 4
	//std::cout << sizeof(node) << std::endl;		// ������ڴ棬���Ա�ʵ��ռ�ø��ռ��



	std::vector<std::vector<int*>> rows(9);

	PrintTime(); std::cout << "������ݣ�ÿ��362880�ֱ仯��" << std::endl;
	int a[9] = { 1,2,3,4,5,6,7,8,9 };
	for (size_t r = 0; r < 9; r++)
	{
		std::sort(a, a + 9);
		do
		{
			int* t = new int[9];
			for (size_t i = 0; i < 9; i++)
			{
				t[i] = a[i];
			}
			rows[r].push_back(t);
		} while (std::next_permutation(a, a + 9));
	}


	// ��
	//int suduku[9][9] = {
	//{3,7,9,4,8,1,5,2,6},
	//{8,2,4,5,7,6,3,1,9},
	//{6,5,1,2,3,9,4,7,8},
	//{1,6,5,7,9,2,8,4,3},
	//{9,4,3,1,6,8,2,5,7},
	//{2,8,7,3,5,4,6,9,1},
	//{7,9,8,6,4,5,1,3,2},
	//{5,3,2,8,1,7,9,6,4},
	//{4,1,6,9,2,3,7,8,5}
	//};


	// ��Ŀ
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

	PrintTime(); std::cout << "������Ŀ�����֣��޳�����Ҫ�ı仯��" << std::endl;
	for (size_t r = 0; r < 9; r++)
	{
		DeleteWrong(rows, r, suduku);
	}


	PrintTime(); std::cout << "ÿ��ʣ��仯��������" << std::endl;
	for (size_t i = 0; i < 9; i++)
	{
		std::cout << "row " << i << " = " << rows[i].size() << std::endl;
	}

	//std::cout << "���ÿ�е����б仯" << std::endl;
	//for (size_t r = 0; r < 9; r++)
	//{
	//	std::cout << "������=" << r << std::endl;
	//	for (size_t index = 0; index < rows[r].size(); index++)
	//	{
	//		for (size_t c = 0; c < 9; c++)
	//		{
	//			std::cout << rows[r][index][c] << " ";
	//		}
	//		std::cout << std::endl;
	//	}
	//}


	// ö�ٱ仯���ٵ��У���������Ϊ��֪���ֵ��У�Ȼ�����һ���޳������ö�ٽ����

	//std::cout << "��ȡ�仯���ٵ��е�������"; PrintTime(); std::cout << std::endl;
	int rows_size[9] = { 0 };
	for (size_t i = 0; i < 9; i++)
	{
		rows_size[i] = (int)rows[i].size();
	}
	size_t min_position = std::min_element(rows_size, rows_size + 9) - rows_size;
	//std::cout << min_position << std::endl;

	for (size_t i = 0; i < rows[min_position].size(); i++) // ö�ٱ仯���ٵ���
	{
		std::vector<std::vector<int*>> rows_copy(rows); // �������ԣ����½�vector��vector<vector>��int*����������int*��ֵ
		rows_copy[min_position].clear();
		rows_copy[min_position].push_back(rows[min_position][i]);

		for (size_t hhh = 0; hhh < 9; hhh++) // ����Ϊ��֪���ֵ���
		{
			suduku[min_position][hhh] = rows_copy[min_position][0][hhh];
		}
		DeleteWrong(rows_copy, min_position, suduku);

		//std::cout << "��ȡ�仯�ڶ��ٵ��е�������"; PrintTime(); std::cout << std::endl;
		int rows_size2[9] = { 0 };
		for (size_t i = 0; i < 9; i++)
		{
			rows_size2[i] = (int)rows_copy[i].size();
		}
		rows_size2[min_position] = 99999999;
		size_t min_position2 = std::min_element(rows_size2, rows_size2 + 9) - rows_size2;
		//std::cout << min_position2 << std::endl;

		for (size_t i2 = 0; i2 < rows_copy[min_position2].size(); i2++) // ö�ٱ仯�ڶ��ٵ���
		{
			std::vector<std::vector<int*>> rows_copy2(rows_copy); // �������ԣ����½�vector��vector<vector>��int*����������int*��ֵ
			rows_copy2[min_position2].clear();
			rows_copy2[min_position2].push_back(rows_copy[min_position2][i2]);

			for (size_t hhh = 0; hhh < 9; hhh++) // ����Ϊ��֪���ֵ���
			{
				suduku[min_position2][hhh] = rows_copy2[min_position2][0][hhh];
			}
			DeleteWrong(rows_copy2, min_position2, suduku);



			//std::cout << "��ȡ�仯�����ٵ��е�������"; PrintTime(); std::cout << std::endl;
			int rows_size3[9] = { 0 };
			for (size_t i = 0; i < 9; i++)
			{
				rows_size3[i] = (int)rows_copy2[i].size();
			}
			rows_size3[min_position] = 99999999;
			rows_size3[min_position2] = 99999999;
			size_t min_position3 = std::min_element(rows_size3, rows_size3 + 9) - rows_size3;
			//std::cout << min_position3 << std::endl;

			for (size_t i3 = 0; i3 < rows_copy2[min_position3].size(); i3++) // ö�ٱ仯�����ٵ���
			{
				std::vector<std::vector<int*>> rows_copy3(rows_copy2); // �������ԣ����½�vector��vector<vector>��int*����������int*��ֵ
				rows_copy3[min_position3].clear();
				rows_copy3[min_position3].push_back(rows_copy2[min_position3][i3]);

				for (size_t hhh = 0; hhh < 9; hhh++) // ����Ϊ��֪���ֵ���
				{
					suduku[min_position3][hhh] = rows_copy3[min_position3][0][hhh];
				}

				DeleteWrong(rows_copy3, min_position3, suduku);

				//std::cout << "��ȡ�仯�����ٵ��е�������"; PrintTime(); std::cout << std::endl;
				int rows_size4[9] = { 0 };
				for (size_t i = 0; i < 9; i++)
				{
					rows_size4[i] = (int)rows_copy3[i].size();
				}
				rows_size4[min_position] = 99999999;
				rows_size4[min_position2] = 99999999;
				rows_size4[min_position3] = 99999999;
				size_t min_position4 = std::min_element(rows_size4, rows_size4 + 9) - rows_size4;
				//std::cout << min_position4 << std::endl;

				for (size_t i4 = 0; i4 < rows_copy3[min_position4].size(); i4++) // ö�ٱ仯�����ٵ���
				{
					std::vector<std::vector<int*>> rows_copy4(rows_copy3); // �������ԣ����½�vector��vector<vector>��int*��������int*��ֵ
					rows_copy4[min_position4].clear();
					rows_copy4[min_position4].push_back(rows_copy3[min_position4][i4]);

					for (size_t hhh = 0; hhh < 9; hhh++) // ����Ϊ��֪���ֵ���
					{
						suduku[min_position4][hhh] = rows_copy4[min_position4][0][hhh];
					}

					DeleteWrong(rows_copy4, min_position4, suduku);

					//std::cout << "��ȡ�仯�����ٵ��е�������"; PrintTime(); std::cout << std::endl;
					int rows_size5[9] = { 0 };
					for (size_t i = 0; i < 9; i++)
					{
						rows_size5[i] = (int)rows_copy4[i].size();
					}
					rows_size5[min_position] = 99999999;
					rows_size5[min_position2] = 99999999;
					rows_size5[min_position3] = 99999999;
					rows_size5[min_position4] = 99999999;
					size_t min_position5 = std::min_element(rows_size5, rows_size5 + 9) - rows_size5;
					//std::cout << min_position5 << std::endl;

					for (size_t i5 = 0; i5 < rows_copy4[min_position5].size(); i5++) // ö�ٱ仯�����ٵ���
					{
						std::vector<std::vector<int*>> rows_copy5(rows_copy4); // �������ԣ����½�vector��vector<vector>��int*��������int*��ֵ
						rows_copy5[min_position5].clear();
						rows_copy5[min_position5].push_back(rows_copy4[min_position5][i5]);

						for (size_t hhh = 0; hhh < 9; hhh++) // ����Ϊ��֪���ֵ���
						{
							suduku[min_position5][hhh] = rows_copy5[min_position5][0][hhh];
						}

						DeleteWrong(rows_copy5, min_position5, suduku);


						//std::cout << "��ȡ�仯��6�ٵ��е�������"; PrintTime(); std::cout << std::endl;
						int rows_size6[9] = { 0 };
						for (size_t i = 0; i < 9; i++)
						{
							rows_size6[i] = (int)rows_copy5[i].size();
						}
						rows_size6[min_position] = 99999999;
						rows_size6[min_position2] = 99999999;
						rows_size6[min_position3] = 99999999;
						rows_size6[min_position4] = 99999999;
						rows_size6[min_position5] = 99999999;
						size_t min_position6 = std::min_element(rows_size6, rows_size6 + 9) - rows_size6;
						//std::cout << min_position5 << std::endl;

						for (size_t i6 = 0; i6 < rows_copy5[min_position6].size(); i6++) // ö�ٱ仯��6�ٵ���
						{
							std::vector<std::vector<int*>> rows_copy6(rows_copy5); // �������ԣ����½�vector��vector<vector>��int*��������int*��ֵ
							rows_copy6[min_position6].clear();
							rows_copy6[min_position6].push_back(rows_copy5[min_position6][i6]);

							for (size_t hhh = 0; hhh < 9; hhh++) // ����Ϊ��֪���ֵ���
							{
								suduku[min_position6][hhh] = rows_copy6[min_position6][0][hhh];
							}

							DeleteWrong(rows_copy6, min_position6, suduku);



							//std::cout << "��ȡ�仯��6�ٵ��е�������"; PrintTime(); std::cout << std::endl;
							int rows_size7[9] = { 0 };
							for (size_t i = 0; i < 9; i++)
							{
								rows_size7[i] = (int)rows_copy5[i].size();
							}
							rows_size7[min_position] = 99999999;
							rows_size7[min_position2] = 99999999;
							rows_size7[min_position3] = 99999999;
							rows_size7[min_position4] = 99999999;
							rows_size7[min_position5] = 99999999;
							rows_size7[min_position6] = 99999999;
							size_t min_position7 = std::min_element(rows_size7, rows_size7 + 9) - rows_size7;
							//std::cout << min_position5 << std::endl;

							for (size_t i6 = 0; i6 < rows_copy6[min_position7].size(); i6++) // ö�ٱ仯��6�ٵ���
							{
								std::vector<std::vector<int*>> rows_copy7(rows_copy6); // �������ԣ����½�vector��vector<vector>��int*��������int*��ֵ
								rows_copy7[min_position7].clear();
								rows_copy7[min_position7].push_back(rows_copy6[min_position7][i6]);

								for (size_t hhh = 0; hhh < 9; hhh++) // ����Ϊ��֪���ֵ���
								{
									suduku[min_position7][hhh] = rows_copy7[min_position7][0][hhh];
								}

								DeleteWrong(rows_copy7, min_position7, suduku);








#pragma region MyRegion

								int ix[9] = { 0 };

								std::vector<std::vector<int*>> rows_final(rows_copy6);

								for (size_t i = 0; i < 9; i++) // �п���������
								{
									if (rows_final[i].size() == 0)
									{
										goto out_emuneration;
									}
								}

								//std::cout << "��ǰ����" << i << "," << i2 << "," << i3 << "," << i4 << "," << i5 << std::endl;




								//std::cout << "ʣ��仯��������";
								//for (size_t i = 0; i < 9; i++)
								//{
								//	std::cout << "row " << i << " = " << rows_final[i].size() << std::endl;
								//}


								for (ix[0] = 0; ix[0] < rows_final[0].size(); ix[0]++) // ö��
								{
									for (ix[1] = 0; ix[1] < rows_final[1].size(); ix[1]++)
									{
										for (ix[2] = 0; ix[2] < rows_final[2].size(); ix[2]++)
										{
											for (ix[3] = 0; ix[3] < rows_final[3].size(); ix[3]++)
											{
												for (ix[4] = 0; ix[4] < rows_final[4].size(); ix[4]++)
												{
													for (ix[5] = 0; ix[5] < rows_final[5].size(); ix[5]++)
													{
														for (ix[6] = 0; ix[6] < rows_final[6].size(); ix[6]++)
														{
															for (ix[7] = 0; ix[7] < rows_final[7].size(); ix[7]++)
															{
																for (ix[8] = 0; ix[8] < rows_final[8].size(); ix[8]++)
																{
																	//std::cout << "�����ǰö�ٵı仯" << std::endl;
																	//for (size_t r = 0; r < 9; r++)
																	//{
																	//	for (size_t c = 0; c < 9; c++)
																	//	{
																	//		std::cout << rows_final[r][ix[r]][c] << " ";
																	//	}
																	//	std::cout << std::endl;
																	//}



																	// ÿ�У��Ƿ����ظ�
																	for (size_t same_c = 0; same_c <= 9; same_c++)
																	{
																		if (same_c != 9)
																		{
																			bool same_num[10] = { false };
																			for (size_t same_r = 0; same_r < 9; same_r++)
																			{
																				int tt = rows_final[same_r][ix[same_r]][same_c];
																				if (same_num[tt])
																				{
																					goto end_same;
																				}
																				else
																				{
																					same_num[tt] = true;
																				}
																			}

																		}
																		else
																		{
																			// ÿ��С�����Ƿ����ظ�	
																			for (size_t nine_r = 0; nine_r < 9; nine_r += 3)
																			{
																				for (size_t nine_c = 0; nine_c < 9; nine_c += 3)
																				{
																					bool same_num[10] = { false };
																					for (size_t nine_r_r = 0; nine_r_r < 3; nine_r_r++)
																					{
																						for (size_t nine_c_c = 0; nine_c_c < 3; nine_c_c++)
																						{
																							int tt = rows_final[nine_r + nine_r_r][ix[nine_r + nine_r_r]][nine_c + nine_c_c];
																							if (same_num[tt])
																							{
																								goto end_same;
																							}
																							else
																							{
																								same_num[tt] = true;
																							}
																						}
																					}
																				}
																			}




																			PrintTime(); std::cout << "���ظ������֣�" << std::endl;
																			for (size_t okr = 0; okr < 9; okr++) // �������
																			{
																				for (size_t okc = 0; okc < 9; okc++)
																				{
																					std::cout << rows_final[okr][ix[okr]][okc];
																				}
																				std::cout << std::endl;
																			}
																		}
																	}
																end_same:;


																}
															}
														}
													}
												}
											}

										}
									}
								}
							out_emuneration:;
#pragma endregion



							}

						}

					}










				}







			}













		}




	}






	PrintTime(); std::cout << "Hello World!" << std::endl;
	return 0;
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�


// �����ԣ�6��ѭ����Ч����ߣ������ų�������Ŀʹ����������ʱЧ�ʸ��ߡ�
#pragma region test
// 5��ѭ��
//Hello World!
//8
//4
//1
//2024�� 6��23��0��174��11ʱ26��13��0����ʱ     0���κ�ʱ(����)     0�ܺ�ʱ(����)������ݣ�ÿ��362880�ֱ仯��
//2024�� 6��23��0��174��11ʱ26��14��0����ʱ   947���κ�ʱ(����)   950�ܺ�ʱ(����)������Ŀ�����֣��޳�����Ҫ�ı仯��
//2024�� 6��23��0��174��11ʱ27��40��0����ʱ 85583���κ�ʱ(����) 86535�ܺ�ʱ(����)ÿ��ʣ��仯��������
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024�� 6��23��0��174��11ʱ29��53��0����ʱ133465���κ�ʱ(����)220001�ܺ�ʱ(����)���ظ������֣�
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024�� 6��23��0��174��11ʱ34��49��0����ʱ295675���κ�ʱ(����)515677�ܺ�ʱ(����)Hello World!

// 6��ѭ��
//Hello World!
//8
//4
//1
//2024�� 6��23��0��174��11ʱ43��19��0����ʱ     0���κ�ʱ(����)     0�ܺ�ʱ(����)������ݣ�ÿ��362880�ֱ仯��
//2024�� 6��23��0��174��11ʱ43��20��0����ʱ   954���κ�ʱ(����)   956�ܺ�ʱ(����)������Ŀ�����֣��޳�����Ҫ�ı仯��
//2024�� 6��23��0��174��11ʱ44��45��0����ʱ 85406���κ�ʱ(����) 86363�ܺ�ʱ(����)ÿ��ʣ��仯��������
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024�� 6��23��0��174��11ʱ45�� 1��0����ʱ 15531���κ�ʱ(����)101896�ܺ�ʱ(����)���ظ������֣�
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024�� 6��23��0��174��11ʱ45��37��0����ʱ 36289���κ�ʱ(����)138187�ܺ�ʱ(����)Hello World!

// 7��ѭ��
//Hello World!
//8
//4
//1
//2024�� 6��23��0��174��11ʱ48��10��0����ʱ     0���κ�ʱ(����)     0�ܺ�ʱ(����)������ݣ�ÿ��362880�ֱ仯��
//2024�� 6��23��0��174��11ʱ48��11��0����ʱ   979���κ�ʱ(����)   982�ܺ�ʱ(����)������Ŀ�����֣��޳�����Ҫ�ı仯��
//2024�� 6��23��0��174��11ʱ49��37��0����ʱ 85814���κ�ʱ(����) 86798�ܺ�ʱ(����)ÿ��ʣ��仯��������
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024�� 6��23��0��174��11ʱ50��21��0����ʱ 43985���κ�ʱ(����)130785�ܺ�ʱ(����)���ظ������֣�
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024�� 6��23��0��174��11ʱ51��53��0����ʱ 92372���κ�ʱ(����)223158�ܺ�ʱ(����)Hello World!
#pragma endregion


// �ڵ�5��6��֮�䣬�����Ƿ��п����жϣ�������������
#pragma region test
//Hello World!
//8
//4
//1
//2024�� 6��23��0��174��21ʱ35��51��0����ʱ     0���κ�ʱ(����)     0�ܺ�ʱ(����)������ݣ�ÿ��362880�ֱ仯��
//2024�� 6��23��0��174��21ʱ35��52��0����ʱ  1289���κ�ʱ(����)  1291�ܺ�ʱ(����)������Ŀ�����֣��޳�����Ҫ�ı仯��
//2024�� 6��23��0��174��21ʱ37��44��0����ʱ111947���κ�ʱ(����)113240�ܺ�ʱ(����)ÿ��ʣ��仯��������
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024�� 6��23��0��174��21ʱ38��35��0����ʱ 50749���κ�ʱ(����)163990�ܺ�ʱ(����)���ظ������֣�
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024�� 6��23��0��174��21ʱ40��22��0����ʱ107415���κ�ʱ(����)271407�ܺ�ʱ(����)Hello World!

//Hello World!
//8
//4
//1
//2024�� 6��23��0��174��21ʱ58�� 9��0����ʱ     0���κ�ʱ(����)     0�ܺ�ʱ(����)������ݣ�ÿ��362880�ֱ仯��
//2024�� 6��23��0��174��21ʱ58��10��0����ʱ  1334���κ�ʱ(����)  1336�ܺ�ʱ(����)������Ŀ�����֣��޳�����Ҫ�ı仯��
//2024�� 6��23��0��174��22ʱ 0�� 2��0����ʱ111518���κ�ʱ(����)112856�ܺ�ʱ(����)ÿ��ʣ��仯��������
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024�� 6��23��0��174��22ʱ 0��52��0����ʱ 50665���κ�ʱ(����)163522�ܺ�ʱ(����)���ظ������֣�
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024�� 6��23��0��174��22ʱ 2��40��0����ʱ107597���κ�ʱ(����)271121�ܺ�ʱ(����)Hello World!
#pragma endregion


#endif // COMPILE_THIS_FILE

