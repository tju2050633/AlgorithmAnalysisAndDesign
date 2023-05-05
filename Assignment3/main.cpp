#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    Node(int i, int j) : x(i), y(j) {}
    int x;
    int y;
};

int getMaximumGold(vector<vector<int>> &grid)
{
    // 出发点列表
    vector<Node> start;

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid.size(); j++)
        {
            if (grid[i][j] != 0)
            {
                Node node(i, j);
            }
        }
    }

    int max_v = 0; // 最大价值
    int cur_v = 0; // 当前价值

    while(true)
    {
        
    }
}

int main()
{
    // 输入
    vector<vector<int>> grid;

    // 输出
    cout << getMaximumGold(grid) << endl;

    return 0;
}
