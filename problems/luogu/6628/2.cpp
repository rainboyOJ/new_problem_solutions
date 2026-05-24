/**
 * Author by Rainboy
 * Problem: P6628 [省选联考 2020 B 卷] 丁香之路
 * Analysis: Eulerian Path + Greedy Parity Matching + MST
 * Reference: Logic based on solution by 木xx木大
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 2505;

struct Edge {
    int u, v, w;
    // 重载小于号用于排序
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

int n, m, s;
int du[maxn];       // 记录度数
int fa[maxn];       // 并查集数组 (用于 MST)
int bel[maxn];      // 记录初始必经边形成的连通块 ID
ll base_sum = 0;    // 必经边的总长度

// 并查集查找
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void init() {
    scanf("%d%d%d", &n, &m, &s);
    
    // 初始化并查集
    for(int i = 1; i <= n; i++) fa[i] = i;

    // 读入必经边
    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        du[u]++;
        du[v]++;
        base_sum += abs(u - v);
        // 合并必经边连接的点
        fa[find(u)] = find(v);
    }

    // 记录初始的连通块状态到 bel 数组
    // 之后每次计算 query 时，我们基于 bel 来做，而不是重置整个图
    for(int i = 1; i <= n; i++) bel[i] = find(i);
}

void solve() {
    // 枚举每一个可能的终点 i
    for(int i = 1; i <= n; i++) {
        // 重置并查集状态：现在的元素是“连通块ID”，即 1..n
        for(int j = 1; j <= n; j++) fa[j] = j;
        
        // 临时增加起点和终点的度数（模拟路径的起止）
        du[s]++;
        du[i]++;
        
        // 初始连通性：起点 S 和终点 i 所在的初始连通块必须视为已连接（虽然是虚拟的）
        // 注意：这里操作的是 bel[s] 和 bel[i]，因为 fa 维护的是连通块之间的关系
        fa[find(bel[s])] = find(bel[i]);

        ll current_ans = base_sum;
        int pre = 0; // 记录上一个奇度点的位置

        // --- 步骤 1: 贪心修正奇偶性 ---
        for(int j = 1; j <= n; j++) {
            // 如果度数是奇数
            if (du[j] & 1) {
                if (pre) {
                    // 找到了一对奇点 (pre, j)，将它们连接
                    current_ans += (j - pre);
                    
                    // 关键：连接 (pre, j) 意味着区间 [pre, j] 之间的所有连通块都被串起来了
                    // 我们将区间内所有点所属的连通块合并
                    for(int k = pre; k < j; k++) {
                        fa[find(bel[k])] = find(bel[j]);
                    }
                    pre = 0; // 配对完成，清空 pre
                } else {
                    pre = j; // 记录第一个奇点，等待下一个
                }
            }
        }

        // --- 步骤 2: MST 修正连通性 ---
        vector<Edge> edges;
        pre = 0; // 这里 pre 含义变为“上一个有度数的点”

        for(int j = 1; j <= n; j++) {
            // 只考虑有度数的点（即涉及到的点）
            if (du[j]) {
                if (pre) {
                    // 如果当前点 j 所在的连通块 和 上一个点 pre 所在的连通块 不连通
                    // 则这两个连通块是 MST 的候选连接对象
                    // 候选边权是 abs(j - pre)
                    if (find(bel[j]) != find(bel[pre])) {
                        edges.push_back({bel[j], bel[pre], abs(j - pre)});
                    }
                }
                pre = j;
            }
        }

        // Kruskal 算法
        sort(edges.begin(), edges.end());
        for(auto &e : edges) {
            int fu = find(e.u);
            int fv = find(e.v);
            if (fu != fv) {
                fa[fu] = fv;
                // 连通性修正的边需要走往返，所以代价 * 2
                current_ans += e.w * 2;
            }
        }

        // 恢复度数，以便下一次循环使用
        du[s]--;
        du[i]--;

        printf("%lld ", current_ans);
    }
}

int main() {
    init();
    solve();
    return 0;
}
