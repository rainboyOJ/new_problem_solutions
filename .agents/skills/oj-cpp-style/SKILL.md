---
name: oj-cpp-style
description: >-
  Write or review OJ C++17 code in a clear Chinese competitive-programming
  style. Use when creating or editing main.cpp, brute.cpp, C++ solution
  snippets, or discussing OJ C++ style. Prefer readable global arrays,
  simple structs, independent auxiliary buckets, ordinary Trie children,
  vector record lists, range-for loops, and direct recursion when constraints
  permit; keep core logic explicit and avoid unnecessary abstractions.
---

# OJ C++ 竞赛风格

这个 skill 约束 AI 写 OJ C++ 代码的形式。读者定位与性能取舍以仓库 `AGENTS.md`「代码的读者与可读性」为准。下面规定如何把这些目标落实到 C++17 实现和验收。

适用文件：`main.cpp`、`brute.cpp`、题解中的 C++ 代码片段、需要审查或改写的 OJ C++17 代码。

完整代码骨架（普通题、链式前向星、动态化静态、01 序列递归）放在 [`references/code-templates.md`](references/code-templates.md)，写完整文件时读取；本文件是判定规则。

## 优先级：题面的显式要求 > 本 skill 的风格偏好

本 skill 教的是**风格**。但**题面里写死的实现手段是硬约束**，优先级高于风格偏好：

| 题面写的 | 该怎么做 |
|---|---|
| 「利用 **for 循环**求解」 | 保留显式 `for`，不要换 `while`/递归/STL 算法 |
| 「用**递归**实现」 | 保留递归 |
| 「**不使用**数组」 | 不用数组 |
| 「用**二分/冒泡排序**做」 | 按题面指定的手段（即使有更快的做法） |

理由：这类题多为教材例题，**实现手段本身就是教学目的**。

⚠ 「题面未指定」时**仍然按本 skill 写**，不要把「题面没禁止」当成放弃规范的理由。

### 判据：题面那段话是「题目设定」还是「实现手段要求」？

不要凭感觉。**用命令查**：

**三步都要跑**（只跑第 1 步会**假阴性**）：

```bash
# ① 关键词
grep -E '利用|循环|递归|不使用|实现手段|请用|for 循环|while|必须用' problem.md

# ② ★ 括号里直接写了算法名，如「（冒泡排序）」
grep -E '（[^）]{2,10}）|\([^)]{2,10}\)' problem.md

# ③ ★ 标题里带算法名，如「【例5.6】冒泡排序」
head -3 problem.md
```

- **任一步命中** ⇒ 题面在**指定实现手段** ⇒ 硬约束，必须遵守
- **三步全空** ⇒ 那段话只是**题目设定/背景描述** ⇒ **不限制解法**

| 例 | 判定 | 依据 |
|---|---|---|
| `5020`「利用 for 循环」 | 硬约束 | ① 命中 |
| `5041`「（**冒泡排序**）」 | **硬约束** | **② 命中**（① 却是 0 —— 只跑 ① 会误判）|
| `5042`「用**筛法**求」 | 硬约束 | ① 命中（`循环`/`请用` 类）|
| `5038` 服务员逐个进房间的模拟描述 | **仅题目设定** | 三步全空 ⇒ 数学法可接受 |

⚠ **本判据只是启发式，存在假阴性**（`5041` 就是）。若你对判定有疑问，
**以题面措辞与标题为准做人工判断**，并把理由写进报告 ——
不要因为「grep 没命中」就断定不限制解法。

**为什么需要这条**：描述性文字往往**读起来像要求**（「第 1 个服务员把所有的门打开，
第 2 个把 2 的倍数相反处理……」），但那是**问题的定义**，不是**算法的规定**。
把设定误读成要求，会逼着解法去写一个笨实现。

**实例**：`5020` 题面写「利用 for 循环」，Python 侧因此保留显式 `for`，未压成推导式。

## 总原则

