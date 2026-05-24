---
oj: "luogu"
problem_id: "P2776"
title: "[SDOI2007] 小组队列"
date: 2025-12-26 21:54
toc: true
tags: ["队列"]
desc: ""
source: https://www.luogu.com.cn/problem/P2776
pre:
 - luogu,P1314
book:
 - bookid
---

[[TOC]]



# 题解 P2776 【小组队列】(Queue 嵌套)

## 1. 题目简述
有 $n$ 个元素，每个元素属于 $m$ 个小组中的某一个。
有一个队列，支持 `push` 和 `pop` 操作。
* **入队规则 (`push x`)**：如果队列中已经有 `x` 所属小组的成员，`x` 会直接插队到该小组所有成员的最后面（但比其他小组靠前）；如果没有该小组成员，则排到整个大队伍的最后。
* **出队规则 (`pop`)**：正常的队头出队。

**数据范围：** $n, T \le 10^5, m \le 300$。

## 2. 思路分析

### 核心逻辑
这就好比食堂排队打饭。
1.  **宏观上看**：队列里排的是**一个个小组**，而不是散乱的人。先来的小组先打饭。
2.  **微观上看**：每个小组内部，成员也是按先后顺序排队的。

### 数据结构设计
我们需要两层结构来维护这个逻辑：

1.  **主队列 (`q_team`)**：存放**小组的编号 (Group ID)**。
    * 用来记录哪个小组先来，哪个小组后来。
    * 只有当某个小组的第一名成员到达，且该小组目前不在队列中时，才把该小组的 ID 入队。
2.  **子队列数组 (`q_member[groupID]`)**：
    * 这是一个队列数组，`q_member[k]` 存储第 $k$ 小组内的所有成员。
    * 用来维护小组内部的先后顺序。
3.  **标记数组 (`in_queue[groupID]`)**：
    * 记录第 $k$ 小组当前是否有人在主队列中。

### 操作流程

#### `push x`
1.  查询 $x$ 所属的小组编号 $gid$。
2.  检查 `in_queue[gid]`：
    * 如果为 `false`（该组目前没人在排队）：将 $gid$ 加入主队列 `q_team`，并标记 `in_queue[gid] = true`。
    * 如果为 `true`：说明该组已经有人在排队了，不需要动主队列。
3.  直接将 $x$ 加入对应的子队列 `q_member[gid]`。

#### `pop`
1.  查看主队列队头的小组编号 $gid = q\_team.front()$。
2.  输出子队列 `q_member[gid]` 的队头元素。
3.  将该元素从子队列 `q_member[gid]` 弹出。
4.  **关键判断**：如果弹出后，子队列 `q_member[gid]` 变为空：
    * 说明该小组没人了。
    * 将 $gid$ 从主队列 `q_team` 中弹出。
    * 标记 `in_queue[gid] = false`。

### 复杂度分析
* 每次 `push` 涉及哈希/数组查找和队列操作，均为 $O(1)$。
* 每次 `pop` 涉及队列操作，均为 $O(1)$。
* 总时间复杂度 $O(T)$，对于 $10^5$ 的数据量轻松 AC。

## 3. 图解推演
假设小组关系：`0->Group A`, `1->Group A`, `2->Group B`。
当前队列空。

1.  `push 0` (Group A):
    * Group A 不在队中 $\rightarrow$ 主队列: `[A]`
    * 子队列 A: `[0]`
2.  `push 2` (Group B):
    * Group B 不在队中 $\rightarrow$ 主队列: `[A, B]`
    * 子队列 B: `[2]`
3.  `push 1` (Group A):
    * Group A 已在队中 $\rightarrow$ 主队列不变: `[A, B]`
    * 子队列 A: `[0, 1]`

此时实际的出队顺序逻辑上是：先处理 A 组所有成员 (0, 1)，再处理 B 组成员 (2)。

## 4. AC 代码

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 100005; // 元素最大数量
const int MAXM = 305;    // 小组最大数量

// 映射：元素 ID -> 小组 ID
int belong_to[MAXN];

// 子队列：q[i] 存储第 i 小组的成员
queue<int> q_member[MAXM];

// 主队列：存储小组的 ID
queue<int> q_team;

// 标记：is_in_queue[i] 表示第 i 小组是否已经在主队列中
bool is_in_queue[MAXM];

int main() {
    // 优化 I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 读入每个元素所属的小组
    // 注意：题目中元素编号 0~n-1，小组编号 0~m-1
    for (int i = 0; i < n; ++i) {
        cin >> belong_to[i];
    }

    int t;
    cin >> t;
    while (t--) {
        string op;
        cin >> op;

        if (op == "push") {
            int x;
            cin >> x;
            int team_id = belong_to[x];

            // 如果这个小组目前不在大队伍里
            if (!is_in_queue[team_id]) {
                q_team.push(team_id);   // 小组ID入队
                is_in_queue[team_id] = true;
            }
            
            // 无论如何，元素都要进入自己小组的小队伍
            q_member[team_id].push(x);

        } else if (op == "pop") {
            // 找到排在最前面的小组
            int first_team = q_team.front();
            
            // 输出该小组排在最前面的成员
            cout << q_member[first_team].front() << "\n";
            q_member[first_team].pop();

            // 如果这个小组的人都走光了
            if (q_member[first_team].empty()) {
                q_team.pop(); // 小组ID出队
                is_in_queue[first_team] = false;
            }
        }
    }

    return 0;
}
```

## 5. 总结
* **模型识别**：遇到“插队”、“同类聚合”的排队问题，优先考虑 **双层队列**（主队列管理类别，子队列管理具体元素）。
* **STL使用**：C++ STL 的 `std::queue` 非常方便，配合数组 `queue<int> q[MAXM]` 即可实现子队列数组。
* **状态维护**：不要忘记用一个 `bool` 数组维护小组是否在队列中的状态，这是避免重复插入小组 ID 的关键。

