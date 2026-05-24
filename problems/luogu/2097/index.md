---
oj: "luogu"
problem_id: "P2097"
title: "资料分发 1"
date: 2026-01-01 21:03
toc: true
tags: ["并查集","dfs"]
desc: "图的连通块的数量"
source: https://www.luogu.com.cn/problem/P2097
---

[[TOC]]

这道题 **P2097 资料分发 1** 是非常经典的 **图论基础题**。

## 题目解析

- **题意转化**：
  - 电脑之间有双向连线，意味着这是一个 **无向图**。
  - 只要一台电脑得到数据，整个连通网络里的电脑都能得到。
  - 问题问“至少输入几台电脑”，其实就是问这个图里有几个 **连通块 (Connected Components)**。
  - 我们只需要在每一个连通块里挑出一台电脑输入数据，整个块就都点亮了。
- **算法选择**：
  - 求连通块个数，最常用的两种方法是 **DFS/BFS 遍历** 和 **并查集 (Union-Find / DSU)**。
  - 对于这道题，**并查集** 代码最短、最适合作为模板使用，而且处理 $10^5$ 级别的数据非常快。

------

##  代码


```cpp
#include <iostream>
#include <vector>
#include <numeric> // for iota

using namespace std;

const int N = 100005; // 根据题目 n <= 10^5

// --- 并查集模板开始 ---
struct DSU {
    int fa[N];

    // 初始化：每个人都是自己的父亲
    void init(int n) {
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
    }

    // 查找 + 路径压缩 (Path Compression)
    // 这一步是让并查集变快的核心
    int find(int x) {
        if (x == fa[x]) return x;
        return fa[x] = find(fa[x]); // 递归找根，并把沿途节点的父亲直接设为根
    }

    // 合并 x 和 y 所在的集合
    void merge(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy) {
            fa[fx] = fy; // 把 x 的老大指向 y 的老大
        }
    }
    
    // 查询是否在同一个集合
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};
// --- 并查集模板结束 ---

DSU dsu;
int n, m;

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m)) return 0; // 防止读取错误

    // 1. 初始化并查集
    dsu.init(n);

    // 2. 读入边并合并
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dsu.merge(u, v);
    }

    // 3. 统计连通块数量
    // 方法：遍历所有点，如果一个点的父亲是它自己，说明它是这个集合的根
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dsu.fa[i] == i) {
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}
```

