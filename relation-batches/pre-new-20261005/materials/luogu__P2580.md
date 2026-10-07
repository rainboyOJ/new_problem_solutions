   1| # luogu P2580 于是他错误的点名开始了
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P2580/index.md`（内容哈希 c8fa803d0f964922）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['集合', '字符串', '状态记录', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 每次读到一个姓名：不在名单输出 `WRONG`，第一次点到合法姓名输出 `OK`，之后再次点到输出 `REPEAT`。
  14| 
  15| ### 思路
  16| 
  17| 维护两个集合：
  18| 
  19| - `valid`：完整合法名单，始终不变；
  20| - `called`：已经正确点到过的姓名。
  21| 
  22| 按 `name not in valid`、`name in called` 的顺序判断即可。只有输出 `OK` 时才加入 `called`，错误姓名重复出现仍然应输出 `WRONG`。
  23| 
  24| ### Python 知识
  25| 
  26| - 集合推导式 `{next(data) for ...}` 直接读取名单。
  27| - `bytes` 可作为集合键，不必为每个姓名解码成 Unicode 字符串。
  28| - `set.add` 记录已出现状态，平均复杂度 $O(1)$。
  29| - 答案列表最后用换行连接，避免频繁输出。
  30| 
  31| ## 代码位置
  32| - `problems/luogu/P2580/brute.cpp`
  33| - `problems/luogu/P2580/gen.py`
  34| - `problems/luogu/P2580/main.cpp`
  35| - `problems/luogu/P2580/main.py`