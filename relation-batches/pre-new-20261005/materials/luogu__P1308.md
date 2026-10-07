   1| # luogu P1308 [NOIP 2011 普及组] 统计单词数
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1308/index.md`（内容哈希 0abd7d11e044e5b8）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['字符串', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 给定一个目标单词和一整行文章。匹配时不区分大小写，但必须匹配完整单词，不能只匹配某个长单词的一部分。输出出现次数和第一次出现的位置；如果没有出现，输出 `-1`。
  14| 
  15| ### 思路
  16| 
  17| 先把目标单词和文章都转成小写。
  18| 
  19| 为了保证“完整单词”匹配，可以在文章两端各补一个空格，并把目标单词也变成 `" " + word + " "`。这样只有左右都是边界空格时才会匹配。
  20| 
  21| 如果：
  22| 
  23| ```text
  24| padded_article = " " + article + " "
  25| padded_word = " " + word + " "
  26| ```
  27| 
  28| 那么 `padded_article.find(padded_word)` 返回的位置，刚好等于目标单词在原文章中的起始位置。
  29| 
  30| 这题是整行输入和字符串查找练习，不创建 `brute.py`。
  31| 
  32| ## 代码位置
  33| - `problems/luogu/P1308/brute.cpp`
  34| - `problems/luogu/P1308/brute.py`
  35| - `problems/luogu/P1308/gen.py`
  36| - `problems/luogu/P1308/main-guide.cpp`
  37| - `problems/luogu/P1308/main-pythonic.py`
  38| - `problems/luogu/P1308/main.cpp`
  39| - `problems/luogu/P1308/main.py`