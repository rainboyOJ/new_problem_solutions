---
oj: "OpenJ_Bailian"
problem_id: "1300"
title: "Door Man"
date: 2026-01-08 22:14
toc: true
tags: ["欧拉路"]
desc: "欧拉回路模板题判定"
source: https://vjudge.net/problem/OpenJ_Bailian-1300
---

[[TOC]]

## 题目解析


这是一个非常经典的 **欧拉回路 / 欧拉路径 (Eulerian Path/Circuit)** 判定题目。

## 题目核心解析

**1. 问题模型化**

- **房间**：看作图的 **节点 (Vertex)**。
- **打开的门**：看作图的 **边 (Edge)**。
- **规则翻译**：
  - “穿过门后立即关上” $\rightarrow$ **每条边只能走一次**。
  - “不能打开关闭的门” $\rightarrow$ **不能重复走边**。
  - “关闭所有打开的门” $\rightarrow$ **遍历图中所有的边**。
  - “起点是 M，终点必须是 0” $\rightarrow$ **寻找一条从 M 到 0 的欧拉路径**。
- 判定条件

这是一个 无向图 的欧拉路径判定问题。

- 基本条件（连通性）：

  所有有门的房间（度数 $>0$ 的节点）必须连通。如果图是分裂的（比如房间 0-1 有门，房间 3-4 有门，但 1 和 3 没连通），管家不可能关上所有的门。(题目隐含暗示通常是连通的，但严谨的代码需要检查，或者只检查度数条件在某些弱数据下也能过，不过 POJ 1300 数据比较强，建议判连通)。

- 核心条件（度数奇偶性）：

  设 $deg[i]$ 为节点 $i$ 的度数（连接的门的数量）。

  - **情况 A：起点 M == 0**
    - 这意味着起点和终点重合。
    - 我们需要找的是 **欧拉回路 (Eulerian Circuit)**。
    - **判定条件**：**所有节点的度数必须是偶数**。
  - **情况 B：起点 M != 0**
    - 这意味着起点和终点不同。
    - 我们需要找的是 **欧拉路径 (Eulerian Path)**。
    - **判定条件**：
      1. **起点 M** 的度数必须是 **奇数**。
      2. **终点 0** 的度数必须是 **奇数**。
      3. **其他所有节点** 的度数必须是 **偶数**。

- 输入处理上的坑

这个题目的输入格式稍微有点“古老”，需要注意：

- 它是多组数据，以 `START M N` 开始，`END` 结束一组，`ENDOFINPUT` 结束所有。
- 读取边的列表时，题目说：“第 $i$ 行列出的是房间 $i$ 连接到的**编号比它大**的房间”。
  - 这意味着如果我们读到 `Room 0: 1 5`，我们连边 `(0, 1)` 和 `(0, 5)`。
  - 不需要担心重复加边。
  - 需要使用 `getline` 和 `stringstream` 来处理每一行的输入，因为每行的数字个数不确定。

------

## 代码


```cpp
/**
 * Author by Rainboy
 * Problem: POJ 1300 Door Man
 * Analysis: 
 * 1. 这是一个无向图欧拉路径/回路判定问题。
 * 2. 目标：判断是否存在从起点 M 走到终点 0 的路径，且经过所有边恰好一次。
 * 3. 判定逻辑：
 * - 首先：图必须是连通的（忽略孤立点）。
 * - 情况1 (M == 0): 需要欧拉回路 -> 所有点度数为偶数。
 * - 情况2 (M != 0): 需要欧拉路径 -> deg[M]和deg[0]为奇数，其余为偶数。
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 25; // 题目说 N <= 20

int start_node, n; // 起点M，房间总数N
int deg[MAXN];     // 度数数组
int edge_count;    // 总边数（门的数量）

// 并查集用于判连通
struct DSU {
    int fa[MAXN];
    void init(int n) {
        for(int i = 0; i < n; i++) fa[i] = i;
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void merge(int u, int v) {
        int fu = find(u);
        int fv = find(v);
        if (fu != fv) fa[fu] = fv;
    }
} dsu;

void solve() {
    string line;
    // 读取 START M N 中的 M 和 N
    // 此时 cin 已经在 main 函数读取了 "START"
    cin >> start_node >> n;
    
    // 清空状态
    memset(deg, 0, sizeof(deg));
    edge_count = 0;
    dsu.init(n);
    
    // 消耗掉 START 行末尾的换行符
    getline(cin, line); 

    // 读取 N 行，每行代表 Room i 连接到的更高编号房间
    for (int i = 0; i < n; i++) {
        getline(cin, line); // 读取整行
        if (line.empty()) continue;

        stringstream ss(line);
        int target;
        while (ss >> target) {
            // 连边 i <-> target
            deg[i]++;
            deg[target]++;
            edge_count++;
            dsu.merge(i, target);
        }
    }

    // 读取该组数据的结束标记 "END"
    string dummy;
    cin >> dummy; 

    // === 核心判定逻辑 ===

    // 1. 连通性检查
    // 找到第一个有度数的点作为基准 root
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (deg[i] > 0) {
            if (root == -1) root = dsu.find(i);
            else if (dsu.find(i) != root) {
                // 发现有度数的点不在同一个连通分量，说明图不连通
                cout << "NO" << endl;
                return;
            }
        }
    }
    
    // 特判：如果没有边，且起点就是终点(0)，且start_node==0，算YES 0？
    // 题目 implied "non-empty series"，通常会有门。
    // 如果没有门，M=0时在自己房间不需要动，M!=0时过不去。
    if (edge_count == 0) {
        if (start_node == 0) cout << "YES 0" << endl;
        else cout << "NO" << endl;
        return;
    }
    
    // 还需要检查起点是否在连通分量里 (防止起点是孤立点，虽然没门的情况上面排除了)
    // 但如果有门，起点必须能通向这些门
    if (deg[start_node] == 0) {
        cout << "NO" << endl;
        return;
    }


    // 2. 度数检查
    bool possible = false;

    if (start_node == 0) {
        // 情况 A: 欧拉回路 (起点=0, 终点=0)
        // 要求：所有点度数均为偶数
        possible = true;
        for (int i = 0; i < n; i++) {
            if (deg[i] % 2 != 0) {
                possible = false;
                break;
            }
        }
    } else {
        // 情况 B: 欧拉路径 (起点=M, 终点=0)
        // 要求：起点和终点度数为奇数，其他为偶数
        if (deg[start_node] % 2 != 0 && deg[0] % 2 != 0) {
            possible = true;
            for (int i = 1; i < n; i++) {
                if (i == start_node) continue; // 起点已经检查过了
                if (deg[i] % 2 != 0) {
                    possible = false;
                    break;
                }
            }
        } else {
            possible = false;
        }
    }

    if (possible) {
        cout << "YES " << edge_count << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    string command;
    while (cin >> command) {
        if (command == "ENDOFINPUT") break;
        if (command == "START") {
            solve();
        }
    }
    return 0;
}
```

## 代码细节说明

1. **输入解析**：利用 `stringstream` 是处理这种“一行不确定有多少个数字”的最佳方式。
2. **连通性**：虽然题目描述可能让人觉得房间都是连通的，但加上并查集判断是最稳妥的（防止有两个独立的房子，管家在房子A，却要关房子B的门，这显然不可能）。
3. **边界情况**：如果 `start_node` 本身没有连接任何门（`deg[start_node] == 0`），但他却需要去关其他的门（`edge_count > 0`），这显然也是 `NO`。代码中通过检查 `deg[start_node] == 0` 处理了这点。
