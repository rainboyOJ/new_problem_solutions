/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:28
 * update_at: 2026-10-01 20:28
 */
// subtask_80.cpp：80% 数据 k <= 5*10^6，可以从 0 号串一步步推到 k 号串。
// 格雷码的相邻两个编号恰好只差一位：编号 i 的串由编号 i-1 的串翻转
// i 的最低位 1 对应的那一位得到。走 k 步即可，时间 O(k)，与 n 无关。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;    // 编码位数
ll k;     // 编号，本文件只处理 k <= 5*10^6
ll gray;  // 当前编号对应的格雷码数值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // 编号 0 的格雷码是全 0。
    gray = 0;

    // 从编号 1 推到编号 k：编号 i 相对 i-1 恰好翻转 lowbit(i) 这一位。
    for (ll i = 1; i <= k; i++) {
        ll low = i & (-i); // 取出 i 的最低非零二进制位
        gray ^= low;
    }

    // 从最高位到最低位输出，恰好 n 位，前导零也要输出。
    for (int bit = n - 1; bit >= 0; bit--) {
        cout << ((gray >> bit) & 1LL);
    }
    cout << '\n';

    return 0;
}
