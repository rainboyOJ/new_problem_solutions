   1| # luogu P4391 [BalticOI 2009] Radio Transmission 无线传输
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P4391/index.md`（内容哈希 5c7ccba7ccc4f211）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['KMP', '周期', 'border', '哈希', '字符串', 'python', 'cpp']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 给出一段可能从周期信号中截取的字符串，求原信号最短可能长度。
  14| 
  15| ### 思路
  16| 
  17| 周期与 border 是同一枚硬币的两面：$\text{周期长度} = n - \text{border长度}$。最小周期对应最长 border。
  18| 
  19| #### KMP 法
  20| 
  21| 求前缀函数 $\text{pref}[i]$ 表示 $s[:i+1]$ 的最长 border。答案 $= n - \text{pref}[n-1]$。
  22| 
  23| #### 哈希法
  24| 
  25| 用滚动哈希直接枚举长度验证。
  26| 
  27| #### 周期与 border 的数学证明
  28| 
  29| **定义**：$\text{len}$ 是字符串 $s[1..n]$ 的周期 $\iff \forall i \in [1, n-\text{len}],\; s[i] = s[i+\text{len}]$。
  30| 
  31| **定理**：$\text{len}$ 是周期 $\iff s[1..n-\text{len}] = s[\text{len}+1..n]$。
  32| 
  33| **证明**（$\Rightarrow$）：对任意 $k \in [1, n-\text{len}]$，左边第 $k$ 个字符为 $s[k]$，右边第 $k$ 个字符为 $s[\text{len}+k]$。由周期定义取 $i=k$ 得 $s[k] = s[\text{len}+k]$。$k$ 的任意性保证两子串在所有对应位置相等，故 $s[1..n-\text{len}] = s[\text{len}+1..n]$。
  34| 
  35| （$\Leftarrow$）若 $s[1..n-\text{len}] = s[\text{len}+1..n]$，则对任意 $k \in [1, n-\text{len}]$ 有 $s[k] = s[\text{len}+k]$，即 $\text{len}$ 是周期。$\square$
  36| 
  37| #### 图解：样例 $cabcabca$（n=8）周期 $3$
  38| 
  39| ```
  40| ┌───┬───┬───┬───┬───┬───┬───┬───┐
  41| │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │  ← 位置
  42| ├───┼───┼───┼───┼───┼───┼───┼───┤
  43| │ c │ a │ b │ c │ a │ b │ c │ a │  ← 字符
  44| └───┴───┴───┴───┴───┴───┴───┴───┘
  45| ├───── s[1..5] ─────┤
  46|               ├───── s[4..8] ─────┤
  47|               ↑ 错位 len=3
  48| 
  49|       c a b c a
  50|       c a b c a        ← 5 个字符逐位相等
  51| ```
  52| 
  53| 逐位验证周期定义 $s[i]=s[i+len]$：
  54| 
  55| ```
  56| i=1: s[1]=c, s[4]=c  ✓
  57| i=2: s[2]=a, s[5]=a  ✓
  58| i=3: s[3]=b, s[6]=b  ✓
  59| i=4: s[4]=c, s[7]=c  ✓
  60| i=5: s[5]=a, s[8]=a  ✓
  61| ```
  62| 
  63| 答案 $= 3 = n - \text{border} = 8 - 5$。
  64| 
  65| #### 哈希原理
  66| 
  67| 滚动哈希把前缀视为 $P$ 进制数，$s[1]$ 在最高位：
  68| 
  69| $$
  70| h[i] = h[i-1] \times P + s[i]
  71| $$
  72| 
  73| 取子串 $s[l..r]$ 等价于切掉 $h[r]$ 的高位（$s[1..l-1]$）和低位（$s[r+1..n]$）：
  74| 
  75| $$
  76| \text{get\_hash}(l, r) = h[r] - h[l-1] \times p^{\,r-l+1}
  77| $$
  78| 
  79| 以 $P=10$，字符串 $\text{"abc"}$ 截取 $\text{"bc"}$（位置 $2\sim3$）为例：
  80| 
  81| | 表达式 | 值 |
  82| |--------|-----|
  83| | $h[3]$ | $a\cdot 10^2 + b\cdot 10 + c$ |
  84| | $h[1]$ | $a$ |
  85| | $h[1] \times 10^{2}$ | $a\cdot 10^2$ |
  86| | $h[3] - h[1]\times 10^{2}$ | $b\cdot 10 + c = \text{"bc"}$ |
  87| 
  88| 减去 $h[l-1] \times P^{\,r-l+1}$ 就是砍掉高位，保留长度 $r-l+1$ 的一段。
  89| 
  90| #### 哈希法枚举周期
  91| 
  92| 定理给出周期的充要条件：$s[1..n-\text{len}] = s[\text{len}+1..n]$。哈希法从 $\text{len}=1$ 枚举到 $n$，用 $\text{get\_hash}$ 判断此条件是否成立，第一个满足的 $\text{len}$ 就是最小周期。每次判断 $O(1)$，总 $O(n)$。
  93| 
  94| ## 代码位置
  95| - `problems/luogu/P4391/1.cpp`
  96| - `problems/luogu/P4391/2.cpp`
  97| - `problems/luogu/P4391/brute.cpp`
  98| - `problems/luogu/P4391/gen.py`
  99| - `problems/luogu/P4391/main-hash.cpp`
 100| - `problems/luogu/P4391/main-kmp.cpp`
 101| - `problems/luogu/P4391/main.cpp`
 102| - `problems/luogu/P4391/main.py`