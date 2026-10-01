---
name: oj-cpp-competitive-style
description: >-
  Write or review OJ C++17 code in a clear Chinese competitive-programming
  style. Use this skill when creating or editing main.cpp, brute.cpp,
  generator-adjacent C++ snippets, or when the user asks to restrict AI C++
  style: no lambda, avoid over-modern C++, prefer global arrays/variables, use
  typedef long long ll for problem data, avoid forced casts, prefer on-the-fly
  enumeration over storing intermediate tables, keep memo state in
  index-expressible arrays, use simple loops, write 01 序列 / 选择序列
  recursive brute force clearly when suitable, allow common STL such as
  queue/map/set/priority_queue/vector when appropriate, and add useful Chinese
  comments.
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
- 题目数据默认 `ll`（见「类型与强制转换」），大容量数组按值域选 `int` / `char`。
- 用声明类型消灭强制转换，不靠 `(long long)`、`(int)` 这类转换修补。
- 能现场枚举就不落地保存中间结构（见「存储选择」）。

## 类型与强制转换

题目数据默认使用 `long long`，在开头给短名：

```cpp
typedef long long ll;
```

默认用 `ll` 的数据：

- 输入规模：`n`、`m`、`k`、`q`、`len` 等。
- 题目值：数值、下标、轮数、答案、乘积、记忆化键。
- 算法辅助结构（`choose[]`、`vis[]` 等）按语义选类型。

例外：大容量数组按值域选更小的类型，并注释原因：

```cpp
char memo[MAXR][MAXV][MAXP]; // 状态标记只有 0/1/2，用 char 控制内存
```

禁止用强制转换修补类型不匹配。常见的坏写法：

```cpp
return ((long long)round * (max_value + 1) + value) * (n + 1) + last_person; // 不好
int len = (int)s.size() - 1; // 不好
```

改成把声明类型写对：

```cpp
ll make_key(ll round, ll value, ll last_person) {
    return (round * (max_value + 1) + value) * (n + 1) + last_person;
}

ll len = s.size() - 1;
```

只有对接第三方接口或必须匹配某种签名时才允许转换，并注释说明原因。
本 skill 各节示例侧重结构，类型不逐一换 `ll`；实际代码按本节选类型。

## 文件头（必须）

所有新建的 `.cpp` 文件必须在第一行添加以下信息头。时间精确到分钟：

```cpp
/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: YYYY-MM-DD HH:mm
 * update_at: YYYY-MM-DD HH:mm
 */
```

规则：

- 信息头放在文件最前面，原有的文件头注释（如 `// brute.cpp：小数据暴力解...`）保留在信息头之后。
- 只对新创建的文件生效，不回溯更新旧文件。
- `create_at` 使用创建文件时的实际时间，`update_at` 使用最近一次实质修改代码时的时间。
- 新建文件时 `create_at` 与 `update_at` 相同，格式均为 `YYYY-MM-DD HH:mm`。
- 修改已有旧格式头时，保留原 `create_at`；如果只有旧字段 `date`，把它迁移为 `create_at`，并更新 `update_at`。
- 仓库工具 `scripts/problem-analysis-tools/cpp_header.py` 负责生成和更新标准信息头；脚手架也应复用这个脚本里的生成函数，避免手写时间。
- 适用于所有 `.cpp` 文件：`main.cpp`、`brute.cpp`、`brute_01_style.cpp`、分值代码（`1.cpp`、`1_v2.cpp` 等）。

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

- 复杂嵌套容器，例如 `vector<vector<pair<int, int> > >`，除非题目确实更清楚（按对象存序列的 `vector<vector<ll> >` 是清楚的，见「存储选择」）。
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

## 存储选择：现场枚举 vs 落地保存

先问数据怎么被使用，再决定要不要存下来：

- 只被单向遍历、可以重复算出来的中间结构（候选边、合法区间里的位置、匹配对），优先现场枚举、用完即丢，不建表。
- 需要边编号、反向边、大规模多源复用、或枚举代价不可重复支付时，才落地保存（图、索引、预处理表）。

教学代码里，“现场扫描所有人的序列，枚举以当前值开头的合法接龙序列”这类写法比预建边表更直观：删掉的存储越多，读者要跟踪的状态越少。

其他存储约定：

- 多个对象各自带序列时直接按对象存，下标从 1 开始和题面对应，不做平铺 + 偏移数组：

```cpp
vector<vector<ll> > seq; // seq[person] = 第 person 个人的序列，下标从 1 开始用
```

- 用简单 struct 聚合固定字段的数据（询问、点对），替代平行数组；struct 只放数据，不放算法逻辑：

```cpp
struct Query {
    ll r;
    ll v;
};
vector<Query> queries;
```

## 图论代码规则

决定要存图之后，默认链式前向星：

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

typedef long long ll;

ll n;
ll a[MAXN]; // 输入数组；值域小时可以改用 int 并注释原因

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
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
- 如果使用标准 01 序列写法，递归只负责生成完整的 `choose[]`，到叶子节点再统一检查合法性和统计答案。
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

