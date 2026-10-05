---
name: oj-cpp-competitive-style
description: >-
  Write or review OJ C++17 code in a clear Chinese competitive-programming
  style. Use this skill when creating or editing main.cpp, brute.cpp,
  generator-adjacent C++ snippets, or when the user asks to restrict AI C++
  style: no lambda, avoid over-modern C++, no parallel arrays (use a struct
  array instead), prefer dynamic-static node allocation (struct array +
  new_node() allocator) for trees/tries/graphs, prefer global arrays/variables,
  use typedef long long ll for problem data, avoid forced casts, prefer
  on-the-fly enumeration over storing intermediate tables, keep memo state in
  index-expressible arrays, use simple loops, write 01 序列 / 选择序列
  recursive brute force clearly when suitable, allow common STL such as
  queue/map/set/priority_queue/vector when appropriate, and add useful Chinese
  comments.
---

# OJ C++ 竞赛风格

这个 skill 约束 AI 写 OJ C++ 代码的形式。目标是：代码像竞赛选手手写的，容易读、容易调试、适合放进题解中教学。

适用文件：`main.cpp`、`brute.cpp`、题解中的 C++ 代码片段、需要审查或改写的 OJ C++17 代码。

完整代码骨架（普通题、链式前向星、动态化静态、01 序列递归）放在 [`references/code-templates.md`](references/code-templates.md)，写完整文件时读取；本文件是判定规则。

## 总原则

- 使用 C++17。
- 代码优先清楚，不追求炫技。
- 变量和数组尽量全局，便于竞赛环境下控制内存和调试。
- 普通 for 循环优先；数组能清楚表达时优先数组，必要时使用常见 STL。
- 写关键中文注释（见「中文注释规则」）。
- 不把核心逻辑藏进复杂封装、lambda、模板或过度 STL 表达式里（见「硬禁用」）。
- 题目数据默认 `ll`，大容量数组按值域选 `int` / `char`（见「类型与强制转换」）。
- 用声明类型消灭强制转换，不靠 `(long long)`、`(int)` 这类转换修补。
- 能现场枚举就不落地保存中间结构（见「存储选择」）。

## 类型与强制转换

题目数据默认 `long long`，文件开头写 `typedef long long ll;`。

- 默认 `ll`：输入规模（`n`、`m`、`k`、`q`、`len` 等）和题目值（数值、下标、轮数、答案、乘积、记忆化键）。
- 算法辅助结构（`choose[]`、`vis[]` 等）按语义选类型。
- 大容量数组按值域选更小的类型并注释原因，例如 `char memo[MAXR][MAXV][MAXP]; // 状态标记只有 0/1/2，用 char 控制内存`。

禁止用强制转换修补类型不匹配，要把声明类型写对：

```cpp
return ((long long)round * (max_value + 1) + value) * (n + 1) + last_person; // 不好
int len = (int)s.size() - 1;                                                 // 不好

ll make_key(ll round, ll value, ll last_person) { // 好：参数和返回值都是 ll
    return (round * (max_value + 1) + value) * (n + 1) + last_person;
}
ll len = s.size() - 1; // 好
```

只有对接第三方接口或必须匹配某种签名时才允许转换，并注释原因。本 skill 其余示例侧重结构，类型不逐一换 `ll`。

## 文件头（必须）

所有新建 `.cpp` 文件的第一行必须是信息头，时间精确到分钟：

```cpp
/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: YYYY-MM-DD HH:mm
 * update_at: YYYY-MM-DD HH:mm
 */
```

- 适用所有 `.cpp`（`main.cpp`、`brute.cpp`、`brute_01_style.cpp`、分值代码等）；原有文件头注释（如 `// brute.cpp：小数据暴力解...`）保留在信息头之后。
- 新建文件 `create_at` 与 `update_at` 相同且为实际时间；修改时保留原 `create_at`，把 `update_at` 刷成修改时间。
- 旧格式头只有 `date` 字段时迁移为 `create_at`；不回溯更新旧文件。
- 用仓库工具 `scripts/problem-analysis-tools/cpp_header.py` 生成和更新，脚手架复用它的生成函数，不要手写时间。

## 硬禁用

不要使用：lambda、structured binding（`auto [u, v] = e`）、C++20/23 特性、ranges、concept、模板元编程、复杂泛型工具、为了炫技写的 class/template 封装、降低新手可读性的宏（`rep(i,n)`、`all(x)`、`pb` 等）、平行数组。

平行数组指用多个下标平行的数组记录同一个对象的字段，例如
`char node_type[MAXL]` + `ll left_son[MAXL]` + `ll right_son[MAXL]` + `char node_value[MAXL]`。
同一个对象的字段必须聚合成 struct 数组（需要动态开点时用动态化静态，见「存储选择」）：

