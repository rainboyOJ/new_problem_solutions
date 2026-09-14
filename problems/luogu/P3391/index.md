---
oj: "luogu"
problem_id: "P3391"
title: "【模板】文艺平衡树"
description: "用隐式 Splay 或隐式 FHQ-Treap 维护序列顺序，通过双哨兵或按排名分裂实现区间翻转。"
difficulty: "提高"
date: 2026-09-14 19:33
toc: true
tags: ["平衡树", "Splay", "FHQ-Treap", "区间翻转", "模板题"]
favorite: false
favorite_reason: ""
categories: []
showAtRoot: ["fhq-treap"]
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3391
---

[[TOC]]

## 形式化题目

初始序列为 $[1,2,\dots,n]$。每次操作给出区间 $[l,r]$，把其中元素的相对顺序完全翻转；完成所有操作后输出最终序列。

## 解法总览

普通数组翻转一次需要 $O(r-l+1)$，最坏会达到 $O(nm)$。本题的关键是把数组看成一棵“中序遍历等于序列顺序”的平衡树。这样只要把区间单独切出来，对它打一个翻转标记，再拼回去即可。

| 解法 | 如何切出 $[l,r]$ | 翻转方式 | 单次复杂度 |
| --- | --- | --- | --- |
| 隐式 Splay | 两个哨兵节点夹住目标区间 | 中段根打 `rev` 标记 | $O(\log n)$ |
| 隐式 FHQ-Treap | 两次按排名 `split` | 中段根打 `rev` 标记 | 期望 $O(\log n)$ |

两种写法都维护子树大小 `size`，用它把“第几个元素”转化为树上的位置。

## 解法一：隐式 Splay

### 思路

在真实序列两端各加一个哨兵，序列变成 $[0,1,2,\dots,n,n+1]$。

要翻转真实区间 $[l,r]$ 时：

1. 找到它左边的节点，即扩展序列中的第 $l$ 个节点，并 Splay 到根；
2. 找到它右边的节点，即第 $r+2$ 个节点，并 Splay 到根的右儿子；
3. 此时右儿子的左子树恰好是 $[l,r]$，给这棵子树的 `rev` 异或一次；
4. 访问子树时再下传标记：交换左右儿子，并把标记传给两个儿子。

Splay 旋转之前必须先将根到当前节点路径上的翻转标记全部下传，否则左右儿子的实际方向会与记录不一致。

### 代码

@include-code(./main-treap.cpp, cpp)

### 复杂度

建树与每次区间翻转均摊 $O(\log n)$，总时间复杂度为 $O((n+m)\log n)$，空间复杂度为 $O(n)$。

## 解法二：隐式 FHQ-Treap

### 思路

FHQ-Treap 的普通模板按“值”分裂有序集合；这里的中序顺序代表序列位置，所以将 `split(u,k)` 改为：左树保留前 $k$ 个元素，右树保留剩余元素。

翻转 $[l,r]$ 分成三步：

```text
split(root, r)       -> [1, r] 与 [r+1, n]
split([1, r], l - 1) -> [1, l-1]、[l, r]
```

对中段根打 `rev` 标记，再按原顺序合并三段即可。`merge` 时也要先下传标记，确保递归合并的左右子树是真实顺序。

