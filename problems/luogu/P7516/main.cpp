/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-24 00:03
 * update_at: 2026-10-24 00:04
 */
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 1005;
const int MAXM = 200005;

// 全局变量与数组
int n, m;

// f[u][v] 表示在原图中，从 u 到 v 且所有中间点编号均严格大于 min(u, v) 的路径中，
// 路径上最小边编号（瓶颈）的最大值。
// 若不存在这样的路径，则 f[u][v] = 0。
int f[MAXN][MAXN];

// ans_cnt[w] 记录使某对点产生贡献的瓶颈边权 w 的频数
// 用于差分与后缀和，最终 ans_cnt[k + 1] 即为 h(G_k) 的答案
int ans_cnt[MAXM];

int main() {
    // 优化输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    // 读入 m 条有向边，边的输入顺序即为边的编号 1..m
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        f[u][v] = i; // 若有重边，后输入的边编号更大，直接覆盖即可
    }

    // 倒序 Floyd 动态规划：外层枚举中转点 k 从 n 到 1
    // 状态转移限制：中转点 k 必须满足 k > min(i, j)
    for (int k = n; k >= 1; --k) {
        int *fk = f[k];

        // 第一类情况：i < k，此时必然有 min(i, j) <= i < k，故对所有 j (1 <= j <= n) 均可转移
        for (int i = 1; i < k; ++i) {
            int fik = f[i][k];
            if (!fik) continue;
            int *fi = f[i];
            for (int j = 1; j <= n; ++j) {
                int fkj = fk[j];
                if (!fkj) continue;
                int val = min(fik, fkj);
                if (val > fi[j]) {
                    fi[j] = val;
                }
            }
        }

        // 第二类情况：i > k，此时必须满足 j < k 才能保证 min(i, j) = j < k
        for (int i = k + 1; i <= n; ++i) {
            int fik = f[i][k];
            if (!fik) continue;
            int *fi = f[i];
            for (int j = 1; j < k; ++j) {
                int fkj = fk[j];
                if (!fkj) continue;
                int val = min(fik, fkj);
                if (val > fi[j]) {
                    fi[j] = val;
                }
            }
        }
    }

    // 统计每对点 (u, v) (1 <= u <= v <= n) 产生贡献的有效边权区间
    for (int u = 1; u <= n; ++u) {
        // 当 u == v 时，自身到自身在任何子图中均连通，在所有 m+1 张图中均存在
        ans_cnt[m + 1]++;

        // 当 u < v 时，中间点必须全部 > u，瓶颈为 min(f[u][v], f[v][u])
        for (int v = u + 1; v <= n; ++v) {
            int w = min(f[u][v], f[v][u]);
            if (w > 0) {
                // 边权最小值 >= w 的子图 G_0..G_{w-1} 中该点对均存在
                // 对应下标 0..w-1，差分打标在 w 处
                ans_cnt[w]++;
            }
        }
    }

    // 计算后缀和，还原出每张子图的答案
    for (int i = m; i >= 1; --i) {
        ans_cnt[i] += ans_cnt[i + 1];
    }

    // 输出 G_0, G_1, ..., G_m 的答案 h(G_k) = ans_cnt[k + 1]
    for (int k = 0; k <= m; ++k) {
        cout << ans_cnt[k + 1] << (k == m ? "" : " ");
    }
    cout << "\n";

    return 0;
}
