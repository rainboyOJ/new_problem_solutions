/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:00
 * update_at: 2026-10-09 21:14
 */
// 20030《异或查询》：Lucas 定理 + 高低位分块
// b[x][y] = XOR_{k ⊆ x} a[y + k]（组合数 C(x,k) 的奇偶性由 Lucas 定理给出 k & x == k）。
// 低 BLOCK_BITS 位的答案全部预处理，查询时只枚举高位的子集。
#include <iostream>

using namespace std;
typedef long long ll;

const int MAXN = 100005;
const int BLOCK_BITS = 8;                    // 低位块宽，低位状态数 2^8 = 256
const int BLOCK_SIZE = 1 << BLOCK_BITS;

int a[MAXN];                    // 题面输入的初始序列
int f[BLOCK_SIZE][MAXN];        // f[j][i] = XOR_{k ⊆ j} a[i + k]，即低 BLOCK_BITS 位为 j 的答案

// 预处理低位表。j 去掉最低位 p 后得到 p_prev，则子集枚举可拆成
// "不取 p" 与 "取 p" 两支，故 f[j][i] = f[p_prev][i] ^ f[p_prev][i + p]。
void build_low_table(int n) {
    for (int i = 0; i < n; i++) {
        f[0][i] = a[i];
    }
    for (int j = 1; j < BLOCK_SIZE; j++) {
        int p = j & -j;            // j 的最低位，作为本次拆分的位权
        int p_prev = j ^ p;
        for (int i = 0; i + j < n; i++) {
            f[j][i] = f[p_prev][i] ^ f[p_prev][i + p];
        }
    }
}

// 单次询问：x 拆成低位 x2 与高位 x1，枚举 x1 的全部子集 k1，
// 每项查表 f[x2][y + (k1 << BLOCK_BITS)] 后异或起来。
int query(int x, int y) {
    int x2 = x & (BLOCK_SIZE - 1);
    int x1 = x >> BLOCK_BITS;

    int ans = 0;
    int k1 = x1;
    while (true) {
        ans ^= f[x2][y + (k1 << BLOCK_BITS)];
        if (k1 == 0) break;        // 子集枚举必须先用完 k1 = 0 再退出，否则漏项
        k1 = (k1 - 1) & x1;        // 枚举 x1 子集的标准位技巧
    }
    return ans;
}

void solve() {
    int n, q;
    if (!(cin >> n >> q)) return;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build_low_table(n);

    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        cout << query(x, y) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
