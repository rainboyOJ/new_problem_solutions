---
oj: "roj"
problem_id: "1060"
title: "均值"
description: "按定义 sum/n 求均值，教学点在定点 4 位小数输出（f-string 的 :.4f 对齐 C++ fixed+setprecision）与按 n 截取 token 的读入方式。"
difficulty: "入门"
date: 2026-09-29 16:45
updated: 2026-09-29 16:50
toc: true
tags: ["入门", "模拟", "浮点输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1060
---

[[TOC]]

## 形式化题目

给定 $n$（$n<100$）个绝对值不超过 $1000$ 的浮点数 $x_1,\dots,x_n$，输出

$$
\bar{x} = \frac{1}{n}\sum_{i=1}^{n} x_i
$$

精确到小数点后 4 位（定点格式，末尾补零）。样例 $n=2$、$x=(1.0,\,3.0)$，输出 `2.0000`。

## 正解

### 思路

本题没有可优化的算法——按定义一遍求和再除以 $n$ 就是最终解法，
朴素写法与最优写法是同一段代码，所以直接讲做法。真正的教学点在三个实现细节。

**第一：输出是"定点 4 位"，不是"最多 4 位"。** 参考实现用的是
`setiosflags(ios::fixed) << setprecision(4)`，即固定小数点后 4 位：不足补零、超出舍入。
样例输出 `2.0000` 而不是 `2.0` 正是这个意思；数据里的 `-4.3700`（problem8）也一样，
末尾两个 0 必须保留。Python 里对应的是 f-string 的定点格式

```python
f"{mean:.4f}"
```

容易踩的坑是写成 `round(mean, 4)` 再 `print`：`round` 只负责数值舍入，
不负责展示格式，`round(2.0, 4)` 打印出来是 `2.0`，尾零丢了，判 WA。

**第二：以 $n$ 为准读数，而不是按行读。** 参考实现是 `for (i=1; i<=num; i++) cin >> n;`
逐个读满 $n$ 个数，行结构不参与逻辑。Python 侧照抄这个语义：一次读入全部内容按空白切成 token，
第 0 个 token 是 $n$，其后**切前 $n$ 个**作为样本：

```python
data = sys.stdin.buffer.read().split()
n = int(data[0])
mean = sum(map(float, data[1:1+n])) / n
```

`data[1:1+n]` 这个切片同时回答了"从哪开始"（跳过 $n$ 本身）和"读几个"（正好 $n$ 个），
与 C++ 循环读 `num` 个数一一对应；至于输入是一行还是多行、空格多宽，都被 `split()` 归一化了。

**第三：求和保持一个表达式。** `sum(map(float, ...))` 是惰性单遍：`map` 把 token 逐个转成
`float`（等价于 `cin >> double`），`sum` 边产边消费，不建中间列表，也不写
"累加变量 + for 循环"的三段式。这正是 Pythonic 求和的惯用形态。

精度上不需要任何处理：每个样本绝对值 $\leqslant 1000$、$n<100$，总和 $|S|<10^5$；
输入十进制只有两位小数，`float`（IEEE 754 双精度，53 位尾数）的转换与求和误差在
$10^{-11}$ 量级，除以 $n$ 后更小，比能改变第 4 位小数舍入的 $5\times10^{-5}$ 小四个数量级，
舍入结果与参考实现一致。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$。读入 $n$ 个 token、转换 $n$ 次、求和一遍、除法与格式化 $O(1)$；
  实测约 0.015 s/组（主要是解释器启动），限额 1000 ms。
- 空间复杂度：$O(n)$。token 列表与常数量级的局部变量，$n<100$，远低于 128 MB。

## 总结

- 均值 = `sum(样本) / n`，一遍 $O(n)$，无任何可优化结构。
- 输出必须定点 4 位：`f"{mean:.4f}"` 对齐 C++ 的 `fixed + setprecision(4)`；
  `round(x, 4)` 不保留尾零，会 WA。
- 读入按 token 全量切分后取 `data[1:1+n]`，以 $n$ 为准，与参考实现"循环读 num 个数"同构。
- 验证：数据仓 10 组真实数据（含负均值、整数均值、尾零场景）全部 PASS。
