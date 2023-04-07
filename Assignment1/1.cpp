#include <iostream>
using namespace std;

int Q1(int m, int n)
{
    // 如果要爬的步数或卡路里数不为正，无法完成，返回0
    if (m <= 0 || n <= 0)
        return 0;

    // 如果要爬的步数为1且卡路里足够，只有1种方法
    if (m == 1 && n >= 1)
        return 1;

    // 如果要爬的步数为2且卡路里足够，只有2种方法
    if (m == 2 && n >= 3)
        return 2;

    // 一般情况，是m-1步、花1卡路里爬1步和m-2步、花3卡路里爬2步的和
    return Q1(m - 1, n - 1) + Q1(m - 2, n - 3);
}

int main()
{
    int m, n;
    cin >> m >> n;
    cout << Q1(m, n) << endl;

    return 0;
}
