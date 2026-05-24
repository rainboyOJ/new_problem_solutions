---
oj: "HDU"
problem_id: "1116"
title: "Play on Words"
date: 2026-01-07 20:03
toc: true
tags: ["欧拉路"]
desc: "有向图的欧拉路径（Eulerian Path）存在性判定"
source: https://vjudge.net/problem/HDU-1116#author=201830221033
---

[[TOC]]

## 题目解析

> 有向图的欧拉路径（Eulerian Path）存在性判定

这个问题实际上是一个经典的图论问题。我们可以将问题进行如下建模：

1. **节点 (Nodes)**: 将26个小写英文字母 ('a' 到 'z') 看作图中的节点。
2. **有向边 (Directed Edges)**: 每一个单词看作一条有向边。单词的首字母是边的起点，尾字母是边的终点。例如，单词 "acm" 可以看作一条从节点 'a' 指向节点 'm' 的有向边。

问题的目标:

题目要求我们判断是否能将所有给定的单词（边）按顺序排列，使得前一个单词的尾字母等于后一个单词的首字母，并且所有单词都必须恰好被使用一次。

转化到图论语言，这就是要求我们在构建的有向图中找到一条路径，这条路径**恰好经过图中所有的边一次**。这就是著名的 **欧拉路径 (Eulerian Path)** 问题。如果这条路径的起点和终点是同一个节点，则称为 **欧拉回路 (Eulerian Circuit)**。

### 欧拉路径存在的充分必要条件（有向图）

对于一个有向图，存在欧拉路径的条件有两个：

条件 1：连通性 (Connectivity)

忽略边的方向后，图中所有度数不为0的节点必须属于同一个连通分量。简单来说，就是所有出现过的字母必须能“串”在一起，不能出现几个单词自成一派，和别的单词完全搭不上边的情况。

例如：单词组 {"ab", "bc"} 和 {"xy", "yz"}。虽然它们内部可以连接，但这两组之间无法连接，所以不行。

条件 2：度数限制 (Degree Constraints)

我们需要统计每个节点（字母）的入度 (In-degree) 和 出度 (Out-degree)。

- 入度：有多少个单词以该字母结尾。
- 出度：有多少个单词以该字母开头。

有向图存在欧拉路径，当且仅当满足以下两种情况之一：

1. **欧拉回路情况**：所有节点的入度等于出度。
2. **欧拉路径情况**：
   - 恰好有一个节点，其 出度 = 入度 + 1 (这个点是路径起点)。
   - 恰好有一个节点，其 入度 = 出度 + 1 (这个点是路径终点)。
   - 其余所有节点的 入度 = 出度。

如果在这两种情况之外（例如，某个点的入度和出度差值大于1，或者有多个起点的特征），则不存在欧拉路径。

------

### 算法实现步骤

我们可以使用以下步骤来解决这个问题：

1. **数据结构准备**:
   - `in[26]` 和 `out[26]` 数组：分别存储 'a'-'z' 的入度和出度。
   - `present[26]` 布尔数组：标记哪些字母在单词中出现过。
   - **并查集 (Disjoint Set Union, DSU)**：用于高效判断图的连通性。我们需要一个 `parent[26]` 数组。
2. **处理输入**:
   - 对于每组数据的 $N$ 个单词，进行遍历。
   - 对于每个单词，找到其首字母 `u` 和尾字母 `v`。
   - 更新度数：`out[u]++`, `in[v]++`。
   - 标记出现：`present[u] = true`, `present[v] = true`。
   - 维护连通性：在并查集中合并 `u` 和 `v` 所在的集合 (`union(u, v)`)。
3. **验证条件**:
   - **验证连通性**: 遍历 `present` 数组。统计对于所有出现过的字母，它们在并查集中是否都有同一个根节点（即属于同一个集合）。如果出现过的字母分属不同的集合，则不连通，输出不可行。
   - **验证度数**: 遍历 26 个字母。
     - 统计满足 `out[i] == in[i] + 1` 的节点数，记为 `start_nodes`。
     - 统计满足 `in[i] == out[i] + 1` 的节点数，记为 `end_nodes`。
     - 如果发现任何节点 `abs(out[i] - in[i]) > 1`，则直接输出不可行。
   - 最后判断：如果 `(start_nodes == 1 && end_nodes == 1)` 或者 `(start_nodes == 0 && end_nodes == 0)`，则输出可行，否则不可行。

###  代码实现



