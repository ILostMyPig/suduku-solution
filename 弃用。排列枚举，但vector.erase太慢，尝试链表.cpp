// 每行都是1-9的排列，根据排列来枚举，就不用所有数了。以此来增加枚举的速度。
// vector.erase在删除末尾元素时，速度很快，但删除中间元素则太慢。
// 据查，是因为要把删除位置之后的元素全部前移。
// 故，改用链表，以避免此操作。

#ifdef COMPILE_THIS_FILE
// suduku solution.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <iomanip>

#include "other.h"


// DeleteWrong的多种算法。（全部弃用，因为基于vector,其删除太慢。）
#pragma region DeleteWrong

// 比（DeleteWrong：浓缩if）慢0秒（AMD Ryzen 5 4600G with Radeon Graphics）
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
///// 根据已知数字，剔除不需要的变化。（DeleteWrong：分支if）
///// </summary>
///// <param name="rows_copy">所有变化</param>
///// <param name="r">处理指定行</param>
///// <param name="suduku">已知数字</param>
//void DeleteWrong(std::vector<std::vector<int*>>& rows_copy, size_t& r, int(&suduku)[9][9])
//{
//	for (size_t c = 0; c < 9; c++)
//	{
//		if (suduku[r][c] != 0) // 已知数字的行和列，即r和c
//		{
//			for (size_t rs = 0; rs < 9; rs++) // 遍历所有行，当前遍历的行是rs
//			{
//				for (int index = (int)rows_copy[rs].size() - 1; index >= 0; index--) // 遍历当前行的所有变化，当前变化的索引是index
//				{
//					for (size_t rs_c = 0; rs_c < 9; rs_c++) // 遍历当前变化的每一列，当前列是rs_c
//					{
//						if (r == rs)
//						{
//							if (rs_c == c)
//							{
//								if (rows_copy[rs][index][rs_c] != suduku[r][c])
//								{
//									rows_copy[rs].erase(rows_copy[rs].begin() + index); // 经测试，仅删除操作，将所有行的所有变化都逐个删除，仅需1秒。
//									break;
//								}
//							}
//							else
//							{
//								if (rows_copy[rs][index][rs_c] == suduku[r][c])
//								{
//									rows_copy[rs].erase(rows_copy[rs].begin() + index); // 经测试，仅删除操作，将所有行的所有变化都逐个删除，仅需1秒。
//									break;
//								}
//							}
//						}
//						else
//						{
//							if (rs_c == c && rows_copy[rs][index][rs_c] == suduku[r][c])
//							{
//								rows_copy[rs].erase(rows_copy[rs].begin() + index); // 经测试，仅删除操作，将所有行的所有变化都逐个删除，仅需1秒。
//								break;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}


// 比（DeleteWrong：浓缩if）慢2秒（AMD Ryzen 5 4600G with Radeon Graphics）
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
///// 根据已知数字，剔除不需要的变化
///// </summary>
///// <param name="rows_copy">所有变化</param>
///// <param name="r">处理指定行</param>
///// <param name="suduku">已知数字</param>
//void DeleteWrong(std::vector<std::vector<int*>>& rows_copy, size_t& r, int(&suduku)[9][9])
//{
//	int* same_int = (int*)malloc(4);
//	if (same_int == nullptr) { return; } // 85
//	for (size_t c = 0; c < 9; c++)
//	{
//		if (suduku[r][c] != 0) // 已知数字的行和列，即r和c
//		{
//			for (size_t rs = 0; rs < 9; rs++) // 遍历所有行，当前遍历的行是rs
//			{
//				for (int index = (int)rows_copy[rs].size() - 1; index >= 0; index--) // 遍历当前行的所有变化，当前变化的索引是index
//				{
//					for (size_t rs_c = 0; rs_c < 9; rs_c++) // 遍历当前变化的每一列，当前列是rs_c
//					{
//						char* same_int_one = (char*)same_int;
//						same_int_one++;
//						*same_int_one = (char)r == rs;
//						same_int_one++;
//						*same_int_one = (char)rs_c == c;
//						same_int_one++;
//						*same_int_one = (char)rows_copy[rs][index][rs_c] == suduku[r][c];
//						if (*same_int == 65997 || *same_int == 16842957 || *same_int == 16777677) // 65997对对错，16842957错对对，16777677对错对
//						{
//							rows_copy[rs].erase(rows_copy[rs].begin() + index); // 经测试，仅删除操作，将所有行的所有变化都逐个删除，仅需1秒。
//							break;
//						}
//					}
//				}
//			}
//		}
//	}
//	free(same_int);
//}


