   1| # luogu P2670 [NOIP 2015 普及组] 扫雷游戏
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P2670/index.md`（内容哈希 69522a6291250f4a）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['模拟', '矩阵', '枚举', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出扫雷棋盘，`*` 表示地雷，`?` 表示非雷格。对每个非雷格，输出它周围八个方向中地雷的个数；地雷格仍输出 `*`。
  16| 
  17| ### 思路
  18| 
  19| 先列出八个方向：
  20| 
  21| ```python
  22| (-1,-1), (-1,0), ..., (1,1)
  23| ```
  24| 
  25| 枚举每个格子：
  26| 
  27| - 如果当前是 `*`，答案也是 `*`；
  28| - 否则枚举八个邻格，检查是否在边界内且为 `*`，统计数量。
  29| 
  30| 每一行用字符列表构造，最后 `"".join(current)` 变成输出字符串。
  31| 
  32| ### Python 知识
  33| 
  34| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符网格可按行保存为字符串列表。
  35| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：二维矩阵枚举常用 `for row` / `for col` 双循环。
  36| - `0 <= nr < n and 0 <= nc < m` 是常见边界判断。
  37| - `"\n".join(answer)` 一次输出多行。
  38| 
  39| ### 代码
  40| 
  41| @include-code(./main.py, python)
  42| 
  43| @include-code(./main.cpp, cpp)
  44| 
  45| 
  46| ### 复杂度
  47| 
  48| 每个格子最多检查 8 个方向，时间复杂度是 $O(nm)$，空间复杂度是 $O(nm)$。
  49| 
  50| ### 总结
  51| 
  52| 网格邻域题先固定方向数组，再对每个格子套同一套边界判断和统计逻辑。
  53| 
  54| ## 代码位置
  55| - `problems/luogu/P2670/gen.py`
  56| - `problems/luogu/P2670/main.cpp`
  57| - `problems/luogu/P2670/main.py`