---
oj: "luogu"
problem_id: "P3378"
title: "【模板】堆"
date: 2026-01-01 12:16
toc: true
tags: ["模板题"]
desc: ""
source: https://www.luogu.com.cn/problem/P3378
---

[[TOC]]

这是一个非常经典的利用 **堆 (Heap)** 数据结构的问题。在 C++ 中，STL 提供了 `std::priority_queue`（优先队列），它的底层实现通常就是堆。

以下是使用 C++ `priority_queue` 解决该问题的完整代码及详细解析。

### 使用STL 代码

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <functional> // 包含 greater<int>

using namespace std;

int main() {
    // 1. IO 提速
    // 数据规模 n <= 10^6，输入输出量很大，必须解除 C++ 标准流与 C 标准流的绑定
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 2. 定义小根堆
    // 默认 priority_queue 是大根堆（大的在堆顶）
    // 加上 vector<int> 和 greater<int> 参数将其变为小根堆（小的在堆顶）
    priority_queue<int, vector<int>, greater<int>> pq;

    int n;
    if (!(cin >> n)) return 0; // 读取操作次数

    while (n--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x;
            cin >> x;
            pq.push(x); // 操作1: 加入元素 O(log N)
        } 
        else if (op == 2) {
            // 操作2: 输出最小数
            // 小根堆的堆顶 pq.top() 即为最小值 O(1)
            cout << pq.top() << "\n"; 
        } 
        else if (op == 3) {
            // 操作3: 删除最小数
            // 删除堆顶元素 O(log N)
            pq.pop(); 
        }
    }

    return 0;
}
```

## 手写堆


```cpp
#include <iostream>
#include <vector>
#include <algorithm> // 包含 swap

using namespace std;

// 泛型小根堆 struct
template <typename T>
struct MinHeap {
    // 使用 vector 省去手动管理数组大小的麻烦
    vector<T> h;

    // 构造函数：初始化塞入一个占位符，保证下标从 1 开始
    MinHeap() {
        h.push_back(T()); 
    }

    // 【核心 1：上浮】
    // 只要比爸爸小，就跟爸爸换位置
    void up(int u) {
        while (u > 1 && h[u] < h[u / 2]) {
            swap(h[u], h[u / 2]);
            u /= 2;
        }
    }

    // 【核心 2：下沉】
    // 找出 (自己, 左孩子, 右孩子) 里最小的，只要最小的不是自己，就交换下去
    void down(int u) {
        int t = u;             // t 代表“最小值的下标”
        int left = u * 2;      // 左孩子
        int right = u * 2 + 1; // 右孩子

        // 如果左孩子存在，且比当前最小值还小，更新 t
        if (left < h.size() && h[left] < h[t]) t = left;
        // 如果右孩子存在，且比当前最小值还小，更新 t
        if (right < h.size() && h[right] < h[t]) t = right;

        // 如果最小值不是自己，说明需要交换并继续下沉
        if (t != u) {
            swap(h[u], h[t]);
            down(t); // 递归下沉
        }
    }

    // --- 用户接口 ---

    // 插入 x
    void push(T x) {
        h.push_back(x);      // 1. 放到数组末尾
        up(h.size() - 1);    // 2. 上浮到正确位置
    }

    // 删除堆顶
    void pop() {
        if (size() == 0) return;
        swap(h[1], h.back()); // 1. 拿末尾元素覆盖堆顶
        h.pop_back();         // 2. 删除末尾
        if (size() > 0) {     // 3. 堆顶下沉
            down(1);
        }
    }

    // 获取堆顶
    T top() {
        return h[1];
    }

    // 获取元素个数
    int size() {
        return h.size() - 1; // 减去那个占位符
    }
    
    bool empty() {
        return size() == 0;
    }
};

// --- 主程序 ---
int main() {
    // 1. IO 优化
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // 2. 实例化 struct (int 类型)
    MinHeap<int> heap;

    while (n--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            heap.push(x);
        } else if (op == 2) {
            cout << heap.top() << "\n";
        } else if (op == 3) {
            heap.pop();
        }
    }
    return 0;
}
```
