---
oj: "luogu"
problem_id: "P4281"
title: "[AHOI2008] 紧急集合 / 聚会"
date: 2026-01-04 16:59
toc: true
tags: ["lca"]
desc: "三点LCA路径问题"
source: https://www.luogu.com.cn/problem/P4281
---

[[TOC]]

## 三点LCA 问题

> 这个题目本质 就是求 三个点的 最短路径, 转为求 lca 问题, 然后什么具体怎么呢:那个深度最深的 LCA，就是我们要找的最优集合点 $P$。

这是一个非常深刻的图论直觉问题。把这个问题搞懂，你对树形结构的理解会上升一个层次。

### 核心结论

三个点在树上构成的连通子图，形状一定是一个“Y”字形（或者退化成一条链）。

而那个深度最深的 LCA，正是这个 “Y”字形的分叉点（中心点）。

我们分三步来解析为什么是这样。

------

### 第一步：直觉 —— “Y”字形结构

想象树上的三个点 $x, y, z$。

如果我们把它们两两之间的路径画出来，取并集，它们一定会形成一个类似 **“Y”** 的形状（中间有一个交汇点 $P$），或者是 **“I”** 字形（一条线上，$P$ 重合于某个点）。

为什么集合点一定是这个分叉点 $P$？

我们可以用“投票法”或者“物理重心”来理解：

1. 如果在 $P$ 点集合：$x, y, z$ 各自走对应的分支过来。
2. 如果你尝试把集合点从 $P$ 向 $x$ 的方向移动一步到 $P'$：
   - 距离 $x$ 近了 1 步（花费 -1）。
   - 距离 $y$ 远了 1 步（花费 +1）。
   - 距离 $z$ 远了 1 步（花费 +1）。
   - **总花费变化**：$-1 + 1 + 1 = +1$。总路程变长了！
3. 同理，向 $y$ 或 $z$ 移动也会导致总路程变长。
4. 向上（根方向）移动：通常会同时远离三个点（或其中两个），代价更大。

**结论：** 这个“Y”字形的**中心交汇点** $P$，就是全局最优解。

------

### 第二步：LCA 的“二同一异”性质

在有根树中，任意三个点 $x, y, z$ 求两两的 LCA，得到三个点：

- $a = LCA(x, y)$
- $b = LCA(y, z)$
- $c = LCA(x, z)$

这三个点一定满足：有两个点是同一个点（较浅），另一个点是不同的点（较深）。

（或者特例：三个点全都是同一个点）。

场景模拟：

假设树的根在最上面。

- $y$ 和 $z$ 在左边的某个子树里“纠缠”得很深，它们在深处的一个点 $P$ 分叉。
  - 那么 $LCA(y, z) = P$ （深）。
- $x$ 在右边的另一个子树里，或者在很上面的位置。
  - $x$ 要去够到 $y$，必须往上走到很高的“祖宗”节点 $Root'$。所以 $LCA(x, y) = Root'$ （浅）。
  - $x$ 要去够到 $z$，也必须往上走到同一个“祖宗”节点 $Root'$。所以 $LCA(x, z) = Root'$ （浅）。

**结果：**

- $LCA(x, y)$ 和 $LCA(x, z)$ 都是那个高高在上的 $Root'$。
- 只有 $LCA(y, z)$ 是那个深处的 $P$。

------

### 第三步：为什么选“最深”的那个？

结合第一步和第二步：

1. 我们知道最优集合点是 **“Y”字形的中心 $P$**。
2. 在有根树的视角下，这个 $P$ 点其实就是 **把这三个点分开的那个最下面的分叉口**。

我们看刚才的例子：

