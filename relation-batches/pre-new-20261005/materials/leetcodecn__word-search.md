   1| # leetcodecn word-search 单词搜索
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/word-search/index.md`（内容哈希 a1beb0ea8a1b51c8）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['回溯', '搜索', 'DFS', '网格']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 在 `m x n` 字符网格中判断是否存在一条路径，按相邻（水平/垂直）单元格依次拼出给定单词 `word`。同一个单元格不能重复使用。
  14| 
  15| ### 思路
  16| 
  17| 最直接的思路是从每个格子出发尝试 DFS 匹配单词：
  18| 
  19| @include-code(./brute.cpp, cpp)
  20| 
  21| brute.cpp 用独立的 `vis` 数组标记已访问格子，逻辑与 main.cpp 相同（本题 DFS 本身就是最优方案，因为必须逐字符尝试所有路径）。
  22| 
  23| 关键实现要点：
  24| 
  25| - 进入格子后立即标记（`vis[i][j] = true` 或 `board[i][j] = '#'`），防止路径中重复使用同一格子。
  26| - 递归返回后必须恢复现场（`vis[i][j] = false` 或 `board[i][j] = tmp`），否则后续从其他起点出发的搜索会看到被污染的网格。
  27| - 匹配失败的条件要全部检查：越界、已访问、字符不匹配。
  28| 
  29| ## 代码位置
  30| - `problems/leetcodecn/word-search/brute.cpp`
  31| - `problems/leetcodecn/word-search/gen.py`
  32| - `problems/leetcodecn/word-search/main.cpp`
  33| - `problems/leetcodecn/word-search/main.py`