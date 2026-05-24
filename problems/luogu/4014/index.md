---
oj: "luogu"
problem_id: "P4014"
title: "分配问题"
date: 2026-01-11 22:58
toc: true
tags: ["费用流"]
desc: "最小费用,最大费用"
source: https://www.luogu.com.cn/problem/P4014
---

[[TOC]]

## 题目解析

# P4014 分配问题 - 费用流详细解析

## 1. 题目背景与核心问题

题目描述：

有 $n$ 个人和 $n$ 件工作。

每个人做每件工作都有一个对应的效益值 $c_{ij}$。

要求：

1. 每个人只能做一件工作。
2. 每件工作只能由一个人做。
3. **目标 1**：求分配方案使得总效益**最小**。
4. **目标 2**：求分配方案使得总效益**最大**。

核心转化：

这是一个标准的二分图最佳完美匹配 (Minimum/Maximum Weight Perfect Matching) 问题。

在网络流中，我们可以通过构建流量限制，强制模型找出“一一对应”的关系，并通过费用（Cost）属性来优化总效益。

## 2. 建模思路：最小费用最大流 (MCMF)

我们将问题转化为一个**流量为** $n$ 的最小费用流模型。

### 2.1 节点设置

我们需要构建一个流网络图：

- **源点 (**$S$**)**：编号 $0$。
- **人节点 (**$People$**)**：编号 $1 \dots n$。
- **工作节点 (**$Jobs$**)**：编号 $n+1 \dots 2n$（为了区分人和工作，给工作编号加 $n$）。
- **汇点 (**$T$**)**：编号 $2n+1$。

### 2.2 建边策略

我们需要建立三层边结构，每一层都有明确的物理意义：

#### 第一层：源点 $\to$ 人

- **连接**：$S \to i$ （其中 $1 \le i \le n$）
- **容量 (Capacity)**：$1$![img]()
- **费用 (Cost)**：$0$![img]()
- **意义**：每个人最多只能提供 $1$ 个单位的劳动力（只能做一份工）。

#### 第二层：人 $\to$ 工作

- **连接**：$i \to j+n$ （其中 $1 \le i, j \le n$）
- **容量 (Capacity)**：$1$![img]()
- **费用 (Cost)**：
  - **求最小效益时**：费用为 $c_{ij}$。
  - **求最大效益时**：费用为 $-c_{ij}$（取相反数，利用“最小费用”算法求“最大收益”）。
- **意义**：如果流走了这条边，代表第 $i$ 个人做了第 $j$ 件工作，并产生了对应的效益（代价）。

#### 第三层：工作 $\to$ 汇点

- **连接**：$j+n \to T$ （其中 $1 \le j \le n$）
- **容量 (Capacity)**：$1$![img]()
- **费用 (Cost)**：$0$![img]()
- **意义**：每件工作最多只能被 $1$ 个人完成。

费用流模型图示 (以 $n=2$ 为例):

```graphviz
digraph MCMF_Assignment {
    rankdir=LR; // 布局从左到右
    node [shape=ellipse, fontname="Helvetica", fontsize=10];
    edge [fontname="Helvetica", fontsize=9];

    // 定义节点，并标注其在代码中的编号
    S [label="Source (0)"];
    Person1 [label="Person 1 (1)"];
    Person2 [label="Person 2 (2)"];
    Job1 [label="Job 1 (3)"]; // 对应编号 n+1 = 2+1
    Job2 [label="Job 2 (4)"]; // 对应编号 n+2 = 2+2
    T [label="Sink (5)"]; // 对应编号 2n+1 = 2*2+1

    // 源点到人节点的边 (容量1, 费用0)
    S -> Person1 [label="Cap:1\nCost:0"];
    S -> Person2 [label="Cap:1\nCost:0"];

    // 人节点到工作节点的边 (容量1, 费用c_ij 或 -c_ij)
    Person1 -> Job1 [label="Cap:1\nCost:c11"];
    Person1 -> Job2 [label="Cap:1\nCost:c12"];
    Person2 -> Job1 [label="Cap:1\nCost:c21"];
    Person2 -> Job2 [label="Cap:1\nCost:c22"];

    // 工作节点到汇点的边 (容量1, 费用0)
    Job1 -> T [label="Cap:1\nCost:0"];
    Job2 -> T [label="Cap:1\nCost:0"];

    // 使用子图对节点进行视觉分组
    subgraph cluster_people_group {
        style=filled;
        color=lightgrey;
        label="People (1 to n)";
        Person1; Person2;
    }
    subgraph cluster_jobs_group {
        style=filled;
        color=lightgrey;
        label="Jobs (n+1 to 2n)";
        Job1; Job2;
    }

    // 整个图的标题和说明
    label = "MCMF Model for Assignment Problem (Example for n=2)\n"
            "Min Total Benefit: Edge cost is c_ij\n"
            "Max Total Benefit: Edge cost is -c_ij (then negate final min_cost)";
    labelloc="t"; // 标题在顶部
    fontsize=12;
    fontname="Helvetica";
}
```

