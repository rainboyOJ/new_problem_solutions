   1| # luogu P1803 凌乱的yyy / 线段覆盖
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1803/index.md`（内容哈希 4f32c73e100fea0f）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['贪心', '排序', '区间贪心', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给定若干比赛的开始时间和结束时间。参加一个比赛必须完整参加，不能同时参加两个比赛。问最多能参加几个比赛。
  16| 
  17| ### 思路
  18| 
  19| 经典区间调度贪心：按结束时间从早到晚排序。
  20| 
  21| 扫描排序后的比赛，如果当前比赛的开始时间不早于上一个已选比赛的结束时间，就选择它。
  22| 
  23| 为什么这样对？结束越早，留给后面比赛的时间越多。若某个最优方案当前选了一个结束更晚的可选比赛，可以把它替换成结束更早的比赛，不会减少后续可选空间。
  24| 
  25| ### Python 知识
  26| 
  27| - 把区间保存成 `(end, start)`，直接 `sort()` 就按结束时间升序排列。
  28| - `sys.stdin.buffer.read().split()` 适合 `n` 最大到 `10^6` 的大量整数输入。
  29| - 扫描时只维护 `last_end` 和答案数量，不需要保存选择列表。
  30| 
  31| 参考笔记：
  32| 
  33| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`
  34| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`
  35| 
  36| ### 代码
  37| 
  38| @include-code(./main.py, python)
  39| 
  40| 
  41| ### 复杂度
  42| 
  43| 排序时间复杂度为 $O(n\log n)$，扫描为 $O(n)$，空间复杂度为 $O(n)$。
  44| 
  45| ### 总结
  46| 
  47| 区间覆盖/区间调度中，“最多选不相交区间”通常优先考虑按右端点排序的贪心。
  48| 
  49| ## 代码位置
  50| - `problems/luogu/P1803/brute.cpp`
  51| - `problems/luogu/P1803/brute.py`
  52| - `problems/luogu/P1803/gen.py`
  53| - `problems/luogu/P1803/main.cpp`
  54| - `problems/luogu/P1803/main.py`