```cpp
// 不好：平行数组，读者要自己脑补四个下标是同一个节点
char node_type[MAXL];
ll left_son[MAXL];
ll right_son[MAXL];
char node_value[MAXL];

// 好：struct 聚合，一个节点就是一个 node[u]
struct Node {
    char type;
    ll left;
    ll right;
    ll value;
};
Node node[MAXL];
```

核心算法一律写成普通函数，不写 `auto solve = [&](){...}`：

```cpp
void solve() {
    ...
}
```

## `auto` 规则

默认避免 `auto`：禁止 `for (auto x : a)` 和 structured binding。只在迭代器类型过长时允许：

```cpp
auto it = mp.find(x);
auto it = lower_bound(a + 1, a + n + 1, x);
```

其余情况写明确类型。

## STL 规则

“尽量不使用 STL”指不要滥用复杂 STL，不是完全禁用。

- 允许并推荐：`queue`、`priority_queue`、`map`、`set`、`vector`、`pair`、`sort`、`lower_bound`、`upper_bound`。
- 避免复杂嵌套容器（如 `vector<vector<pair<int, int> > >`），除非确实更清楚；按对象存序列的 `vector<vector<ll> >` 是清楚的（见「存储选择」）。
- 避免大量 `unordered_map` / `unordered_set`，除非明确需要且说明哈希风险。
- 不用 STL 算法链式写法替代清楚的循环；不用 `function` 保存递归或状态转移。
- 数组优先（`const int MAXX = ...;` + 全局数组）；动态规模或小教学题可以用 `vector<int> g[MAXN]`。

## 全局变量规则

核心数据定义为全局变量，数组含义写注释。原因：避免大数组爆栈、方便多个函数共享、接近 OI/ACM 习惯。局部变量只放循环变量、临时结果和很小的辅助变量。

## 存储选择：现场枚举 vs 落地保存

先问数据怎么被使用，再决定要不要存下来：

- 只被单向遍历、可以重复算出来的中间结构（候选边、合法区间里的位置、匹配对），优先现场枚举、用完即丢，不建表。
- 需要边编号、反向边、大规模多源复用、或枚举代价不可重复支付时，才落地保存（图、索引、预处理表）。

教学代码里“现场扫描序列枚举合法选择”比预建边表直观：删掉的存储越多，读者要跟踪的状态越少。

其他约定：

- 多对象序列按对象存、下标从 1 开始和题面对应，不做平铺 + 偏移数组：`vector<vector<ll> > seq; // seq[person] = 第 person 个人的序列`。
- 用简单 struct 聚合固定字段数据（询问、点对、树/图节点），替代平行数组；struct 只放数据，不放算法逻辑：

```cpp
struct Query {
    ll r;
    ll v;
};
```

- 元素个数事先不确定、需要“开点”的结构（表达式树、Trie、可持久化结构、逐步加点的图）用动态化静态：struct 数组 + `node_cnt` 当分配指针，`new_node()` 负责开点，不用指针、`new` 或动态内存：

```cpp
struct Node {
    char type;   // 节点类型
    ll left;     // 左儿子编号，叶子为 0
    ll right;    // 右儿子编号，叶子为 0
    ll value;    // 节点的值
};

// 动态化静态：静态大数组 + node_cnt 当分配指针，new_node 每次“开点”就把 node_cnt 加一
Node node[MAXL];  // 节点 u 就是 node[u]
ll node_cnt;      // 已经创建的节点个数，最后一个节点是 node[node_cnt]

// 新建一个节点（动态开点），返回编号
ll new_node(char ch, ll left_id, ll right_id) {
    node_cnt++;
    node[node_cnt].type = ch;
    node[node_cnt].left = left_id;
    node[node_cnt].right = right_id;
    return node_cnt;
}
```

动态化静态的好处：写法是静态数组（好调、好控内存），用法像指针树（按编号引用 `node[u].left`），比平行数组清楚，也比 `Node*` 指针递归建树安全（不爆指针栈、不用手写释放）。完整模板见 [`references/code-templates.md`](references/code-templates.md)。

## 图论代码规则

决定要存图之后，默认链式前向星（模板见 [`references/code-templates.md`](references/code-templates.md)）：

- 适合链式前向星：边数大、需要边编号、需要反向边、网络流/最短路/Tarjan/树上差分等模板。
- 允许 `vector<int> g[MAXN]`：树题、简单 DFS/BFS、无权图、数据范围不大、教学上明显更直观。

## 推荐代码骨架

普通题骨架见 [`references/code-templates.md`](references/code-templates.md)。简单入门题可以直接写在 `main()` 中，不强制拆函数；复杂题拆成 `read_input()`、`solve()`、`add_edge()`、`dfs()` / `bfs()` / `check()` 等清楚命名的函数。

## `brute.cpp` 规则

`brute.cpp` 用于小数据验证和帮助读者理解朴素想法：