### 2.3 为什么这样建模有效？

1. **最大流约束**：
   - 由于源点 $S$ 发出的总容量是 $n$（有 $n$ 条容量为 1 的边连向人）。
   - 汇点 $T$ 接收的总容量也是 $n$（有 $n$ 条容量为 1 的边来自工作）。
   - 当最大流达到 $n$ 时，意味着必然有 $n$ 条路径贯通了 $S \to 人 \to 工作 \to T$。
   - 这保证了**所有人**都被安排了工作，且**所有工作**都有人做（完美匹配）。
2. **最小费用优化**：
   - MCMF 算法会在所有可能的满流（流量为 $n$）方案中，寻找**总费用最小**的那一种。
   - 这正是题目要求的“最小总效益”。

## 3. 处理“最大总效益”的技巧

常用的 MCMF 算法（如 SPFA 版）是求**最小**费用的。如何求最大费用？

**核心技巧：取反（Negation）**

数学原理：



$$\max(\sum c_{ij}) \iff \min(\sum -c_{ij})$$

求最大效益时，我们将所有人与工作之间的连边费用设为 $-c_{ij}$。

1. 运行最小费用最大流算法。
2. 得到的 `min_cost` 将是一个负数（因为我们在累加负权值）。
3. 最终答案为 **`-min_cost`**。

## 4. 算法流程总结

对于本题，我们需要运行**两次** MCMF 算法：

### 第一步：求最小效益

1. **清空图** (`init`)。
2. 建立 $S \to i$ 和 $j \to T$ 的边。
3. 建立 $i \to j$ 的边，**费用为** $c_{ij}$。
4. 运行 `mcmf.solve(s, t)`。
5. 输出 `mcmf.min_cost`。

### 第二步：求最大效益

1. **清空图** (`init`)。
2. 建立 $S \to i$ 和 $j \to T$ 的边。
3. 建立 $i \to j$ 的边，**费用为** $-c_{ij}$。
4. 运行 `mcmf.solve(s, t)`。
5. 输出 `-mcmf.min_cost`（注意取反）。

## 更多图例


### 1.1 整体网络结构 (n=3 示例)

```mermaid
graph TD
    S[源点 S] -->|cap=1, cost=0| P1[人 1]
    S -->|cap=1, cost=0| P2[人 2]
    S -->|cap=1, cost=0| P3[人 3]
  
    P1 -->|cap=1, cost=c11| J1[工作 1]
    P1 -->|cap=1, cost=c12| J2[工作 2]
    P1 -->|cap=1, cost=c13| J3[工作 3]
  
    P2 -->|cap=1, cost=c21| J1
    P2 -->|cap=1, cost=c22| J2
    P2 -->|cap=1, cost=c23| J3
  
    P3 -->|cap=1, cost=c31| J1
    P3 -->|cap=1, cost=c32| J2
    P3 -->|cap=1, cost=c33| J3
  
    J1 -->|cap=1, cost=0| T[汇点 T]
    J2 -->|cap=1, cost=0| T
    J3 -->|cap=1, cost=0| T
  
    style S fill:#e1f5fe
    style T fill:#fce4ec
    style P1 fill:#c8e6c9
    style P2 fill:#c8e6c9
    style P3 fill:#c8e6c9
    style J1 fill:#fff3e0
    style J2 fill:#fff3e0
    style J3 fill:#fff3e0
```

