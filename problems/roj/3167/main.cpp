/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:58
 * update_at: 2026-10-06 11:58
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int OFF = 10000;          // 值域平移量，把 [-10000,10000] 映射到 [0,20000]
const int MAXV = 2 * OFF + 1;   // DP 值域大小

int n;
ll t;
ll a[105];          // 原始数组，下标从 1 开始
int f[105][MAXV];   // f[i][v]：前缀到 i 凑出值 v 时 a[i] 的符号（1=+，-1=-，0=不可达）
int s[105];         // 回溯得到的符号序列，s[1] 恒为 +1

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> t)) return 0;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    if (n == 1) return 0;   // 无操作，不输出

    // 初始化：a[1] 系数恒为 +1；a[2] 必为 -1（第一次操作只能在位置 1）
    f[1][OFF + (int)a[1]] = 1;
    f[2][OFF + (int)(a[1] - a[2])] = -1;

    // 线性 DP：f[i][v] 由 f[i-1][v-a[i]]（取 +）或 f[i-1][v+a[i]]（取 -）转移
    for (int i = 3; i <= n; ++i) {
        for (int j = 0; j < MAXV; ++j) {
            if (f[i - 1][j] == 0) continue;
            if (j + (int)a[i] < MAXV) f[i][j + (int)a[i]] = 1;   // 取 +
            if (j >= (int)a[i])       f[i][j - (int)a[i]] = -1;  // 取 -
        }
    }

    int cur = OFF + (int)t;
    if (f[n][cur] == 0) return 0;   // 无解，静默输出 0 行

    // 倒推符号，优先取 +1（与标程约定一致）
    for (int i = n; i >= 1; --i) {
        s[i] = f[i][cur];
        if (s[i] == 1) cur -= (int)a[i];
        else if (s[i] == -1) cur += (int)a[i];
    }

    // 还原操作位置：先依次消去每个 +1 项，末尾再从 1 号位消掉所有 -1 项
    int cnt = 0;    // 已消去的 +1 个数，其后元素位置整体左移
    for (int i = 2; i <= n; ++i) {
        if (s[i] == 1) {
            cout << (i - cnt - 1) << "\n";
            ++cnt;
        }
    }
    for (int i = 2; i <= n; ++i) {
        if (s[i] == -1) {
            cout << "1\n";
        }
    }

    return 0;
}
