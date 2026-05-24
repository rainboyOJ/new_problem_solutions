---
oj: "luogu"
problem_id: "P2872"
title: "[USACO07DEC] Building Roads S"
date: 2026-01-03 09:56
toc: true
tags: ["最小生成树"]
desc: "最小生成树必选边问题"
source: https://www.luogu.com.cn/problem/P2872
---

[[TOC]]

这是一个非常经典的 **“必选边 + 最小生成树”** 模型。

## 题目解析

1. 题目本质

你需要连接所有的点，使总长度最小。这就是标准的 最小生成树 (MST) 问题。

**2. 题目特殊点**

- **坐标系**：边的权重不是直接给出的，而是两点之间的欧几里得距离 $\sqrt{(x_1-x_2)^2 + (y_1-y_2)^2}$。
- **已存在的边**：题目给出了 $M$ 条已经连接的边。这些边的“建设成本”为 **0**。
- 解决方案思路

我们可以把这个问题看作：在一个完全图（任意两点间都有边）中求 MST。

- **对于已存在的边**：直接在并查集（DSU）中将它们合并（Merge）。这相当于我们优先选择了权值为 0 的边。
- **对于其他可能的边**：因为 $N$ 只有 1000，我们可以枚举**所有**两点之间的组合 $(i, j)$，计算距离作为边权，加入到待选边集中。
- **Kruskal 流程**：
  1. 初始化并查集。
  2. 读入 $M$ 条现有边，直接合并这些点。
  3. 生成 $N$ 个点之间所有可能的连线（共 $\frac{N(N-1)}{2}$ 条），计算距离。
  4. 对这些生成的边按距离排序。
  5. 运行 Kruskal：如果某条边的两个端点还未连通，就选这条边，累加距离。

**4. 复杂度分析**

- 点数 $N=1000$。
- 生成的边数 $E \approx N^2/2 \approx 500,000$。
- 排序复杂度 $O(E \log E)$，大约 $10^7$ 次操作，对于 C++ 来说 1秒内绰绰有余。

## 处理 必选边 问题 



这是最直观的方法。既然这些边是“必选”的，那我们在开始计算 MST 之前，先把它们连上不就完了吗？

**核心逻辑：**

1. **初始化** 并查集 (DSU)。
2. **处理必选边**：遍历所有必选边 $(u, v)$，直接调用 `dsu.merge(u, v)`。
   - 如果题目要求计算总权值，记得把这些必选边的权值先加到 `ans` 里。
   - *注意*：如果必选边内部构成了环，通常题目通过 `merge` 返回 `false` 可以检测到，但大多数题目保证必选边不构成环，或者允许冗余连接。
3. **处理可选边**：将剩余的所有边按权值排序。
4. **跑 Kruskal**：像往常一样遍历排序后的可选边，如果 `dsu.merge(u, v)` 成功，则加入。

------

## 代码实现


```cpp
/**
 * P2872 [USACO07DEC] Building Roads S
 */
#include <bits/stdc++.h>
#include <numeric> // for std::iota

using namespace std;

// 坐标结构体
struct Point {
    int x, y;
};

// 距离计算函数
double get_dist(const Point& a, const Point& b) {
    // 使用 hypot 函数可以直接求 sqrt(dx^2 + dy^2)，防止中间过程溢出且写起来简单
    // 或者手动写: sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2))
    return std::hypot(a.x - b.x, a.y - b.y);
}

// 这里的 Edge 需要适配 double 类型的权重
struct Edge {
    int u, v;
    double w; // 权值改为 double
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct KruskalAlgorithm {
    struct DSU {
        std::vector<int> fa;
        void init(int n) {
            fa.resize(n + 1);
            std::iota(fa.begin(), fa.end(), 0);
        }
        int find(int x) {
            return x == fa[x] ? x : fa[x] = find(fa[x]);
        }
        bool merge(int x, int y) {
            int fx = find(x), fy = find(y);
            if (fx == fy) return false;
            fa[fx] = fy;
            return true;
        }
    } dsu;

    int n;
    std::vector<Edge> edges;

    void init(int _n) {
        n = _n;
        edges.clear();
        dsu.init(n);
    }

    void add_edge(int u, int v, double w) {
        edges.push_back({u, v, w});
    }

    // 预先合并已经存在的边（相当于权值为0）
    void merge_existing(int u, int v) {
        dsu.merge(u, v);
    }

    // 返回最小生成树需要的额外长度
    double solve() {
        std::sort(edges.begin(), edges.end());
        
        double ans = 0;
        int cnt = 0; // 这里的 cnt 不太好直接用来判断退出，因为有一些边是预先合并的
                     // 但我们可以依靠遍历完所有边或者增加一个连通块计数器来优化
                     // 这里为了代码简单，直接遍历所有边即可

        for (const auto& e : edges) {
            if (dsu.merge(e.u, e.v)) {
                ans += e.w;
            }
        }
        
        return ans;
    }
} kruskal;

Point points[1005]; // 存储点坐标

int main() {
    // 优化 IO
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    kruskal.init(n);

    // 1. 读入坐标
    for (int i = 1; i <= n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    // 2. 处理已有的路 (直接在并查集中合并，不需要加入边列表参与排序)
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        kruskal.merge_existing(u, v);
    }

    // 3. 生成所有可能的边 (完全图)
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double w = get_dist(points[i], points[j]);
            kruskal.add_edge(i, j, w);
        }
    }

    // 4. 计算结果
    double result = kruskal.solve();

    // 5. 输出，保留两位小数
    cout << fixed << setprecision(2) << result << endl;

    return 0;
}
```

## 关键点解释

1. **`merge_existing` 函数**：
   - 在模板里加了一个小函数。对于题目输入的 $M$ 条边，我们不需要把它们当成权值为 0 的边加入 `edges` 数组再去排序。直接调用 `dsu.merge(u, v)` 效率更高，逻辑也更清晰（表示这两点物理上已经通了）。
2. **生成所有边**：
   - 代码中的双重循环 `for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++)` 负责构建完全图。因为 $N \le 1000$，$N^2$ 只有 $10^6$，内存和时间都完全够用。
3. **`std::hypot`**：
   - `<cmath>` 库里的函数，`hypot(x, y)` 等价于 $\sqrt{x^2+y^2}$。它会自动处理可能发生的中间值溢出问题（虽然本题数据范围较小不太会溢出），是计算几何距离的好习惯。
4. **数据类型**：
   - 输出要求实数，所以权值 `w` 和答案 `ans` 必须是 `double`。不要习惯性地用 `long long`。****
