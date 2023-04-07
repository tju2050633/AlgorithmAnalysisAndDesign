#include <iostream>
using namespace std;

// 返回值第一个元素为爬m步、尽量多花n卡路里的方式数，第二个元素为最大消耗卡路里数
pair<int, int> Q2(int m, int n)
{
    // 如果要爬的步数或卡路里数不为正，无法完成，返回0
    if (m <= 0 || n <= 0)
        return pair<int, int>(0, 0);

    // 如果要爬的步数为1且卡路里足够，只有1种方法尽可能消耗卡路里，最大消耗卡路里数为1
    if (m == 1 && n >= 1)
        return pair<int, int>(1, 1);

    // 如果要爬的步数为2且卡路里足够，只有1种方法尽可能消耗卡路里，最大消耗卡路里数为3
    if (m == 2 && n >= 3)
        return pair<int, int>(1, 3);

    int k1 = Q2(m - 1, n - 1).second + 1; // 从m-1步爬上来最多消耗的卡路里数
    int k2 = Q2(m - 2, n - 3).second + 3; // 从m-2步爬上来最多消耗的卡路里数

    // 从m-1步爬上来最多消耗的卡路里数大于从m-2步爬上来最多消耗的卡路里数，那么从m-1步爬上来的方法数就是最大消耗卡路里数
    // 此时舍弃从m-2步爬上来的方法数
    if (k1 > k2)
    {
        return Q2(m - 1, n - 1);
    }
    // 从m-1步爬上来最多消耗的卡路里数小于从m-2步爬上来最多消耗的卡路里数，那么从m-2步爬上来的方法数就是最大消耗卡路里数
    // 此时舍弃从m-1步爬上来的方法数
    else if (k1 < k2)
    {
        return Q2(m - 2, n - 3);
    }
    // 从m-1步爬上来最多消耗的卡路里数等于从m-2步爬上来最多消耗的卡路里数
    // 那么从m-1步爬上来的方法数和从m-2步爬上来的方法数需要求和
    else
    {
        return pair<int, int>(Q2(m - 1, n - 1).first + Q2(m - 2, n - 3).first, k1);
    }
}

int main()
{
    int m, n;
    cin >> m >> n;
    cout << Q2(m, n).first << endl;

    return 0;
}
