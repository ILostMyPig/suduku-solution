
// suduku solution.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#define DEBUG


#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <iomanip>


//// vector��ɾ������̫������Ҫ����
struct node // ˫��ѭ������
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
	node* present_node; // û�ж�ȡ������Ϊnullptr
	int count;

	/// <summary>
	/// ����½ڵ㡣
	/// �½ڵ�ĵ�ַ������first_node.last��
	/// </summary>
	/// <param name="value"></param>
	void Add_node_ToLast(int*& value);

	/// <summary>
	/// ָ����һ���ڵ㡣
	/// ���޽ڵ㣬��ָ��nullptr��
	/// </summary>
	void PresentNode_Next();


	// ���á�
	// ��present_nodeָ�����һ���ڵ�ʱ��ɾ��present_node�Ľڵ㣬����present_nodeֱ��ָ��first�����޷������Ƿ�ת��һȦ��
	/// <summary>
	/// ָ����һ���ڵ㡣
	/// ���޽ڵ㣬��ָ��nullptr��
	/// ����һ���ڵ��ǵ�һ���ڵ㣬��ָ��nullptr��
	/// </summary>
	//void PresentNode_Next_StopLast();

	/// <summary>
	/// �ָ���û�ж�ȡ��������ָ��nullptr��
	/// </summary>
	void PresentNode_Reset() { present_node = nullptr; }

	/// <summary>
	/// ɾ����ǰ�ڵ㣬��ָ����һ���ڵ㡣
	/// ��ɾ�����޽ڵ㣬��ָ��nullptr��
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

	if (first_node == nullptr) // �޽ڵ�
	{
		first_node = add_node;
		first_node->last = first_node;
		first_node->next = first_node;

		count++; // ������
	}
	else
	{


		//// ���ã�if���������������ͬһ�δ�����		
		//if (first_node->last == first_node->next ) // ֻ��һ���ڵ�
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

		count++; // ������
	}
}

void TwoWay_Cyclic_LinkedList::PresentNode_Next()
{
	if (first_node == nullptr) // �޽ڵ�
	{
		// ������Ϊ�쳣��������Ϊ���ǿ��ܳ��ֵ������
		// һ�߱�����һ��ɾ����ȫ��ɾ���󣬱�������nullptr��
		present_node = nullptr;
	}
	else
	{
		if (present_node == nullptr) // û�ж�ȡ������Ϊnullptr
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
		throw std::range_error("������û�нڵ�ɹ�ɾ����");
	}
	else if (present_node == nullptr)
	{
		throw std::range_error("Ҫɾ���Ľڵ���nullptr��");
	}
#endif // DEBUG

	// ֻ�������ڵ�ʱ���������ڵ��next��last����ͬ��
	// �ʣ����ܸ��ݴ������ж��Ƿ�ֻ��һ���ڵ㡣
	//if (present_node->next == present_node->last) // ָ���һ���ڵ㣬�������н���һ���ڵ�
	if (count == 1)
	{
		present_node = nullptr;
		first_node = nullptr;
	}
	else
	{
		if (present_node == first_node) // Ҫɾ�����ǵ�һ���ڵ�
		{
			first_node = present_node->next;
		}

		present_node->last->next = present_node->next;
		present_node->next->last = present_node->last;
		present_node = present_node->next;
	}
	count--; // ������
}



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



