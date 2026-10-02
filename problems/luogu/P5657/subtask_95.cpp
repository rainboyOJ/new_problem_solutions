/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:28
 * update_at: 2026-10-01 20:28
 */
// subtask_95.cpp：95% 数据 k <= 2^63-1，正好装进有符号 long long。
// 直接套二进制反射格雷码的公式 gray = k ^ (k >> 1)，时间 O(n)。
// 注意 k 最大是 2^63-1，它的最高位一定是 0，所以 gray 非负、有符号右移也安全；
// 再大一点（n = 64 时 k 可以到 2^64-1）就装不下了，需要 main.cpp 的无符号写法。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;    // 编码位数
ll k;     // 编号，0 <= k <= 2^63-1
ll gray;  // 编号 k 对应的格雷码数值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // 编号与右移一位的编号异或，得到的每一位表示「相邻两位是否不同」。
    gray = k ^ (k >> 1);

    // 从最高位到最低位输出，恰好 n 位，前导零也要输出。
    for (int bit = n - 1; bit >= 0; bit--) {
        cout << ((gray >> bit) & 1LL);
    }
    cout << '\n';

    return 0;
}
