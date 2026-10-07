   1| # luogu P1598 [USACO03FEB] 垂直柱状图 Vertical Histogram
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1598/index.md`（内容哈希 e260719e774cb178）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['字符串', '计数', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 读入四行字符，统计 `A` 到 `Z` 每个大写字母出现的次数，并按样例格式输出垂直柱状图。每一行末尾不能有多余空格。
  14| 
  15| ### 思路
  16| 
  17| 先统计 26 个大写字母的出现次数。设最高次数是 `max_height`，柱状图就从第 `max_height` 层往第 1 层输出。
  18| 
  19| 对于某一层 `level`：
  20| 
  21| - 如果某个字母的次数 `>= level`，这一列输出 `*`；
  22| - 否则输出空格。
  23| 
  24| 列与列之间固定用一个空格隔开。整行生成后，用 `rstrip()` 删除右侧多余空格，避免违反格式要求。最后输出字母行：
  25| 
  26| ```text
  27| A B C ... Z
  28| ```
  29| 
  30| 这题是计数和格式化输出练习，不创建 `brute.py`。
  31| 
  32| ## 代码位置
  33| - `problems/luogu/P1598/gen.py`
  34| - `problems/luogu/P1598/main-guide.cpp`
  35| - `problems/luogu/P1598/main-pythonic.py`
  36| - `problems/luogu/P1598/main.cpp`
  37| - `problems/luogu/P1598/main.py`