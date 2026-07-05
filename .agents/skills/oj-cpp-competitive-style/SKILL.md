---
name: oj-cpp-competitive-style
description: >-
  Write or review OJ C++17 code in a clear Chinese competitive-programming
  style. Use this skill when creating or editing main.cpp, brute.cpp,
  generator-adjacent C++ snippets, or when the user asks to restrict AI C++
  style: no lambda, avoid over-modern C++, prefer global arrays/variables, use
  simple loops, write 01 序列 / 选择序列 recursive brute force clearly when
  suitable, allow common STL such as queue/map/set/priority_queue/vector when
  appropriate, and add useful Chinese comments.
---

# OJ C++ 竞赛风格

这个 skill 约束 AI 写 OJ C++ 代码的形式。目标是：代码像竞赛选手手写的，容易读、容易调试、适合放进题解中教学。

适用文件：

- `main.cpp`
- `brute.cpp`
- 题解中的 C++ 代码片段
- 需要审查或改写的 OJ C++17 代码

## 总原则

- 使用 C++17。
- 代码优先清楚，不追求炫技。
- 变量和数组尽量全局，便于竞赛环境下控制内存和调试。
- 普通 for 循环优先。
- 数组优先；必要时使用常见 STL。
- 写关键中文注释，帮助读者理解算法和变量含义。
- 不把核心逻辑藏进复杂封装、lambda、模板或过度 STL 表达式里。

## 硬禁用

不要使用：

- lambda，例如 `[&](){...}`。
- structured binding，例如 `auto [u, v] = edge;`。
- C++20/23 特性。
- ranges。
- concept。
- 模板元编程。
- 复杂泛型工具。
- 为了炫技写的 class/template 封装。
- 降低新手可读性的宏，例如 `rep(i,n)`、`all(x)`、`pb` 等。

不要把核心算法写成：

```cpp
auto solve = [&]() {
    ...
};
```

改成普通函数：

```cpp
void solve() {
    ...
}
```

## `auto` 规则

默认避免 `auto`。

禁止：

```cpp
auto [u, v] = e;
for (auto x : a) {
    ...
}
```

可以接受：

```cpp
auto it = mp.find(x);
auto it = lower_bound(a + 1, a + n + 1, x);
```

如果不用 `auto` 会让迭代器类型很长，可以使用 `auto`。其它情况优先写明确类型。

## STL 规则

“尽量不使用 STL”指不要滥用复杂 STL，不是完全禁用 STL。

允许并推荐在合适场景使用：

- `queue`
- `priority_queue`
- `map`
- `set`
- `vector`
- `pair`
- `sort`
- `lower_bound`
- `upper_bound`

避免：

- 复杂嵌套容器，例如 `vector<vector<pair<int, int>>>`，除非题目确实更清楚。
- 大量 `unordered_map` / `unordered_set`，除非明确需要且说明哈希风险。
- 用 STL 算法链式写法替代清楚循环。
- 用 `function` 保存递归或状态转移。

数组能清楚表达时优先数组：

```cpp
const int MAXN = 100005;
int a[MAXN], dp[MAXN];
```

动态规模或小教学题可以用 `vector`：

```cpp
vector<int> g[MAXN];
```

## 全局变量规则

优先把核心数据定义为全局变量：

```cpp
const int MAXN = 100005;
const int MAXM = 200005;

int n, m;
int a[MAXN];       // 输入数组
int dp[MAXN];      // dp[i] 表示以 i 结尾的最优值
```

原因：

- 避免大数组爆栈。
- 方便多个函数共享。
- 更接近 OI/ACM 竞赛代码习惯。

局部变量适合：

- 循环变量。
- 临时结果。
- 很小的辅助变量。

## 图论代码规则

默认优先链式前向星：

```cpp
const int MAXN = 100005;
const int MAXM = 200005;

int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

// 加一条 u -> v 的边。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}
```

适合链式前向星：

- 边数大。
- 需要边编号。
- 需要反向边。
- 网络流、最短路、Tarjan、树上差分等模板。

允许 `vector<int> g[MAXN]`：

- 树题。
- 简单 DFS/BFS。
- 无权图。
- 数据范围不大。
- 教学上明显更直观。

遍历链式前向星：

```cpp
for (int i = head[u]; i != 0; i = nxt[i]) {
    int v = to[i];
    ...
}
```

## 推荐代码骨架

普通题：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int a[MAXN]; // 输入数组

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

