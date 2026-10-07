   1| # shumeng CSP202104B 邻域均值
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/shumeng/CSP202104B/index.md`（内容哈希 db9377580dd2c228）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['前缀和', '二维前缀和', '模拟']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ## 思路
  12| 
  13| 朴素做法是对每个像素遍历整个邻域求和，复杂度为 $O(n^2r^2)$。用二维前缀和可以把每个邻域的求和降为 $O(1)$。
  14| 
  15| ### 二维前缀和
  16| 
  17| $sum[i][j]$ 表示以 $(1,1)$ 到 $(i,j)$ 为对角矩形的像素总和，递推式为
  18| 
  19| $$
  20| sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+A[i][j]。
  21| $$
  22| 
  23| ### 判断较暗区域
  24| 
  25| 1. 对像素 $(i,j)$，把邻域裁剪成矩形 $[top,bottom]\times[left,right]$；
  26| 2. 用前缀和 $O(1)$ 求矩形内的总和与格子个数；
  27| 3. 用 $sum\le t\times count$ 比较，避免浮点误差。
  28| 
  29| 先看一个直接枚举邻域格子的朴素解：
  30| 
  31| @include-code(./brute.cpp, cpp)
  32| 
  33| ## 代码位置
  34| - `problems/shumeng/CSP202104B/brute.cpp`
  35| - `problems/shumeng/CSP202104B/gen.py`
  36| - `problems/shumeng/CSP202104B/main.cpp`