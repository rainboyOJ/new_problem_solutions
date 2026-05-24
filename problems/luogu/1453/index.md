---
oj: "luogu"
problem_id: "P1453"
title: "城市环路"
date: 2026-01-09 16:12
toc: true
tags: []
desc: "基环树上的最大独立集"
source: https://www.luogu.com.cn/problem/P1453
pre:
 - luogu,P2607
book:
 - bookid
---

[[TOC]]

## 题目解析

> 基环树上的最大独立集问题 

> 这个题目和 [[problem : luogu,P2607]] 差不多

这个题目的难点不再于代码, 而是人类的大脑不擅长同时思考思考太多的东西(图上的点),现在我来带你一步一步思考:

1. 取环上的任意一条边 $(u,v)$,  显然最最终的答案里面, $u,v$ 两个点不能同时出现
2. 设第 $i$ 合法的 独立集合为 $d_i$
3. 显然 我们可以把所有的独立集组成的集合$A = \{d_1,d_2,\cdots , d_n\}$, 分成,不重不漏的三个集合
   1. $B(u) =\{ d_i | u \in d_i \}$ 含有 $u$ 的独立集 组成的集合
   2. $B(v) = \{d_i | v \in d_i \}$ 含有 $v $ 的独立集 组成的集合
   3. $C = \{d_i | v \notin d_i \land u \notin d_i \}$

4. 显然 $A = B(u) \cup B(v) \cup C$ (我觉得整个题目的核心就在这里!!!,理解这个就能理解整个题目)
5. 进一步的,可以想到(为了减小写代码的量), 根据补集的思想
   1. $\overline {B(u)} = B(v) \cup C = \{d_i | u \notin d_i \}$ ,表示 不含有 $u$ 的集合
   2. $\overline {B(v)} = B(u) \cup C= \{d_i | v \notin d_i \}$,表示 不含有 $v$ 的集合

```dot
digraph G {
    rankdir=TB;
    node [shape=ellipse, style=filled];
    edge [dir=none];
    
    // 全集 A
    A [label="A\n所有独立集的集合", fillcolor=lightblue, shape=doublecircle];
    
    // 三个子集
    B_u [label="B(u)\n包含u的独立集", fillcolor=yellow];
    B_v [label="B(v)\n包含v的独立集", fillcolor=orange];
    C [label="C\n既不包含u也不包含v的独立集", fillcolor=lightgreen];
    
    // 补集
    not_B_u [label="¬B(u)\n不包含u的独立集", fillcolor=yellow, style="filled,dashed"];
    not_B_v [label="¬B(v)\n不包含v的独立集", fillcolor=orange, style="filled,dashed"];
    
    // 全集分解
    A -> B_u;
    A -> B_v;
    A -> C;
    
    // 补集关系
    not_B_u -> B_v [label="∪", fontcolor=red];
    not_B_u -> C [label="∪", fontcolor=red];
    
    not_B_v -> B_u [label="∪", fontcolor=red];
    not_B_v -> C [label="∪", fontcolor=red];
    
    // 布局调整
    {rank=same; B_u; B_v; C}
    {rank=same; not_B_u; not_B_v}
}
```



那么不就得到了 : $A = \overline{B(u)} \cup \overline{B(v)}$

那么 $\max (A) = \max( \max(\overline{B(u)}) ,\max(\overline{B(u)}))$

哪怎么求 $\max(\overline{B(u)})$ 呢? 显然这表示 不选 $u$ 的情况,



可以想到如果 $u$ 删除,那么

1. 变成一个树 , 直接树上DP

2. 图断可能开成 两个连通分量: 

下面的图有点问题: 不是删除边,是删除点
   

```dot
digraph G {
    rankdir=LR;
    subgraph cluster_case1 {
        label="情况1：删除边(u,v)后形成一棵树";
        style=dashed;
        
        node [shape=circle];
        u [label="u", fillcolor=yellow];
        v [label="v", fillcolor=orange];
        a [label="a"];
        b [label="b"];
        c [label="c"];
        u1 [label="u1"];
        v1 [label="v1"];
        
        // 树结构
        u -> a;
        a -> b;
        b -> c;
        c -> v;
        u -> u1;
        v -> v1;
        
        // 删除的边用虚线表示
        u -> v [style=dashed, color=gray, label="删除"];
    }
    
    subgraph cluster_case2 {
        label="情况2：删除边(u,v)后形成两个连通分量";
        style=dashed;
        
        node [shape=circle];
        u2 [label="u", fillcolor=yellow];
        v2 [label="v", fillcolor=orange];
        a2 [label="a"];
        b2 [label="b"];
        c2 [label="c"];
        u12 [label="u1"];
        v12 [label="v1"];
        
        // 第一个连通分量（包含u）
        subgraph cluster_comp1 {
            label="连通分量1";
            u2 -> a2;
            a2 -> b2;
            b2 -> c2;
            u2 -> u12;
        }
        
        // 第二个连通分量（包含v）
        subgraph cluster_comp2 {
            label="连通分量2";
            v2 -> v12;
        }
        
        // 删除的边用虚线连接两个分量
        u2 -> v2 [style=dashed, color=gray, label="删除", constraint=false];
    }
}
```





这个时候,可以虚拟的点,把两个部分,连接起来,形成一颗树,

```dot
digraph G {
    rankdir=TB;
    node [shape=circle];
    
    // 虚拟节点
    virtual [label="虚拟节点", shape=doublecircle, fillcolor=lightgray, style=filled];
    
    // 第一个连通分量（包含u）
    subgraph cluster_left {
        label="连通分量1（包含u）";
        style=dotted;
        
        u [label="u", fillcolor=yellow];
        a [label="a"];
        b [label="b"];
        u1 [label="u1"];
        
        u -> a;
        a -> b;
        u -> u1;
    }
    
    // 第二个连通分量（包含v）
    subgraph cluster_right {
        label="连通分量2（包含v）";
        style=dotted;
        
        v [label="v", fillcolor=orange];
        c [label="c"];
        v1 [label="v1"];
        
        v -> c;
        v -> v1;
    }
    
    // 虚拟节点连接两个分量
    virtual -> u [style=dashed, color=blue, label="连接"];
    virtual -> v [style=dashed, color=blue, label="连接"];
    
    // 说明
    note [label="虚拟节点：\n1. 不能被选中\n2. 连接两个连通分量\n3. 形成一棵树", shape=note, fillcolor=lightyellow, style=filled];
}
```



这个虚拟的点不能被选中, 那么就是求$dp[u][0]$


> 本质: 最值集合拆分

## 怎么题目虚拟点 ?

最简单的方式,就是删除点$u$在环上的一条边: 这样体现出来的虚拟的思想

![](./1.excalidraw.svg)

## 代码 

@include-code(./1.cpp, cpp)