## 2. 具体示例图解 (n=3)

假设输入为：
```
3
2 7 4
3 6 1
5 8 3
```

### 2.1 最小效益匹配 (费用为正数)

```dot
digraph G {
    rankdir=LR;
    node [shape=circle, style=filled, fontname="Helvetica"];
    edge [fontname="Helvetica", fontsize=10];
  
    // 定义节点
    S [label="S", fillcolor="#e1f5fe"];
    T [label="T", fillcolor="#fce4ec"];
  
    P1 [label="人1", fillcolor="#c8e6c9"];
    P2 [label="人2", fillcolor="#c8e6c9"];
    P3 [label="人3", fillcolor="#c8e6c9"];
  
    J1 [label="工作1", fillcolor="#fff3e0"];
    J2 [label="工作2", fillcolor="#fff3e0"];
    J3 [label="工作3", fillcolor="#fff3e0"];
  
    // 源点到人 (容量=1, 费用=0)
    S -> P1 [label="cap=1\ncost=0", color="#2196f3"];
    S -> P2 [label="cap=1\ncost=0", color="#2196f3"];
    S -> P3 [label="cap=1\ncost=0", color="#2196f3"];
  
    // 人到工作 (容量=1, 费用=c_ij)
    P1 -> J1 [label="cap=1\ncost=2", color="#4caf50"];
    P1 -> J2 [label="cap=1\ncost=7", color="#4caf50"];
    P1 -> J3 [label="cap=1\ncost=4", color="#4caf50"];
  
    P2 -> J1 [label="cap=1\ncost=3", color="#4caf50"];
    P2 -> J2 [label="cap=1\ncost=6", color="#4caf50"];
    P2 -> J3 [label="cap=1\ncost=1", color="#4caf50"];
  
    P3 -> J1 [label="cap=1\ncost=5", color="#4caf50"];
    P3 -> J2 [label="cap=1\ncost=8", color="#4caf50"];
    P3 -> J3 [label="cap=1\ncost=3", color="#4caf50"];
  
    // 工作到汇点 (容量=1, 费用=0)
    J1 -> T [label="cap=1\ncost=0", color="#e91e63"];
    J2 -> T [label="cap=1\ncost=0", color="#e91e63"];
    J3 -> T [label="cap=1\ncost=0", color="#e91e63"];
  
    // 图标题
    label = "最小效益匹配网络 (n=3)\n费用矩阵: [2,7,4; 3,6,1; 5,8,3]";
    labelloc="t";
    fontsize=12;
}
```

### 2.2 最小效益匹配结果 (流量=3)

