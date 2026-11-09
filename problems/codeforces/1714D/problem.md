# 1714D Color with Occurrences

## 题目描述

给定一段文本$t$和一组$n$字符串$s_1, s_2, \dots, s_n$。

在每一步操作中，你可以选择文本$t$中任意出现的字符串$s_i$，并将文本中对应的字符标记为红色。例如，若$t=\texttt{bababa}$且$s_1=\texttt{ba}$，$s_2=\texttt{aba}$，则通过一步操作可以得到$t=\color{red}{\texttt{ba}}\texttt{baba}$、$t=\texttt{b}\color{red}{\texttt{aba}}\texttt{ba}$或$t=\texttt{bab}\color{red}{\texttt{aba}}$。

你需要将文本$t$的所有字母都标记为红色。当某个字母被重复标记时，其红色状态保持不变。

在上例中，只需三步即可完成：

- 首先标记$t[2 \dots 4]=s_2=\texttt{aba}$为红色，得到$t=\texttt{b}\color{red}{\texttt{aba}}\texttt{ba}$；
- 接着标记$t[1 \dots 2]=s_1=\texttt{ba}$为红色，得到$t=\color{red}{\texttt{baba}}\texttt{ba}$；
- 最后标记$t[4 \dots 6]=s_2=\texttt{aba}$为红色，得到$t=\color{red}{\texttt{bababa}}$。

每个字符串$s_i$可以被使用任意次数（或完全不使用）。标记时的字符串出现位置可以任意重叠。

请确定将所有字母$t$标记为红色所需的最少操作步数及具体方案。若无法将文本$t$的所有字母标红，则输出-1。

## 输入格式

输入第一行包含整数$q$（$1 \le q \le 100$）——表示测试用例的数量。

接下来描述每个测试用例。

每个测试用例的第一行包含文本$t$（$1 \le |t| \le 100$），该文本仅由小写拉丁字母组成，其中$|t|$表示文本$t$的长度。

第二行包含一个整数$n$（$1 \le n \le 10$）——表示字符串集合中的字符串数量。

随后$n$行，每行包含一个字符串$s_i$（$1 \le |s_i| \le 10$），这些字符串仅由小写拉丁字母组成，其中$|s_i|$表示字符串$s_i$的长度。

## 输出格式

对于每个测试用例，在单独一行输出答案。

若无法将所有字母标红，则输出一行包含数字-1。

否则，第一行输出数字$m$——表示将所有字母$t$标红所需的最少操作步数。

接下来的$m$行输出索引对：$w_j$和$p_j$（$1 \le j \le m$），表示使用索引为$w_j$的字符串作为子串，覆盖文本$t$中从位置$p_j$开始的出现位置。这些索引对可以按任意顺序输出。

若存在多种可行方案，输出其中任意一种即可。

## 提示

第一个测试用例的说明已在题目描述中给出。

在第二个测试用例中，无法将所有字母标红。

## 输入输出样例 #1

### 输入 #1

```
6
bababa
2
ba
aba
caba
2
bac
acab
abacabaca
3
aba
bac
aca
baca
3
a
c
b
codeforces
4
def
code
efo
forces
aaaabbbbcccceeee
4
eeee
cccc
aaaa
bbbb
```

### 输出 #1

```
3
2 2
1 1
2 4
-1
4
1 1
2 6
3 3
3 7
4
3 1
1 2
2 3
1 4
2
4 5
2 1
4
3 1
4 5
2 9
1 13
```
