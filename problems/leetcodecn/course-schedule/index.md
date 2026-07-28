---
oj: leetcodecn; problem_id: course-schedule; title: 课程表
difficulty: 中等; tags: [拓扑排序, BFS, 图, cpp, python]
description: 建图 + Kahn 队列删入度为零节点，处理完全部节点即无环。
---
[[TOC]]
### 题意
给定课程数和依赖关系，判断能否完成所有课程。
### 思路
建依赖图，统计入度，Kahn 算法不断删除入度为 0 的节点。全部处理完则无环。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(V+E)，空间 O(V+E)。
### 总结
拓扑排序判环，图的边方向是"先修课 -> 课程"。
