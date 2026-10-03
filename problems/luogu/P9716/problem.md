# P9716 [EC Final 2022] Coloring
## 题目描述

You are given $n$ elements numbered from $1$ to $n$. Element $i$ has value $w_i$ and color $c_i$. Each element also has a pointer $a_i$ to some other element.

Initially, the color of element $s$ is $1$, while the color of all the other elements is $0$. More formally, $c_s=1$ and $c_i=0$ for all $i\neq s$ $(1 \le i \le n)$.

You can perform the following operation for any number of times:

- Assign $c_i\leftarrow c_{a_i}$ at a cost of $p_i$.

Your score is equal to the sum of values of all the elements with color $1$ after the operations minus the sum of costs of the operations.

Find the maximum possible score you can obtain.

## 输入格式

The first line contains two integers $n,s$ ($1 \leq s\le n \leq 5\times 10^3$) $-$ the number of elements and the element with color $1$ initially.

The second line contains $n$ integers $w_1,w_2,\dots,w_n$ ($-10^9\le w_i\le 10^9$) $-$ the value of the elements.

The third line contains $n$ integers $p_1,p_2,\dots,p_n$ ($0\le p_i\le 10^9$) $-$ the cost of changing the color of each element.

The fourth line contains $n$ integers $a_1,a_2,\dots,a_n$ ($1\le a_i\le n$, $a_i\neq i$).

## 输出格式

Output one integer representing the answer in one line.

## 输入输出样例 #1

### 输入 #1

```
3 1
-1 -1 2
1 0 0
3 1 2
```

### 输出 #1

```
1
```

## 输入输出样例 #2

### 输入 #2

```
10 8
36175808 53666444 14885614 -14507677 
-92588511 52375931 -87106420 -7180697 
-158326918 98234152
17550389 45695943 55459378 18577244 
93218347 64719200 84319188 34410268 
20911746 49221094
8 1 2 2 8 8 4 7 8 4
```

### 输出 #2

```
35343360
```

## 说明/提示

(There won’t be extra line breakers 
in the actual test cases.)

In the first sample, you can successively perform the following operations:

- Assign $c_2\leftarrow c_{a_2}$ at a cost of $p_2$, then $c=[1,1,0]$;
- Assign $c_1\leftarrow c_{a_1}$ at a cost of $p_1$, then $c=[0,1,0]$;
- Assign $c_3\leftarrow c_{a_3}$ at a cost of $p_3$, then $c=[0,1,1]$;
- Assign $c_2\leftarrow c_{a_2}$ at a cost of $p_2$, then $c=[0,0,1]$.

After the operations, only the color of element $3$ is $1$, so your score is equal to $w_3-(p_2+p_1+p_3+p_2)=1$. It can be shown that it is impossible to obtain a score greater than $1$.
