
// suduku solution.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define DEBUG


#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <iomanip>


//// vector的删除操作太慢，需要链表。
struct node // 双向循环链表
{
	int* value = nullptr;
	node* last = nullptr;
	node* next = nullptr;
};

class TwoWay_Cyclic_LinkedList
{
public:
	TwoWay_Cyclic_LinkedList();
	TwoWay_Cyclic_LinkedList(TwoWay_Cyclic_LinkedList& shallow_copy);
	~TwoWay_Cyclic_LinkedList();
	node* first_node;
	node* present_node; // 没有读取过，则为nullptr
	int count;

	/// <summary>
	/// 添加新节点。
	/// 新节点的地址，即，first_node.last。
	/// </summary>
	/// <param name="value"></param>
	void Add_node_ToLast(int*& value);

	/// <summary>
	/// 指向下一个节点。
	/// 若无节点，则指向nullptr。
	/// </summary>
	void PresentNode_Next();


	// 弃用。
	// 当present_node指向最后一个节点时，删除present_node的节点，导致present_node直接指向first，就无法盼盼是否转了一圈。
	/// <summary>
	/// 指向下一个节点。
	/// 若无节点，则指向nullptr。
	/// 若下一个节点是第一个节点，则指向nullptr。
	/// </summary>
	//void PresentNode_Next_StopLast();

	/// <summary>
	/// 恢复成没有读取过，即，指向nullptr。
	/// </summary>
	void PresentNode_Reset() { present_node = nullptr; }

	/// <summary>
	/// 删除当前节点，并指向下一个节点。
	/// 若删除后无节点，则指向nullptr。
	/// </summary>
	void PresentNode_Delete();


private:
};

TwoWay_Cyclic_LinkedList::TwoWay_Cyclic_LinkedList()
{
	first_node = nullptr;
	present_node = nullptr;
	count = 0;
}

TwoWay_Cyclic_LinkedList::TwoWay_Cyclic_LinkedList(TwoWay_Cyclic_LinkedList& shallow_copy)
{
	first_node = nullptr;
	present_node = nullptr;
	count = 0;

	node* ptr = shallow_copy.first_node;
	for (size_t i = 0; i < shallow_copy.count; i++)
	{
		Add_node_ToLast(ptr->value);
		if (shallow_copy.present_node == ptr)
		{
			present_node = first_node->last;
		}
		ptr = ptr->next;
	}

}

TwoWay_Cyclic_LinkedList::~TwoWay_Cyclic_LinkedList()
{
}

void TwoWay_Cyclic_LinkedList::Add_node_ToLast(int*& value)
{
	node* add_node = new node;
	add_node->value = value;

	if (first_node == nullptr) // 无节点
	{
		first_node = add_node;
		first_node->last = first_node;
		first_node->next = first_node;

		count++; // 计数。
	}
	else
	{


		//// 弃用，if的两种情况，可用同一段代码解决		
		//if (first_node->last == first_node->next ) // 只有一个节点
		//{
		//	first_node->next = add_node;
		//	first_node->last  = add_node;
		//	add_node->last = first_node;
		//	add_node->next = first_node;
		//}
		//else
		//{
		//	node* last_node = first_node->last;
		//	last_node->next = add_node;
		//	first_node->last = add_node;
		//	add_node->last = last_node;
		//	add_node->next = first_node;
		//}

		node* last_node = first_node->last;
		last_node->next = add_node;
		first_node->last = add_node;
		add_node->last = last_node;
		add_node->next = first_node;

		count++; // 计数。
	}
}

void TwoWay_Cyclic_LinkedList::PresentNode_Next()
{
	if (first_node == nullptr) // 无节点
	{
		// 不能作为异常来处理，因为这是可能出现的情况。
		// 一边遍历，一边删除，全部删除后，遍历返回nullptr。
		present_node = nullptr;
	}
	else
	{
		if (present_node == nullptr) // 没有读取过，则为nullptr
		{
			present_node = first_node;
		}
		else
		{
			present_node = present_node->next;
		}
	}
}

