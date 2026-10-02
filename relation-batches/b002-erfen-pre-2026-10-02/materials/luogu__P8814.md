# luogu P8814 [CSP-J 2022] 解密

> 原文摘录，非模型摘要。来源：`problems/luogu/P8814/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及/提高-；标签：['数学题', '二分', '数论']

## 题目解析（原文摘录）

### 题意

给出 `k` 组询问，每组有三个正整数 `n,e,d`。

要求寻找正整数 $p,q$，满足：

$$
n = p * q
$$
$$
e * d = (p - 1)(q - 1) + 1
$$

如果存在这样的 `p,q`，输出它们；否则输出 `NO`。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

朴素做法枚举 `p`，如果 `p` 能整除 `n`，就令 $q=n/p$ 再检查第二个式子。这个思路正确，但 `n` 可以到 $10^18$，即使枚举到 `sqrt(n)` 也太慢。

关键是把第二个式子展开：

| 式子 | 含义 |
| --- | --- |
| $e*d = (p-1)(q-1)+1$ | 题目给出的条件 |
| $e*d = pq - p - q + 2$ | 展开括号 |
| $e*d = n - p - q + 2$ | 因为 $pq=n$ |
| $p+q = n - e*d + 2$ | 得到两个数的和 |

令：

$$
sum = p + q = n - e*d + 2
$$

现在我们已经知道了 $p*q=n$ 和 $p+q=sum$。这说明 $p,q$ 是方程：

$$
x^2 - sum*x + n = 0
$$

的两个根。

所以只需要判断这个二次方程有没有正整数根。判别式为：

$$
delta = sum^2 - 4*n
$$

若 `delta` 不是非负完全平方数，就没有整数解。若 $root = sqrt(delta)$，则两个根只能是：

$$
p = (sum - root) / 2
$$
$$
q = (sum + root) / 2
$$

这里的 `sqrt(delta)` 需要得到一个整数候选根。
一种写法是直接调用 `sqrt` 得到候选值，再回代检查 `p+q` 和 $p*q$ 是否正确。
另一种更稳的写法是用二分求整数平方根：二分最大的 `x`，使得 $x*x <= delta$。

## 代码位置
- `problems/luogu/P8814/brute.cpp`
- `problems/luogu/P8814/gen.py`
- `problems/luogu/P8814/main.cpp`
- `problems/luogu/P8814/main_isqrt.cpp`
