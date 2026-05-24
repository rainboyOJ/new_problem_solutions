---
oj: "HDU"
problem_id: "5124"
title: "lines"
date: 2026-01-02 13:38
toc: true
tags: ["扫描线","离散化","差分"]
desc: "通过这个题目学习扫描线思想"
source: https://vjudge.net/problem/HDU-5124#author=DeepSeek_zh
---

[[TOC]]

## 题目解析

> 这个题目的本质是: 区间加, 然后求最大单点值, 可以用桶了解决(暴力), 使用 差分优化区间加, 在使用离散化优化 数值大的问题

准确地抓住了这道题目的三个核心要素：

1. **问题的本质**：这就是典型的“求最大重叠区间数”问题，也就是寻找被覆盖次数最多的那个点。
2. **核心算法**：利用**差分数组（Difference Array）**的思想，将区间修改的操作复杂度从 $O(L)$ 降为 $O(1)$。
3. **优化手段**：由于坐标范围 $10^9$ 太大，无法直接开数组，所以必须使用**离散化（Discretization）**来把大坐标映射为紧凑的小整数。

下面我按照你提供的思路，整理了一份详细的题目解析和对应的 C++ 代码。

------

### 题目解析：最大重叠区间问题

#### 1. 朴素思路与瓶颈

如果坐标范围很小（比如 $X, Y \le 1000$），我们可以开一个大数组 `count[]`，对于每个区间 $[L, R]$，用循环把 `count[L]` 到 `count[R]` 都加 1。最后遍历数组找最大值。

**瓶颈**：

- **空间问题**：题目中坐标高达 $10^9$，内存存不下这么大的数组。
- **时间问题**：如果 $N=10^5$，每个区间都很长，暴力循环更新会超时。

#### 2. 优化一：差分思想

为了避免循环更新区间，我们利用差分的性质。

对于区间 $[L, R]$ 的增加操作，我们只需要做两步：

- 在点 $L$ 处 `+1`（表示从这里开始，覆盖层数增加）。
- 在点 $R+1$ 处 `-1`（表示过了 $R$ 之后，覆盖层数减少，恢复原状）。

最后，对差分数组做**前缀和**，就能得到每个点的实际覆盖次数。

#### 3. 优化二：离散化

因为我们只关心每个区间的“端点” ($L$ 和 $R+1$)，而实际上 $N$ 只有 $10^5$。这意味着最多只有 $2 \times 10^5$ 个关键坐标。

我们可以将所有出现过的 $L$ 和 $R+1$ 收集起来，排序并去重，建立一个映射关系（例如：$1 \to 1, 500 \to 2, 10000 \to 3$）。

#### 4. 算法流程

1. **收集端点**：对于每个输入区间 $[X_i, Y_i]$，将 $X_i$ 和 $Y_i + 1$ 加入到一个列表中。
2. **离散化**：对列表进行排序（Sort）和去重（Unique），得到所有有效的关键坐标。
3. **构建差分数组**：利用 `lower_bound` 函数（二分查找）找到原坐标在离散化数组中的下标（Rank）。在 `diff[rank(X_i)]` 处加 1，在 `diff[rank(Y_i + 1)]` 处减 1。
4. **扫描求最大值**：从左到右遍历差分数组，计算前缀和（即当前重叠层数），维护一个 `max_overlap` 变量记录最大值。

------

### C++ 代码实现

这里提供一份标准的基于“离散化 + 差分数组”的代码。