**先取 rbook 代码模板，再按本 skill 调形**。题目用到标准算法结构（LCA、倍增、线段树、图论、DP、数学、字符串等）时，写代码前先按 [`oj-problem-workflow` 阶段 3](../oj-problem-workflow/references/stages.md) 取模板：本地 `$RBOOK2_CODE_PATH/code.yaml` 优先，读不到再走 `rbook-http`。**算法骨架与正确性以模板为准，命名与封装形式以本 skill 为准**，并裁剪掉本题用不到的辅助代码。纯输入输出题可跳过，但需记录理由。

- 使用 C++17。
- 在满足时间、空间限制的前提下，优先选择读者需要掌握的额外机制更少的实现。结构体、数组和 STL 都服务于可读性，不机械套用。
- 多个函数共享的数据可以放全局；仅在单个函数使用的数据优先留在该函数，避免无关状态互相影响。
- 只遍历元素时优先范围 for；需要下标、倒序或步长时用下标循环。普通数组与 `vector` 按规模、生命周期和算法操作选择，不强制某一种。
- 写关键中文注释（见「中文注释规则」）。
- 不把核心逻辑藏进复杂封装、lambda、模板或过度 STL 表达式里（见「硬禁用」）。
- 类型按值域选择，计算中间结果也要防溢出；必要的显式转换允许，但不能掩盖范围错误（见下一节）。
- 能现场枚举就不落地保存中间结构（见「存储选择」）。

## 类型与强制转换

按值域选类型：规模和节点编号在 `int` 范围内时用 `int`，可能较大的和、距离、乘积用 `long long`；可用 `using ll = long long;` 简化重复声明。不因为数组参与一次大整数运算，就把整个数组改成 `long long`。

计算前提升类型，不能等溢出后再赋给大类型。需要转换时优先 `static_cast`，并确认目标类型能容纳该值；避免堆叠转换。

```cpp
int width, height;
cin >> width >> height;
// 两个边长各自能放进 int，但面积可能超出 int。
long long area = static_cast<long long>(width) * height;
```

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

不要使用 C++20/23 特性、ranges、concept、模板元编程、复杂泛型工具，以及隐藏循环、类型或操作的宏（`rep(i,n)`、`all(x)`、`pb` 等）；常量用 `const` / `constexpr`。

允许含义明确的 C++17 结构化绑定，例如 `auto [u, v] = edge`。核心算法优先普通具名函数；排序等局部操作可用简单 lambda，不把状态转移或递归藏在嵌套 lambda 中。位运算用于状态集合等自然模型时允许，须交代每一位的含义；普通判断不改写成晦涩位运算。

复杂条件先命名或分步判断；分支与循环用花括号展开，多步更新分行写。详见模板中的「状态转移展开示例」。

**不要用显式栈（`Frame`、`vector<pair<int,int>>` 调用栈、手写访问阶段）模拟 DFS 递归。** DFS、Tarjan、Kosaraju、树剖、点分治这类“进入节点 → 处理 → 离开节点”的递归结构，一律直接写递归函数。

```cpp
// 不推荐：手工维护调用栈，丢失递归语义
void tarjan() {
    vector<array<int,3>> call;
    call.push_back({start, 0, 0});
    while (!call.empty()) { ... }
}

// 好：直接递归，一眼看出进/出节点的边界
void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    ...
    for (const Edge& e : g[u]) {
        if (dfn[e.to] == 0) {
            tarjan(e.to);
            if (low[e.to] < low[u]) low[u] = low[e.to];
        } else if (in_stack[e.to]) { ... }
    }
    if (low[u] == dfn[u]) { ...出栈... }
}
```

理由与边界：

- 递归深度是否安全按题目规模核算，用最深链输入加 `--stack` 实测（见 `oj-judge-and-stress`）。不要用本机 `ulimit -s` 推测，也不要因为“可能爆栈”就预防性改写。**`roj-local-judge-lite` 的栈上限与内存上限一样大**（`--memory 512` → 512 MB 栈），比本机 shell 常见的 8 MB 大一个量级以上；本机跑不过不代表评测跑不过。
- 手工拆解递归还容易漏掉“子树返回后更新父节点 `low`”“出栈时机”等与递归结构强绑定的顺序，这是实际出错点，不是风格问题。
- 只有**题目规模确定会超出栈容量**（例如深度达 $10^6$ 级）时才改用显式栈，并在文件头注明“因规模必须改为迭代”。这是例外，不是默认写法。

