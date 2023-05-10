#include <iostream>
#include <vector>
using namespace std;

/*
 * 给定地图grid、已访问格子visited和当前位置pos，返回下一步可走的格子
 */

vector<pair<int, int>> calc_next_steps(vector<vector<int>> &grid, vector<vector<bool>> &visited, pair<int, int> &pos)
{
    vector<pair<int, int>> next_steps;
    int x = pos.first;
    int y = pos.second;
    if (x - 1 >= 0 && grid[x - 1][y] != 0 && !visited[x - 1][y])
    {
        next_steps.push_back(make_pair(x - 1, y));
    }
    if (x + 1 < grid[0].size() && grid[x + 1][y] != 0 && !visited[x + 1][y])
    {
        next_steps.push_back(make_pair(x + 1, y));
    }
    if (y - 1 >= 0 && grid[x][y - 1] != 0 && !visited[x][y - 1])
    {
        next_steps.push_back(make_pair(x, y - 1));
    }
    if (y + 1 < grid.size() && grid[x][y + 1] != 0 && !visited[x][y + 1])
    {
        next_steps.push_back(make_pair(x, y + 1));
    }
    return next_steps;
}

int getMaximumGold(vector<vector<int>> &grid)
{
    vector<vector<bool>> visited;  // 已访问格子
    vector<pair<int, int>> starts; // 起始格子
    vector<pair<int, int>> steps;  // 步骤栈
    vector<pair<int, int>> path;   // 路径
    vector<pair<int, int>> forks;  // 分叉点
    vector<int> fork_count;        // 分叉点计数
    int maxGold = 0;               // 最大黄金

    // 初始化
    for (int i = 0; i < grid.size(); i++)
    {
        vector<bool> tmp;
        for (int j = 0; j < grid[i].size(); j++)
        {
            tmp.push_back(false);
        }
        visited.push_back(tmp);
    }

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] != 0)
            {
                starts.push_back(make_pair(i, j));
            }
        }
    }

    // 对每个起始格子进行搜索
    for (auto start : starts)
    {
        // 重置数据结构
        for (int i = 0; i < visited.size(); i++)
        {
            for (int j = 0; j < visited[i].size(); j++)
            {
                visited[i][j] = false;
            }
        }
        steps.clear();
        path.clear();
        forks.clear();
        fork_count.clear();

        steps.push_back(start);
        while (!steps.empty())
        {
            // 取出栈顶格子，标记为已经过，加入当前路径，然后判断其有没有下一步
            pair<int, int> pos = steps.back();
            steps.pop_back();
            visited[pos.first][pos.second] = true;
            path.push_back(pos);

            vector<pair<int, int>> next_steps = calc_next_steps(grid, visited, pos);

            // 如果有下一步，将下一步压入栈中
            if (!next_steps.empty())
            {
                for (auto next_step : next_steps)
                {
                    steps.push_back(next_step);
                }

                // 如果有多于一步的下一步，将当前路径压入分岔点栈中
                if (next_steps.size() > 1)
                {
                    forks.push_back(pos);
                    fork_count.push_back(next_steps.size() - 1);
                }
            }
            // 如果没有下一步，计算当前路径的黄金总量
            else
            {
                int gold = 0;
                for (auto step : path)
                {
                    gold += grid[step.first][step.second];
                }

                // 更新最大黄金
                if (gold > maxGold)
                {
                    maxGold = gold;
                }

                // 回退路径栈
                while (!path.empty())
                {
                    pair<int, int> last_step = path.back();
                    auto fork_pos = find(forks.begin(), forks.end(), last_step);
                    // 如果不是分岔点，或者是分岔点但是分岔点栈中的分岔点已经被回退完了，则回退
                    if (fork_pos == forks.end() || fork_count[fork_pos - forks.begin()] == 0)
                    {
                        path.pop_back();
                        visited[last_step.first][last_step.second] = false;
                    }
                    // 如果是分岔点，减少该分岔点分岔数，回退到分岔点
                    else
                    {
                        fork_count[fork_pos - forks.begin()]--;
                        break;
                    }
                }
            }
        }
    }

    // 返回最大黄金
    return maxGold;
}

int main()
{
    vector<vector<int>> grid;

    // 获取输入
    cout << "请输入单元格行数、列数：" << endl;
    int row, col;
    cin >> row >> col;
    cout << "请输入单元格黄金数：" << endl;
    for (int i = 0; i < row; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < col; j++)
        {
            int gold;
            cin >> gold;
            tmp.push_back(gold);
        }
        grid.push_back(tmp);
    }

    cout << endl;

    // grid = {{0, 6, 0}, {5, 8, 7}, {0, 9, 0}};
    // grid = {{1, 0, 7}, {2, 0, 6}, {3, 4, 5}, {0, 3, 0}};
    // grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // 输出
    cout << getMaximumGold(grid) << endl;

    return 0;
}
