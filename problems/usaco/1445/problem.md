# 1445 It's Mooin' Time

## 赛事信息

USACO 2024 December Contest, Bronze

## 题目描述

Farmer John 正在试图向 Elsie 描述他最喜欢的 USACO 竞赛，但她很难理解为什么他这么喜欢它。他说「竞赛中我最喜欢的部分是 Bessie 说 『现在是哞哞时间』并在整个竞赛中一直哞哞叫」。
Elsie 仍然不理解，所以 Farmer John 将竞赛以文本文件形式下载，并试图解释他的意思。竞赛被定义为一个长度为 $N$（$3 \leq N \leq 20\,000$）的小写字母字符串。一种哞叫一般地定义为子串 $c_ic_jc_j$，其中某字符 $c_i$ 之后紧跟着 $2$ 个某字符 $c_j$，且 $c_i \neq c_j$。根据 Farmer John 的说法，Bessie 哞叫了很多，所以如果某种哞叫在竞赛中出现了至少 $F$（$1\le F\le N$）次，那可能就是 Bessie 发出的。
然而，Farmer John 的下载可能损坏，文本文件可能存在至多一个字符与原始文件不同。将可能的误差考虑在内，输出所有可能是 Bessie 发出的哞叫，按字母顺序排序。

## 输入格式

输入的第一行包含 $N$ 和 $F$，表示字符串的长度以及 Bessie 的哞叫的频次下限。
第二行包含一个长度为 $N$ 的小写字母字符串，表示竞赛。

## 输出格式

输出可能是 Bessie 发出的哞叫的数量，以下是按字典序排序的哞叫列表。每行输出一种哞叫。

## 输入输出样例 #1

### 输入 #1

```
10 2
zzmoozzmoo
```

### 输出 #1

```
1
moo
```

## 输入输出样例 #2

### 输入 #2

```
17 2
momoobaaaaaqqqcqq
```

### 输出 #2

```
3
aqq
baa
cqq
```

## 输入输出样例 #3

### 输入 #3

```
3 1
ooo
```

### 输出 #3

```
25
aoo
boo
coo
doo
eoo
foo
goo
hoo
ioo
joo
koo
loo
moo
noo
poo
qoo
roo
soo
too
uoo
voo
woo
xoo
yoo
zoo
```

## 测试点性质

- 测试点 4-8：$N \le 100$。
- 测试点 9-13：没有额外限制。
