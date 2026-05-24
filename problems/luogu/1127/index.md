---
oj: "luogu"
problem_id: "P1127"
title: "词链"
date: 2025-12-23 10:35
toc: true
tags: ["欧拉路","todo"]
desc: "有向图字典序最小欧拉路径"
source: https://www.luogu.com.cn/problem/P1127
pre:
 - hdu,1116
---

[[TOC]]

TODO: 添加代码


你找对了方向！这道题的建模是解题的关键，也是**欧拉路（Euler Path）**问题的经典应用。

这是核心逻辑，简明扼要版：

### 1. 核心建模：单词即“边”

不要把单词当成“点”，否则会变成哈密顿路径问题（NP-Hard）。

* **节点（Node）**： 个小写字母（'a' ~ 'z'）。
* **边（Edge）**：每一个单词。
* 如果单词是 `dog`，则建立一条有向边：****。
* 这条边的权重/内容就是字符串 `"dog"`。



**目标转化**：
题目要求“所有单词各用一次”，转化为：**在图中找一条路径，经过每一条边恰好一次**。
这就是**欧拉路（或者欧拉回路）**。

### 2. 判别条件（有向图）

只有满足以下 **连通性** 和 **度数** 条件，才存在解：

1. **连通性**：所有涉及到的字母（节点）必须在同一个连通分量里（可以用并查集或DFS判断）。
2. **度数检查**：
* 设  为入度， 为出度。
* **欧拉回路**（起点回到起点）：所有点满足 。
* **欧拉路径**（起点不回到起点）：
* **起点**： （且仅有一个）。
* **终点**： （且仅有一个）。
* **其余点**：。


* **无解**：除上述两种情况外，直接输出 `***`。



### 3. 字典序最小

题目要求字典序最小，这影响我们在 DFS 时的贪心策略：

1. **邻接表排序**：对于节点 ，它连出的边（单词）可能有多个。将这些单词按**字典序从小到大**排序。
2. **DFS 顺序**：在遍历时，优先走字典序小的单词。
3. **确定起点**：
* 如果是欧拉路径，必须从那个  的点开始。
* 如果是欧拉回路，必须从字典序最小的有出度的点开始（通常是题目中涉及的最小字母）。



### 4. 代码实现 (C++)

核心是 **Hierholzer 算法** 的变体。

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

const int MAXN = 30;
// adj[u] 存储从字符 u 出发的所有单词
vector<string> adj[MAXN];
int in[MAXN], out[MAXN];
int p[MAXN]; // 并查集父节点
bool exist[MAXN]; // 记录字母是否出现过
stack<string> ans; // 存储结果路径

// 并查集查找
int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

void dfs(int u) {
    // 必须倒序取，或者用 vector 配合 pop_back 减少开销
    // 这里因为已经排序过(大到小)，尾部就是字典序最小的
    while (!adj[u].empty()) {
        string w = adj[u].back();
        adj[u].pop_back();
        int v = w.back() - 'a';
        dfs(v);
        ans.push(w); // 回溯时入栈（逆序）
    }
}

int main() {
    // 1. 初始化
    for (int i = 0; i < 26; i++) p[i] = i;
    
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int u = s.front() - 'a';
        int v = s.back() - 'a';
        
        // 为了方便从尾部 pop (O(1))，我们稍后将按字典序“从大到小”排序
        // 这样 vector 的尾部就是字典序最小的单词
        adj[u].push_back(s); 
        
        out[u]++;
        in[v]++;
        exist[u] = exist[v] = true;
        
        // 并查集
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) p[rootU] = rootV;
    }

    // 2. 预处理：排序邻接表
    for (int i = 0; i < 26; i++) {
        // 排序：从大到小，这样 back() 取出的是最小的
        sort(adj[i].begin(), adj[i].end(), greater<string>());
    }

    // 3. 判定欧拉路/回路并寻找起点
    int start_node = -1;
    int cnt_start = 0, cnt_end = 0;
    
    // 找起点逻辑
    for (int i = 0; i < 26; i++) {
        if (!exist[i]) continue;
        if (out[i] == in[i]) continue;
        if (out[i] == in[i] + 1) {
            start_node = i;
            cnt_start++;
        } else if (in[i] == out[i] + 1) {
            cnt_end++;
        } else {
            cout << "***"; return 0; // 度数不平衡，无解
        }
    }

    // 必须 1起1终 (路径) 或者 0起0终 (回路)
    if (!((cnt_start == 1 && cnt_end == 1) || (cnt_start == 0 && cnt_end == 0))) {
        cout << "***"; return 0;
    }

    // 如果是回路，起点设为字典序最小的有出度的点
    if (start_node == -1) {
        for (int i = 0; i < 26; i++) {
            if (exist[i] && out[i] > 0) {
                start_node = i;
                break;
            }
        }
    }

    // 4. 连通性检查 (必须只有一个连通分量)
    int root = find(start_node);
    for (int i = 0; i < 26; i++) {
        if (exist[i] && find(i) != root) {
            cout << "***"; return 0;
        }
    }

    // 5. DFS 求解
    dfs(start_node);

    // 6. 检查是否走完了所有边
    if (ans.size() != n) {
        cout << "***"; return 0;
    }

    // 7. 输出
    bool first = true;
    while (!ans.empty()) {
        if (!first) cout << ".";
        cout << ans.top();
        ans.pop();
        first = false;
    }
    
    return 0;
}

```

### 记忆要点

1. **单词是边**，不是点。
2. **`vector` 存边并排序**，用 `pop_back` 配合 `greater` 排序来实现  取最小字典序。
3. **回溯时入栈**，最后倒序输出（Hierholzer 算法核心）。
