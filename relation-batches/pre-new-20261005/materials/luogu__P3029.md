   1| # luogu P3029 [USACO11NOV] Cow Lineup S
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3029/index.md`（内容哈希 d924a75fbf1ada7f）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['双指针', '滑动窗口', '计数', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 在数轴上选择一个最短区间，使其中至少包含全体奶牛中每一种品种。
  14| 
  15| ### 思路
  16| 
  17| 先按坐标排序。右指针逐个加入奶牛；窗口已经包含全部品种时，不断移动左指针并更新长度，直到刚好缺少一种品种。
  18| 
  19| ### Python 知识
  20| 
  21| - `Counter` 保存窗口内各品种次数，删除计数归零的键后，`len(counts)` 就是当前品种数。
  22| - 集合推导式 `{breed for _, breed in cows}` 统计全局不同品种。
  23| - 元组排序同时保留坐标和品种信息，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`。
  24| 
  25| ## 代码位置
  26| - `problems/luogu/P3029/brute.cpp`
  27| - `problems/luogu/P3029/gen.py`
  28| - `problems/luogu/P3029/main-rainboy.py`
  29| - `problems/luogu/P3029/main.cpp`
  30| - `problems/luogu/P3029/main.py`