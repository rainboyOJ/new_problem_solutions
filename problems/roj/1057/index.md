---
oj: "roj"
problem_id: "1057"
title: "简单计算器"
description: "把「操作符→运算」做成 4 键分发表，合法性即键是否存在；除零单独判，并用绝对值补符号实现 C++ 的向零取整除法。"
difficulty: "入门"
date: 2026-09-29 16:35
updated: 2026-09-29 16:48
toc: true
tags: ["入门", "模拟", "分派表", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1057
---

[[TOC]]

## 形式化题目

给定两个整数 $a, b$ 和一个操作符 $\operatorname{op}$，输出

$$
\text{answer} = \begin{cases}
\texttt{Invalid operator!} & \operatorname{op} \notin \{+,-,*,/\} \\
\texttt{Divided by zero!} & \operatorname{op} = / \;\wedge\; b = 0 \\
a \operatorname{op} b & \text{otherwise}
\end{cases}
$$

这里的 `/` 是整数除法，口径与参考实现一致：商向零取整；
$b = 0$ 时除法无定义，落入第二条错误分支。样例 `1 2 +` 落在第三种情况，输出 `3`。

## 正解

### 思路

本题没有可优化的算法——整题就是一次分支加一次二元运算，写一份"暴力"会与正解逐字相同，
所以直接讲做法。真正的教学点有两个：**如何组织四则运算的分派**，以及
**Python 的整除和 C++ 到底差在哪**。

先看最直白的写法，也就是把参考实现 `std.cpp` 的 `if + switch` 直译过来
（为便于阅读，这段假定 `op` 已解码成 `str`；最终代码里它是 `bytes`）：

```python
if op == '+':
    print(a + b)
elif op == '-':
    print(a - b)
elif op == '*':
    print(a * b)
elif op == '/':
    print('Divided by zero!' if b == 0 else a // b)
else:
    print('Invalid operator!')
```

它能过题，但有两处值得改的写法，另有一处顺序细节极易写错。

**第一处：同一张映射表被写了两遍。** `+ - * /` 四个字符在这里各出现两次——
一次在外层的合法性判断（`op == '+'` 等），一次在具体的运算上。题面的
"操作符 $\to$ 运算"本来就是一张 4 行的数据表；摊进控制流之后，增删一种运算要改两个地方，
而且"合法"这个概念在代码里没有名字。

把映射关系还给数据，就得到**分派表**：`operator` 模块把 `+ - *` 暴露为函数
`add / sub / mul`，于是

```python
OPS = {b'+': operator.add, b'-': operator.sub, b'*': operator.mul, b'/': trunc_div}
```

合法性判断随之变成一次成员测试 `op in OPS`——**"合法"与"怎么算"共用同一份表**，
四个操作符字符在代码里只需在表里各写一次（`/` 额外在除零判断里被引用一次）。
这也是 Python 里“用 `dict` 收掉 `switch`”的常见形态：
分支数固定且互斥时，查表比 `if` 链既短又不容易漏项。

**第二处：`a // b` 不是 C++ 的整除。** 这不是风格问题，是会直接错答案的语义差异：

| 输入 | C++ `/`（参考实现） | Python `//` | 差异原因 |
| --- | --- | --- | --- |
| `-7 2 /` | `-3` | `-4` | 向下取整 vs 向零取整 |
| `7 -2 /` | `-3` | `-4` | 同上 |
| `-7 -2 /` | `3` | `3` | 同号时两者一致 |
| `6 -3 /` | `-2` | `-2` | 同号时两者一致 |

Python 的 `//` 是向下取整（floor），C++ 的 `/` 是向零取整（truncate），
两者只在**异号**时不同。本题的期望输出由 C++ 参考实现 `std.cpp` 生成，而负操作数在这次
数据里确实出现过（只是恰好没落在除法那一组），语义上仍必须对齐参考实现，
所以不能把 `a // b` 当等价写法，要自己实现截断除法：

$$
\frac{a}{b}\bigg|_{\text{向零}} = \operatorname{sign}(a \cdot b) \cdot \frac{|a|}{|b|}
$$

因为 $|a|$ 和 $|b|$ 非负，`abs(a) // abs(b)` 的 floor 与 truncate 结果相同，
符号单独由 `(a < 0) == (b < 0)` 判断。这就是 `trunc_div()` 的全部内容。

**顺序细节：两条错误分支谁先判。** 合法操作符的检查必须在最外层：

| 输入 | 输出 | 为什么 |
| --- | --- | --- |
| `5 0 +` | `5` | 除数为 $0$ 但运算不是除法，不算错误 |
| `5 0 /` | `Divided by zero!` | 合法除法且除数为 $0$ |
| `5 0 %` | `Invalid operator!` | 操作符非法优先于除零报错 |

所以判定链写成

```python
if op not in OPS:
    return INVALID          # 非法操作符优先
if op == b'/' and b == 0:
    return DIV_ZERO
return str(OPS[op](a, b))   # 剩下的情况一定能算
```

与参考实现 `if(合法){...} else { Invalid operator! }` 的嵌套关系同构。
第二条 `if` 里 `op == b'/'` 那半个条件不能省：它把除零限制在除法上，
`5 0 +` 才不会误报（那一问由 `operator.add` 正常算出 `5`）。

最后是读入侧的小选择。主流程只有一句解包加一句输出：

```python
x, y, op = sys.stdin.buffer.read().split()  # 两个操作数 + 一个操作符
print(evaluate(int(x), int(y), op))
```

`split()` 切出的 token 是 `bytes` 而不是 `str`，于是 `op` 保持 `bytes`
（用 `b'/'` 比较）就能直接当字典键，省掉一次解码，也不受编码影响的干扰；
两个操作数就地 `int()` 转换后传进 `evaluate()`，函数签名（整数进、字符串出）
正好对应题面的"两个整数 + 一个操作符进、一行结果出"。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(1)$。一次整份读入、一次切分、两次整数转换、一次成员测试、
  一次查表调用、一次输出，全部常数时间。
- 空间复杂度：$O(1)$。输入字节串、3 个 token、2 个整数，加上固定的 4 键分发表。

## 总结

- 四则运算的分派用 `dict` 而不是 `if/elif` 链：`OPS = {b'+': add, b'-': sub, b'*': mul, b'/': trunc_div}`，
  合法性就是 `op in OPS`，一张表同时承担校验与求值。
- Python `//` 向下取整，C++ `/` 向零取整，两者只在异号时不同；
  对齐 C++ 语义要写成 `abs(a) // abs(b)` 再按符号回填。
- 两条错误分支有先后：**非法操作符优先**于除零报错，
  除零判断额外要求 `op == b'/'`，否则 `5 0 +` 会被误判。
- 读入直接用 `bytes` 做字典键，省一次解码；`split()` 已归一化换行与多余空白。
- 验证：数据仓 10 组真实数据全部 PASS（约 0.016 s/组、峰值 14.5 MB，限额 1000 ms / 128 MB）；
  除零、非法操作符、异号整除这三类数据未覆盖的分支由手工用例核对。
