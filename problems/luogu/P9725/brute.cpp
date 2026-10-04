/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-02 15:23
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：从少到多枚举“要添加的通道集合”，对每个新图用博弈状态搜索判断
//       Pang 能否从任意起点抓住 Shou，第一个可行的加边数就是答案。
#include <bits/stdc++.h>
using namespace std;
const int maxn = 12;

int n;
bool edge[maxn][maxn];          // 当前图的邻接矩阵
int candU[maxn * maxn];         // 可以添加的通道（原图中的非边）
int candV[maxn * maxn];
int candCnt;

int closedMask[maxn];           // 闭邻域：自己 + 所有邻居
int winMask[maxn];              // winMask[b] 的第 p 位为 1 表示：
                                // Shou 在 b、Pang 在 p、轮到 Shou 走时，Pang 能保证抓住

// 迭代求出 Pang 的所有必胜状态（最小不动点）
void buildWinMask() {
    for (int b = 0; b < n; ++b) {
        closedMask[b] = 1 << b;
        for (int c = 0; c < n; ++c) {
            if (edge[b][c]) {
                closedMask[b] |= 1 << c;
            }
        }
    }
    for (int b = 0; b < n; ++b) {
        winMask[b] = 1 << b;    // 两人同格，Shou 已经被抓
    }
    bool changed = true;
    while (changed) {
        changed = false;
        for (int b = 0; b < n; ++b) {
            for (int p = 0; p < n; ++p) {
                if (b == p) continue;
                if ((winMask[b] >> p) & 1) continue;
                // 假设轮到 Shou 走：他所有的走法 b2 都必须被 Pang 回应掉
                bool allCaught = true;
                for (int b2 = 0; b2 < n; ++b2) {
                    if (!((closedMask[b] >> b2) & 1)) continue;   // 不走 b2 这个格子
                    // Pang 在 p 走一步后能否进入必胜状态（或直接踩到 b2）
                    if ((winMask[b2] & closedMask[p]) == 0) {
                        allCaught = false;
                        break;
                    }
                }
                if (allCaught) {
                    winMask[b] |= 1 << p;
                    changed = true;
                }
            }
        }
    }
}

// 所有起点组合下 Pang 都抓不到 Shou，才算合法
bool isGood() {
    for (int b = 0; b < n; ++b) {
        for (int p = 0; p < n; ++p) {
            if (b != p && ((winMask[b] >> p) & 1)) {
                return false;
            }
        }
    }
    return true;
}

// 从 candU/candV 的下标 idx 起再选 need 条边，判断是否存在可行方案
bool dfs(int idx, int need) {
    if (need == 0) {
        buildWinMask();
        return isGood();
    }
    if (candCnt - idx < need) {
        return false;
    }
    for (int i = idx; i < candCnt; ++i) {
        int u = candU[i], v = candV[i];
        edge[u][v] = true;
        edge[v][u] = true;
        bool ok = dfs(i + 1, need - 1);
        edge[u][v] = false;
        edge[v][u] = false;
        if (ok) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                edge[i][j] = false;
            }
        }
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            edge[u][v] = true;
            edge[v][u] = true;
        }

        candCnt = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (!edge[i][j]) {
                    candU[candCnt] = i;
                    candV[candCnt] = j;
                    candCnt++;
                }
            }
        }

        int ans = -1;
        for (int k = 0; k <= candCnt; ++k) {
            if (dfs(0, k)) {
                ans = k;
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
