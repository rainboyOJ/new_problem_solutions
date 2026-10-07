   1| # leetcodecn letter-combinations-of-a-phone-number 电话号码的字母组合
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/letter-combinations-of-a-phone-number/index.md`（内容哈希 099088bcd6f674cd）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['回溯', '枚举', '递归']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 给定仅含数字 `2-9` 的字符串 `digits`，每个数字对应一组字母（如 `2→abc`、`7→pqrs`、`9→wxyz`），返回所有可能的字母组合。空输入返回空列表。
  14| 
  15| ### 思路
  16| 
  17| 每层递归处理一个数字，枚举该数字映射的所有字母，选一个后递归到下一层。这棵递归树的深度等于 `digits` 的长度，每层分支数由对应按键决定（`7` 和 `9` 各 4 个字母，其余 3 个）。
  18| 
  19| 先看一个可以直接验证想法的朴素解：
  20| 
  21| @include-code(./brute.cpp, cpp)
  22| 
  23| 朴素解与最终做法完全相同——本题的回溯枚举本身就是最优方案，因为必须输出所有组合，总方案数 $4^k$ 无法省略。brute.cpp 与 main.cpp 的区别仅在代码组织形式。
  24| 
  25| 关键实现：`cur` 在递归前 `push_back`，递归后 `pop_back`，保证每个位置的选择、递归、恢复三步对称；`dfs(i)` 表示正在决定第 `i` 位数字对应的字母。
  26| 
  27| 空输入直接返回空列表，不需要进入递归。
  28| 
  29| ## 代码位置
  30| - `problems/leetcodecn/letter-combinations-of-a-phone-number/brute.cpp`
  31| - `problems/leetcodecn/letter-combinations-of-a-phone-number/gen.py`
  32| - `problems/leetcodecn/letter-combinations-of-a-phone-number/main.cpp`
  33| - `problems/leetcodecn/letter-combinations-of-a-phone-number/main.py`