void solve() {
    // 核心逻辑
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
```

简单入门题可以直接写在 `main()` 中，不强制拆函数。

复杂题推荐拆成：

- `read_input()`
- `solve()`
- `add_edge()`
- `dfs()` / `bfs()` / `check()` 等清楚命名的辅助函数

## `brute.cpp` 规则

`brute.cpp` 用于小数据验证和帮助读者理解朴素想法。

要求：

- 和 `main.cpp` 使用同样输入输出格式。
- 开头注释说明它是暴力/朴素解。
- 如果使用 01 序列 / 选择序列枚举，文件头应说明每层递归在做一个选择。
- 逻辑优先直观，不追求高效。
- 复杂度高可以接受，但要在题解中说明只适合小数据。
- 不使用 lambda 或复杂 STL。

推荐开头：

```cpp
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
```

如果采用 01 序列 / 选择序列写法，可以使用：

```cpp
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
// brute.cpp：小数据暴力解，把每一步操作看成选择序列来递归枚举。
```

## 01 序列 / 选择序列递归风格

这种写法常用于教学暴力。它把问题拆成一层一层的选择，适合选/不选、填某一位、走下一步、选一条边、选一个区间等场景。

优先写成普通函数，不使用 lambda 或 `function`：

```cpp
void dfs(int pos, int sum) {
    if (pos == n + 1) {
        // 检查当前选择序列。
        return;
    }

    // 选择 0：不选当前位置。
    dfs(pos + 1, sum);

    // 选择 1：选择当前位置。
    path.push_back(a[pos]);
    dfs(pos + 1, sum + a[pos]);
    path.pop_back();
}
```

多分支选择也保持同样结构：

```cpp
void dfs(int step, int u) {
    if (step == max_step) {
        return;
    }

    // 下一步可以选择任意一个合法后继。
    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to[i];
        dfs(step + 1, v);
    }
}
```

写法要求：

- 用全局数组或清楚的全局容器保存输入、路径、答案和访问状态。
- 函数名表达递归含义，例如 `dfs_choose`、`dfs_build`、`dfs_walk`、`dfs_game`。
- 注释写“这一层在选择什么”，不要注释 `i++`、`push_back` 这类显然操作。
- 回溯时成对写 `push_back` / `pop_back`，或清楚恢复全局状态。
- 如果重复状态明显，可以加简单 `vis` / `memo`，但保持递归选择结构清楚。
- `brute.cpp` 的数据规模只服务小数据理解和对拍，不需要按满分约束优化。

## 中文注释规则

必须注释：

- 核心全局数组的含义。
- 核心函数的作用。
- DP 状态定义和转移来源。
- 贪心选择标准。
- 图论边、节点、队列、堆的含义。
- 容易错的边界处理。
- `brute.cpp` 为什么只适合小数据。

不要注释：

- `cin >> n`。
- `i++`。
- `q.push()` / `q.pop()` 这种显然操作。

好注释：

```cpp
int dp[MAXN]; // dp[i] 表示以第 i 个数结尾的最长上升子序列长度

// 判断容量 mid 是否足够完成所有任务。
bool check(long long mid) {
    ...
}
```

坏注释：

```cpp
i++; // i 加一
cin >> n; // 输入 n
```

## 审查 Checklist

审查已有 C++ 代码时，按下面顺序输出问题。

### 必须改

- 使用 lambda。
- 使用 structured binding。
- 使用 C++20/23 特性。
- 核心逻辑藏在复杂 class/template/function 里。
- 缺少 `main()` 或输入输出格式和题目不一致。
- `brute.cpp` 不是完整程序或和 `main.cpp` 输入输出不一致。

### 建议改

- 核心大数组是局部变量，可能爆栈。
- 可以用数组却用了复杂嵌套 STL。
- 图论代码没有清楚的 `add_edge()` 或邻接结构说明。
- 使用过多 `auto` 或 range-for。
- 变量名过于抽象，读者难以对应题解。
- 核心数组/函数缺少中文注释。

### 可接受

- Dijkstra / Huffman / 堆相关题使用 `priority_queue`。
- BFS 使用 `queue`。
- 需要有序映射时使用 `map` / `set`。
- 简单树题使用 `vector<int> g[MAXN]`。
- 迭代器类型太长时使用 `auto it = ...`。

报告格式：

```text
必须改
- 使用了 lambda，改成普通函数 `dfs()`。

建议改
- `vector<vector<int>>` 存图不利于竞赛风格阅读，当前题可以改成 `head/to/nxt`。

可接受
- 使用 `priority_queue` 是合理的，因为这是 Dijkstra 的核心结构。
```

## 与题解写作配合

当 `oj-problem-analysis-writer` 创建或修改 `main.cpp` / `brute.cpp` 时，必须遵守本 skill。

如果未来存在：

```bash
python3 scripts/problem-analysis-tools/check_cpp_style.py problems/<oj>/<problem_id>/main.cpp
```

生成或审查后应运行它。目前第一版只依赖本 skill 的人工/AI 审查规则。
