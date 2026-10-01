# C++ 代码模板

`oj-cpp-competitive-style` 的完整代码模板。写完整文件或复制骨架时读取本文件；判定规则见 [SKILL.md](../SKILL.md)。模板侧重结构，类型按 SKILL.md「类型与强制转换」选择。

## 普通题骨架

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

## 链式前向星

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

遍历：

```cpp
for (int i = head[u]; i != 0; i = nxt[i]) {
    int v = to[i];
    ...
}
```

## 01 序列递归（选/不选）

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

教学重点：长度为 `n` 的 01 序列一共有 `2^n` 种，每一种都代表一种完整方案。合法性检查、答案统计放在叶子节点，逻辑最直接。

## 多分支选择序列

结构和 01 序列完全一致，只把每层的选项换成 `0..k`：

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
