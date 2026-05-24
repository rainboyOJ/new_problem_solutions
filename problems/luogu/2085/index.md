---
oj: "luogu"
problem_id: "P2085"
title: "最小函数值"
date: 2026-01-01 12:30
toc: true
tags: ["归并排序","堆"]
desc: "多路归并"
source: https://www.luogu.com.cn/problem/P2085
---

[[TOC]]

这道题目是典型的 **“多路归并”** 问题，可以使用 **小根堆 (Min-Heap)** 完美解决。

## 核心思路

1. 函数单调性：

   题目给出的函数是 $F_i(x)=A_ix^2+B_ix+C_i$。由于 $A_i, B_i, C_i \ge 0$ 且 $A_i \ge 1$，当 $x \ge 1$ 时，这些函数都是单调递增的。

   这意味着对于任意第 $i$ 个函数：$F_i(1) < F_i(2) < F_i(3) < \dots$

2. 问题转化：

   这就相当于我们有 $n$ 个有序的数列，我们需要从这 $n$ 个数列中找出合并后最小的 $m$ 个数。

   - 数列 1: $F_1(1), F_1(2), F_1(3), \dots$
   - 数列 2: $F_2(1), F_2(2), F_2(3), \dots$
   - ...
   - 数列 $n$: $F_n(1), F_n(2), F_n(3), \dots$

3. **算法流程**：

   - 首先，把所有 $n$ 个函数的第一个值（即 $x=1$ 时的值）放入一个小根堆中。
   - 每次从小根堆中取出堆顶元素（当前的最小值），输出它。
   - 如果这个最小值来自于第 $i$ 个函数，且刚才的自变量是 $x$，那么就算出该函数的下一个值 $F_i(x+1)$ 并放入堆中。
   - 重复上述步骤 $m$ 次。

------

## C++ 代码实现



```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 用于存储函数系数
struct Func {
    int a, b, c;
    // 计算函数值 F(x)
    int eval(int x) const {
        return a * x * x + b * x + c;
    }
} funcs[10005];

// 堆中的节点结构
struct Node {
    int val;  // 当前函数值
    int id;   // 属于第几个函数 (1~n)
    int x;    // 当前的自变量 x

    // 优先队列默认是大根堆（大的在堆顶）
    // 我们重载 < 运算符，让 value 大的反而被视为“小”，
    // 这样 value 小的就会浮到堆顶，变相实现小根堆。
    bool operator<(const Node& other) const {
        return val > other.val; 
    }
};

int main() {
    // IO 提速
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 定义优先队列 (不需要写 greater，因为我们在 struct 里反向重载了 <)
    priority_queue<Node> pq;

    // 1. 读入数据并初始化堆
    for (int i = 1; i <= n; ++i) {
        cin >> funcs[i].a >> funcs[i].b >> funcs[i].c;
        // 将每个函数的第一个值 (x=1) 入堆
        pq.push({funcs[i].eval(1), i, 1});
    }

    // 2. 取出前 m 个最小值
    for (int k = 0; k < m; ++k) {
        // 取出堆顶（当前最小）
        Node top = pq.top();
        pq.pop();

        // 输出
        cout << top.val << " ";

        // 将该函数对应的下一个 x 的值入堆
        // 下一个自变量是 top.x + 1
        int next_x = top.x + 1;
        int next_val = funcs[top.id].eval(next_x);
        
        pq.push({next_val, top.id, next_x});
    }

    return 0;
}
```

------

## 代码与算法详解

### 1. 结构体设计

我们定义了一个 `Node` 结构体来存储放入堆中的元素：

- `val`: 具体的函数值（用于排序）。
- `id`: 记录这个值是由第几个函数产生的（用于回溯系数）。
- `x`: 记录这个值是用什么自变量计算出来的（用于推算下一个 $x+1$）。

### 2. 小根堆的实现技巧

C++ STL 的 `priority_queue` 默认是**大根堆**。为了让它变成**小根堆**，通常有两种写法：

1. 使用 `priority_queue<Type, vector<Type>, greater<Type>>`。

2. **（本题做法）** 在结构体内部重载 `<` 运算符，将逻辑反过来：

   C++

   ```
   bool operator<(const Node& other) const {
       return val > other.val; // 这里的 > 让值越小的优先级越高
   }
   ```

   这样写代码比较简洁，不需要引入 `functional` 头文件，也不用写很长的模板参数。

### 3. 为什么是 $x+1$？

因为函数是单调递增的。

假设堆顶弹出了第 3 个函数的 $F_3(1)$，那么第 3 个函数可能提供的下一个最小候选值一定是 $F_3(2)$。我们不需要把 $F_3(3), F_3(4)...$ 一次性全放进去，只需要按需放入“下一位候选人”。

### 4. 时间复杂度

- **初始化堆**：插入 $n$ 个元素，复杂度 $O(n)$。
- **循环 $m$ 次**：每次进行一次 `pop` 和一次 `push`，堆的操作复杂度是 $O(\log n)$。总复杂度 $O(m \log n)$。
- **数据规模**：$n, m \le 10000$，总计算量约为 $10^5$ 级别，远低于时间限制，可以瞬间完成。

### 5. 数据范围注意事项

- $A_i \le 10, B_i \le 100, C_i \le 10000$。
- 在最坏情况下（只取某一个函数的值），$x$ 可能会达到 $m=10000$。
- 函数值最大约为 $10 \times 10000^2 \approx 10^9$，正好在 `int` 范围内（`int` 最大约 $2.1 \times 10^9$），所以使用 `int` 是安全的，不需要 `long long`。
