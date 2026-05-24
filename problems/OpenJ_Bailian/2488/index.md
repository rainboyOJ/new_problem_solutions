---
oj: "OpenJ_Bailian"
problem_id: "2488"
title: "A Knight&#39;s Journey"
date: 2026-01-20 19:54
toc: true
tags: ["dfs"]
desc: ""
source: https://vjudge.net/problem/OpenJ_Bailian-2488#author=GPT_zh
---

[[TOC]]

这道题目是一个经典的**骑士巡逻问题（Knight's Tour Problem）的变体。它的核心要求是：在给定的 $p \times q$ 棋盘上，寻找一条路径，使骑士恰好访问每个方格一次，并要求输出字典序最小**的路径。

> 题目的难点在于 字典序, 你自己画个图就知道了

------

### 1. 核心难点解析

- 字典序最小（Lexicographically Smallest）：

  这是本题的关键。棋盘的坐标表示为“字母+数字”（如 A1, B2）。字典序比较时，先比字母，再比数字。

  - **起点选择**：为了让路径字典序最小，**必须从 A1 开始**。因为任何从 B1 或 A2 开始的路径，其首字符在字典序上都大于 A1。
  - **移动顺序**：在 DFS（深度优先搜索）过程中，骑士有 8 个可选方向。为了保证找到的第一条完整路径就是字典序最小的，我们需要按照特定的顺序尝试这 8 个方向。

### 2. 贪心策略：确定 8 个方向的顺序

假设当前坐标为 $(col, row)$，其中 $col$ 代表字母（A, B...），$row$ 代表数字（1, 2...）。我们需要按照 $col$ 增量优先、再看 $row$ 增量的原则排序：

1. $col-2, row-1$ (例如：从 C3 移动到 A2)
2. $col-2, row+1$
3. $col-1, row-2$
4. $col-1, row+2$
5. $col+1, row-2$
6. $col+1, row+2$
7. $col+2, row-1$
8. $col+2, row+1$

**严格遵守这个顺序进行 DFS，找到的第一组解即为最优解。**

------

### 3. 算法步骤 (DFS + 回溯)

1. **初始化**：
   - 读取测试用例数量 $n$。
   - 对于每个用例，创建一个 $p \times q$ 的标记数组 `visited`，记录方格是否走过。
   - 设定总步数目标为 $p \times q$。
2. **搜索 (DFS)**：
   - 从 `A1` (即坐标 `(1, 1)`) 开始搜索。
   - 标记当前格为已访问，并存入路径序列。
   - **递归基准**：如果路径长度等于 $p \times q$，说明已遍历全图，返回成功。
   - **尝试移动**：按照上述 8 个方向的顺序依次尝试。
   - **检查合法性**：目标格必须在棋盘内且未被访问。
   - **回溯**：如果某个分支走不通，撤销标记，尝试下一个方向。
3. **输出**：
   - 如果 DFS 找到解，输出路径。
   - 如果 DFS 遍历完所有可能仍未找到解，输出 `impossible`。

------

### 4. 逻辑实现伪代码


```cpp
// 8个方向的偏移量 (注意顺序：先看col位移，再看row位移)
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool dfs(int x, int y, int step) {
    if (step == p * q) return true; // 找齐了

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 1 && nx <= q && ny >= 1 && ny <= p && !vis[ny][nx]) {
            vis[ny][nx] = true;
            path[step] = {nx, ny}; // 记录路径
            if (dfs(nx, ny, step + 1)) return true;
            vis[ny][nx] = false; // 回溯
        }
    }
    return false;
}
```

------

### 5. 注意事项

- **行列混淆**：题目中 $p$ 是数字（行），$q$ 是字母（列）。通常我们习惯 $(x, y)$，这里建议明确 $x$ 对应列（A, B, C...），$y$ 对应行（1, 2, 3...）。
- **棋盘大小**：$p \times q \le 26$ 是个很小的范围，这意味着简单的 DFS 不会超时，不需要使用复杂的优化算法（如 Warnsdorff's rule）。
- **不可能的情况**：某些尺寸的棋盘（如 $3 \times 3$, $2 \times 3$ 等）是无法完成全巡逻的，DFS 会自然返回失败。

## 代码

@include-code(./1.cpp,cpp)

@include-code(./1.py,python)


