#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <queue>

clock_t start_, end_;

using namespace std;

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
	// TODO
	int row = matrix.size();
	int col = matrix[0].size();

	int i = 0, j = col - 1;
	while (i < row && j >= 0)
	{
		if (matrix[i][j] == target)
			return true;
		else if (matrix[i][j] > target)
			j--;
		else
			i++;
	}
	return false;
}

// bool searchMatrix(vector<vector<int>> &matrix, int target)
// {
// 	// TODO
// 	int m = matrix.size();
// 	int n = matrix[0].size();

// 	// 待搜索子矩阵的左上角和右下角构成2元元组，元组构成队列
// 	queue<pair<pair<int, int>, pair<int, int>>> to_be_searched;
// 	// 初始子矩阵为整个矩阵
// 	to_be_searched.push(pair<pair<int, int>, pair<int, int>>(
// 		pair<int, int>(0, 0),
// 		pair<int, int>(m - 1, n - 1)));

// 	while (!to_be_searched.empty())
// 	{
// 		// 取出队列头
// 		auto sub_matrix = to_be_searched.front();
// 		to_be_searched.pop();

// 		// 计算子矩阵最上面一行、最左边一列、最下面一行和最右边一列的值
// 		int top_row = sub_matrix.first.first;
// 		int bottom_row = sub_matrix.second.first;
// 		int left_col = sub_matrix.first.second;
// 		int right_col = sub_matrix.second.second;

// 		// 获取子矩阵中间值
// 		int mid_row = (top_row + bottom_row) / 2;
// 		int mid_col = (left_col + right_col) / 2;
// 		int mid_value = matrix[mid_row][mid_col];

// 		// 如果中间值等于目标值，返回true
// 		if (mid_value == target)
// 			return true;

// 		// 中间值不等于目标值，说明该行、该列都不可能有目标值
// 		// 将子矩阵分为四个子矩阵
// 		auto left_top_sub_matrix = // 左上角子矩阵
// 			pair<pair<int, int>, pair<int, int>>(
// 				pair<int, int>(top_row, left_col),
// 				pair<int, int>(mid_row - 1, mid_col - 1));

// 		auto left_bottom_sub_matrix = // 左下角子矩阵
// 			pair<pair<int, int>, pair<int, int>>(
// 				pair<int, int>(mid_row + 1, left_col),
// 				pair<int, int>(bottom_row, mid_col - 1));

// 		auto right_top_sub_matrix = // 右上角子矩阵
// 			pair<pair<int, int>, pair<int, int>>(
// 				pair<int, int>(top_row, mid_col + 1),
// 				pair<int, int>(mid_row - 1, right_col));

// 		auto right_bottom_sub_matrix = // 右下角子矩阵
// 			pair<pair<int, int>, pair<int, int>>(
// 				pair<int, int>(mid_row + 1, mid_col + 1),
// 				pair<int, int>(bottom_row, right_col));

// 		// 判断子矩阵是否存在
// 		bool left_top_exist = left_top_sub_matrix.first.first <= left_top_sub_matrix.second.first &&
// 							  left_top_sub_matrix.first.second <= left_top_sub_matrix.second.second;
// 		bool left_bottom_exist = left_bottom_sub_matrix.first.first <= left_bottom_sub_matrix.second.first &&
// 								 left_bottom_sub_matrix.first.second <= left_bottom_sub_matrix.second.second;
// 		bool right_top_exist = right_top_sub_matrix.first.first <= right_top_sub_matrix.second.first &&
// 							   right_top_sub_matrix.first.second <= right_top_sub_matrix.second.second;
// 		bool right_bottom_exist = right_bottom_sub_matrix.first.first <= right_bottom_sub_matrix.second.first &&
// 								  right_bottom_sub_matrix.first.second <= right_bottom_sub_matrix.second.second;

// 		// 左下角和右上角子矩阵加入队列
// 		if (left_bottom_exist)
// 			to_be_searched.push(left_bottom_sub_matrix);
// 		if (right_top_exist)
// 			to_be_searched.push(right_top_sub_matrix);

// 		// 如果中间值大于目标值，左上角子矩阵加入队列
// 		if (mid_value > target && left_top_exist)
// 			to_be_searched.push(left_top_sub_matrix);

// 		// 如果中间值小于目标值，右下角子矩阵加入队列
// 		if (mid_value < target && right_bottom_exist)
// 			to_be_searched.push(right_bottom_sub_matrix);
// 	}

// 	return false;
// }

int main()
{
	//	读取测试数据
	ifstream inFile("testcase.csv", ios::in);
	string lineStr;

	start_ = clock();

	if (!inFile.is_open())
	{
		cout << "Error!" << endl;
	}

	//	测试结果标记
	int correct_num = 0;
	int error_num = 0;

	//	运行测试数据，输出结果
	int line_count = 0;
	while (getline(inFile, lineStr))
	{
		line_count++;
		vector<vector<int>> matrix;

		string number;
		bool num_end = false;
		bool line_end = false;
		int target = -1;
		bool result = false;
		vector<int> line;
		for (int i = 0; i < lineStr.size(); i++)
		{
			if (!num_end)
			{
				if (lineStr[i] == '[')
				{
					line_end = false;
					line.clear();
				}
				else if (lineStr[i] == ']' && line_end)
				{
					number = "";
					num_end = true;
				}
				else if (lineStr[i] == ']' && !num_end)
				{
					line.push_back(atoi(number.c_str()));
					matrix.push_back(line);
					line_end = true;
					number = "";
				}

				else if (lineStr[i] >= '0' && lineStr[i] <= '9')
					number += lineStr[i];
				else if (lineStr[i] == ',' && !line_end)
				{
					line.push_back(atoi(number.c_str()));
					number = "";
				}
			}
			else
			{
				if (target == -1)
				{
					if (lineStr[i] >= '0' && lineStr[i] <= '9')
						number += lineStr[i];
					else if (lineStr[i] == ',' && number != "")
						target = atoi(number.c_str());
				}
				else
					result = lineStr[i] - '0';
			}
		}

		if(line_count == 3)
		{
			cout << "test" << endl;
			for(int i = 0; i < matrix.size(); i++)
			{
				for(int j = 0; j < matrix[i].size(); j++)
					cout << matrix[i][j] << " ";
				cout << endl;
			}
			cout << target << endl;
			cout << result << endl;
		}

		if (result == searchMatrix(matrix, target))
			correct_num += 1;
			// cout << line_count << " correct" << endl;
		else
			error_num += 1;
			// cout << line_count << " error" << endl;
	}
	end_ = clock();
	double endtime = (double)(end_ - start_) / CLOCKS_PER_SEC;
	inFile.close();

	cout << "correct:" << correct_num << endl;
	cout << "error:" << error_num << endl;
	cout << "用时:" << endtime * 1000 << "ms" << endl;

	// system("pause");

	return 0;
}
