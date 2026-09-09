/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 23:40
 * update_at: 2026-08-28 23:40
 */
// main.cpp：把每个 3x3 小矩阵编码成一个 9 位三进制数（R=0, G=1, B=2），
// 用 bool seen[19683] 标记出现过的编码，统计不同小矩阵的数量。
// 复杂度 O(nm)：每个像素恰好被扫一次。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;      // n <= 3000
const int MAXCODE = 19683;  // 3^9：9 个格子每格取 R/G/B 之一，共 3^9 种小矩阵

int n, m;
string g[MAXN];      // 像素矩阵的每一行
bool seen[MAXCODE];  // seen[x] = true 表示编码为 x 的 3x3 小矩阵已出现过

// 把颜色字符映射成三进制位：R -> 0，G -> 1，B -> 2。
int color_id(char c) {
    if (c == 'R') return 0;
    if (c == 'G') return 1;
    return 2; // 'B'
}

// 提取左上角为 (x, y) 的 3x3 小矩阵，按行优先顺序拼成三进制数。
// 逐位 code = code * 3 + 当前颜色，编码唯一落在 0..19682。
int encode(int x, int y) {
    int code = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            code = code * 3 + color_id(g[x + i][y + j]);
        }
    }
    return code;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> g[i];

    int ans = 0;
    // 横向 n/3 块、纵向 m/3 块；块 (bi, bj) 的左上角是 (bi*3, bj*3)。
    for (int bi = 0; bi < n / 3; bi++) {
        for (int bj = 0; bj < m / 3; bj++) {
            int code = encode(bi * 3, bj * 3);
            if (!seen[code]) {
                seen[code] = true;
                ans++;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}