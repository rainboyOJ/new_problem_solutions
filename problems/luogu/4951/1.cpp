/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-06 09:20:33
 */
#include <bits/stdc++.h>
#include <iomanip>
#include <ios>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 4e6+5;
const int mod = 1e9+7;

int n,m,F;
int a[maxn];

//oisnip_begin最小生成树mst_kruskal.cpp
// 定义边的结构体
struct Edge {
    int u, v;
    long long c;
    long long t;
    double val = 0; // c_i + x * t_i , 排序用
    // 重载 < 运算符，方便 std::sort 直接排序
    bool operator<(const Edge& other) const {
        return val < other.val;
    }
};
std::vector<Edge> edges; // 存储所有边

// Kruskal 算法封装结构体
struct KruskalAlgorithm {
    struct DSU {
        std::vector<int> fa;
        // 初始化并查集
        void init(int n) {
            fa.resize(n + 1);
            std::iota(fa.begin(), fa.end(), 0); // 赋值 0, 1, 2... n
        }
        int find(int x) {
            return x == fa[x] ? x : fa[x] = find(fa[x]); // 路径压缩
        }
        bool merge(int x, int y) {
            int fx = find(x), fy = find(y);
            if (fx == fy) return false; // 已经在同一个集合
            fa[fx] = fy;
            return true;
        }
    } dsu;

    int n; // 点的数量

    // 初始化：清空边，设定点数
    void init(int _n) {
        n = _n;
        edges.clear();
        dsu.init(n);
    }

    // 加边函数：心智负担低，不用操心数组下标
    void add_edge(int u, int v, long long c,ll t) {
        edges.push_back({u, v, c,t});
    }

    // 执行算法
    // 返回值：最小生成树的权值和。如果无法连通，返回 -1
    double solve() {
        // 1. 排序：贪心的基础
        std::sort(edges.begin(), edges.end());
        
        // 2. 重新初始化并查集状态（防止多次调用 solve 出错）
        dsu.init(n);

        double ans = 0; // 权值和，注意开 long long
        int cnt = 0;       // 记录选了多少条边

        for (const auto& e : edges) {
            if (dsu.merge(e.u, e.v)) { // 如果不在同一集合，合并
                ans += e.val;
                cnt++;
                // 如果需要输出选中的边，可以在这里打印
                // cout << e.u << " " << e.v << " " << e.w << endl;
            }
            if (cnt == n - 1) break; // 优化：选够了边就退出
        }

        // 3. 连通性检查：如果选的边数少于 n-1，说明图不连通
        if (cnt < n - 1) return -1;
        
        return ans;
    }
} kruskal;
//oisnip_end

bool check(double x) {
    for( auto & e : edges) {
        e.val = e.c + x * e.t;
    }

    double ans = kruskal.solve();
    return F >= ans;

}

void init(){
    std::cin >> n >> m >> F;
    kruskal.init(n);
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v,c,t;
        std::cin >> u >> v >> c >> t;
        kruskal.add_edge(u,v,c,t);
    }


}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);

    init();
    double l = 0, r = F;

    for(int i = 0 ;i< 100;i++) {
        double mid = (l+r) / 2;
        if( check(mid) )
            l = mid; // 可行
        else
            r = mid;
    }
    std::cout << fixed << setprecision(4) << l << "\n";
    
    return 0;
}