// 比（DeleteWrong：浓缩if）慢3秒（AMD Ryzen 5 4600G with Radeon Graphics）
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
///// 根据已知数字，剔除不需要的变化
///// </summary>
///// <param name="rows_copy">所有变化</param>
///// <param name="r">处理指定行</param>
///// <param name="suduku">已知数字</param>
//void DeleteWrong(std::vector<std::vector<int*>>& rows_copy, size_t& r, int(&suduku)[9][9])
//{
//	int* same_int = (int*)calloc(1,4);
//	if (same_int == nullptr) { return; } // 85
//	for (size_t c = 0; c < 9; c++)
//	{
//		if (suduku[r][c] != 0) // 已知数字的行和列，即r和c
//		{
//			for (size_t rs = 0; rs < 9; rs++) // 遍历所有行，当前遍历的行是rs
//			{
//				for (int index = (int)rows_copy[rs].size() - 1; index >= 0; index--) // 遍历当前行的所有变化，当前变化的索引是index
//				{
//					for (size_t rs_c = 0; rs_c < 9; rs_c++) // 遍历当前变化的每一列，当前列是rs_c
//					{
//						// （DeleteWrong：分支if）就是三次对比，但此处有6次对比。
//						// 令人奇怪的是，时间差距仅约4%。
//						// 就只有if的跳转问题了，分支的跳转开销和对比的开销相同。
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
//						// 比if (*same_int== ......)更慢，if约98888ms，switch约99205ms。
//						//switch (*same_int)// 65792对对错，16842752错对对，16777472对错对
//						//{
//						//case 16842957:
//						//	rows_copy[rs].erase(rows_copy[rs].begin() + index); // 经测试，仅删除操作，将所有行的所有变化都逐个删除，仅需1秒。
//						//	goto end_goto;
//						//case 16777677:
//						//	rows_copy[rs].erase(rows_copy[rs].begin() + index); // 经测试，仅删除操作，将所有行的所有变化都逐个删除，仅需1秒。
//						//	goto end_goto;
//						//case 65997:
//						//	rows_copy[rs].erase(rows_copy[rs].begin() + index); // 经测试，仅删除操作，将所有行的所有变化都逐个删除，仅需1秒。
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


//// 比（DeleteWrong：浓缩if）慢1秒（AMD Ryzen 5 4600G with Radeon Graphics）
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
///// 根据已知数字，剔除不需要的变化
///// </summary>
///// <param name="rows_copy">所有变化</param>
///// <param name="r">处理指定行</param>
///// <param name="suduku">已知数字</param>
//void DeleteWrong(std::vector<std::vector<int*>>& rows_copy, size_t& r, int(&suduku)[9][9])
//{
//	int* same_int = (int*)calloc(9, 4);	
//	if (same_int == nullptr) { return; } // 85
//	bool* same_int_one = (bool*)same_int;
//	int tt[3] = { 0 };
//	for (size_t c = 0; c < 9; c++)
//	{
//		if (suduku[r][c] != 0) // 已知数字的行和列，即r和c
//		{
//			for (size_t rs = 0; rs < 9; rs++) // 遍历所有行，当前遍历的行是rs
//			{
//				for (int index = (int)rows_copy[rs].size() - 1; index >= 0; index--) // 遍历当前行的所有变化，当前变化的索引是index
//				{
//					for (size_t rs_c = 0; rs_c < 9; rs_c++) // 遍历当前变化的每一列，当前列是rs_c
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


