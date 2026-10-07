   1| # luogu P5266 【深基17.例6】学籍管理
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P5266/index.md`（内容哈希 02d16b24e8b3a4cf）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['字典', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 维护学生姓名和成绩，支持插入或修改、查询、删除，以及输出当前学生人数。
  16| 
  17| ### 思路
  18| 
  19| 姓名唯一确定一名学生，成绩是随姓名保存的值，正好对应字典的 `key -> value` 模型：
  20| 
  21| - `students[name]=score`：插入新学生或覆盖旧成绩；
  22| - `name in students`：判断学生是否存在；
  23| - `students[name]`：取得成绩；
  24| - `del students[name]`：删除；
  25| - `len(students)`：当前人数。
  26| 
  27| 逐条模拟即可，不需要自己实现哈希表。
  28| 
  29| ### Python 知识
  30| 
  31| - 字典赋值天然同时覆盖“插入”和“修改”两种情况。
  32| - 查询前先用 `in` 判断，避免不存在的键触发 `KeyError`。
  33| - `del mapping[key]` 删除指定键值对，`len(mapping)` 直接得到记录数。
  34| - 姓名保留为 `bytes` 也可以作为字典键，减少批量输入后的解码工作。
  35| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：字典的增删改查模式。
  36| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：按不同操作参数个数解析 token。
  37| 
  38| ### 代码
  39| 
  40| @include-code(./main.py, python)
  41| 
  42| @include-code(./main.cpp, cpp)
  43| 
  44| 
  45| ### 复杂度
  46| 
  47| 每次操作期望时间复杂度 $O(1)$；字典最多保存 $O(q)$ 名学生，空间复杂度 $O(q)$。
  48| 
  49| ### 总结
  50| 
  51| 先识别数据模型：唯一姓名是键，成绩是值。Python 字典已经完整提供这类管理系统需要的操作。
  52| 
  53| ## 代码位置
  54| - `problems/luogu/P5266/main.cpp`
  55| - `problems/luogu/P5266/main.py`