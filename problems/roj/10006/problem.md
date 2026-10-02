# 涨薪

【题目描述】

公司中总共有 $n$ 个人，其中第 $i$ 个人的初始工资为 $a_i$。公司根据每个人的绩效（工作表现）来评定每个人的涨薪幅度。每年有 $x$ 个人绩效为 A，工资可以变为原来的 3 倍；$y$ 个人绩效为 B，工资可以变为原来的 2 倍，其余人绩效为 C，工资不变，连续两年绩效为 C 会被开除。（保证 $x + y \leqslant n$）

假如公司没有一直招聘新员工，请问 $m$ 年后，公司需要给所有**在职员工**支付的工资总和最多为多少。由于答案可能很大，请输出对 $10^9 + 7$ 取模后的结果。

【输入格式】

输入第一行包含四个正整数 $n, m, x, y$，意义如题面所示。

接下来一行包含 $n$ 个正整数，第 $i$ 个正整数为 $a_i$ 代表第 $i$ 个人的初始工资。

【输出格式】

输出一行一个整数表示 $m$ 年后工资总和对 $10^9 + 7$ 取模后的结果。

【样例 1 输入】

```plaintext
2 1 1 1
5 3
```

【样例 1 输出】

```plaintext
21
```

【样例 2 输入】

```plaintext
2 2 0 0
5 2
```

【样例 2 输出】

```plaintext
0
```

【数据范围】

- 对于 20% 的数据范围，满足 $n \leqslant 10, m \leqslant 10, a_i \leqslant 10$
- 对于 40% 的数据范围，满足 $n \leqslant 10^5, m \leqslant 10, a_i \leqslant 10^5$
- 对于另外 20% 的数据范围，满足 $n \leqslant 10^5, m \leqslant 10, a_i \leqslant 10^5$ 且 $x + y = n$
- 对于另外 20% 的数据范围，满足 $n \leqslant 10^5, m \leqslant 10^9, a_i \leqslant 10^5$ 且 $x + y = n$
- 对于 100% 的数据范围，满足 $1 \leqslant n \leqslant 10^5, 1 \leqslant m \leqslant 10^9, 1 \leqslant a_i \leqslant 10^5$

来源：https://roj.ac.cn/problem/10006