```cpp
/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * Problem: 三小只探险/密码门 (欧拉路径存在性判定)
 * Analysis: 这个题目是 P1127 的简化版。
 * 我们只需要判定有向图中是否存在欧拉路径，不需要输出路径，也不需要字典序最小。
 * 因此，我们只需要进行度数检查和连通性检查，不需要 DFS 和排序。
 * 由于是多组测试数据，需要注意每次初始化全局变量。
 */
#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
#include <string>
#include <vector>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 30; // 最多26个字母

// 全局变量，用于存储图的状态
int n;
// out[i]: 字母 i 的出度
int out[maxn];
// in[i]: 字母 i 的入度
int in[maxn];
// exist[i]: 标记字母 i 是否在输入的单词中出现过
bool exist[maxn]; 

// 注意：本题不需要存储具体的边和路径，所以去掉了 adj 和 ans

// === 并查集 (用于判断图的弱连通性) ===
// 保持原有的并查集实现不变
int fa[maxn]; // 并查集父节点数组

// 查找元素 x 所在集合的代表元素（根节点），带路径压缩
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

// 合并 u 和 v 所在的两个集合
void dsu_merge(int u, int v) {
    int fu = find(u);
    int fv = find(v);
    if (fu != fv) {
        fa[fu] = fv; // 将 u 的根指向 v 的根
    }
}
// === 并查集结束 ===

// 多组数据初始化函数：重置所有状态数组
void reset(){
    for(int i = 0; i <= 26; ++i) {
        fa[i] = i;      // 重置并查集
        out[i] = 0;     // 重置出度
        in[i] = 0;      // 重置入度
        exist[i] = 0;   // 重置存在标记
    }
}

// 处理单组数据的函数
void solve() {
    reset(); // 每次开始前清空状态
    cin >> n;
    
    // 特判 n=0 的情况（虽然题目说 n>=1，但防御性编程是个好习惯）
    if (n == 0) {
        cout << "Ordering is possible.\n";
        return;
    }

    for(int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        int u = s.front() - 'a'; // 首字母
        int v = s.back() - 'a';  // 尾字母

        // 标记首尾字母已存在
        exist[u] = 1;
        exist[v] = 1;
        
        // 更新出度及入度
        out[u]++;
        in[v]++;

        // 在并查集中合并首尾字母所在的集合，维护弱连通性
        dsu_merge(u, v);
    }

    // --- 1. 度数检查 ---
    int cnt_start = 0;   // 统计符合起点度数条件 (out = in + 1) 的节点个数
    int cnt_end = 0;     // 统计符合终点度数条件 (in = out + 1) 的节点个数
    
    for(int i = 0; i < 26; ++i) {
        if (!exist[i]) continue; // 跳过未出现的字母
        
        // 如果任意节点的入度和出度差绝对值大于1，一定不存在欧拉路径
        if (abs(out[i] - in[i]) > 1) {
            cout << "The door cannot be opened.\n";
            return;
        }

        if (out[i] == in[i] + 1) {
            cnt_start++;
        }
        else if (in[i] == out[i] + 1) {
            cnt_end++;
        }
        // else if (out[i] == in[i]) { 继续循环 }
    }

    // 判定度数条件是否满足欧拉路径或欧拉回路的定义
    // 欧拉路径: 1个起点, 1个终点; 欧拉回路: 0个起点, 0个终点
    bool degree_ok  = (cnt_start == 1 && cnt_end == 1 ) || (cnt_start == 0 && cnt_end == 0);
    if (!degree_ok) {
        cout << "The door cannot be opened.\n";
        return;
    }

    // --- 2. 连通性检查 ---
    // 找到第一个存在的字母作为基准点
    int start_node = -1;
    for(int i = 0; i < 26; ++i) {
        if (exist[i]) {
            start_node = i;
            break;
        }
    }

    // 如果 n > 0，start_node 一定能找到。
    int root = find(start_node); // 获取基准点的集合代表元素
    for(int i = 0; i < 26; ++i) {
        // 如果某个存在的点与基准点不在同一个集合，说明图不连通
        if (exist[i] && find(i) != root) {
            cout << "The door cannot be opened.\n";
            return;
        }
    }

    // 如果度数和连通性都满足
    cout << "Ordering is possible.\n";
}

signed main () {
    // 关闭同步流，加速输入输出
    ios::sync_with_stdio(false); cin.tie(0);
    
    int t;
    cin >> t; // 读取测试数据组数
    while(t--) {
        solve();
    }
    
    return 0;
}
```

### 样例分析

Sample 1:

2

acm (a -> m)

ibm (i -> m)

- 度数: 'a' (out 1), 'i' (out 1), 'm' (in 2).
- 分析: 'm' 的入度比出度大 2，不满足任一度数条件。
- 输出: The door cannot be opened.

Sample 2:

3

acm (a -> m)

malform (m -> m)

mouse (m -> e)

- 连通性: a-m 相连，m-m 相连，m-e 相连。所有出现字母 a,m,e 在一个连通块内。
- 度数:
  - 'a': out 1, in 0 (起点特征)
  - 'm': out 2, in 2 (平衡)
  - 'e': out 0, in 1 (终点特征)
- 分析: 1个起点，1个终点，其余平衡。满足欧拉路径条件。
- 输出: Ordering is possible.

Sample 3:

2

ok (o -> k)

ok (o -> k)

- 连通性: o-k 相连。
- 度数:
  - 'o': out 2, in 0
  - 'k': out 0, in 2
- 分析: 'o' 出度比入度大2，'k' 入度比出度大2。不满足条件。
- 输出: The door cannot be opened.