标准 01 序列写法的核心是：

1. 用全局数组 `choose[]` 保存每一层的选择。
2. `dfs(dep)` 只负责枚举第 `dep` 层的选择，并递归到下一层。
3. 当 `dep == n + 1` 时，说明一条完整 01 序列已经生成。
4. 在叶子节点调用 `check()` 判断当前 `choose[]` 是否合法，再调用 `calc_answer()` 或直接统计当前选择数量更新答案。

优先写成普通函数，不使用 lambda 或 `function`。不要把合法性判断提前藏进递归参数里，例如不要把区间题写成 `dfs(pos, last_end, cnt)` 来边搜边剪枝；标准 01 序列应该先完整生成 `choose[]`，再统一检查。

下面的示例重点在递归结构，类型按「类型与强制转换」一节选择。

```cpp
const int MAXN = 35;

int n;
int choose[MAXN]; // choose[i] 表示第 i 个对象的选择：0 不选，1 选
int ans;

bool check() {
    // 检查当前完整 choose[1..n] 是否合法。
    // 例如区间题在这里判断所有被选区间是否两两不冲突。
    return true;
}

int calc_answer() {
    // 统计当前完整 choose[1..n] 对应的答案。
    // 例如统计 choose[i] == 1 的数量。
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose[i] == 1) cnt++;
    }
    return cnt;
}

void dfs(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (ans < value) ans = value;
        }
        return;
    }

    // 这一层枚举第 dep 个对象的 01 选择。
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs(dep + 1);
    }
}
```

这个模板的教学重点是让学生看到：长度为 `n` 的 01 序列一共有 `2^n` 种，每一种都代表一种完整方案。合法性检查、答案统计放在叶子节点，逻辑最直接。

多分支选择也保持同样结构：

```cpp
int choose_step[MAXN];

void dfs(int dep) {
    if (dep == max_step + 1) {
        if (check()) {
            int value = calc_answer();
            if (ans < value) ans = value;
        }
        return;
    }

    // 第 dep 层可以选择 0..k 中的任意一种决策。
    for (int i = 0; i <= k; i++) {
        choose_step[dep] = i;
        dfs(dep + 1);
    }
}
```

写法要求：

- 用全局数组或清楚的全局容器保存输入、路径、答案和访问状态。
- 标准 01 序列优先使用 `choose[]` 保存完整选择，不优先使用 `path.push_back()` / `pop_back()`。
- 函数名表达递归含义，例如 `dfs_choose`、`dfs_build`、`dfs_walk`、`dfs_game`。
- 注释写“这一层在选择什么”，不要注释 `i++`、`push_back` 这类显然操作。
- 如果确实使用路径容器，回溯时成对写 `push_back` / `pop_back`，或清楚恢复全局状态。
- 如果重复状态明显，可以加简单 `vis` / `memo`，但保持递归选择结构清楚。
- 记忆化优先“下标即状态”：状态能写成固定下标时用多维数组（如 `char memo[MAXR][MAXV][MAXP]`），注释里写清 `memo[round][value][person]` 的含义和 `0/1/2` 取值。
- 只有状态稀疏到数组开不出时才用 `map` + 键编码，键的构造公式必须写注释。
- 清理数组只清实际会用到的范围，并注释为什么够（例如 DFS 只写前 `target_round` 层）。
- `brute.cpp` 的数据规模只服务小数据理解和对拍，不需要按满分约束优化。

## 命名规则

- 不要使用和 std 标识符冲突的名字，例如 `next`、`prev`、`div`、`y0/y1/j0/j1`；`next` 改成 `next_last`、`nxt` 这类表达含义的名字。
- 变量名表达它在题中的含义（`reachable`、`last_person`、`right_end`），不用 `a1`、`tmp2` 这类读者对不上题解的名字。

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
- 用强制转换（`(long long)`、`(int)` 等）修补类型不匹配。

### 建议改

- 核心大数组是局部变量，可能爆栈。
- 可以用数组却用了复杂嵌套 STL。
- 图论代码没有清楚的 `add_edge()` 或邻接结构说明。
- 使用过多 `auto` 或 range-for。
- 变量名过于抽象、与 std 标识符冲突（如 `next`），读者难以对应题解。
- 可用固定下标表达的状态却用了 `map` + 键编码。
- 可现场枚举的中间结构被落地建表。
- 核心数组/函数缺少中文注释。

### 可接受

- Dijkstra / Huffman / 堆相关题使用 `priority_queue`。
- BFS 使用 `queue`。
- 需要有序映射时使用 `map` / `set`。
- 简单树题使用 `vector<int> g[MAXN]`。
- 迭代器类型太长时使用 `auto it = ...`。
- 数据变量使用 `ll`，大数组使用 `int` / `char` 并注释原因。
- 用简单 struct 聚合询问、点对等固定字段数据。
- 记忆化只清理实际用到的数组范围并有注释。

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