/// <summary>
/// ������֪���֣��޳�����Ҫ�ı仯��
/// </summary>
/// <param name="rows">�����У��ں��������б仯</param>
/// <param name="r">�к�</param>
/// <param name="suduku">��֪����</param>
void DeleteWrong(TwoWay_Cyclic_LinkedList(&rows)[9], int& r, int(&suduku)[9][9])
{
	for (size_t c = 0; c < 9; c++) // ��
	{
		if (c >= 7)
		{
			c = c;
		}
		if (suduku[r][c] != 0) // ��֪���ֵ��к��У���r��c
		{
			for (size_t rs = 0; rs < 9; rs++) // ���������У���ǰ����������rs
			{
				rows[rs].PresentNode_Reset();
				rows[rs].PresentNode_Next();
				int t = rows[rs].count; // count��仯�����Բ���ֱ����count
				for (int i = 0; i < t; i++) // ���ݽڵ�������ȷ��ѭ��������
				{
					for (size_t rs_c = 0; rs_c <= 9; rs_c++) // ������ǰ�仯��ÿһ�У���ǰ����rs_c
					{
						if (rs_c == 9)
						{
							rows[rs].PresentNode_Next();
							break;
						}
						else
						{
							if ((r == rs && rs_c == c && rows[rs].present_node->value[rs_c] != suduku[r][c]) /* ����֪����ͬ��ͬ�С����ֲ�ͬ�����޳� */
								|| (r == rs && rs_c != c && rows[rs].present_node->value[rs_c] == suduku[r][c]) /* ����֪����ͬ�С���ͬ�С�������ͬ�����޳� */
								|| (r != rs && rs_c == c && rows[rs].present_node->value[rs_c] == suduku[r][c]) /* ����֪���ֲ�ͬ�С�ͬ�С�������ͬ�����޳� */
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

	PrintTime(); std::cout << "������ݣ�ÿ��362880�ֱ仯��" << std::endl;
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

		// ö�ٱ仯���ٵ���
		rows[min_position].PresentNode_Reset();
		for (size_t i = 0; i < rows[min_position].count; i++)
		{
			rows[min_position].PresentNode_Next();

			// ����rows�ĸ���
			TwoWay_Cyclic_LinkedList rows_copy[9];
			for (size_t i = 0; i < 9; i++)
			{
				rows_copy[i] = TwoWay_Cyclic_LinkedList(rows[i]);
			}

			// �仯��������rows_copy�У�ʹ�õ�ǰö�ٵı仯��
			rows_copy[min_position] = TwoWay_Cyclic_LinkedList();
			rows_copy[min_position].Add_node_ToLast(rows[min_position].present_node->value);

			// ����Ϊ��֪���ֵ���
			for (size_t i = 0; i < 9; i++)
			{
				suduku[min_position][i] = rows[min_position].present_node->value[i];
			}

			// ���ݵ�ǰ�еı仯���޳�����Ҫ�ı仯
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

											//// ��ǰ�仯
											//for (size_t i = 0; i < 9; i++)
											//{
											//	for (size_t ii = 0; ii < 9; ii++)
											//	{
											//		std::cout << rows[i].present_node->value[ii];
											//	}
											//	std::cout << std::endl;
											//}
											//std::cout << std::endl;

											// �У��Ƿ����ظ�����
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

											// С�����Ƿ����ظ�����
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

											// �С�С���񣬾����ظ�
											PrintTime(); std::cout << "�С�С���񣬾����ظ���" << std::endl;
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

	PrintTime(); std::cout << "��¼�����ڵ㣬��������ͷ���Դ��" << std::endl;
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


	PrintTime(); std::cout << "������Ŀ�����֣��޳�����Ҫ�ı仯��" << std::endl;
	for (int r = 0; r < 9; r++)
	{
		DeleteWrong(rows, r, suduku);
	}


	PrintTime(); std::cout << "ÿ��ʣ��仯��������" << std::endl;
	for (size_t i = 0; i < 9; i++)
	{
		std::cout << "row " << i << " = " << rows[i].count << std::endl;
	}


	PrintTime(); std::cout << "�ӱ仯���ٵ��п�ʼ����ö�ٱ��޳���" << std::endl;
	std::vector<int> least;
	EnumLoop(rows, least, suduku);


	PrintTime(); std::cout << "�ͷ���Դ��" << std::endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 362880; j++)
		{
			//��C++�У�delete �ؼ��������ͷ��� new ������������ڴ档
			//������ᵽ�ġ�delete��ݹ顱��ָ��ɾ��һ������ʱ���ö����ڲ����ܻ���ָ�����������ָ�룬������Щ����Ҳ��Ҫ��ɾ������ô���ǲ���delete �����Զ��ݹ�ɾ�������ڲ��ĳ�Ա��
			//�������Ҫɾ��һ���������ڲ��������õĶ�������Ҫ�ֶ�������¡�
			delete[] del[i][j]->value;
		}
	}
	delete[] del;


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



//Hello World!
//2024�� 6��28��5��179��17ʱ18��14��0����ʱ     0���κ�ʱ(����)     0�ܺ�ʱ(����)������ݣ�ÿ��362880�ֱ仯��
//2024�� 6��28��5��179��17ʱ18��15��0����ʱ  1077���κ�ʱ(����)  1079�ܺ�ʱ(����)��¼�����ڵ㣬��������ͷ���Դ��
//2024�� 6��28��5��179��17ʱ18��15��0����ʱ   219���κ�ʱ(����)  1300�ܺ�ʱ(����)������Ŀ�����֣��޳�����Ҫ�ı仯��
//2024�� 6��28��5��179��17ʱ18��17��0����ʱ  1432���κ�ʱ(����)  2734�ܺ�ʱ(����)ÿ��ʣ��仯��������
//row 0 = 94
//row 1 = 2206
//row 2 = 68
//row 3 = 66
//row 4 = 4
//row 5 = 298
//row 6 = 104
//row 7 = 16
//row 8 = 2348
//2024�� 6��28��5��179��17ʱ18��17��0����ʱ     1���κ�ʱ(����)  2736�ܺ�ʱ(����)�ӱ仯���ٵ��п�ʼ����ö�ٱ��޳���
//2024�� 6��28��5��179��17ʱ18��25��0����ʱ  8922���κ�ʱ(����) 11659�ܺ�ʱ(����)�С�С���񣬾����ظ���
//736518429
//845972631
//192364578
//568123947
//423796185
//971845263
//657289314
//289431756
//314657892
//2024�� 6��28��5��179��17ʱ18��47��0����ʱ 21149���κ�ʱ(����) 32809�ܺ�ʱ(����)�ͷ���Դ��
//2024�� 6��28��5��179��17ʱ18��47��0����ʱ   356���κ�ʱ(����) 33167�ܺ�ʱ(����)Hello World!