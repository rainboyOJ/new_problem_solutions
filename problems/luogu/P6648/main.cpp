/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-27 14:34
 * update_at: 2026-10-30 17:09
 */
// main.cpp：P6648 解法一（主解），纯正三角形倍增 + 查询时用 6 块拼出目标三角形。
// 全程只处理正三角形，不做 DAG 递归分解，只滚动保留 2 层表。
// 时间 O(n^2 log k)，空间 O(n^2) 且只有 2 层，与 k 无关。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 3005;

// f[p][i][j]：p = 0/1 两层轮换；(i,j) 为上顶点、边长 2^t 的三角形内的最大值。
// 单层 3005 x 3005 的 int 约 36 MB，两层合计约 72 MB。
int f[2][MAXN][MAXN];

int n, k;   // 三角形大小、要求的子三角形边长；都不超过 3000，只当长度和下标用，所以用 int
int lg;     // 不超过 k 的最大 2 的幂的指数
int block;  // block = 2^lg，查询时用的块边长

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    lg = 0;
    while ((2 << lg) <= k) {
        lg++;
    }
    block = 1 << lg;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> f[0][i][j];
        }
    }

    // 倍增：从边长 1 逐层推到边长 block。
    // 边长 2^t 的三角形用 6 个边长 2^(t-1) 的块盖住：三个在角上（偏移 half），
    // 三个往中间挪（偏移 quarter），把中间那块倒三角空隙补上。
    // pre / cur 是 f 的两层下标；算完 swap 一下，刚写完的一层就变成下一轮的读表。
    int pre = 0;
    int cur = 1;
    for (int t = 1; t <= lg; t++) {
        int half = 1 << (t - 1);                     // 这一层的块边长
        int quarter = (t >= 2) ? (1 << (t - 2)) : 0;  // 补块偏移；t = 1 时没有补块
        for (int i = 1; i + (1 << t) - 1 <= n; i++) {
            for (int j = 1; j <= i; j++) {
                int best = f[pre][i][j];
                best = max(best, f[pre][i + half][j]);
                best = max(best, f[pre][i + half][j + half]);
                if (t > 1) {
                    best = max(best, f[pre][i + half][j + quarter]);
                    best = max(best, f[pre][i + quarter][j]);
                    best = max(best, f[pre][i + quarter][j + quarter]);
                }
                f[cur][i][j] = best;
            }
        }
        swap(pre, cur);
    }

    // 查询：边长 k 的三角形同样用 6 个边长 block 的块盖住。
    // 位置还是构建时那套模板，只把偏移 half 换成 k - block、quarter 换成 cha。
    ll answer = 0;
    for (int i = 1; i + k - 1 <= n; i++) {
        int bottom = i + k - 1;
        for (int j = 1; j <= i; j++) {
            int right = j + k - 1;
            int best = f[pre][i][j];
            best = max(best, f[pre][bottom - block + 1][j]);
            best = max(best, f[pre][bottom - block + 1][right - block + 1]);
            if (lg >= 1) {
                int cha = (k - block) / 2;
                best = max(best, f[pre][bottom - block + 1][j + cha]);
                best = max(best, f[pre][i + cha][j]);
                best = max(best, f[pre][i + cha][j + cha]);
            }
            answer += best;
        }
    }

    cout << answer << '\n';
    return 0;
}
