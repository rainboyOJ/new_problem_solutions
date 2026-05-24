---
oj: "luogu"
problem_id: "P1168"
title: "中位数"
date: 2026-01-01 12:26
toc: true
tags: ["堆"]
desc: ""
source: https://www.luogu.com.cn/problem/P1168
---

[[TOC]]

这是一个非常经典的**对顶堆**（Dual Heap）应用题。

## 核心思路：对顶堆 (The "Sandglass" Pattern)

要动态求中位数，我们可以把所有读入的数分成两部分：

1. **较小的一半**：放在一个 **大根堆**（Max Heap）里，堆顶是这部分最大的数（也就是中间位置偏左的那个）。
2. **较大的一半**：放在一个 **小根堆**（Min Heap）里，堆顶是这部分最小的数（也就是中间位置偏右的那个）。

中位数在哪里？

题目要求针对奇数个数字求中位数。我们可以维护这样一个性质：大根堆的元素个数比小根堆多 1 个。

这样，大根堆的堆顶就是整个序列的中位数。

## 算法流程

1. 定义两个堆：
   - `down`：大根堆（存较小的一半数）。
   - `up`：小根堆（存较大的一半数）。
2. 读入第一个数，直接放入 `down`，并输出 `down.top()`。
3. 从第 2 个数开始，循环读入 `x`：
   - 如果 `x` 比 `down` 的堆顶大，说明它属于“较大的一半”，放入 `up`。
   - 否则，说明它属于“较小的一半”，放入 `down`。
4. **维护平衡**（关键）：
   - 插入后，堆的大小可能会失衡。我们要保证 `down` 的大小只比 `up` 大 1（在总数为奇数时）或者相等（总数为偶数时）。
   - 如果 `down` 里的数太多（`down.size() > up.size() + 1`）：把 `down` 的堆顶移到 `up`。
   - 如果 `up` 里的数太多（`up.size() > down.size()`）：把 `up` 的堆顶移到 `down`。
5. 每当读入的总个数是奇数时，输出 `down.top()`。

## C++ 代码实现


```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <functional> // 为了使用 greater<int>

using namespace std;

int main() {
    // 1. IO 提速
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // 大根堆：存储较小的一半数据 (top 是这半边最大的)
    priority_queue<int> down;
    // 小根堆：存储较大的一半数据 (top 是这半边最小的)
    priority_queue<int, vector<int>, greater<int>> up;

    // 先读入第一个数
    int x;
    cin >> x;
    down.push(x);
    cout << x << "\n"; // 第1个数的中位数就是它自己

    // 从第2个数开始处理
    for (int i = 2; i <= n; ++i) {
        cin >> x;

        // 2. 决定插入哪个堆
        // 如果比当前中位数大，放入右边(up)，否则放入左边(down)
        if (x > down.top()) {
            up.push(x);
        } else {
            down.push(x);
        }

        // 3. 动态调整，保持平衡
        // 我们约定：中位数永远在 down 的堆顶
        // 所以 down 的大小必须等于 up 的大小，或者比 up 大 1

        // 情况A: down 太大了，把最大的扔给 up
        if (down.size() > up.size() + 1) {
            up.push(down.top());
            down.pop();
        }
        // 情况B: up 太大了 (比 down 还大)，把最小的扔给 down
        if (up.size() > down.size()) {
            down.push(up.top());
            up.pop();
        }

        // 4. 如果是奇数项，输出中位数
        if (i % 2 == 1) {
            cout << down.top() << "\n";
        }
    }

    return 0;
}
```

## 代码解析

1. **数据结构**：
   - `priority_queue<int> down;` 是默认的大根堆。
   - `priority_queue<int, vector<int>, greater<int>> up;` 是小根堆。
2. **平衡逻辑**：
   - 我们的目标是让 `down` 负责存储序列排序后 `[1 ... mid]` 的元素，`up` 负责 `[mid+1 ... n]`。
   - 当总数为奇数时，`down` 应该有 $(N+1)/2$ 个元素，`up` 有 $(N-1)/2$ 个元素。
   - 当总数为偶数时，两边个数相等（或者 `down` 比 `up` 多 1 也可以，取决于具体实现，这里我们选择只要是偶数步，两边数量相等，奇数步 `down` 多 1）。
3. **时间复杂度**：
   - 每次插入操作耗时 $O(\log N)$。
   - 总共 $N$ 次操作，总复杂度 $O(N \log N)$。
   - $N=10^5$，计算量约为 $1.7 \times 10^6$，远低于 C++ 的 1秒处理上限（约 $10^8$），可以轻松通过。

## 为什么不每次排序？

如果每读入一个奇数项就 `sort` 一次数组，时间复杂度是 $O(N^2 \log N)$ 或 $O(N^2)$，对于 $N=100000$ 的数据，运算次数会达到 $10^{10}$ 级别，绝对会超时（TLE）。使用对顶堆可以将每次查询优化到对数级别。
