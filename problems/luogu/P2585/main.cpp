/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:05
 * update_at: 2026-10-23 23:32
 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 500005;

// 二叉树左右子节点编号，0 表示无子节点
int ls[maxn];
int rs[maxn];

// 树上节点总数
int node_cnt = 0;

// dp_max[u][c]: 以 u 为根的子树，u 染颜色 c 时，子树内最多能染出的绿色节点数
// dp_min[u][c]: 以 u 为根的子树，u 染颜色 c 时，子树内最少能染出的绿色节点数
// 颜色定义：0 表示绿色，1 表示红色，2 表示蓝色
int dp_max[maxn][3];
int dp_min[maxn][3];

string s;
int pos_idx = 0;

// 按照先序遍历建树，返回当前子树根节点编号
int build_tree() {
    int u = ++node_cnt;
    char type = s[pos_idx++];
    if (type == '0') {
        ls[u] = 0;
        rs[u] = 0;
    } else if (type == '1') {
        ls[u] = build_tree();
        rs[u] = 0;
    } else if (type == '2') {
        ls[u] = build_tree();
        rs[u] = build_tree();
    }
    return u;
}

// 树形 DP 计算以 u 为根的最值
void dfs(int u) {
    if (u == 0) return;

    int l = ls[u];
    int r = rs[u];

    if (l != 0) dfs(l);
    if (r != 0) dfs(r);

    for (int c = 0; c < 3; ++c) {
        int val = (c == 0 ? 1 : 0);

        if (l == 0 && r == 0) {
            // 叶子节点
            dp_max[u][c] = val;
            dp_min[u][c] = val;
        } else if (r == 0) {
            // 只有一个子节点 l
            int max_sub = 0;
            int min_sub = 1e9;
            for (int cl = 0; cl < 3; ++cl) {
                if (cl == c) continue;
                max_sub = max(max_sub, dp_max[l][cl]);
                min_sub = min(min_sub, dp_min[l][cl]);
            }
            dp_max[u][c] = val + max_sub;
            dp_min[u][c] = val + min_sub;
        } else {
            // 两个子节点 l 和 r
            // 父节点为 c，l 和 r 的颜色必须满足：cl != c, cr != c, cl != cr
            // 剩余两个颜色恰好是 {0, 1, 2} \ {c}，设为 c1, c2
            int c1 = -1, c2 = -1;
            for (int i = 0; i < 3; ++i) {
                if (i != c) {
                    if (c1 == -1) c1 = i;
                    else c2 = i;
                }
            }
            // 方案 1: l 染 c1, r 染 c2
            // 方案 2: l 染 c2, r 染 c1
            int max_sub = max(dp_max[l][c1] + dp_max[r][c2], dp_max[l][c2] + dp_max[r][c1]);
            int min_sub = min(dp_min[l][c1] + dp_min[r][c2], dp_min[l][c2] + dp_min[r][c1]);

            dp_max[u][c] = val + max_sub;
            dp_min[u][c] = val + min_sub;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> s)) return 0;

    int root = build_tree();
    dfs(root);

    int ans_max = max({dp_max[root][0], dp_max[root][1], dp_max[root][2]});
    int ans_min = min({dp_min[root][0], dp_min[root][1], dp_min[root][2]});

    cout << ans_max << " " << ans_min << "\n";

    return 0;
}