C++

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 用于离散化的辅助函数：返回 x 在 nums 中的下标（从0开始）
int get_id(const vector<int>& nums, int x) {
    // lower_bound 返回第一个大于等于 x 的迭代器
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

void solve() {
    int N;
    if (!(cin >> N)) return;

    // 存储所有的区间
    vector<pair<int, int>> segments(N);
    // 存储所有需要离散化的坐标点 (L 和 R+1)
    vector<int> coords;

    for (int i = 0; i < N; ++i) {
        cin >> segments[i].first >> segments[i].second;
        coords.push_back(segments[i].first);
        // 注意：差分是在 R+1 的位置减 1
        coords.push_back(segments[i].second + 1);
    }

    // 1. 离散化处理
    // 排序
    sort(coords.begin(), coords.end());
    // 去重 unique 返回去重后末尾的迭代器，erase 删除多余部分
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    // 2. 构建差分数组
    // 差分数组的大小等于去重后的坐标数量
    vector<int> diff(coords.size() + 1, 0);

    for (int i = 0; i < N; ++i) {
        // 找到 L 对应的离散化下标
        int l_idx = get_id(coords, segments[i].first);
        // 找到 R+1 对应的离散化下标
        int r_idx = get_id(coords, segments[i].second + 1);

        diff[l_idx]++;   // 区间开始，计数+1
        diff[r_idx]--;   // 区间结束的下一位，计数-1
    }

    // 3. 求前缀和并找最大值
    int max_overlap = 0;
    int current_overlap = 0;
    
    // 只需要遍历到 coords.size() 即可
    for (int i = 0; i < coords.size(); ++i) {
        current_overlap += diff[i];
        if (current_overlap > max_overlap) {
            max_overlap = current_overlap;
        }
    }

    cout << max_overlap << endl;
}

int main() {
    // 优化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
```

### 另一种更简洁的写法（扫描线思想）

其实，"离散化+差分"在实现上有一个更简单的变体，通常被称为**扫描线（Sweep Line）**。我们不需要显式地去重和查找下标，只需要把所有“事件”存下来排序即可。这也是竞赛中更常用的写法。

- 把区间 $[L, R]$ 看作两个事件：
  - 在 $L$ 处发生 `+1` 事件。
  - 在 $R+1$ 处发生 `-1` 事件。
- 把所有事件按坐标排序，坐标相同时，先处理 `+1` 还是 `-1` 都可以（对于求最大值，通常不影响，但在某些边界条件下要注意）。



### 什么是扫描线思想



> 我的话
>
> 扫描线思想: 想象 有一根线 在数轴上移动, 会发生三个事件
>
> 1. 保持
> 2. +1 ,区间的开头处
> 3. -1 区间的结尾+1处
>
> 我们略过 "保持的事件", 每次到达一个点,计算完这个点的所有事件后,可以得到,得到几个值x, 答案就是x的最大值,



上面描述了**扫描线（Sweep Line）**算法最精髓的“事件驱动”思想。

“略过‘保持’的事件”，正是为什么这个算法快的原因：我们将连续的坐标轴变成了离散的“关键点”。

### 扫描线算法的核心图解

想象有一根垂直的**扫描线**，正沿着 X 轴从左向右移动。

在这个移动过程中，绝大多数时候线下的覆盖层数是**保持不变**的。我们不需要一格一格地走，而是可以“跳跃”式地前进，只在发生**事件**的地方停下来。

我们将所有的线段拆解为两类“事件”：

1. **入场事件（+1）**：
   - 当扫描线碰到线段的**起点 $X$** 时，意味着进入了一个新区间。
   - 此时，当前的覆盖层数 **加 1**。
2. **出场事件（-1）**：
   - 当扫描线碰到线段的**终点后一位 $Y+1$** 时，意味着离开了该区间。
   - 此时，当前的覆盖层数 **减 1**。

### 算法执行流程

我们将所有的“入场”和“出场”事件收集起来，按照坐标从小到大排序。扫描线将按照以下逻辑处理：

1. **快速跳跃**：扫描线直接跳到下一个事件的坐标位置，略过中间所有“保持不变”的区域。
2. **批量结算**：如果同一个坐标点有多个事件（例如既有线段在这里开始，也有线段在这里结束），我们必须**一次性处理完**该点所有的 $+1$ 和 $-1$。
3. **统计峰值**：当该点的所有事件处理完毕后，我们得到了一个稳定的“当前覆盖数”。如果这个数超过了历史记录，就更新**最大值**。

------

### 关键点总结（为什么这么做是对的？）

- **略过“保持”**：这使得我们的计算量只与**线段的数量 $N$** 有关，而与坐标轴的长度（$10^9$）无关。这正是这一算法能处理大坐标的核心原因。
- **先结算，后统计**：必须处理完同一坐标下的所有变动，才能确信当前的覆盖数是真实的。







```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int N;
    cin >> N;
    
    // 存储事件：pair<坐标, 类型>
    // 类型 1 表示区间开始，-1 表示区间结束(的后一位)
    vector<pair<int, int>> events;
    
    for(int i = 0; i < N; ++i) {
        int l, r;
        cin >> l >> r;
        events.push_back({l, 1});
        events.push_back({r + 1, -1});
    }
    
    // 按坐标排序
    sort(events.begin(), events.end());
    
    int max_overlap = 0;
    int current_overlap = 0;
    
    // 遍历所有事件
    for(int i = 0; i < events.size(); ++i) {
        // 更新当前覆盖数
        current_overlap += events[i].second;
        
        // 注意：如果多个事件坐标相同，我们需要把它们都累加完再统计最大值
        // 比如在坐标 2 处，有一个区间结束(-1)，有一个区间开始(+1)
        // 我们应该处理完该坐标下的所有变动后再看 current_overlap
        if(i == events.size() - 1 || events[i].first != events[i+1].first) {
            max_overlap = max(max_overlap, current_overlap);
        }
    }
    
    cout << max_overlap << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}
```

### 总结

你提出的方案是完全正确的。

- **时间复杂度**：主要消耗在排序上，为 $O(N \log N)$。对于 $N=10^5$，这完全在 1秒 的时间限制内。
- **空间复杂度**：$O(N)$，用于存储坐标或事件。

你可以根据个人喜好选择“显式离散化”（第一种代码）或者“扫描线事件排序”（第二种代码），两者的本质在数学上是一模一样的。
