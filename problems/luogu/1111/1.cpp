#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // 用于 std::iota

using namespace std;

// 定义边的结构体
struct Edge {
    int u, v;
    long long w; // 这里的 w 代表修路所需时间 t
    // 重载 < 运算符，方便 std::sort 直接排序
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

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
    std::vector<Edge> edges; // 存储所有边

    // 初始化：清空边，设定点数
    void init(int _n) {
        n = _n;
        edges.clear();
        dsu.init(n);
    }

    // 加边函数
    void add_edge(int u, int v, long long w) {
        edges.push_back({u, v, w});
    }

    // 执行算法
    // 修改点：本题需要返回“最早通车时间”，即连通时当前边的权值
    long long solve() {
        // 1. 排序：按时间从小到大
        std::sort(edges.begin(), edges.end());
        
        // 2. 重新初始化并查集
        dsu.init(n);

        long long max_time = 0; // 记录完成最后一条路的时间
        int cnt = 0;            // 记录选了多少条边

        for (const auto& e : edges) {
            if (dsu.merge(e.u, e.v)) { // 如果不在同一集合，合并
                max_time = e.w; // 更新时间（因为是排序过的，后加入的肯定时间更晚）
                cnt++;
            }
            // 优化：一旦连接了 N-1 条边，说明所有村庄已连通
            if (cnt == n - 1) return max_time; 
        }

        // 3. 连通性检查：如果选的边数少于 n-1，说明图不连通
        return -1;
    }
} kruskal;

int main() {
    // 优化输入输出
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    if (cin >> N >> M) {
        kruskal.init(N);

        for (int i = 0; i < M; i++) {
            int x, y, t;
            cin >> x >> y >> t;
            kruskal.add_edge(x, y, t);
        }

        // 特判：如果只有1个村庄，不需要修路，时间为0
        // 虽然题目 N >= 1，但这是一个常见的边界情况
        if (N == 1) {
            cout << 0 << endl;
        } else {
            cout << kruskal.solve() << endl;
        }
    }

    return 0;
}