void TwoWay_Cyclic_LinkedList::PresentNode_Delete()
{
#ifdef DEBUG
	if (count == 0)
	{
		throw std::range_error("空链表，没有节点可供删除。");
	}
	else if (present_node == nullptr)
	{
		throw std::range_error("要删除的节点是nullptr。");
	}
#endif // DEBUG

	// 只有两个节点时，这两个节点的next和last都相同。
	// 故，不能根据此条件判断是否只有一个节点。
	//if (present_node->next == present_node->last) // 指向第一个节点，且链表中仅有一个节点
	if (count == 1)
	{
		present_node = nullptr;
		first_node = nullptr;
	}
	else
	{
		if (present_node == first_node) // 要删除的是第一个节点
		{
			first_node = present_node->next;
		}

		present_node->last->next = present_node->next;
		present_node->next->last = present_node->last;
		present_node = present_node->next;
	}
	count--; // 计数。
}



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



/// <summary>
/// 根据已知数字，剔除不需要的变化。
/// </summary>
/// <param name="rows">所有行，内含此行所有变化</param>
/// <param name="r">行号</param>
/// <param name="suduku">已知数字</param>
void DeleteWrong(TwoWay_Cyclic_LinkedList(&rows)[9], int& r, int(&suduku)[9][9])
{
	for (size_t c = 0; c < 9; c++) // 列
	{
		if (c >= 7)
		{
			c = c;
		}
		if (suduku[r][c] != 0) // 已知数字的行和列，即r和c
		{
			for (size_t rs = 0; rs < 9; rs++) // 遍历所有行，当前遍历的行是rs
			{
				rows[rs].PresentNode_Reset();
				rows[rs].PresentNode_Next();
				int t = rows[rs].count; // count会变化，所以不能直接用count
				for (int i = 0; i < t; i++) // 根据节点数量，确定循环次数。
				{
					for (size_t rs_c = 0; rs_c <= 9; rs_c++) // 遍历当前变化的每一列，当前列是rs_c
					{
						if (rs_c == 9)
						{
							rows[rs].PresentNode_Next();
							break;
						}
						else
						{
							if ((r == rs && rs_c == c && rows[rs].present_node->value[rs_c] != suduku[r][c]) /* 和已知数字同行同列、数字不同，则剔除 */
								|| (r == rs && rs_c != c && rows[rs].present_node->value[rs_c] == suduku[r][c]) /* 和已知数字同行、不同列、数字相同，则剔除 */
								|| (r != rs && rs_c == c && rows[rs].present_node->value[rs_c] == suduku[r][c]) /* 和已知数字不同行、同列、数字相同，则剔除 */
								)
							{
								rows[rs].PresentNode_Delete();
								break;
							}
						}
					}

				}
			}
		}
	}
}




void FillDate(TwoWay_Cyclic_LinkedList(&rows)[9])
{

	PrintTime(); std::cout << "填充数据，每行362880种变化。" << std::endl;
	int permutation[9] = { 1,2,3,4,5,6,7,8,9 };
	for (size_t r = 0; r < 9; r++)
	{
		std::sort(permutation, permutation + 9);
		do
		{
			if (permutation[0] == 3
				&& permutation[1] == 7
				&& permutation[2] == 9
				&& permutation[3] == 4
				&& permutation[4] == 8
				&& permutation[5] == 1
				)
			{

			}
			int* new_change = new int[9];
			for (size_t i = 0; i < 9; i++)
			{
				new_change[i] = permutation[i];
			}
			rows[r].Add_node_ToLast(new_change);
		} while (std::next_permutation(permutation, permutation + 9));
	}
}


