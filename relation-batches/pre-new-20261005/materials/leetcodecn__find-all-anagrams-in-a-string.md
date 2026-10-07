   1| # leetcodecn find-all-anagrams-in-a-string 找到字符串中所有字母异位词
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/find-all-anagrams-in-a-string/index.md`（内容哈希 25dee677d7ae3d38）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['哈希表', '字符串', '滑动窗口', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给定字符串 s 和 p，找出 s 中所有 p 的字母异位词子串的起始下标。
  16| 
  17| ### 思路
  18| 
  19| 暴力排序每个窗口 O(nk log k)。优化：用 26 维计数器维护窗口内字符频次，每次窗口滑动时只更新进出两个字符，然后比较整个计数数组是否归零。
  20| 
  21| 
  22| ### 代码
  23| 
  24| @include-code(./main.cpp, cpp)
  25| @include-code(./main.py, python)
  26| ### 复杂度
  27| 
  28| - 时间复杂度：O(n)，每个字符进出各一次，每次检查 26 个计数（常数）。
  29| - 空间复杂度：O(1)，固定 26 长度的计数数组。
  30| 
  31| ### 总结
  32| 
  33| 固定长度滑动窗口配合计数数组做"异位词匹配"，是字符串模式匹配的经典模型。窗口滑动时只维护变化的两端，将每次匹配的时间从 O(k log k) 降到 O(1)。
  34| 
  35| ## 代码位置
  36| - `problems/leetcodecn/find-all-anagrams-in-a-string/brute.cpp`
  37| - `problems/leetcodecn/find-all-anagrams-in-a-string/gen.py`
  38| - `problems/leetcodecn/find-all-anagrams-in-a-string/main.cpp`
  39| - `problems/leetcodecn/find-all-anagrams-in-a-string/main.py`