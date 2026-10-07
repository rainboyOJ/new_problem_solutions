   1| # luogu P2345 [USACO04OPEN] MooFest G
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P2345/index.md`（内容哈希 2dc86c45ba393f48）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['树状数组', '排序', '前缀和']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| $n$ 头奶牛，第 $i$ 头坐标 $x_i$（互不相同）、听力 $v_i$。每对奶牛 $(i,j)$ 交流音量 = $\max\{v_i, v_j\} \times |x_i - x_j|$。求所有点对音量之和。
  14| 
  15| 数据范围：$n \leqslant 2 \times 10^4$，$v_i, x_i \leqslant 2 \times 10^4$。
  16| 
  17| ### 思路
  18| 
  19| **一句话本质**：音量公式里的 $\max\{v_i, v_j\}$ 是障碍——按 $v$ 排序后，处理每头牛时它和"前面所有牛"的贡献中 $\max$ 就是它自己的 $v$，问题退化成"对每个 $x_i$，统计前面牛中左边/右边的数量与坐标和"，用两个树状数组 $O(\log n)$ 完成。
  20| 
  21| 先看最直接的暴力：
  22| 
  23| @include-code(./brute.cpp, cpp)
  24| 
  25| 暴力枚举所有 $\binom{n}{2}$ 个点对，$O(n^2)$，$n = 2 \times 10^4$ 时 $2 \times 10^8$ 次计算，不可行。
  26| 
  27| **$\max\{v_i, v_j\}$ 怎么消掉？**
  28| 
  29| 如果让听力小的先被处理，那它和听力大的牛配对时，$\max$ 一定是大的一方。把牛按 $v$ **从小到大排序**，依次处理。处理到第 $i$ 头牛时，它和前面 $i-1$ 头牛的贡献都是 $v_i \times |x_i - x_j|$——$\max$ 被排序消掉了。
  30| 
  31| **剩下的 $|x_i - x_j|$ 怎么统计？**
  32| 
  33| 对第 $i$ 头牛，它和前面所有牛的贡献：
  34| 
  35| $$v_i \times \sum_{j < i} |x_i - x_j|$$
  36| 
  37| 绝对值拆成左右两边：坐标比 $x_i$ 小的牛（数量 $c_l$、坐标和 $s_l$）贡献 $x_i \cdot c_l - s_l$；坐标比 $x_i$ 大的牛（$c_g$、$s_g$）贡献 $s_g - x_i \cdot c_g$。于是只需要维护：前面牛的坐标中，**小于某个值的数量与坐标和**——标准的树状数组前缀查询。
  38| 
  39| **为什么用两个树状数组？**
  40| 
  41| 坐标范围只有 $2 \times 10^4$，直接以坐标为下标：
  42| 
  43| - `bit_cnt` 维护坐标出现次数（查 $c_l$）；
  44| - `bit_sum` 维护坐标值之和（查 $s_l$）。
  45| 
  46| 查询 $x_i - 1$ 的前缀得到"左边"，总数减去左边得到"右边"：
  47| 
  48| ```cpp
  49| long long cnt_less = query(bit_cnt, x - 1);
  50| long long sum_less = query(bit_sum, x - 1);
  51| long long cnt_greater = cnt_all - cnt_less;      // cnt_all = i-1
  52| long long sum_greater = sum_all - sum_less;
  53| 
  54| ans += 1LL * v * (x * cnt_less - sum_less + sum_greater - x * cnt_greater);
  55| ```
  56| 
  57| 处理完当前牛再把它插入两个 BIT，保证"前面"的含义正确。
  58| 
  59| ## 代码位置
  60| - `problems/luogu/P2345/brute.cpp`
  61| - `problems/luogu/P2345/gen.py`
  62| - `problems/luogu/P2345/main.cpp`
  63| - `problems/luogu/P2345/main.py`