---
oj: "shumeng"
problem_id: "CSP202104C"
title: "DHCP 服务器"
description: "按时刻处理租约到期事件，并模拟地址池状态与 DHCP 报文规则。"
difficulty: "提高+/省选-"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "优先队列", "状态机"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202104C
---

[[TOC]]

### 题意

模拟 DHCP 服务器收到的 Discover 和 Request 报文，维护地址的未分配、待分配、占用和过期状态，并输出服务器回复。

### 思路

地址记录状态、占用者和过期时刻。按报文时间推进前，弹出所有已经到期的事件：待分配变回未分配，占用变为过期。用两个有序集合分别维护最小未分配地址和最小过期地址；主机名映射到其地址，以常数或对数时间复用旧地址、撤销发往其它服务器的待分配地址。

处理报文前先按题意过滤接收者和类型。Discover 选择该主机原有地址，否则选择最小未分配、再选择最小过期地址，并回复 Offer；Request 发往本机时验证占用者、更新租约并回复 Ack 或 Nak。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个地址状态变化至多产生一个可验证的过期事件。除输出外每个报文的集合和堆操作为 $O(\log N)$，空间复杂度为 $O(N)$。

### 总结

把到期处理放在每个报文处理之前，能将逻辑时钟规则转为普通事件模拟；地址状态和最小可用地址集合必须同步更新。
