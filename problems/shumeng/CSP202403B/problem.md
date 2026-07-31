<blockquote class="note">
<p>
题目来自<a href="https://sim.csp.thusaac.com/contest/33/problem/1">第 33 次 CSP 认证 T2</a>，评测使用自造高质量复刻数据。我们承认原始题面与大样例版权均归<a href="https://www.ccf.org.cn/">中国计算机学会（CCF）</a>所有，因此题面与评测服务均免费对外开放。如果您认为我们侵犯了您的权益，可<a href="https://oj.shumeng.tech/wiki/about#contact">联系我们</a>。
</p>
</blockquote>


<blockquote class="note">
<p>本评测链接与原题在数据范围进行微调，修改了 $n,m$ 的上限，时间限制对应调整到 2 秒。</p>
</blockquote>

**时间限制：** ~~1.0 秒~~ 2.0 秒

**空间限制：** ~~512 MB~~ 1024 MB

## 题目背景

两个集合的 Jaccard 相似度定义为：

$$
 Sim(A, B) = \frac{|A \cap B|}{|A \cup B|} 
$$

即交集的大小除以并集的大小。当集合 $A$ 和 $B$ 完全相同时，$Sim(A, B) = 1$ 取得最大值；当二者交集为空时，$Sim(A, B) = 0$ 取得最小值。

## 题目描述

除了进行简单的词频统计，小 P 还希望使用 Jaccard 相似度来评估两篇文章的相似性。 具体来说，每篇文章均由若干个英文单词组成，且英文单词仅包含“大小写英文字母”。 对于给定的两篇文章，小 P 首先需要提取出两者的单词集合 $A$ 和 $B$，即去掉各自重复的单词。 然后计算出：

- $|A \cap B|$，即有多少个不同的单词同时出现在两篇文章中；
- $|A \cup B|$，即两篇文章一共包含了多少个不同的单词。

最后再将两者相除即可算出相似度。 需要注意，在整个计算过程中应当**忽略英文字母大小写**的区别，比如 `the`、`The` 和 `THE` 三者都应被视作同一个单词。

试编写程序帮助小 P 完成前两步，计算出 $|A \cap B|$ 和 $|A \cup B|$；小 P 将亲自完成最后一步的除法运算。

## 输入格式

从标准输入读入数据。

输入共三行。

输入的第一行包含两个正整数 $n$ 和 $m$，分别表示两篇文章的单词个数。

第二行包含空格分隔的 $n$ 个单词，表示第一篇文章；

第三行包含空格分隔的 $m$ 个单词，表示第二篇文章。

## 输出格式

输出到标准输出。

输出共两行。

第一行输出一个整数 $|A \cap B|$，即有多少个不同的单词同时出现在两篇文章中；

第二行输出一个整数 $|A \cup B|$，即两篇文章一共包含了多少个不同的单词。


```input1
3 2
The tHe thE
the THE
```

```output1
1
1
```

## 样例 1 解释

$A = B = A \cap B = A \cup B =$ `{the}`


```input2
9 7
Par les soirs bleus dete jirai dans les sentiers
PICOTE PAR LES BLES FOULER LHERBE MENUE
```

```output2
2
13
```

## 样例 2 解释

$A =$ `{bleus, dans, dete, jirai, les, par, sentiers, soirs}` $|A| = 8$

$B =$ `{bles, fouler, les, lherbe, menue, par, picote}` $|B| = 7$

$A \cap B =$ `{les, par}` $|A \cap B| = 2$


```input3
15 15
Thou that art now the worlds fresh ornament And only herald to the gaudy spring
Shall I compare thee to a summers day Thou art more lovely and more temperate
```


```output3
4
24
```

## 子任务

$80\%$ 的测试数据满足：$n, m \leq 100$ 且所有字母均为小写；

全部的测试数据满足：$n, m \leq 5\times 10^{5}$ 且每个单词最多包含 $10$ 个字母。

## 提示

本题输入量较大，请采用效率较高的读入方式。
