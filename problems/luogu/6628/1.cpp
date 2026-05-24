/**
 * [题解] P6628 丁香之路
 * 基于严谨的“奇偶性修正 -> 连通性修正”两步法
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 2505;

// MST 的边结构体
struct Edge {
    int u, v, w;
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

int n, m, s;
int deg[MAXN];       // 初始度数
int fa[MAXN];        // 并查集数组
int block_id[MAXN];  // 记录只包含必经边的初始连通块ID
ll base_weight = 0;  // 必经边的基础权值和

// 并查集查找
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

// 并查集合并
void unite(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) fa[fx] = fy;
}

void init() {
    cin >> n >> m >> s;
    for (int i = 1; i <= n; ++i) fa[i] = i;

    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        base_weight += abs(u - v);
        deg[u]++;
        deg[v]++;
        unite(u, v); // 初始必经边合并
    }

    // 保存初始的连通状态，避免每次循环都重新跑m条边的合并
    for (int i = 1; i <= n; ++i) {
        block_id[i] = find(i);
    }
}

void solve() {
    // 枚举每一个点作为终点 i
    for (int i = 1; i <= n; ++i) {
        // --- 0. 状态重置 ---
        // 每次计算基于 block_id 重建并查集
        for (int k = 1; k <= n; ++k) fa[k] = k; // 这里 fa 维护的是 block_id 之间的关系
        
        // 复制一份度数，避免修改原数组
        vector<int> cur_deg(n + 1);
        for(int k=1; k<=n; ++k) cur_deg[k] = deg[k];
        
        // 虚拟增加起点和终点度数
        cur_deg[s]++;
        cur_deg[i]++;

        // 初始时，起点s和终点i所在的块必须视为已有了某种关系（虽不一定连通，但在逻辑上纳入考量）
        // 实际上这一步在下面的奇偶修正或MST中会自动处理，但为了逻辑严密，
        // 我们先把 s 和 i 所在的初始块标记为“通过路径连接”
        // 这里不需要显式 unite，因为后面连通性检查会覆盖。

        ll current_ans = base_weight;

        // --- 1. 奇偶性修正 (Parity Fix) ---
        // 找出所有奇数度的点
        vector<int> odds;
        for (int k = 1; k <= n; ++k) {
            if (cur_deg[k] % 2 != 0) odds.push_back(k);
        }

        // 相邻配对
        for (size_t k = 0; k < odds.size(); k += 2) {
            int u = odds[k];
            int v = odds[k+1];
            current_ans += (v - u); // 加上距离花费

            // 【关键】：连接 u, v 意味着区间 [u, v] 内所有的连通块都被串联了
            // 我们遍历 u 到 v 之间的所有点，把它们所在的初始块(block_id)都合并起来
            int root_u = find(block_id[u]);
            for (int x = u + 1; x <= v; ++x) {
                int root_x = find(block_id[x]);
                if (root_u != root_x) {
                    fa[root_x] = root_u; // 合并
                }
            }
        }

        // --- 2. 连通性修正 (MST) ---
        // 经过上面的操作，可能还有若干个大的连通块是断开的
        // 我们需要用 Kruskal 把它们连起来，边的代价是 2 * dist
        
        vector<Edge> edges;
        int pre = 0; // 上一个“有度数的点”或“被涉及到的点”

        for (int k = 1; k <= n; ++k) {
            // 如果点 k 有度数（必经边涉及点 或 s 或 i），或者它在奇偶修正中被连上了
            // 判断方法：只要 cur_deg > 0 或者它被包含在某个连通分量里
            // 更简单的判断：我们只关心那些“有初始度数”的点形成的块之间的连接
            // 因为奇偶修正已经把中间空的都连上了。
            
            // 严谨判断：我们需要连接的是所有“非空”的连通块。
            // 只要 cur_deg[k] > 0，它就是一个关键点。
            if (cur_deg[k] > 0) {
                if (pre != 0) {
                    int root_k = find(block_id[k]);
                    int root_pre = find(block_id[pre]);
                    if (root_k != root_pre) {
                        // 相邻两个关键点所在块不同，添加候选边
                        // 权值为距离，但在 MST 中实际代价是 2 * 距离
                        edges.push_back({root_k, root_pre, abs(k - pre)});
                    }
                }
                pre = k;
            }
        }

        sort(edges.begin(), edges.end());

        for (auto &e : edges) {
            int fu = find(e.u); // e.u 已经是 block_id 的 root 了，但为了保险再 find 一次
            int fv = find(e.v);
            if (fu != fv) {
                fa[fu] = fv;
                current_ans += (ll)e.w * 2; // 必须走往返，所以 * 2
            }
        }

        cout << current_ans << (i == n ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    solve();
    return 0;
}
