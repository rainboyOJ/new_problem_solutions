/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:34
 * update_at: 2026-10-06 14:34
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

typedef long long ll;

ll n;             // 节点数
ll root;          // 根节点编号
ll weight[MAXN];  // weight[i]：点 i 的权值 A[i]
ll father[MAXN];  // father[i]：点 i 的父节点，根节点保持为 0

// 并查集数组，只有块根 x 满足 belong[x] == x
ll belong[MAXN];
// up[x]：点 x 的父节点所在块的块根；up[root] = root 表示根块没有父块
ll up[MAXN];
ll block_size[MAXN];   // block_size[x]：块根 x 这一块的节点数
ll block_total[MAXN];  // block_total[x]：块根 x 这一块的权值和

// 返回 x 所在染色块的块根，并顺路做路径压缩
ll find_block(ll x) {
    while (belong[x] != x) {
        belong[x] = belong[belong[x]];
        x = belong[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> root;

    // 每个点自己那一轮先把 A[i] 记一次
    ll cost = 0;
    for (ll i = 1; i <= n; i++) {
        cin >> weight[i];
        cost += weight[i];
    }

    for (ll i = 1; i <= n - 1; i++) {
        ll a, b;
        cin >> a >> b;
        father[b] = a;  // 题目保证 a 是 b 的父节点
    }

    // 初始化：每个点自成一个块
    for (ll i = 1; i <= n; i++) {
        belong[i] = i;
        up[i] = father[i];
        block_size[i] = 1;
        block_total[i] = weight[i];
    }
    up[root] = root;  // 根块之上没有块

    // Horn 贪心：每轮把平均值最大的非根块并入父块，共合并 n-1 轮
    for (ll round = 1; round <= n - 1; round++) {
        ll best = 0;  // 当前平均值最大的非根块
        for (ll i = 1; i <= n; i++) {
            if (belong[i] != i || i == root) {
                continue;
            }
            // 用乘法比较平均值 total/size，避免浮点误差
            if (best == 0 ||
                block_total[i] * block_size[best] > block_total[best] * block_size[i]) {
                best = i;
            }
        }

        ll parent_block = find_block(up[best]);
        // best 块每个点都排在父块每个点之后，为这一批「后来者」各记一次代价
        cost += block_total[best] * block_size[parent_block];

        // 把 best 块整体并入父块
        up[best] = parent_block;
        belong[best] = parent_block;
        block_size[parent_block] += block_size[best];
        block_total[parent_block] += block_total[best];
    }

    cout << cost << "\n";
    return 0;
}