核心算法一律写成普通函数，不写 `auto solve = [&](){...}`：

```cpp
void solve() {
    ...
}
```

## 结构体与辅助桶

平行数组指用多个下标平行的数组记录同一个对象的字段，例如
`char node_type[MAXL]` + `ll left_son[MAXL]` + `ll right_son[MAXL]` + `char node_value[MAXL]`。
同一个对象的核心字段优先聚合成 struct 数组（需要动态开点时用动态化静态，见「存储选择」）：

```cpp
// 不推荐：拆散节点核心字段，读者要自己对应多个数组
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

辅助数据可以独立开全局桶，不要求所有通过同一个编号访问的数据都塞进结构体。例如：

```cpp
struct Node {
    int ch[26]; // 字符对应的孩子编号，0 表示不存在
    int parent;
    int weight;
};
Node node[MAXNODE];
vector<int> record_ids[MAXNODE]; // record_ids[u]：挂在节点 u 上的记录编号
vector<int> group_records[MAXGROUP]; // group_records[g]：第 g 组的记录编号
bool has_query[MAXGROUP]; // has_query[g]：第 g 组是否包含询问
```

节点结构保存树本身的信息；挂载记录、分组记录和状态标记按用途独立保存。桶要注释下标含义，避免混淆节点编号、记录编号和组编号。复用节点或组编号时，同步清空相应桶和标记。

## `auto` 规则

只需要遍历元素、不需要下标时，允许并推荐使用范围 for，避免多写一层下标访问：

```cpp
for (auto record_id : record_ids[u]) {
    // 直接处理当前记录编号
}
```

- `for (auto x : a)` 适合复制整数、编号等小对象。
- 只读遍历字符串、结构体等较大对象时，可用 `for (const auto &x : a)` 避免复制；需要修改原元素时可用 `for (auto &x : a)`。
- 需要下标、倒序或指定步长时，使用普通下标 for 循环。
- 迭代器类型过长时也允许 `auto`：

```cpp
auto it = mp.find(x);
auto it = lower_bound(a + 1, a + n + 1, x);
```

其余情况优先写明确类型；结构化绑定允许用于含义明确的字段拆分。

## STL 规则

“尽量不使用 STL”指不要滥用复杂 STL，不是完全禁用。

- 允许并推荐：`queue`、`priority_queue`、`map`、`set`、`vector`、`pair`、`sort`、`lower_bound`、`upper_bound`。
- 避免复杂嵌套容器（如 `vector<vector<pair<int, int> > >`），除非确实更清楚；按对象存序列的 `vector<vector<ll> >` 是清楚的（见「存储选择」）。
- 避免大量 `unordered_map` / `unordered_set`，除非明确需要且说明哈希风险。
- 不用 STL 算法链式写法替代清楚的循环；不用 `function` 保存递归或状态转移。
- 普通数组与 `vector` 按规模和操作选择；按编号挂载变长列表时，可以用 `vector<int> bucket[MAXN]`。

## 全局变量规则

多个函数共享的核心数据可以定义为全局变量；仅在一个函数使用的数据可以用局部 `vector` 或普通数组。数组位置按生命周期和实际栈容量判断，栈限制遵循 `AGENTS.md`，不要为了竞赛形式强制所有数据全局化。

## 存储选择：现场枚举 vs 落地保存

先问数据怎么被使用，再决定要不要存下来：

- 只被单向遍历、可以重复算出来的中间结构（候选边、合法区间里的位置、匹配对），优先现场枚举、用完即丢，不建表。
- 需要边编号、反向边、大规模多源复用、或枚举代价不可重复支付时，才落地保存（图、索引、预处理表）。

教学代码里“现场扫描序列枚举合法选择”比预建边表直观：删掉的存储越多，读者要跟踪的状态越少。

其他约定：

- 多对象序列按对象存、下标从 1 开始和题面对应，不做平铺 + 偏移数组：`vector<vector<ll> > seq; // seq[person] = 第 person 个人的序列`。
- 用简单 struct 聚合固定核心字段（询问、点对、树/图节点），辅助桶可以独立定义（见「结构体与辅助桶」）；struct 只放数据，不放算法逻辑：

