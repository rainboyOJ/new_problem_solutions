   1| # leetcodecn palindrome-partitioning 分割回文串
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/palindrome-partitioning/index.md`（内容哈希 dba4fa87e2683019）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['回溯', '枚举', '字符串', '动态规划']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 给定字符串 `s`，将其分割成若干子串，使每个子串都是回文串。返回所有可能的分割方案。
  14| 
  15| ### 思路
  16| 
  17| 最直接的思路是枚举所有切分方式，逐一检查每段是否回文：
  18| 
  19| @include-code(./brute.cpp, cpp)
  20| 
  21| brute.cpp 每次枚举 `s[i..j]` 作为下一段，只有当它是回文时才递归 `dfs(j+1)`。这种"只递归回文前缀"的剪枝已经排除了大量无效分支。
  22| 
  23| 优化的关键是：将回文判断从 $O(k)$ 降到 $O(1)$。预处理 `pal[i][j]` 表示 `s[i..j]` 是否回文：`pal[i][j] = (s[i]==s[j]) && (j-i<2 || pal[i+1][j-1])`，从右下向左上填充。递归时只需查表，不再逐字符比较。
  24| 
  25| ## 代码位置
  26| - `problems/leetcodecn/palindrome-partitioning/brute.cpp`
  27| - `problems/leetcodecn/palindrome-partitioning/gen.py`
  28| - `problems/leetcodecn/palindrome-partitioning/main.cpp`
  29| - `problems/leetcodecn/palindrome-partitioning/main.py`