// 耗时121秒（AMD Ryzen 5 4600G with Radeon Graphics）
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
/// 根据已知数字，剔除不需要的变化。（DeleteWrong：浓缩if）
/// </summary>
/// <param name="rows_copy">所有变化</param>
/// <param name="r">处理指定行</param>
/// <param name="suduku">已知数字</param>
void DeleteWrong(std::vector<std::vector<int*>>& rows_copy, size_t& r, int(&suduku)[9][9])
{
	for (size_t c = 0; c < 9; c++)
	{
		if (suduku[r][c] != 0) // 已知数字的行和列，即r和c
		{
			for (size_t rs = 0; rs < 9; rs++) // 遍历所有行，当前遍历的行是rs
			{
				for (int index = (int)rows_copy[rs].size() - 1; index >= 0; index--) // 遍历当前行的所有变化，当前变化的索引是index
				{
					for (size_t rs_c = 0; rs_c < 9; rs_c++) // 遍历当前变化的每一列，当前列是rs_c
					{
						// 经测试，if判断速度很快。
						if ((r == rs && rs_c == c && rows_copy[rs][index][rs_c] != suduku[r][c]) /* 和已知数字同行同列、数字不同，则剔除 */
							|| (r == rs && rs_c != c && rows_copy[rs][index][rs_c] == suduku[r][c]) /* 和已知数字同行、不同列、数字相同，则剔除 */
							|| (r != rs && rs_c == c && rows_copy[rs][index][rs_c] == suduku[r][c]) /* 和已知数字不同行、同列、数字相同，则剔除 */
							)
						{
							// 经测试，结合网上信息：
							// vector的删除操作，会将后面的所有节点往前移。
							// 因此，删除最后一个的操作最快，删除中间节点操作很慢。
							// 经测试，删除所有行的所有变化，从最后一个开始删除，仅需一秒，但从中间删，就要很久。
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
	//std::cout << sizeof(node) << std::endl;		// 会对齐内存，所以比实际占用给空间大



	std::vector<std::vector<int*>> rows(9);

	PrintTime(); std::cout << "填充数据，每行362880种变化。" << std::endl;
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


	// 答案
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


	// 题目
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

	PrintTime(); std::cout << "根据题目的数字，剔除不需要的变化。" << std::endl;
	for (size_t r = 0; r < 9; r++)
	{
		DeleteWrong(rows, r, suduku);
	}


	PrintTime(); std::cout << "每行剩余变化的数量。" << std::endl;
	for (size_t i = 0; i < 9; i++)
	{
		std::cout << "row " << i << " = " << rows[i].size() << std::endl;
	}

	//std::cout << "输出每行的所有变化" << std::endl;
	//for (size_t r = 0; r < 9; r++)
	//{
	//	std::cout << "行索引=" << r << std::endl;
	//	for (size_t index = 0; index < rows[r].size(); index++)
	//	{
	//		for (size_t c = 0; c < 9; c++)
	//		{
	//			std::cout << rows[r][index][c] << " ";
	//		}
	//		std::cout << std::endl;
	//	}
	//}


	// 枚举变化较少的行，依次设其为已知数字的行，然后进行一次剔除，最后枚举结果。

	//std::cout << "获取变化最少的行的索引。"; PrintTime(); std::cout << std::endl;
	int rows_size[9] = { 0 };
	for (size_t i = 0; i < 9; i++)
	{
		rows_size[i] = (int)rows[i].size();
	}
	size_t min_position = std::min_element(rows_size, rows_size + 9) - rows_size;
	//std::cout << min_position << std::endl;

	for (size_t i = 0; i < rows[min_position].size(); i++) // 枚举变化最少的行
	{
		std::vector<std::vector<int*>> rows_copy(rows); // 经过测试，是新建vector、vector<vector>、int*，但复制容int*的值
		rows_copy[min_position].clear();
		rows_copy[min_position].push_back(rows[min_position][i]);

		for (size_t hhh = 0; hhh < 9; hhh++) // 设其为已知数字的行
		{
			suduku[min_position][hhh] = rows_copy[min_position][0][hhh];
		}
		DeleteWrong(rows_copy, min_position, suduku);

		//std::cout << "获取变化第二少的行的索引。"; PrintTime(); std::cout << std::endl;
		int rows_size2[9] = { 0 };
		for (size_t i = 0; i < 9; i++)
		{
			rows_size2[i] = (int)rows_copy[i].size();
		}
		rows_size2[min_position] = 99999999;
		size_t min_position2 = std::min_element(rows_size2, rows_size2 + 9) - rows_size2;
		//std::cout << min_position2 << std::endl;

		for (size_t i2 = 0; i2 < rows_copy[min_position2].size(); i2++) // 枚举变化第二少的行
		{
			std::vector<std::vector<int*>> rows_copy2(rows_copy); // 经过测试，是新建vector、vector<vector>、int*，但复制容int*的值
			rows_copy2[min_position2].clear();
			rows_copy2[min_position2].push_back(rows_copy[min_position2][i2]);

			for (size_t hhh = 0; hhh < 9; hhh++) // 设其为已知数字的行
			{
				suduku[min_position2][hhh] = rows_copy2[min_position2][0][hhh];
			}
			DeleteWrong(rows_copy2, min_position2, suduku);



			//std::cout << "获取变化第三少的行的索引。"; PrintTime(); std::cout << std::endl;
			int rows_size3[9] = { 0 };
			for (size_t i = 0; i < 9; i++)
			{
				rows_size3[i] = (int)rows_copy2[i].size();
			}
			rows_size3[min_position] = 99999999;
			rows_size3[min_position2] = 99999999;
			size_t min_position3 = std::min_element(rows_size3, rows_size3 + 9) - rows_size3;
			//std::cout << min_position3 << std::endl;

			for (size_t i3 = 0; i3 < rows_copy2[min_position3].size(); i3++) // 枚举变化第三少的行
			{
				std::vector<std::vector<int*>> rows_copy3(rows_copy2); // 经过测试，是新建vector、vector<vector>、int*，但复制容int*的值
				rows_copy3[min_position3].clear();
				rows_copy3[min_position3].push_back(rows_copy2[min_position3][i3]);

				for (size_t hhh = 0; hhh < 9; hhh++) // 设其为已知数字的行
				{
					suduku[min_position3][hhh] = rows_copy3[min_position3][0][hhh];
				}

				DeleteWrong(rows_copy3, min_position3, suduku);

				//std::cout << "获取变化第四少的行的索引。"; PrintTime(); std::cout << std::endl;
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

				for (size_t i4 = 0; i4 < rows_copy3[min_position4].size(); i4++) // 枚举变化第四少的行
				{
					std::vector<std::vector<int*>> rows_copy4(rows_copy3); // 经过测试，是新建vector、vector<vector>、int*，但复制int*的值
					rows_copy4[min_position4].clear();
					rows_copy4[min_position4].push_back(rows_copy3[min_position4][i4]);

					for (size_t hhh = 0; hhh < 9; hhh++) // 设其为已知数字的行
					{
						suduku[min_position4][hhh] = rows_copy4[min_position4][0][hhh];
					}

					DeleteWrong(rows_copy4, min_position4, suduku);

					//std::cout << "获取变化第五少的行的索引。"; PrintTime(); std::cout << std::endl;
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

					for (size_t i5 = 0; i5 < rows_copy4[min_position5].size(); i5++) // 枚举变化第五少的行
					{
						std::vector<std::vector<int*>> rows_copy5(rows_copy4); // 经过测试，是新建vector、vector<vector>、int*，但复制int*的值
						rows_copy5[min_position5].clear();
						rows_copy5[min_position5].push_back(rows_copy4[min_position5][i5]);

						for (size_t hhh = 0; hhh < 9; hhh++) // 设其为已知数字的行
						{
							suduku[min_position5][hhh] = rows_copy5[min_position5][0][hhh];
						}

						DeleteWrong(rows_copy5, min_position5, suduku);


						//std::cout << "获取变化第6少的行的索引。"; PrintTime(); std::cout << std::endl;
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

						for (size_t i6 = 0; i6 < rows_copy5[min_position6].size(); i6++) // 枚举变化第6少的行
						{
							std::vector<std::vector<int*>> rows_copy6(rows_copy5); // 经过测试，是新建vector、vector<vector>、int*，但复制int*的值
							rows_copy6[min_position6].clear();
							rows_copy6[min_position6].push_back(rows_copy5[min_position6][i6]);

							for (size_t hhh = 0; hhh < 9; hhh++) // 设其为已知数字的行
							{
								suduku[min_position6][hhh] = rows_copy6[min_position6][0][hhh];
							}

							DeleteWrong(rows_copy6, min_position6, suduku);



							//std::cout << "获取变化第6少的行的索引。"; PrintTime(); std::cout << std::endl;
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

							for (size_t i6 = 0; i6 < rows_copy6[min_position7].size(); i6++) // 枚举变化第6少的行
							{
								std::vector<std::vector<int*>> rows_copy7(rows_copy6); // 经过测试，是新建vector、vector<vector>、int*，但复制int*的值
								rows_copy7[min_position7].clear();
								rows_copy7[min_position7].push_back(rows_copy6[min_position7][i6]);

								for (size_t hhh = 0; hhh < 9; hhh++) // 设其为已知数字的行
								{
									suduku[min_position7][hhh] = rows_copy7[min_position7][0][hhh];
								}

								DeleteWrong(rows_copy7, min_position7, suduku);








#pragma region MyRegion

								int ix[9] = { 0 };

								std::vector<std::vector<int*>> rows_final(rows_copy6);

								for (size_t i = 0; i < 9; i++) // 有空行则跳过
								{
									if (rows_final[i].size() == 0)
									{
										goto out_emuneration;
									}
								}

								//std::cout << "当前进度" << i << "," << i2 << "," << i3 << "," << i4 << "," << i5 << std::endl;




								//std::cout << "剩余变化的数量。";
								//for (size_t i = 0; i < 9; i++)
								//{
								//	std::cout << "row " << i << " = " << rows_final[i].size() << std::endl;
								//}


								for (ix[0] = 0; ix[0] < rows_final[0].size(); ix[0]++) // 枚举
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
																	//std::cout << "输出当前枚举的变化" << std::endl;
																	//for (size_t r = 0; r < 9; r++)
																	//{
																	//	for (size_t c = 0; c < 9; c++)
																	//	{
																	//		std::cout << rows_final[r][ix[r]][c] << " ";
																	//	}
																	//	std::cout << std::endl;
																	//}



																	// 每列，是否有重复
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
																			// 每个小宫格，是否有重复	
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




																			PrintTime(); std::cout << "无重复的数字：" << std::endl;
																			for (size_t okr = 0; okr < 9; okr++) // 输出数字
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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件


// 经测试，6层循环的效率最高，但不排除部分题目使用其它层数时效率更高。
#pragma region test
// 5层循环
//Hello World!
//8
//4
//1
//2024年 6月23日0周174天11时26分13秒0夏令时     0单次耗时(毫秒)     0总耗时(毫秒)填充数据，每行362880种变化。
//2024年 6月23日0周174天11时26分14秒0夏令时   947单次耗时(毫秒)   950总耗时(毫秒)根据题目的数字，剔除不需要的变化。
//2024年 6月23日0周174天11时27分40秒0夏令时 85583单次耗时(毫秒) 86535总耗时(毫秒)每行剩余变化的数量。
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024年 6月23日0周174天11时29分53秒0夏令时133465单次耗时(毫秒)220001总耗时(毫秒)无重复的数字：
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024年 6月23日0周174天11时34分49秒0夏令时295675单次耗时(毫秒)515677总耗时(毫秒)Hello World!

// 6层循环
//Hello World!
//8
//4
//1
//2024年 6月23日0周174天11时43分19秒0夏令时     0单次耗时(毫秒)     0总耗时(毫秒)填充数据，每行362880种变化。
//2024年 6月23日0周174天11时43分20秒0夏令时   954单次耗时(毫秒)   956总耗时(毫秒)根据题目的数字，剔除不需要的变化。
//2024年 6月23日0周174天11时44分45秒0夏令时 85406单次耗时(毫秒) 86363总耗时(毫秒)每行剩余变化的数量。
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024年 6月23日0周174天11时45分 1秒0夏令时 15531单次耗时(毫秒)101896总耗时(毫秒)无重复的数字：
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024年 6月23日0周174天11时45分37秒0夏令时 36289单次耗时(毫秒)138187总耗时(毫秒)Hello World!

// 7层循环
//Hello World!
//8
//4
//1
//2024年 6月23日0周174天11时48分10秒0夏令时     0单次耗时(毫秒)     0总耗时(毫秒)填充数据，每行362880种变化。
//2024年 6月23日0周174天11时48分11秒0夏令时   979单次耗时(毫秒)   982总耗时(毫秒)根据题目的数字，剔除不需要的变化。
//2024年 6月23日0周174天11时49分37秒0夏令时 85814单次耗时(毫秒) 86798总耗时(毫秒)每行剩余变化的数量。
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024年 6月23日0周174天11时50分21秒0夏令时 43985单次耗时(毫秒)130785总耗时(毫秒)无重复的数字：
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024年 6月23日0周174天11时51分53秒0夏令时 92372单次耗时(毫秒)223158总耗时(毫秒)Hello World!
#pragma endregion


// 在第5、6层之间，增加是否有空行判断，几乎无提升。
#pragma region test
//Hello World!
//8
//4
//1
//2024年 6月23日0周174天21时35分51秒0夏令时     0单次耗时(毫秒)     0总耗时(毫秒)填充数据，每行362880种变化。
//2024年 6月23日0周174天21时35分52秒0夏令时  1289单次耗时(毫秒)  1291总耗时(毫秒)根据题目的数字，剔除不需要的变化。
//2024年 6月23日0周174天21时37分44秒0夏令时111947单次耗时(毫秒)113240总耗时(毫秒)每行剩余变化的数量。
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024年 6月23日0周174天21时38分35秒0夏令时 50749单次耗时(毫秒)163990总耗时(毫秒)无重复的数字：
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024年 6月23日0周174天21时40分22秒0夏令时107415单次耗时(毫秒)271407总耗时(毫秒)Hello World!

//Hello World!
//8
//4
//1
//2024年 6月23日0周174天21时58分 9秒0夏令时     0单次耗时(毫秒)     0总耗时(毫秒)填充数据，每行362880种变化。
//2024年 6月23日0周174天21时58分10秒0夏令时  1334单次耗时(毫秒)  1336总耗时(毫秒)根据题目的数字，剔除不需要的变化。
//2024年 6月23日0周174天22时 0分 2秒0夏令时111518单次耗时(毫秒)112856总耗时(毫秒)每行剩余变化的数量。
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024年 6月23日0周174天22时 0分52秒0夏令时 50665单次耗时(毫秒)163522总耗时(毫秒)无重复的数字：
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024年 6月23日0周174天22时 2分40秒0夏令时107597单次耗时(毫秒)271121总耗时(毫秒)Hello World!
#pragma endregion


#endif // COMPILE_THIS_FILE