```cpp
struct Query {
    ll r;
    ll v;
};
```

- 元素个数事先不确定、需要“开点”的结构（表达式树、Trie、可持久化结构、逐步加点的图）用动态化静态：struct 数组 + `node_cnt` 当分配指针，`new_node()` 负责开点，节点池不用逐节点指针或 `new` 分配；辅助列表仍可使用 `vector`：

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

动态化静态的好处：写法是静态数组（好调、好控内存），用法像指针树（按编号引用 `node[u].left`），便于集中管理节点内存，不用逐节点分配和释放；递归调用是否会爆栈仍取决于深度和栈空间。完整模板见 [`references/code-templates.md`](references/code-templates.md)。

## Trie、记录列表与 DFS

- 字符集固定且内存允许时，普通 Trie 优先用 `int ch[26]`（按实际字符集大小调整）。先核算节点数与每节点大小，确有空间压力或字符集稀疏时，再用 `child/sibling` 等稀疏表示。
- 挂载记录优先用 `vector<int>` 和 `push_back()`，遍历用范围 for；不要默认引入 `head、next、left_next` 手写链表。只有空间、性能或操作需求确有依据时才改用链式存储。
- DFS 直接递归，清楚表达“进入节点 → 访问孩子 → 离开节点”；**不要用显式栈或 `Frame` 模拟递归**，见「硬禁用」。递归深度是否安全按实际规模核算，用最深链输入加 `--stack` 实测（见 `oj-judge-and-stress`）。
- 节点池为全局数组不等于递归调用不会爆栈；需要核算的是**递归深度 × 单帧大小**，不是节点池大小。

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
- 核心枚举写成普通函数与循环，不藏进复杂 lambda 或 STL 表达式。

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

允许 `i/j`、题目规模 `n/m/k` 和 `dp`、`dfs`、`ans`、`dist`、`vis`、边端点 `u/v` 等通用记法。核心状态不能仅因习惯就叫 `f/g/a/b`；本题特有含义用 `prefix_sum`、`max_reach` 等短词表达，并注明状态及下标含义。

- 不要使用和 std 标识符冲突的名字，例如 `next`、`prev`、`div`、`y0/y1/j0/j1`；`next` 改成 `next_last`、`nxt` 这类表达含义的名字。
- 变量名表达它在题中的含义（`reachable`、`last_person`、`right_end`），不用 `a1`、`tmp2` 这类读者对不上题解的名字。
- **变量名不准带 `_arr` 后缀**（`_array`、`Arr` 同理）。数组身份由声明处的 `[]` 和注释表达，名字只写含义：`depth_arr` → `depth`、`dist_arr` → `dist`、`parent_arr` → `parent`。后缀不提供新信息，只让名字变长，还会在改动存储方式时变成误导。

## 中文注释规则

必须注释：核心全局数组的含义、核心函数的作用、DP 状态定义和转移来源、贪心选择标准、图论边/节点/队列/堆的含义、容易错的边界处理、`brute.cpp` 为什么只适合小数据。不要注释 `cin >> n`、`i++`、`q.push()` 这类显然操作。

```cpp
int dp[MAXN]; // dp[i] 表示以第 i 个数结尾的最长上升子序列长度（好）
// 判断容量 mid 是否足够完成所有任务。（好）
i++; // i 加一（坏）
```

## 完成代码后自检表

写完 `main.cpp` / `brute.cpp` 后逐条自检（审查已有代码时也按这张表过一遍），每条给出结论：
「必须」级不合格必须改掉；「建议」级尽量改，确实不用改时说明原因。

自检表不含“怎么跑”。样例、测试点、对拍、时空与栈限制的验证一律用 `roj-local-judge`，见 `oj-judge-and-stress`；不要自写脚本或手量本机 `ulimit`。

