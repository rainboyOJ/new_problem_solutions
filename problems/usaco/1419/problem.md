# 1419 Logical Moos

## 赛事信息

USACO 2024 US Open Contest, Bronze

## 题目描述

Farmer John 有一个布尔语句，包含 $N$ 个关键字（$1 \leq N < 2 \cdot 10^5$，$N$ 为奇数）。奇数位置仅出现 $\texttt{true}$ 或 $\texttt{false}$，偶数位置上仅出现 $\texttt{and}$ 或 $\texttt{or}$。
一个 $x\text{ OPERATOR }y$ 形式的短语，其中 $x$ 和 $y$ 为 $\texttt{true}$ 或 $\texttt{false}$，而 $\text{OPERATOR}$ 为 $\texttt{and}$ 或 $\texttt{or}$，按如下规则求值：
- $x\texttt{ and }y$：如果 $x$ 和 $y$ 均为 true，则求值结果为 true，否则为 false。
- $x\texttt{ or }y$：如果 $x$ 或 $y$ 为 true，则求值结果为 true，否则为 false。
在求值该语句时，FJ 必须考虑 Moo 语言中的运算符优先级。与 C++ 类似，$\texttt{and}$ 优先级高于 $\texttt{or}$。更具体地说，在求值该语句时，重复以下步骤直至该语句仅包含一个关键字。
- 如果语句中包含 $\texttt{and}$，选择其中任意一个，并将其周围的短语替换为其求值结果。
- 否则，该语句包含 $\texttt{or}$。选择其中任意一个，并将其周围的短语替换为其求值结果。
可以证明，如果在指定的一个步骤中可以求值多个短语，那么选择哪一个求值并不重要；该语句最终的求值结果将始终相同。
FJ 有 $Q$（$1 \leq Q \leq 2 \cdot 10^5$）个询问。在每个询问中，他给你两个整数 $l$ 和 $r$（$1 \leq l \leq r \leq N$，$l$ 和 $r$ 均为奇数），并删除关键字 $l$ 到关键字 $r$ 之间的段。反过来，他希望用一个简单的 $\texttt{true}$ 或 $\texttt{false}$ 替换他刚刚删除的段，以使整个语句的求值结果为某个指定的布尔值。帮助 FJ 判断是否可行！

## 输入格式

输入的第一行包含 $N$ 和 $Q$。
下一行包含 $N$ 个字符串，为一个合法的布尔语句。
以下 $Q$ 行，每行包含两个整数 $l$ 和 $r$，以及一个字符串 $\texttt{true}$ 或 $\texttt{false}$，表示他希望整个语句的求值结果为 true 还是 false。

## 输出格式

输出一个长度为 $Q$ 的字符串，其中如果第 $i$ 个询问的结果为可能，则第 $i$ 个字符为 Y，否则为 N。

## 输入输出样例 #1

### 输入 #1

```
5 7
false and true or true
1 1 false
1 3 true
1 5 false
3 3 true
3 3 false
5 5 false
5 5 true
```

### 输出 #1

```
NYYYNYY
```

## 输入输出样例 #2

### 输入 #2

```
13 4
false or true and false and false and true or true and false
1 5 false
3 11 true
3 11 false
13 13 true
```

### 输出 #2

```
YNYY
```

## 测试点性质

- 测试点 3-5：$N,Q\le 10^2$。
- 测试点 6-8：$N,Q\le 10^3$。
- 测试点 9-26：没有额外限制。
