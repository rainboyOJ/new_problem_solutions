---
oj: "HDU"
problem_id: "3634"
title: "City Planning"
date: 2026-01-02 00:32
toc: true
tags: ["枚举","离散化"]
desc: ""
source: https://vjudge.net/problem/HDU-3634#author=wloving
---

[[TOC]]

## 题目解析

![](./1.png)

![](./2.png)

这道题目 **HDU 3634 - City Planning** 是典型的计算几何题目，主要涉及矩形面积并集的问题，但带有权值。

### 核心题意分析

龙先生想要重建建筑，每栋建筑是一个矩形，且有一个单位面积的“价值”。

关键句在于：“当他们建造新建筑时，应该移除所有重叠部分”以及“如何安排建造顺序使价值最高”。

这意味着对于平面上的任意一点 $(x, y)$：

1. 如果它被多个矩形覆盖，这个点最终保留的价值应该是覆盖它的所有矩形中**价值最高**的那个（因为我们可以安排顺序，让价值高的建筑最后建，覆盖掉价值低的）。
2. 如果不被任何矩形覆盖，价值为 0。

题目本质：

计算所有矩形覆盖区域的加权面积之和。对于每一个被覆盖的微小区域，其贡献 = $\text{该区域面积} \times \max(\text{覆盖该区域的所有矩形的 value})$。

------

### 算法选择：坐标离散化 (Coordinate Discretization)

观察数据范围：

- $N \le 20$（矩形数量非常少）。
- 坐标范围 $0 \le x, y \le 10000$（比较大，不能直接开二维数组作为网格）。
- $T < 3000$（测试用例较多，算法常数要小）。

由于 $N$ 很小，最简单且不易出错的方法是**坐标离散化**。

#### 离散化步骤：

1. **收集坐标**：将所有矩形的 $x_1, x_2$ 放入一个数组 $X$，将 $y_1, y_2$ 放入数组 $Y$。
2. **排序去重**：对 $X$ 和 $Y$ 数组进行排序并移除重复元素。
   - 去重后，$X$ 数组中有 $cntX$ 个元素，$Y$ 数组中有 $cntY$ 个元素。
   - 这些坐标将整个平面切割成了 $(cntX-1) \times (cntY-1)$ 个小矩形块（网格）。
3. **网格遍历**：
   - 遍历每一个由 $X[i], X[i+1]$ 和 $Y[j], Y[j+1]$ 形成的小矩形块。
   - 这个小块的面积是 $(X[i+1] - X[i]) \times (Y[j+1] - Y[j])$。
   - **寻找最大值**：枚举所有 $N$ 个原始矩形，检查哪些矩形完全覆盖了这个小块。在覆盖该小块的矩形中，找到最大的 `value`。
   - 累加结果：`Total += Area * max_value`。

#### 复杂度分析：

- 最多有 $2N$ 个不同的 x 坐标和 $2N$ 个不同的 y 坐标。
- 网格数量最多为 $(2N)^2 = 400$ 个。
- 对于每个网格，我们需要遍历 $N$ 个矩形来找最大值。
- 单次询问复杂度：$O((2N)^2 \cdot N) \approx O(N^3)$。
- 代入 $N=20$，运算量约为 $20^3 \times 4 = 32000$。
- 总运算量：$T \times 32000 \approx 3000 \times 32000 \approx 10^8$，在 C++ 1秒的时限内是可以接受的（且实际情况中坐标往往没那么多）。

------

### C++ 代码实现

C++

```
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 定义矩形结构体
struct Rect {
    int x1, y1, x2, y2;
    int val;
};

// 存储离散化的坐标
vector<int> X, Y;
Rect rects[25];
int n;

int main() {
    // 优化 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        for (int caseNum = 1; caseNum <= T; ++caseNum) {
            cin >> n;
            X.clear();
            Y.clear();

            for (int i = 0; i < n; ++i) {
                cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2 >> rects[i].val;
                // 将用到的坐标加入集合
                X.push_back(rects[i].x1);
                X.push_back(rects[i].x2);
                Y.push_back(rects[i].y1);
                Y.push_back(rects[i].y2);
            }

            // 排序并去重 (Sort and Unique)
            sort(X.begin(), X.end());
            X.erase(unique(X.begin(), X.end()), X.end());

            sort(Y.begin(), Y.end());
            Y.erase(unique(Y.begin(), Y.end()), Y.end());

            long long totalValue = 0;

            // 遍历离散化后的网格
            // 注意：如果有 k 个坐标，则有 k-1 个区间
            for (int i = 0; i < X.size() - 1; ++i) {
                for (int j = 0; j < Y.size() - 1; ++j) {
                    
                    // 当前小块的物理范围
                    int x_start = X[i];
                    int x_end = X[i+1];
                    int y_start = Y[j];
                    int y_end = Y[j+1];

                    // 计算该小块的面积
                    long long area = (long long)(x_end - x_start) * (y_end - y_start);
                    if (area == 0) continue;

                    // 找出覆盖这个小块的矩形中，价值最大的那个
                    int maxVal = 0;
                    for (int k = 0; k < n; ++k) {
                        // 判断矩形 k 是否完全覆盖当前小块
                        // 只要矩形 k 的范围包含当前小块的范围即可
                        if (rects[k].x1 <= x_start && rects[k].x2 >= x_end &&
                            rects[k].y1 <= y_start && rects[k].y2 >= y_end) {
                            maxVal = max(maxVal, rects[k].val);
                        }
                    }

                    totalValue += area * maxVal;
                }
            }

            cout << "Case " << caseNum << ": " << totalValue << endl;
        }
    }
    return 0;
}
```

### 关键点解释

1. 判断覆盖条件：

   在代码中，判断原始矩形 rects[k] 是否覆盖当前的网格单元 [X[i], X[i+1]] $\times$ [Y[j], Y[j+1]] 时，我们使用了：

   rects[k].x1 <= x_start && rects[k].x2 >= x_end

   这是因为 x_start 和 x_end 本身就是从原始矩形的边界集合中取出来的，所以不会出现“部分覆盖”的情况。一个原始矩形要么完全包含这个小网格，要么完全不包含（或仅接触边缘）。

2. 数据类型：

   虽然输入的坐标和价值都在 int 范围内，但最终的总价值可能会超过 32 位整数（例如 $10000 \times 10000 \times 20$），所以累加器 totalValue 和面积计算必须使用 long long。

3. 替代方案：

   如果 $N$ 很大（例如 $N=1000$），这种 $O(N^3)$ 的方法会超时。那时候通常需要使用线段树扫描线 (Segment Tree with Sweep Line) 算法。但对于 $N=20$，离散化网格法是最容易实现且足够快的。