rbook 的 [FHQ-Treap 模板说明](https://rbook2.roj.ac.cn/data_structure/fhq-treap/index.html) 中，`split / merge / size` 是核心接口；本题只将“按值分裂”替换成“按排名分裂”，并增加区间翻转标记。

### 图示：两次重叠翻转中的懒标记

下面固定初始序列为 $[1,2,3,4,5,6,7,8]$，依次翻转 $[2,6]$ 和 $[3,7]$。为了让树形稳定，图中不用代码生成的随机大整数，而人为指定优先级：

| value | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| pri | 50 | 70 | 30 | 100 | 40 | 80 | 20 | 60 |

每个节点都写出 `value / pri / size / rev`。橙色表示 `rev=1`，它只说明整棵子树“将要翻转”，并不表示所有后代已立即交换；蓝色边表示本步 `push_down` 刚交换过该节点的左右子树。所有图均由 [`fhq_treap_viz.py`](./problem-analysis-workspace/fhq_treap_viz.py) 生成。

#### 步骤 0：初始树

调用：`merge(1), merge(2), ..., merge(8)`。

![初始隐式 FHQ-Treap，所有节点列出 value、pri、size、rev](./problem-analysis-workspace/fhq-treap-steps/01-initial.svg)

中序遍历是初始序列 `1 2 3 4 5 6 7 8`。此时 `size` 已保存每个子树的元素个数，所以 `split` 可以按排名工作。

#### 步骤 1：切出第一次翻转区间 `[2,6]`

调用：`split(root, 6)`，再调用 `split(first, 1)`。

![第一次按排名分裂后得到 before、middle、last 三棵树](./problem-analysis-workspace/fhq-treap-steps/02-first-split.svg)

两次分裂后，三部分依次是“位置 1”“位置 2 到 6”“位置 7 到 8”。这里写的是**位置范围**，不是节点的 `value`；注意每棵树的 `size` 已在断边回溯时重新计算。

#### 步骤 2：只给中段根打标记

调用：`middle.rev ^= 1`。

![第一次翻转只在中段根留下 rev 标记](./problem-analysis-workspace/fhq-treap-steps/03-first-mark.svg)

橙色根表示整个 `[2,6]` 需要翻转。这里没有递归访问后代，因此一次区间翻转本身不需要线性时间。

#### 步骤 3：第一次合并时按需下传

调用：`root = merge(merge(before, middle), last)`。

![第一次合并时 push_down 下传懒标记并交换左右子树](./problem-analysis-workspace/fhq-treap-steps/04-first-merge.svg)

`merge` 为了继续递归，访问到带标记的节点才执行 `push_down`。蓝色边记录本步发生的左右交换；这就是 lazy 的含义：用到时才做。

#### 步骤 4：第二次翻转重新按位置切开

调用：`split(root, 7)`，再调用 `split(first, 2)`。

![第二次翻转按排名切出 before middle last 三段](./problem-analysis-workspace/fhq-treap-steps/05-second-split.svg)

第二次操作与第一次重叠，但不必展开整个序列。沿着 `split` 的访问路径，遗留的 `rev` 会自然下传；最终仍切成前缀、中段、后缀三棵树。

#### 步骤 5：第二个中段继续延迟翻转

调用：`middle.rev ^= 1`。

![第二次翻转给中段根打 rev 标记](./problem-analysis-workspace/fhq-treap-steps/06-second-mark.svg)

`rev` 使用异或而不是赋值：同一段被翻转两次时，`1 xor 1 = 0`，恰好恢复原顺序。

#### 步骤 6：合并回最终的树形

调用：`root = merge(merge(before, middle), last)`。

![第二次合并后的隐式 FHQ-Treap 树形](./problem-analysis-workspace/fhq-treap-steps/07-final-merge.svg)

`pri` 只决定 Treap 的树形和 `merge` 选哪个根；元素的先后顺序始终由中序遍历决定，两者不能混淆。

#### 步骤 7：输出时清理剩余标记

调用：中序遍历中的 `push_down(node)`。

![输出前下传所有剩余 rev 标记后的树](./problem-analysis-workspace/fhq-treap-steps/08-output.svg)

访问节点前下传标记后，中序遍历得到最终答案：`1 6 7 2 3 4 5 8`。这说明翻转标记可以一直留在未访问的子树根上，直到下次 `split`、`merge` 或输出真正需要它。

### C++ 代码

@include-code(./main-fhq.cpp, cpp)

### Python 代码

@include-code(./main-fhq.py, python)

### 复杂度

每次 `split` 与 `merge` 的期望复杂度为 $O(\log n)$，总时间复杂度为 $O((n+m)\log n)$，空间复杂度为 $O(n)$。

## 总结

文艺平衡树的本质是用平衡树维护“序列位置”，不是维护元素值的大小关系。区间操作先切出中段，再延迟修改中段根，最后合并回去。

Splay 用哨兵把中段变成固定位置的子树；FHQ-Treap 用两次按排名分裂直接得到中段。两种方法都可以迁移到区间移动、插入、删除和区间查询等序列维护问题。
