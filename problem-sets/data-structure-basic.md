---
title: "基础数据结构题单"
description: "从栈、队列、堆、并查集到单调栈和单调队列，建立后续图论、树和区间算法所需的数据结构基础。"
order: 52
---

# 基础数据结构题单

数据结构题的训练目标不是记住 API，而是知道每种结构维护了什么信息，以及为什么能把一次操作降到合适的复杂度。

## 一、栈与表达式

先掌握后进先出、括号匹配和表达式求值。遇到“最近的、还没有匹配的对象”，优先想到栈。

- [ ] [[problem: luogu,P1449]] · [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)
- [ ] [[problem: luogu,P1739]] · [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
- [ ] [[problem: luogu,P1241]] · [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)
- [ ] [[problem: luogu,P1175]] · [P1175 表达式的转换](https://www.luogu.com.cn/problem/P1175)

## 二、队列与模拟

队列适合处理先进先出的事件；循环队列和双端队列则是滑动窗口与 BFS 的基础。

- [ ] [[problem: luogu,P1996]] · [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)
- [ ] [[problem: luogu,P1540]] · [P1540 机器翻译](https://www.luogu.com.cn/problem/P1540)
- [ ] [[problem: luogu,P1160]] · [P1160 队列安排](https://www.luogu.com.cn/problem/P1160)
- [ ] [[problem: luogu,P2058]] · [P2058 海港](https://www.luogu.com.cn/problem/P2058)

## 三、堆与优先队列

堆解决“动态加入元素并反复取最小/最大值”的问题。先做模板，再做哈夫曼合并和多路归并。

- [ ] [[problem: luogu,P3378]] · [P3378 【模板】堆](https://www.luogu.com.cn/problem/P3378)
- [ ] [[problem: luogu,P1090]] · [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [ ] [[problem: luogu,P1631]] · [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
- [ ] [[problem: luogu,P2085]] · [P2085 最小函数值](https://www.luogu.com.cn/problem/P2085)

## 四、并查集

并查集维护动态连通块。重点理解路径压缩、按秩合并，以及“把额外关系挂在集合代表元上”的扩展方式。

- [ ] [[problem: luogu,P3367]] · [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
- [ ] [[problem: luogu,P1551]] · [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)
- [ ] [[problem: luogu,P1955]] · [P1955 程序自动分析](https://www.luogu.com.cn/problem/P1955)
- [ ] [[problem: luogu,P1455]] · [P1455 搭配购买](https://www.luogu.com.cn/problem/P1455)

## 五、单调栈与单调队列

当题目只关心窗口中的最值，或要求找到左侧/右侧第一个更大元素时，单调结构可以删除永远不可能成为答案的元素。

- [ ] [[problem: luogu,P5788]] · [P5788 【模板】单调栈](https://www.luogu.com.cn/problem/P5788)
- [ ] [[problem: luogu,P2866]] · [P2866 Bad Hair Day S](https://www.luogu.com.cn/problem/P2866)
- [ ] [[problem: luogu,P1886]] · [P1886 【模板】单调队列 / 滑动窗口](https://www.luogu.com.cn/problem/P1886)
- [ ] [[problem: luogu,P2032]] · [P2032 扫描](https://www.luogu.com.cn/problem/P2032)

## 过关标准

做完本题单后，应能解释：

```text
为什么这个操作符合栈/队列/堆的顺序：
为什么某个元素可以从单调结构中永久删除：
并查集合并后，哪些信息仍然可以代表整个集合：
```