- **浅点 ($Root'$)**：这是 $x$ 和 $(y, z)$ 分家的地方。如果在 $Root'$ 集合，$x$ 很高兴，但 $y$ 和 $z$ 需要先走到 $P$，再一起爬到 $Root'$。这显然让 $y$ 和 $z$ 多走了冤枉路（从 $P$ 到 $Root'$ 这段路走了两次）。
- **深点 ($P$)**：这是 $y$ 和 $z$ 分家的地方。如果在 $P$ 集合，$y$ 和 $z$ 只要走到 $P$ 就到了。$x$ 虽然要先走到 $Root'$ 再下来走到 $P$，但这是不可避免的。
- **对比**：选 $P$ 比选 $Root'$ 少走了“$y$ 和 $z$ 共同爬升的那段路”。

数学证明：

假设三个 LCA 分别是 $u, u, v$（其中 $depth[u] < depth[v]$）。

- $u$ 是上面那个浅点，$v$ 是下面那个深点。
- $v$ 一定在 $u$ 的子树里。
- 这意味有两个点（比如 $y, z$）在 $v$ 的下面，有一个点（$x$）在 $u$ 的其他分支。
- **如果选 $u$ (浅点)**：代价是 $dist(x, u) + dist(y, u) + dist(z, u)$。
  - 其中 $dist(y, u) = dist(y, v) + dist(v, u)$。
  - 其中 $dist(z, u) = dist(z, v) + dist(v, u)$。
  - 总代价 = $dist(x, u) + dist(y, v) + dist(z, v) + \mathbf{2 \times dist(v, u)}$。
- **如果选 $v$ (深点)**：代价是 $dist(x, v) + dist(y, v) + dist(z, v)$。
  - 其中 $dist(x, v) = dist(x, u) + dist(u, v)$。
  - 总代价 = $dist(x, u) + \mathbf{1 \times dist(u, v)} + dist(y, v) + dist(z, v)$。

**显然：** 选 $v$ (深点) 的代价比选 $u$ 少了 $dist(u, v)$。

所以，**那个深度最大的 LCA，就是所有人的“妥协点”，也就是最优集合点。**


## 1. 题目解析

题目核心：

给定一棵 $N$ 个节点的树，以及 $M$ 次询问。每次询问给出三个点 $x, y, z$，要求在树上找到一个集合点 $P$，使得 $x, y, z$ 到 $P$ 的距离之和最小（即 $dist(x, P) + dist(y, P) + dist(z, P)$ 最小）。输出这个点 $P$ 的编号以及最小距离和。

数学/图论推导：

这就好比三个人在树上要碰头，怎么走最省力？

我们考虑三个点两两之间的 LCA（最近公共祖先）：

1. $a = LCA(x, y)$
2. $b = LCA(y, z)$
3. $c = LCA(x, z)$

重要结论：

在树上的任意三个点 $x, y, z$，求出的这三个 LCA ($a, b, c$) 中，必然有两个是相同的，且另一个的深度比这两个更深（或者三个都相同）。

那个深度最深的 LCA，就是我们要找的最优集合点 $P$。

- **直观理解**：想象三条路径汇聚成一个“Y”字形或者一条线。三条路径的交汇点就是那个“分叉口”。
  - 如果有两条路径先汇合（比如 $x$ 和 $y$ 在深处汇合），然后再去汇合 $z$，那么 $x,y$ 的 LCA 深度最大，它就是集合点。
  - 如果 $x$ 在 $y$ 到 $z$ 的路径上，那么 $x$ 就是集合点。

**算法步骤：**

1. **建树**：使用链式前向星存储。
2. **LCA 预处理**：计算倍增数组 `f[][]` 和深度 `d[]`。
3. **处理查询**：
   - 算出 $a = LCA(x, y)$, $b = LCA(y, z)$, $c = LCA(x, z)$。
   - 比较 `d[a]`, `d[b]`, `d[c]`，取深度最大的那个点作为集合点 $P$。
   - 利用公式计算代价：$Cost = dist(x, P) + dist(y, P) + dist(z, P)$。
   - 其中树上距离公式：$dist(u, v) = d[u] + d[v] - 2 \times d[LCA(u, v)]$。

------

## 2. 代码实现

使用了你的 linkList 和 LCA 模板。

注意：数据范围 $N, M \le 500,000$，必须使用快读/快写（ios::sync_with_stdio(0)）且数组大小要开够。



```cpp
/**
 * Author by Rainboy
 * Problem: P4281 [AHOI2008] 紧急集合 / 聚会
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 500005; 
const int maxe = 1000005; // 双向边
const int MAXLOG = 20;

int n, m;

// === 1. 链式前向星 ===
struct linkList {
    struct edge { int v, next; };
    edge e[maxe];
    int h[maxn], edge_cnt;
    
    linkList(){ reset(); }
    
    void reset() {
        edge_cnt = 0;
        memset(h, -1, sizeof(h));
    }
    
    void add2(int u, int v) {
        e[edge_cnt] = {v, h[u]}; h[u] = edge_cnt++;
        e[edge_cnt] = {u, h[v]}; h[v] = edge_cnt++;
    }

    // 你的语法糖
#ifdef __cpp_range_based_for
    struct AdjIterator {
        int i; linkList* p;
        AdjIterator(linkList* p, int i) : p(p), i(i) {}
        AdjIterator& operator++() { i = p->e[i].next; return *this; }
        bool operator!=(const AdjIterator& oth) { return i != oth.i; }
        int operator*() { return p->e[i].v; }
    };
    struct BaseRange {
        int start; linkList* p;
        BaseRange(linkList* p, int start) : p(p), start(start) {}
        AdjIterator begin() { return AdjIterator(p, p->h[start]); }
        AdjIterator end()   { return AdjIterator(p, -1); }
    };
    BaseRange adj(int u) { return BaseRange(this, u); }
#endif
} e;

// === 2. LCA 模板 ===
struct LCA {
    int f[maxn][MAXLOG + 1];
    int d[maxn];

    void init(int n, int root){
        dfs(root, 0, 1);
        // 黑洞优化
        for (int j = 1; j <= MAXLOG; ++j) {
            for (int i = 1; i <= n; ++i) {
                f[i][j] = f[ f[i][j-1] ][ j-1 ];
            }
        }
    }

    void dfs(int u, int fa, int depth) {
        d[u] = depth;
        f[u][0] = fa; 
        
        for (int v : e.adj(u)) {
            if (v != fa) {
                dfs(v, u, depth + 1);
            }
        }
    }

    int ask(int u, int v) {
        if (d[u] < d[v]) swap(u, v);
        for (int i = MAXLOG; i >= 0; --i) {
            if (d[u] - (1 << i) >= d[v]) u = f[u][i];
        }
        if (u == v) return u;
        for (int i = MAXLOG; i >= 0; --i) {
            if (f[u][i] != f[v][i]) {
                u = f[u][i];
                v = f[v][i];
            }
        }
        return f[u][0];
    }

    // 辅助函数：求两点间距离
    int get_dist(int u, int v) {
        return d[u] + d[v] - 2 * d[ask(u, v)];
    }

} lca;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> n >> m;
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        e.add2(u, v);
    }
    
    lca.init(n, 1);
    
    for(int i = 1; i <= m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        
        // 1. 求出三个两两组合的 LCA
        int lca_xy = lca.ask(x, y);
        int lca_yz = lca.ask(y, z);
        int lca_xz = lca.ask(x, z);
        
        // 2. 结论：集合点 P 是这三个 LCA 中深度最大的那个
        int P = lca_xy;
        if(lca.d[lca_yz] > lca.d[P]) P = lca_yz;
        if(lca.d[lca_xz] > lca.d[P]) P = lca_xz;
        
        // 3. 计算总花费
        int cost = lca.get_dist(x, P) + lca.get_dist(y, P) + lca.get_dist(z, P);
        
        cout << P << " " << cost << "\n";
    }
    
    return 0;
}
```