| # | 级别 | 自检项 | 合格标准 | 不合格时的改法 |
|:-:|:---:|---|---|---|
| 1 | 必须 | 禁用特性 | 无 C++20/23、ranges、炫技模板或隐藏核心逻辑的复杂 lambda；**无显式栈模拟 DFS 递归** | 改成普通函数和普通循环；DFS/Tarjan 直接写递归 |
| 2 | 建议 | 结构体与辅助桶 | 核心字段适当聚合；独立桶的下标含义清楚，编号复用时同步清理 | 聚合零散核心字段；辅助记录和标记可独立开桶 |
| 3 | 必须 | 核心逻辑位置 | 核心逻辑是普通函数，没有藏进复杂 class/template/function | 拆成 `solve()` / `dfs()` 等普通函数 |
| 4 | 必须 | 程序完整性 | 有 `main()`，输入输出格式和题面一致；`brute.cpp` 和 `main.cpp` 输入输出一致 | 补齐 `main()`、对齐输入输出格式 |
| 5 | 必须 | 类型与范围 | 存储和中间计算都不会溢出，必要转换的目标范围安全 | 按值域选类型，在运算前提升类型 |
| 6 | 建议 | 数组位置 | 数据位置符合共享范围与生命周期，含义有注释 | 调整作用域并补注释 |
| 7 | 建议 | 存储与 STL | 能用数组的没用复杂嵌套 STL；图论代码有清楚的 `add_edge()` 或邻接结构说明 | 改成数组 / 补 `add_edge()` |
| 8 | 建议 | `auto` 用量 | 范围 for、长类型迭代器可用 `auto`；其余情况优先明确类型 | 按遍历需求选择范围 for 或下标循环，避免大对象无谓复制 |
| 9 | 必须 | 命名 | 变量名表达题意，不和 std 标识符冲突（如 `next`），也没有 `_arr` / `_array` / `Arr` 后缀 | 改成表达含义的名字，去掉类型后缀 |
| 10 | 建议 | 存储选择 | 可用固定下标表达的状态没用 `map` + 键编码；可现场枚举的中间结构没落地建表 | 改数组下标 / 改现场枚举 |
| 11 | 必须 | 中文注释 | 核心数组、核心函数、状态定义、易错边界都有中文注释 | 按「中文注释规则」补注释 |
| 12 | 建议 | Trie、列表与 DFS | 约束允许时用孩子数组、vector 记录列表和直接递归；**DFS/Tarjan 没有手写调用栈** | 去掉没有必要的稀疏链接、手写记录链表和模拟递归状态 |

额外核对：复杂转移和判断是否分步展开，学生能否把题解中的状态与代码变量对应起来；若只能靠逐行解释才能看懂，先调整命名和结构。不得仅因代码短、用了 STL 或通过评测就判可读性合格。

以下写法本身不算问题，仍须检查实际逻辑：

- `priority_queue`（Dijkstra / Huffman / 堆）、`queue`（BFS）、`map` / `set`（有序映射）、`vector<int> g[MAXN]`（简单树题）。
- `Node` 保存核心字段，`record_ids[u]`、`group_records[g]`、`has_query[g]` 等辅助桶独立定义；内存允许时使用 `ch[26]`，栈空间允许时直接递归 DFS。
- 使用 `for (auto x : a)` 遍历小对象，或按用途使用 `const auto &x` / `auto &x`；迭代器类型太长时使用 `auto it = ...`。
- 数据按值域使用 `int` / `long long` / `char`；用简单 struct 聚合询问、点对、节点；树/图节点用动态化静态（struct 数组 + `node_cnt` 开点）；记忆化只清理实际用到的数组范围并有注释。

## 与题解写作配合

当 `oj-problem-analysis-writer` 创建或修改 `main.cpp` / `brute.cpp` 时，必须遵守本 skill。仓库若提供 `python3 scripts/problem-analysis-tools/check_cpp_style.py <file>`，生成或审查后应运行它；目前依赖人工/AI 按上述规则审查。
