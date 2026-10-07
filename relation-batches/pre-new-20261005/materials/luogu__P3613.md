   1| # luogu P3613 【深基15.例2】寄包柜
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3613/index.md`（内容哈希 5cfc599964487a78）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['字典', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 有很多寄包柜，每个柜子的格子上界未知。支持给 `(柜子,格子)` 写入物品编号，以及查询该位置的物品。
  16| 
  17| ### 思路
  18| 
  19| 格子编号可能很大，但操作总数只有 `10^5`，没有必要为每个柜子开到最大编号。
  20| 
  21| 建立 `lockers[i]` 字典，只记录第 `i` 个柜子实际写入过的 `cell -> item`。写入和查询都直接使用两次下标，期望 $O(1)$ 完成。
  22| 
  23| ### Python 知识
  24| 
  25| - `[dict() for _ in range(n+1)]` 为每个柜子创建独立字典；不能写 `[{}]*(n+1)`，否则所有柜子会共享同一个字典。
  26| - `lockers[locker][cell]=item` 直接表达二维稀疏映射。
  27| - 操作行长度不同，按行读取后解包比整份 token 更直观。
  28| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`dict` 键值映射。
  29| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：可变容器不能用乘法复制。
  30| 
  31| ### 代码
  32| 
  33| @include-code(./main.py, python)
  34| 
  35| @include-code(./main.cpp, cpp)
  36| 
  37| 
  38| ### 复杂度
  39| 
  40| 每次操作期望 $O(1)$，总空间与不同的实际写入格子数成正比，最坏 $O(q)$。
  41| 
  42| ### 总结
  43| 
  44| 面对巨大但稀疏的二维编号空间，字典只存出现过的位置，通常比按最大下标开二维数组更自然。
  45| 
  46| ## 代码位置
  47| - `problems/luogu/P3613/main.cpp`
  48| - `problems/luogu/P3613/main.py`