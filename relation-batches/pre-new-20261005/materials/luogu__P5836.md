   1| # luogu P5836 [USACO19DEC] Milk Visits S
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P5836/index.md`（内容哈希 9e9214c70fd1e597）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及；标签：['LCA', '倍增', '前缀和', '树', 'USACO']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ## 思路
  12| 
  13| 先看一个可以直接验证想法的朴素解：
  14| 
  15| @include-code(./brute.cpp, cpp)
  16| 
  17| `brute.cpp` 对每次询问从 $a$ 出发沿树 DFS 找通向 $b$ 的唯一路径，再逐点统计 G 的个数：单次询问 $O(N)$，总复杂度 $O(NM)$，在 $10^5$ 的数据上不可行。
  18| 
  19| 关键观察：**只数一种颜色，剩下的用路径长度补**。以 1 为根，预处理每个节点到根路径上 G 的数量 `sumG[i]`，那么任意路径 $a \to b$ 上 G 的数量可以容斥得到：
  20| 
  21| $$\mathrm{cntG} = \mathrm{sumG}(a) + \mathrm{sumG}(b) - 2 \cdot \mathrm{sumG}(\mathrm{lca}(a,b)) + [\mathrm{color}(\mathrm{lca}) = G]$$
  22| 
  23| 路径上的点数 $\mathrm{len} = \mathrm{depth}(a) + \mathrm{depth}(b) - 2 \cdot \mathrm{depth}(\mathrm{lca}) + 1$，于是 $\mathrm{cntH} = \mathrm{len} - \mathrm{cntG}$。回答询问时，看目标品种的计数是否大于 0 即可。
  24| 
  25| 这句话的几何含义：路径 $a \to b$ 等于"根到 $a$ 的路径"和"根到 $b$ 的路径"的并集去掉公共前缀"根到 LCA"，再把被减了两次的 LCA 补回来。用样例树（颜色串 `HHGHG`，边 1-2、2-3、2-4、1-5）验证一条询问：
  26| 
  27| ```text
  28|        1 (H)
  29|       / \
  30|     2 (H) 5 (G)
  31|    / \
  32|  3 (G) 4 (H)
  33| 
  34| 询问 1 -> 4，喜欢 H：路径是 1 2 4，三个节点全是 H
  35| sumG(1) = 0    sumG(4) = 0    lca(1,4) = 1
  36| cntG = sumG(1) + sumG(4) - 2*sumG(1) + [color(1)=G] = 0
  37| len = depth(1) + depth(4) - 2*depth(1) + 1 = 1 + 3 - 2 + 1 = 3
  38| cntH = len - cntG = 3 > 0   ->  输出 1（样例第一位的 `1`）
  39| ```
  40| 
  41| 再看两个退化情况验证公式的鲁棒性：询问 `1 3 G` 时 LCA 仍是 1，`cntG = sumG(3) = 1 > 0`，输出 `1`；询问 `5 5 H` 时路径只有节点 5 自己（它是 G），`cntH = 1 - 1 = 0`，输出 `0`，正好对应样例输出 `10110` 的最后一位。可见当 LCA 恰是某个端点、甚至 $a = b$ 时，公式无需特判。
  42| 
  43| 实现上，一次 BFS 就能同时求出 `depth`、`sumG` 和倍增祖先表 `up[u][j]`；每次询问先用倍增表 $O(\log N)$ 求 LCA，再 $O(1)$ 套公式。这个预处理结构直接来自 rbook 的《[倍增求 LCA](https://rbook2.roj.ac.cn/tree-algo/jump-lca/index.html)》（模板 `lca-binary-lifting`）。
  44| 
  45| ## 代码位置
  46| - `problems/luogu/P5836/brute.cpp`
  47| - `problems/luogu/P5836/gen.py`
  48| - `problems/luogu/P5836/main.cpp`
  49| - `problems/luogu/P5836/main.py`