```dot
digraph G {
    rankdir=LR;
    node [shape=circle, style=filled, fontname="Helvetica"];
    edge [fontname="Helvetica", fontsize=10];
  
    // 定义节点
    S [label="S", fillcolor="#e1f5fe"];
    T [label="T", fillcolor="#fce4ec"];
  
    P1 [label="人1", fillcolor="#c8e6c9"];
    P2 [label="人2", fillcolor="#c8e6c9"];
    P3 [label="人3", fillcolor="#c8e6c9"];
  
    J1 [label="工作1", fillcolor="#fff3e0"];
    J2 [label="工作2", fillcolor="#fff3e0"];
    J3 [label="工作3", fillcolor="#fff3e0"];
  
    // 最小效益匹配路径 (用红色加粗显示)
    // 人1 -> 工作1 (cost=2)
    // 人2 -> 工作3 (cost=1)
    // 人3 -> 工作2 (cost=8)
  
    // 源点到人
    S -> P1 [label="flow=1", color="#f44336", penwidth=3];
    S -> P2 [label="flow=1", color="#f44336", penwidth=3];
    S -> P3 [label="flow=1", color="#f44336", penwidth=3];
  
    // 匹配边 (红色加粗)
    P1 -> J1 [label="flow=1\ncost=2", color="#f44336", penwidth=3];
    P2 -> J3 [label="flow=1\ncost=1", color="#f44336", penwidth=3];
    P3 -> J2 [label="flow=1\ncost=8", color="#f44336", penwidth=3];
  
    // 未使用的边 (灰色虚线)
    P1 -> J2 [label="cost=7", style=dashed, color="#9e9e9e"];
    P1 -> J3 [label="cost=4", style=dashed, color="#9e9e9e"];
    P2 -> J1 [label="cost=3", style=dashed, color="#9e9e9e"];
    P2 -> J2 [label="cost=6", style=dashed, color="#9e9e9e"];
    P3 -> J1 [label="cost=5", style=dashed, color="#9e9e9e"];
    P3 -> J3 [label="cost=3", style=dashed, color="#9e9e9e"];
  
    // 工作到汇点
    J1 -> T [label="flow=1", color="#f44336", penwidth=3];
    J2 -> T [label="flow=1", color="#f44336", penwidth=3];
    J3 -> T [label="flow=1", color="#f44336", penwidth=3];
  
    // 图标题
    label = "最小效益匹配结果\n总效益 = 2 + 1 + 8 = 11\n匹配: 人1->工作1, 人2->工作3, 人3->工作2";
    labelloc="t";
    fontsize=12;
}
```

### 2.3 最大效益匹配 (费用取负数)

```dot
digraph G {
    rankdir=LR;
    node [shape=circle, style=filled, fontname="Helvetica"];
    edge [fontname="Helvetica", fontsize=10];
  
    // 定义节点
    S [label="S", fillcolor="#e1f5fe"];
    T [label="T", fillcolor="#fce4ec"];
  
    P1 [label="人1", fillcolor="#c8e6c9"];
    P2 [label="人2", fillcolor="#c8e6c9"];
    P3 [label="人3", fillcolor="#c8e6c9"];
  
    J1 [label="工作1", fillcolor="#fff3e0"];
    J2 [label="工作2", fillcolor="#fff3e0"];
    J3 [label="工作3", fillcolor="#fff3e0"];
  
    // 源点到人 (容量=1, 费用=0)
    S -> P1 [label="cap=1\ncost=0", color="#2196f3"];
    S -> P2 [label="cap=1\ncost=0", color="#2196f3"];
    S -> P3 [label="cap=1\ncost=0", color="#2196f3"];
  
    // 人到工作 (容量=1, 费用=-c_ij)
    P1 -> J1 [label="cap=1\ncost=-2", color="#ff9800"];
    P1 -> J2 [label="cap=1\ncost=-7", color="#ff9800"];
    P1 -> J3 [label="cap=1\ncost=-4", color="#ff9800"];
  
    P2 -> J1 [label="cap=1\ncost=-3", color="#ff9800"];
    P2 -> J2 [label="cap=1\ncost=-6", color="#ff9800"];
    P2 -> J3 [label="cap=1\ncost=-1", color="#ff9800"];
  
    P3 -> J1 [label="cap=1\ncost=-5", color="#ff9800"];
    P3 -> J2 [label="cap=1\ncost=-8", color="#ff9800"];
    P3 -> J3 [label="cap=1\ncost=-3", color="#ff9800"];
  
    // 工作到汇点 (容量=1, 费用=0)
    J1 -> T [label="cap=1\ncost=0", color="#e91e63"];
    J2 -> T [label="cap=1\ncost=0", color="#e91e63"];
    J3 -> T [label="cap=1\ncost=0", color="#e91e63"];
  
    // 图标题
    label = "最大效益匹配网络 (费用取负)\n原费用矩阵: [2,7,4; 3,6,1; 5,8,3]\n算法求最小费用流，然后取反得最大效益";
    labelloc="t";
    fontsize=12;
}
```

### 2.4 最大效益匹配结果 (流量=3)

