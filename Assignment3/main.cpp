#include <iostream>
#include <string>
#include <vector>

using namespace std;

int maxGold(vector<vector<int>> &grid, int i, int j)
{
	int max_gold = 0;									// 最大黄金数
	int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}; // 方向数组
	int temp = grid[i][j];								// 保存当前位置的黄金数
	grid[i][j] = 0;										// 将当前位置的黄金数置为0，表示已经访问过

	// 遍历当前位置的四个方向
	for (int k = 0; k < 4; ++k)
	{
		// 计算下一步坐标
		int x = i + dir[k][0], y = j + dir[k][1];

		// 如果新坐标合法，则递归计算该路径上最大黄金数
		if (x >= 0 && x < grid.size() && y >= 0 && y < grid[i].size() && grid[x][y] != 0)
		{
			max_gold = max(max_gold, maxGold(grid, x, y));
		}
	}

	// 将当前位置的黄金数还原
	grid[i][j] = temp;

	return max_gold + grid[i][j];
}

int getMaximumGold(vector<vector<int>> &grid)
{
	// 最大黄金数
	int max_gold = 0;

	// 遍历每个位置
	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			// 如果当前位置有黄金，就以当前位置为起点计算可以获得的最大黄金数
			// 并更新最大黄金数
			if (grid[i][j] != 0)
			{
				max_gold = max(max_gold, maxGold(grid, i, j));
			}
		}
	}
	return max_gold;
}

int main()
{
	vector<vector<int>> grid;

	string lineStr;
	getline(cin, lineStr);

	string number;
	bool num_end = false;
	bool line_end = false;
	int target = -1;
	bool result;
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
				grid.push_back(line);
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
	}

	cout << getMaximumGold(grid) << endl;

	return 0;
}
