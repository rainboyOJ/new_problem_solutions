   1| # luogu P1470 [IOI 1996 / USACO2.3] 最长前缀 Longest Prefix
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1470/index.md`（内容哈希 3e72db76ebdb204c）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['动态规划', '字符串', 'defaultdict', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 给定最多 200 个短原串，它们可以重复使用。求目标序列能由这些原串拼出的最长前缀长度。
  14| 
  15| ### 思路
  16| 
  17| 令 `dp[i]` 表示前缀 `S[0..i)` 能否由词集完整拆开，边界 `dp[0]=true`。
  18| 
  19| 转移时枚举最后一个词的长度 `len`：若后缀 `S[i-len..i)` 是一个词，且 `dp[i-len]` 为真，则 `dp[i]=true`。词长最多 10，所以从 `i` 往回最多尝试 10 个长度，而不是遍历全部原串。
  20| 
  21| “后缀是否是词”有两种查询方式：
  22| 
  23| - 哈希：`hash.cpp` 直接用 `unordered_set` 存词，构造子串后查询，实现最简单。
  24| - 有序集合：`set.cpp` 用 `set<string>` 存词，查询 `O(log |P|)` 次字符串比较；词集只有 200 个、词长不超过 10，开销可忽略。
  25| - 倒序 Trie：`trie.cpp` 把每个词反着插入，让 `S` 从 `i` 往回走，边走边判断；走不动时说明不存在更长的候选词，直接剪枝。
  26| 
  27| 注意 `dp[i]` 并不是单调的（例如 `i` 可达不代表 `i+1` 可达），所以答案要取所有可达位置的最大值。
  28| 
  29| ## 代码位置
  30| - `problems/luogu/P1470/brute.cpp`
  31| - `problems/luogu/P1470/gen.py`
  32| - `problems/luogu/P1470/hash.cpp`
  33| - `problems/luogu/P1470/main.cpp`
  34| - `problems/luogu/P1470/main.py`
  35| - `problems/luogu/P1470/set.cpp`
  36| - `problems/luogu/P1470/trie.cpp`