```dot
digraph G {
    rankdir=LR;
    node [shape=circle, style=filled, fontname="Helvetica"];
    edge [fontname="Helvetica", fontsize=10];
  
    // 定义节点
    S [label="S", fillcolor="#e1f5fe"];
    T [label="T", fillcolor="#fce4ec"];
  
    P1 [label="人1", fillcolor="#c8e6c9"];
    P2 [label="人2", fillcolor="#c8e6c9"];
    P3 [label="人3", fillcolor="#c8e6c9"];
  
    J1 [label="工作1", fillcolor="#fff3e0"];
    J2 [label="工作2", fillcolor="#fff3e0"];
    J3 [label="工作3", fillcolor="#fff3e0"];
  
    // 最大效益匹配路径 (用蓝色加粗显示)
    // 人1 -> 工作2 (cost=-7)
    // 人2 -> 工作1 (cost=-3)
    // 人3 -> 工作3 (cost=-3)
  
    // 源点到人
    S -> P1 [label="flow=1", color="#2196f3", penwidth=3];
    S -> P2 [label="flow=1", color="#2196f3", penwidth=3];
    S -> P3 [label="flow=1", color="#2196f3", penwidth=3];
  
    // 匹配边 (蓝色加粗)
    P1 -> J2 [label="flow=1\ncost=-7", color="#2196f3", penwidth=3];
    P2 -> J1 [label="flow=1\ncost=-3", color="#2196f3", penwidth=3];
    P3 -> J3 [label="flow=1\ncost=-3", color="#2196f3", penwidth=3];
  
    // 未使用的边 (灰色虚线)
    P1 -> J1 [label="cost=-2", style=dashed, color="#9e9e9e"];
    P1 -> J3 [label="cost=-4", style=dashed, color="#9e9e9e"];
    P2 -> J2 [label="cost=-6", style=dashed, color="#9e9e9e"];
    P2 -> J3 [label="cost=-1", style=dashed, color="#9e9e9e"];
    P3 -> J1 [label="cost=-5", style=dashed, color="#9e9e9e"];
    P3 -> J2 [label="cost=-8", style=dashed, color="#9e9e9e"];
  
    // 工作到汇点
    J1 -> T [label="flow=1", color="#2196f3", penwidth=3];
    J2 -> T [label="flow=1", color="#2196f3", penwidth=3];
    J3 -> T [label="flow=1", color="#2196f3", penwidth=3];
  
    // 图标题
    label = "最大效益匹配结果 (费用流网络)\n算法最小费用 = (-7) + (-3) + (-3) = -13\n实际最大效益 = -(-13) = 13\n匹配: 人1->工作2, 人2->工作1, 人3->工作3";
    labelloc="t";
    fontsize=12;
}
```

## 3. 算法流程总结图

```mermaid
graph TD
    A[开始] --> B[读取n和效益矩阵c_ij]
    B --> C[构建最小效益网络]
    C --> D[运行MCMF算法<br/>求最小费用最大流]
    D --> E[输出最小总效益]
    E --> F[构建最大效益网络<br/>费用取负-c_ij]
    F --> G[运行MCMF算法<br/>求最小费用最大流]
    G --> H[输出 -min_cost<br/>作为最大总效益]
    H --> I[结束]
  
    style A fill:#e1f5fe
    style E fill:#c8e6c9
    style H fill:#c8e6c9
    style I fill:#fce4ec
```

## 4. 关键点说明

1. **容量限制**：
   - 所有边的容量都是 1，确保每个人只做一份工作，每份工作只由一个人做
   - 最大流为 n 时，表示找到了完美匹配

2. **费用设置**：
   - 最小效益：费用 = c_ij
   - 最大效益：费用 = -c_ij（利用最小费用流求最大效益）

3. **算法保证**：
   - MCMF 算法会在所有流量为 n 的可行流中，找到总费用最小的方案
   - 由于网络是二分图结构，匈牙利算法也可以解决，但 MCMF 更通用

这些图示清晰地展示了如何将分配问题转化为网络流问题，并通过费用流算法求解最小和最大效益匹配。