- 和 `main.cpp` 使用同样输入输出格式；开头注释说明它是暴力/朴素解。
- 使用 01 序列 / 选择序列枚举时，文件头说明每层递归在做一个选择；标准 01 序列递归只负责生成完整 `choose[]`，到叶子节点统一检查合法性并统计答案。
- 逻辑优先直观，复杂度高可以接受，但要在题解中说明只适合小数据。
- 不使用 lambda 或复杂 STL。

推荐开头注释：

```cpp
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
// brute.cpp：小数据暴力解，把每一步操作看成选择序列来递归枚举。
```

## 01 序列 / 选择序列递归风格

教学暴力的固定套路：一层一个选择，先完整生成方案再检查。适合选/不选、填某一位、走下一步、选一条边、选一个区间。

1. 全局数组 `choose[]` 保存每层的选择；`dfs(dep)` 只枚举第 `dep` 层并递归到下一层。
2. `dep == n + 1` 时完整方案已生成；叶子节点调 `check()` 判断合法性，再调 `calc_answer()` 更新答案。
3. 不把合法性判断提前藏进递归参数里（不要写成 `dfs(pos, last_end, cnt)` 边搜边剪枝）。

完整模板和教学说明见 [`references/code-templates.md`](references/code-templates.md)。写法要求：

- 用全局数组或清楚的全局容器保存输入、路径、答案和访问状态；标准 01 序列优先 `choose[]`，不用 `path.push_back()` / `pop_back()`（确实用路径容器时回溯要成对写）。
- 函数名表达递归含义，例如 `dfs_choose`、`dfs_build`、`dfs_walk`、`dfs_game`；注释写“这一层在选择什么”。
- 重复状态用简单 `vis` / `memo`，但保持递归结构清楚：记忆化优先“下标即状态”，用多维数组（如 `char memo[MAXR][MAXV][MAXP]`）并在注释里写清 `memo[round][value][person]` 的含义和 `0/1/2` 取值；状态稀疏到数组开不出时才用 `map` + 键编码，且键的构造公式必须写注释；清理数组只清实际会用到的范围，并注释为什么够。
- `brute.cpp` 的数据规模只服务小数据理解和对拍，不按满分约束优化。

## 命名规则

- 不要使用和 std 标识符冲突的名字，例如 `next`、`prev`、`div`、`y0/y1/j0/j1`；`next` 改成 `next_last`、`nxt` 这类表达含义的名字。
- 变量名表达它在题中的含义（`reachable`、`last_person`、`right_end`），不用 `a1`、`tmp2` 这类读者对不上题解的名字。

## 中文注释规则

必须注释：核心全局数组的含义、核心函数的作用、DP 状态定义和转移来源、贪心选择标准、图论边/节点/队列/堆的含义、容易错的边界处理、`brute.cpp` 为什么只适合小数据。不要注释 `cin >> n`、`i++`、`q.push()` 这类显然操作。

```cpp
int dp[MAXN]; // dp[i] 表示以第 i 个数结尾的最长上升子序列长度（好）
// 判断容量 mid 是否足够完成所有任务。（好）
i++; // i 加一（坏）
```

## 审查 Checklist

审查已有 C++ 代码时，按「必须改 → 建议改 → 可接受」输出问题，每条指出位置和改法。

### 必须改

- lambda、structured binding、C++20/23 特性。
- 平行数组（多个下标平行的数组记录同一个对象的字段）；应改成 struct 数组，需要动态开点时用动态化静态 + `new_node()`。
- 核心逻辑藏在复杂 class/template/function 里。
- 缺少 `main()` 或输入输出格式和题目不一致；`brute.cpp` 不是完整程序或和 `main.cpp` 输入输出不一致。
- 用强制转换（`(long long)`、`(int)` 等）修补类型不匹配。

### 建议改

- 核心大数组是局部变量，可能爆栈。
- 可以用数组却用了复杂嵌套 STL；图论代码没有清楚的 `add_edge()` 或邻接结构说明。
- 使用过多 `auto` 或 range-for。
- 变量名过于抽象、与 std 标识符冲突（如 `next`），读者难以对应题解。
- 可用固定下标表达的状态却用了 `map` + 键编码；可现场枚举的中间结构被落地建表。
- 核心数组/函数缺少中文注释。

### 可接受

- `priority_queue`（Dijkstra / Huffman / 堆）、`queue`（BFS）、`map` / `set`（有序映射）、`vector<int> g[MAXN]`（简单树题）。
- 迭代器类型太长时使用 `auto it = ...`。
- 数据变量使用 `ll`，大数组使用 `int` / `char` 并注释原因；用简单 struct 聚合询问、点对、节点；树/图节点用动态化静态（struct 数组 + `node_cnt` 开点）；记忆化只清理实际用到的数组范围并有注释。

## 与题解写作配合

当 `oj-problem-analysis-writer` 创建或修改 `main.cpp` / `brute.cpp` 时，必须遵守本 skill。仓库若提供 `python3 scripts/problem-analysis-tools/check_cpp_style.py <file>`，生成或审查后应运行它；目前依赖人工/AI 按上述规则审查。
