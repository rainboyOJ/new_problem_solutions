---
title: "C++ STL 竞赛入门题单"
description: "从 string、vector 和常用算法起步，练习栈、队列、list、关联容器与优先队列在竞赛中的选择和使用。"
order: 38
---

# C++ STL 竞赛入门题单

这份题单面向已经会 C++ 基础语法、但还没有 STL 实战经验的同学。做题时先问：我要保存什么、最常做什么操作、是否需要有序或去重；再选择容器或算法，不要把 STL 当成要背的接口表。

## 一、`string`：把文本当作可操作的序列

`string` 适合读入、扫描、修改文本。注意 `getline` 与 `cin` 的换行问题，以及下标访问前先确认没有越界。

- [ ] [[problem: luogu,P5733]] · [P5733 自动修正](https://www.luogu.com.cn/problem/P5733)
- [ ] [[problem: luogu,P1308]] · [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [ ] [[problem: luogu,P1553]] · [P1553 数字反转（升级版）](https://www.luogu.com.cn/problem/P1553)

## 二、`vector` 与 `pair`：动态保存同类数据和多字段记录

元素数量运行时才确定，或要整体传给算法时，优先考虑 `vector`。`pair` 能把紧密相关的两个值绑在一起；排序前要先写清“第一关键字、第二关键字”的顺序。

- [ ] [[problem: luogu,P3156]] · [P3156 询问学号](https://www.luogu.com.cn/problem/P3156)
- [ ] [[problem: luogu,P5738]] · [P5738 歌唱比赛](https://www.luogu.com.cn/problem/P5738)
- [ ] [[problem: luogu,P1104]] · [P1104 生日](https://www.luogu.com.cn/problem/P1104)
- [ ] [[problem: luogu,P1093]] · [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)

## 三、常用 `<algorithm>`：排序后再利用顺序

这一节练习 `sort`、`reverse`、`lower_bound` / `upper_bound`、`unique` + `erase` 和 `next_permutation`。二分查找的前提是区间已经按同一规则排序；`unique` 只把不重复元素移到前面，不能忘记再 `erase`。

- [ ] [[problem: luogu,P1177]] · [P1177 排序](https://www.luogu.com.cn/problem/P1177)
- [ ] [[problem: luogu,P1102]] · [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
- [ ] [[problem: luogu,P1678]] · [P1678 烦恼的高考志愿](https://www.luogu.com.cn/problem/P1678)
- [ ] [[problem: luogu,P1059]] · [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
- [ ] [[problem: luogu,P1706]] · [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)

## 四、`stack`：处理最近尚未匹配的对象

遇到括号匹配、后缀表达式，或“最后进入的元素先处理”时使用栈。每次 `top()` 或 `pop()` 前，都要保证栈非空。

- [ ] [[problem: luogu,P1739]] · [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
- [ ] [[problem: luogu,P1449]] · [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)
- [ ] [[problem: luogu,P1981]] · [P1981 表达式求值](https://www.luogu.com.cn/problem/P1981)

## 五、`queue` 与 `list`：按顺序处理和局部插删

`queue` 对应先进先出事件；弹出元素前先判断非空。`list` 只在已经定位到位置、又需要频繁插入或删除时才值得考虑；竞赛中多数连续存储需求仍优先选 `vector` 或数组。

- [ ] [[problem: luogu,P1540]] · [P1540 机器翻译](https://www.luogu.com.cn/problem/P1540)
- [ ] [[problem: luogu,P2058]] · [P2058 海港](https://www.luogu.com.cn/problem/P2058)
- [ ] [[problem: luogu,P1996]] · [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)
- [ ] [[problem: luogu,P1160]] · [P1160 队列安排](https://www.luogu.com.cn/problem/P1160)

## 六、`set` 与 `map`：去重、计数和按键查找

只关心“是否出现过”时用 `set`；要把键映射到次数或信息时用 `map`。`map[key]` 会在键不存在时创建它，纯查询时要留意这一点；有序性是它们比哈希容器更适合入门题的原因。

- [ ] [[problem: luogu,P1097]] · [P1097 统计数字](https://www.luogu.com.cn/problem/P1097)
- [ ] [[problem: luogu,P2141]] · [P2141 珠心算测验](https://www.luogu.com.cn/problem/P2141)
- [ ] [[problem: luogu,P3879]] · [P3879 阅读理解](https://www.luogu.com.cn/problem/P3879)
- [ ] [[problem: luogu,P3405]] · [P3405 Cities and States](https://www.luogu.com.cn/problem/P3405)

## 七、`priority_queue`：动态维护当前最值

`priority_queue` 适合不断加入元素、同时反复取当前最大或最小值。默认是大根堆；需要最小值时明确写出比较规则，并检查堆为空的边界。

- [ ] [[problem: luogu,P3378]] · [P3378 堆](https://www.luogu.com.cn/problem/P3378)
- [ ] [[problem: luogu,P1090]] · [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [ ] [[problem: luogu,P2085]] · [P2085 最小函数值](https://www.luogu.com.cn/problem/P2085)

## 八、综合练习：从操作需求反推工具

下面几题不再直接提示使用哪一种 STL。先列出每种操作的频率和顺序要求，再决定是否需要 `pair`、有序容器、堆或算法组合。

- [ ] [[problem: luogu,P1309]] · [P1309 瑞士轮](https://www.luogu.com.cn/problem/P1309)
- [ ] [[problem: luogu,P1631]] · [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
- [ ] [[problem: luogu,P1168]] · [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
- [ ] [[problem: luogu,P2234]] · [P2234 营业额统计](https://www.luogu.com.cn/problem/P2234)

## 复盘要求

每道题完成后补充：

```text
我选择的容器或算法：
它支持的关键操作及复杂度：
为什么数组、另一个容器或暴力做法不合适：
本题最容易遗漏的边界：
```