## 为什么求“最大费用”时要取反？

### 1. 我们的工具箱里有什么？

首先，我们要明确一点：我们手头现成的代码模板（基于 SPFA 或 Dijkstra 的算法）叫什么名字？

它是 “最小费用” 最大流算法 (Min-Cost Max-Flow)。

- **SPFA/Dijkstra 的核心本能**：寻找**最短**路径。
- 它们就像水往低处流一样，天生只会找“数值最小”的那条路。
- 如果你给它一堆正数代表效益（比如 100, 200, 500），它会毫不犹豫地选 **100**，因为 100 比 500 小，这显然不是我们想要的“最大效益”。

所以，我们面临的问题是：**我们要找“最高”的山峰，但我们手里的探测器只会找“最深”的峡谷。**

### 2. 数学上的“镜像”魔法

怎么办呢？我们不需要重新发明一个“找山峰”的探测器，我们只需要把地图**颠倒**过来。

想象一下数轴：

- 我们有两个数：$10$ 和 $2$。
- 显然，$10$ 是大的（最大效益），$2$ 是小的。
- 现在，我们把它们都乘上 $-1$（取反）。
- 变成了：$-10$ 和 $-2$。
- 这时候，谁更小？$-10$ **更小！**

**发现规律了吗？**

> 在正数世界里越**大**的数，取反后在负数世界里就越**小**。

### 公式推导

假设我们要选一组边 $e$，使得它们的费用之和 $\sum Cost$ 最大：

$$\text{目标：} \max(Cost_1 + Cost_2 + \dots)$$

根据数学等式：$\max(A) = -\min(-A)$![img]()

$$\text{等价于：} -\min((-Cost_1) + (-Cost_2) + \dots)$$

这就意味着：

1. 把所有边的权值 $W$ 变成 $-W$。
2. 告诉 SPFA：“去吧，帮我找费用最小的路径！”
3. SPFA 会非常开心地找到 $-100$（因为它比 $-1$ 小得多）。
4. 实际上，它选中的正是原本权值为 $100$ 的那条大边。

### 3. 举个栗子 🌰

假设你要分配工作，有两个选择：

- **工作 A**：效益 100 元
- **工作 B**：效益 10 元

**如果我们直接跑最小费用流：**

- 算法看到：费用 100，费用 10。
- 算法选择：**工作 B**（因为它便宜）。
- **结果**：总效益 10。（亏了！）

**如果我们取反跑最小费用流：**

- **工作 A**：费用 -100
- **工作 B**：费用 -10
- 算法看到：-100 比 -10 更小（更靠数轴左边）。
- 算法选择：**工作 A**（因为它“最小”）。
- **跑出来的结果**：min_cost = -100。
- **还原结果**：我们把 -100 再取个反，得到 **100**。
- **结果**：总效益 100。（赚了！选到了最大的！）

### 4. 总结

作为一个聪明的程序员，我们不需要为了“最大费用”单独写一份代码。我们只需要用这个简单的**三步走**策略：

1. **输入取反**：读入数据时，把所有的 $c_{ij}$ 变成 $-c_{ij}$。
2. **跑最小费用流**：用你最熟悉的模板（SPFA版）跑一遍。
3. **输出取反**：最后得到的 `min_cost` 肯定是个负数，把它再变回正数（`-mcmf.min_cost`）就是我们要的最大效益。

这就好比你想找全班最高的同学，但你只会找最矮的。那你只需要让全班同学倒立过来，头朝下，那个“最矮”（头离天花板最远）的人，就是原本最高的人！

## 5. 代码实现

@include-code(./2.cpp,cpp)

## 6. 复杂度分析

- **点数** $V$：$2n + 2 \approx 100$。
- **边数** $E$：$n^2 + 2n \approx 2600$。
- **流量** $F$：$n = 50$。
- **MCMF (SPFA) 复杂度**：大致为 $O(k \cdot E \cdot F)$，其中 $k$ 是 SPFA 的平均松弛次数（通常较小）。
- 计算量非常小，完全可以在 1s 内通过。

