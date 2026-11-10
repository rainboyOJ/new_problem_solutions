# AT_abc202_d [ABC202D] aab aba baa
## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc202/tasks/abc202_d

$ A $ 個の `a` と $ B $ 個の `b` からなる長さ $ A\ +\ B $ の文字列のうち、辞書順で $ K $ 番目のものを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ B $ $ K $

## 输出格式

答えを出力せよ。

## 输入输出样例 #1

### 输入 #1

```
2 2 4
```

### 输出 #1

```
baab
```

## 输入输出样例 #2

### 输入 #2

```
30 30 118264581564861424
```

### 输出 #2

```
bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
```

## 说明/提示

### 制約

- $ 1\ \leq\ A,\ B\ \leq\ 30 $
- $ A $ 個の `a` と $ B $ 個の `b` からなる長さ $ A\ +\ B $ の文字列の総数を $ S $ 個とおいたとき、$ 1\ \leq\ K\ \leq\ S $
- 入力は全て整数である。

### Sample Explanation 1

$ 2 $ 個の `a` と $ 2 $ 個の `b` からなる文字列を辞書順に並べると、`aabb`、`abab`、`abba`、`baab`、`baba`、`bbaa` となります。 よって、$ 4 $ 番目である `baab` を出力します。

### Sample Explanation 2

$ K $ の値は $ 32 $ bit 整数に収まらないことがあります。
