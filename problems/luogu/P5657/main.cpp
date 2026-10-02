/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:28
 * update_at: 2026-10-01 20:28
 */
// main.cpp：满分做法，直接用二进制反射格雷码公式 gray = k ^ (k >> 1)。
// 时间 O(n)，空间 O(1)，是本题正式提交版本。
#include <bits/stdc++.h>
using namespace std;

// 本题 k 的上界是 2^64-1，超出有符号 long long 的范围，
// 所以编号和答案都用无符号 64 位整数，靠声明类型解决，不做任何强制转换。
typedef unsigned long long ull;

int n;    // 编码位数，1 <= n <= 64
ull k;    // 编号，0 <= k < 2^n
ull gray; // 编号 k 对应的格雷码数值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // 每一位表示「编号的相邻两位是否不同」，这正是格雷码的定义。
    gray = k ^ (k >> 1);

    // 从第 n-1 位输出到第 0 位，恰好 n 位，前导零也要输出。
    // n = 64 时最大只右移到第 63 位，不会出现 1ULL << 64 这种非法左移。
    for (int bit = n - 1; bit >= 0; bit--) {
        cout << ((gray >> bit) & 1ULL);
    }
    cout << '\n';

    return 0;
}