void EnumLoop(TwoWay_Cyclic_LinkedList(&rows)[9], std::vector<int> least, int(&suduku)[9][9])
{
	if (least.size() <= 6)
	{
		int rows_count[9] = { 0 };
		for (size_t i = 0; i < 9; i++)
		{
			rows_count[i] = rows[i].count;
		}
		for (size_t i = 0; i < least.size(); i++)
		{
			rows_count[least[i]] = 999999;
		}
		int min_position = std::min_element(rows_count, rows_count + 9) - rows_count;
		least.push_back(min_position);

		// 枚举变化最少的行
		rows[min_position].PresentNode_Reset();
		for (size_t i = 0; i < rows[min_position].count; i++)
		{
			rows[min_position].PresentNode_Next();

			// 创建rows的副本
			TwoWay_Cyclic_LinkedList rows_copy[9];
			for (size_t i = 0; i < 9; i++)
			{
				rows_copy[i] = TwoWay_Cyclic_LinkedList(rows[i]);
			}

			// 变化最少行在rows_copy中，使用当前枚举的变化。
			rows_copy[min_position] = TwoWay_Cyclic_LinkedList();
			rows_copy[min_position].Add_node_ToLast(rows[min_position].present_node->value);

			// 设其为已知数字的行
			for (size_t i = 0; i < 9; i++)
			{
				suduku[min_position][i] = rows[min_position].present_node->value[i];
			}

			// 根据当前行的变化，剔除不需要的变化
			DeleteWrong(rows_copy, min_position, suduku);

			EnumLoop(rows_copy, least, suduku);
		}
	}
	else
	{
		//for (size_t i = 0; i < 9; i++)
		//{
		//	std::cout << rows[i].count << " ";
		//}
		//std::cout << std::endl;
		// 1 2 1 1 1 1 1 1 2
		rows[0].PresentNode_Reset();
		for (size_t r0 = 0; r0 < rows[0].count; r0++)
		{
			rows[0].PresentNode_Next();
			rows[1].PresentNode_Reset();
			for (size_t r1 = 0; r1 < rows[1].count; r1++)
			{
				rows[1].PresentNode_Next();
				rows[2].PresentNode_Reset();
				for (size_t r2 = 0; r2 < rows[2].count; r2++)
				{
					rows[2].PresentNode_Next();
					rows[3].PresentNode_Reset();
					for (size_t r3 = 0; r3 < rows[3].count; r3++)
					{
						rows[3].PresentNode_Next();
						rows[4].PresentNode_Reset();
						for (size_t r4 = 0; r4 < rows[4].count; r4++)
						{
							rows[4].PresentNode_Next();
							rows[5].PresentNode_Reset();
							for (size_t r5 = 0; r5 < rows[5].count; r5++)
							{
								rows[5].PresentNode_Next();
								rows[6].PresentNode_Reset();
								for (size_t r6 = 0; r6 < rows[6].count; r6++)
								{
									rows[6].PresentNode_Next();
									rows[7].PresentNode_Reset();
									for (size_t r7 = 0; r7 < rows[7].count; r7++)
									{
										rows[7].PresentNode_Next();
										rows[8].PresentNode_Reset();
										for (size_t r8 = 0; r8 < rows[8].count; r8++)
										{
											rows[8].PresentNode_Next();

											//// 当前变化
											//for (size_t i = 0; i < 9; i++)
											//{
											//	for (size_t ii = 0; ii < 9; ii++)
											//	{
											//		std::cout << rows[i].present_node->value[ii];
											//	}
											//	std::cout << std::endl;
											//}
											//std::cout << std::endl;

											// 列，是否有重复数字
											for (size_t c = 0; c < 9; c++)
											{
												bool same_num[10] = { false };
												for (size_t r = 0; r < 9; r++)
												{
													int t = rows[r].present_node->value[c];
													if (same_num[t])
													{
														goto FIND_SAME;
													}
													else
													{
														same_num[t] = true;
													}
												}
											}

											// 小宫格，是否有重复数字
											for (size_t r = 0; r < 9; r += 3)
											{
												for (size_t c = 0; c < 9; c += 3)
												{
													bool same_num[10] = { false };
													for (size_t rr = 0; rr < 3; rr++)
													{
														for (size_t cc = 0; cc < 3; cc++)
														{
															int t = rows[r + rr].present_node->value[c + cc];
															if (same_num[t])
															{
																goto FIND_SAME;
															}
															else
															{
																same_num[t] = true;
															}
														}
													}
												}
											}

											// 列、小宫格，均无重复
											PrintTime(); std::cout << "列、小宫格，均无重复：" << std::endl;
											for (size_t r = 0; r < 9; r++)
											{
												for (size_t c = 0; c < 9; c++)
												{
													std::cout << rows[r].present_node->value[c];
												}
												std::cout << std::endl;
											}

										FIND_SAME:;

										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}




int main()
{
	std::cout << "Hello World!\n";

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






	TwoWay_Cyclic_LinkedList rows[9];

	
	FillDate(rows);

	PrintTime(); std::cout << "记录完整节点，用于最后释放资源。" << std::endl;
	node* (*del)[362880] = new node * [9][362880];
	for (int i = 0; i < 9; i++)
	{
		rows[i].PresentNode_Reset();
		for (int j = 0; j < 362880; j++)
		{
			rows[i].PresentNode_Next();
			del[i][j] = rows[i].present_node;
		}
	}


	PrintTime(); std::cout << "根据题目的数字，剔除不需要的变化。" << std::endl;
	for (int r = 0; r < 9; r++)
	{
		DeleteWrong(rows, r, suduku);
	}


	PrintTime(); std::cout << "每行剩余变化的数量。" << std::endl;
	for (size_t i = 0; i < 9; i++)
	{
		std::cout << "row " << i << " = " << rows[i].count << std::endl;
	}


	PrintTime(); std::cout << "从变化最少的行开始，边枚举边剔除。" << std::endl;
	std::vector<int> least;
	EnumLoop(rows, least, suduku);


	PrintTime(); std::cout << "释放资源。" << std::endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 362880; j++)
		{
			//在C++中，delete 关键字用于释放由 new 操作符分配的内存。
			//如果你提到的“delete会递归”是指在删除一个对象时，该对象内部可能还有指向其他对象的指针，并且这些对象也需要被删除，那么答案是不，delete 不会自动递归删除对象内部的成员。
			//如果你需要删除一个对象及其内部所有引用的对象，你需要手动做这件事。
			delete[] del[i][j]->value;
		}
	}
	delete[] del;


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



//Hello World!
//2024年 6月28日5周179天17时18分14秒0夏令时     0单次耗时(毫秒)     0总耗时(毫秒)填充数据，每行362880种变化。
//2024年 6月28日5周179天17时18分15秒0夏令时  1077单次耗时(毫秒)  1079总耗时(毫秒)记录完整节点，用于最后释放资源。
//2024年 6月28日5周179天17时18分15秒0夏令时   219单次耗时(毫秒)  1300总耗时(毫秒)根据题目的数字，剔除不需要的变化。
//2024年 6月28日5周179天17时18分17秒0夏令时  1432单次耗时(毫秒)  2734总耗时(毫秒)每行剩余变化的数量。
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024年 6月28日5周179天17时18分17秒0夏令时     1单次耗时(毫秒)  2736总耗时(毫秒)从变化最少的行开始，边枚举边剔除。
//2024年 6月28日5周179天17时18分25秒0夏令时  8922单次耗时(毫秒) 11659总耗时(毫秒)列、小宫格，均无重复：
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024年 6月28日5周179天17时18分47秒0夏令时 21149单次耗时(毫秒) 32809总耗时(毫秒)释放资源。
//2024年 6月28日5周179天17时18分47秒0夏令时   356单次耗时(毫秒) 33167总耗时(毫秒)Hello World!