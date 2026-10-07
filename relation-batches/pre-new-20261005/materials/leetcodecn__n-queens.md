   1| # leetcodecn n-queens N 皇后
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/n-queens/index.md`（内容哈希 c720635b73f8d26e）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['回溯', '枚举', '递归']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 在 $n \times n$ 棋盘上放置 $n$ 个皇后，使任意两个皇后不在同一行、同一列或同一斜线上。返回所有合法方案的棋盘表示。
  14| 
  15| ### 思路
  16| 
  17| 最直接的思路是枚举每行皇后放在哪一列，全部决定后再检查冲突：
  18| 
  19| @include-code(./brute.cpp, cpp)
  20| 
  21| brute.cpp 先生成完整排列再检查冲突，复杂度 $O(n^n)$，对 $n \geqslant 8$ 会超时。
  22| 
  23| 优化的关键是：逐行放置时用三个冲突集合实时剪枝。
  24| 
  25| - `col[c]`：第 `c` 列是否已有皇后。
  26| - `diag1[r+c]`：主对角线（左上到右下）是否已有皇后。同一主对角线上的格子满足 `r+c` 相等。
  27| - `diag2[r-c+n-1]`：副对角线（右上到左下）是否已有皇后。同一副对角线上的格子满足 `r-c` 相等（偏移 `n-1` 避免负下标）。
  28| 
  29| 每行只放一个皇后，所以行冲突天然不存在。三个数组实时标记当前占据的列和对角线，放置前检查、放置后标记、递归后恢复，保证每一步只扩展合法分支。
  30| 
  31| ## 代码位置
  32| - `problems/leetcodecn/n-queens/brute.cpp`
  33| - `problems/leetcodecn/n-queens/gen.py`
  34| - `problems/leetcodecn/n-queens/main.cpp`
  35| - `problems/leetcodecn/n-queens/main.py`