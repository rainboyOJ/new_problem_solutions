   1| # luogu P1786 帮贡排序
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1786/index.md`（内容哈希 110a6c805b37893f）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['排序', '模拟', '结构体', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 帮派成员有姓名、职位、帮贡和等级。帮主和副帮主职位不能调整；其他人先按帮贡从高到低、输入顺序从前到后排序，重新分配职位。最后按职位高低、等级从高到低、输入顺序从前到后输出。
  14| 
  15| ### 思路
  16| 
  17| 每个成员用字典保存：
  18| 
  19| ```python
  20| name, role, contribution, level, index
  21| ```
  22| 
  23| 第一阶段：筛出可调整成员，排序关键字为：
  24| 
  25| ```python
  26| (-contribution, index)
  27| ```
  28| 
  29| 然后按名额依次分配 `HuFa`、`ZhangLao`、`TangZhu`、`JingYing`、`BangZhong`。
  30| 
  31| 第二阶段：全体成员排序，关键字为：
  32| 
  33| ```python
  34| (role_rank[role], -level, index)
  35| ```
  36| 
  37| 其中 `role_rank` 表示职位从高到低的顺序。
  38| 
  39| ## 代码位置
  40| - `problems/luogu/P1786/gen.py`
  41| - `problems/luogu/P1786/main.cpp`
  42| - `problems/luogu/P1786/main.py`