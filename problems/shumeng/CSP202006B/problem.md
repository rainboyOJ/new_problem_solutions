**时间限制：** 2.0 秒

**空间限制：** 512 MB

## 题目描述

对于一个 $n$ 维整数向量 $\boldsymbol{v} \in \mathbb{Z}^n$，其在第 $index$ 个维度上的取值记作 $\boldsymbol{v}_{index}$。这里我们约定 $index$ 的取值从 $1$ 开始，即 $\boldsymbol{v} = ( \boldsymbol{v}_1, \boldsymbol{v}_2, \cdots, \boldsymbol{v}_n )$。 下面介绍一种向量的稀疏表示方法。

如果 $\boldsymbol{v}$ 仅在少量维度上的取值**不**为 $0$，则称其为**稀疏向量**。

例如当 $n = 10$ 时，$\boldsymbol{v} = ( 0, 0, 0, 5, 0, 0, -3, 0, 0, 1 )$ 就是一个稀疏向量。

由于稀疏向量的非零值较少，我们可以通过仅存储非零值的方式来节省空间。具体来说，每个非零值都可以用一个 $(index, value)$ 对来表示，即该向量在第 $index$ 个维度上的取值 $\boldsymbol{v}_{index} = value \neq 0$。在上面的例子中，$\boldsymbol{v}$ 就可以表示为 $[ (4, 5), (7, -3), (10, 1) ]$。

接下来给出这种稀疏表示一般化的定义。

- 对于任意一个 $n$ 维整数向量 $\boldsymbol{v} \in \mathbb{Z}^n$，如果其在且仅在 $a$ 个维度上取值不为 $0$，则可以唯一表示为： 
	$$
	 [ (index_1, value_1), (index_2, value_2), \cdots, (index_a, value_a) ] 
	$$
- 其中所有的 $index$ 均为整数且满足： 
	$$
	 1 \leq index_1 < index_2 < \cdots < index_a \leq n 
	$$
- $value_i$ 表示向量 $\boldsymbol{v}$ 在对应维度 $index_i$ 上的非零值。

给出两个 $n$ 维整数向量 $\boldsymbol{u}, \boldsymbol{v} \in \mathbb{Z}^n$ 的稀疏表示，试计算它们的内积。

$$
 \boldsymbol{u} \cdot \boldsymbol{v} = \sum_{i=1}^{n}{\boldsymbol{u}_i \cdot \boldsymbol{v}_i} 
$$

## 输入格式

从标准输入读入数据。

输入的第一行包含用空格分隔的三个正整数 $n$、$a$ 和 $b$，其中 $n$ 表示向量 $\boldsymbol{u}$、$\boldsymbol{v}$ 的维数，$a$ 和 $b$ 分别表示两个向量所含非零值的个数。

第二行到第 $a+1$ 行输入向量 $\boldsymbol{u}$ 的稀疏表示。第 $i+1$ 行（$1 \leq i \leq a$）包含用空格分隔的两个整数 $index_i$ 和 $value_i$，表示 $\boldsymbol{u}_{index_i} = value_i \neq 0$。

第 $a+2$ 行到第 $a+b+1$ 行输入向量 $\boldsymbol{v}$ 的稀疏表示。第 $j+a+1$ 行（$1 \leq j \leq b$）包含用空格分隔的两个整数 $index_j$ 和 $value_j$，表示 $\boldsymbol{v}_{index_j} = value_j \neq 0$。

## 输出格式

输出到标准输出。

输出一个整数，表示向量 $\boldsymbol{u}$ 和 $\boldsymbol{v}$ 的内积 $\boldsymbol{u} \cdot \boldsymbol{v}$。


```input1
10 3 4
4 5
7 -3
10 1
1 10
4 20
5 30
7 40
```


```output1
-20
```

## 样例 1 解释

$\boldsymbol{u} = ( 0, 0, 0, 5, 0, 0, -3, 0, 0, 1 )$

$\boldsymbol{v} = ( 10, 0, 0, 20, 30, 0, 40, 0, 0, 0 )$

$\boldsymbol{u} \cdot \boldsymbol{v} = 5 \times 20 + (-3) \times 40 = -20$

## 子任务

- 输入数据保证 $0 < a, b < n$；
- 向量 $\boldsymbol{u}$ 和 $\boldsymbol{v}$ 在每一维度上取值的绝对值 $| \boldsymbol{u}_i |, | \boldsymbol{v}_i | \leq 10^{2}\ (1 \leq i \leq n)$。

| 测试点编号 | $n\le$ | $a,b\le$ |
| :---: | :---: | :---: |
| $1\sim 3$ | $10^5$ | $10^3$ |
| $4\sim 6$ | $5\times 10^5$ | $10^5$ |
| $7\sim 10$ | $10^9$ | $5\times 10^5$ |

## 提示

本题输入量较大，请采用效率较高的读入方式。
