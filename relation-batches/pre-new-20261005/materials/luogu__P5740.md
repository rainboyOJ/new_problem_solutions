   1| # luogu P5740 【深基7.例9】最厉害的学生
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P5740/index.md`（内容哈希 f1c2f5b1deb83a37）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['模拟', '结构体', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出若干名学生的姓名和三科成绩。输出总分最高的学生信息；如果总分相同，输出输入中靠前的那位。
  16| 
  17| ### 思路
  18| 
  19| Python 里可以用元组保存一名学生：
  20| 
  21| ```python
  22| (name, chinese, math, english)
  23| ```
  24| 
  25| 顺序读入每名学生，计算三科总分。只有当当前学生总分严格大于 `best_total` 时，才更新答案。这样如果总分相同，就会自然保留先出现的学生。
  26| 
  27| 这题是记录数据和维护最大值练习，不创建 `brute.py`。
  28| 
  29| ### Python 知识
  30| 
  31| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：一行中混合字符串和整数时，先 `split()` 再分别转换。
  32| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：元组适合保存固定结构的一条记录。
  33| - `best_student = (name, chinese, math, english)` 保存当前最优记录。
  34| - 只在 `total > best_total` 时更新，保留并列时靠前者。
  35| 
  36| ### 代码
  37| 
  38| @include-code(./main.py, python)
  39| 
  40| @include-code(./main.cpp, cpp)
  41| 
  42| ### Guide 风格代码
  43| 
  44| cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：
  45| 
  46| @include-code(./main-guide.cpp, cpp)
  47| 
  48| ### 复杂度
  49| 
  50| 扫描 `N` 名学生，每名学生只处理常数个字段，时间复杂度是 $O(N)$，空间复杂度是 $O(1)$。
  51| 
  52| ### 总结
  53| 
  54| 结构体入门题在 Python 中可以先用元组表达记录。维护“最先出现的最大值”时，并列不更新即可。
  55| 
  56| ## 代码位置
  57| - `problems/luogu/P5740/gen.py`
  58| - `problems/luogu/P5740/main-guide.cpp`
  59| - `problems/luogu/P5740/main.cpp`
  60| - `problems/luogu/P5740/main.py`