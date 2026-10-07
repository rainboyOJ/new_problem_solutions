   1| # noi_openjudge ch0107-11 潜伏者
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0107-11/index.md`（内容哈希 b0f8436ca8faf49e）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['字符串', '映射', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 已知一条密文及其原文，恢复代换密码并翻译新密文；映射必须是一一对应且覆盖全部 $26$ 个大写字母。
  16| 
  17| ### 思路
  18| 
  19| `cipher_to_plain` 记录密字对应的原字，`plain_to_cipher` 记录反向关系。扫描已知对应时，两张表都不能和已有记录冲突。最后检查密文字母是否恰有 $26$ 个，才能翻译新信息。
  20| 
  21| ### 代码
  22| 
  23| ## Python代码
  24| 
  25| @include-code(./main.py, python)
  26| 
  27| ## C++代码
  28| 
  29| @include-code(./main.cpp, cpp)
  30| 
  31| ### 复杂度
  32| 
  33| 设三行字符串总长度为 $n$，时间复杂度为 $O(n)$，映射空间为 $O(26)$。
  34| 
  35| ### 总结
  36| 
  37| 一一映射校验应同时检查正向和反向，才能发现两个原字共用一个密字。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0107-11/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0107-11/main.cpp`
  42| - `problems/noi_openjudge/ch0107-11/main.py`