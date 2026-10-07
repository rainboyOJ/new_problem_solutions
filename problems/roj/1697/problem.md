### 【题目描述】

有的词语常常别有深意，现给出一段话$s$，和一个单词$t$，已知单词$t$别有深意，
也就是说有两个意思，求$s$可能有多少个意思？答案对$1000000007$ 取模。

### 【输入】

第一行一个数 $n$，表示测试的组数。 
接下来$n$组，每组两行，表示$s$和$t$。

### 【输出】

一共 $n$行，第$i$ 行表示第$i$组$s$的意思个数。

### 【输入样例】

```
4 
hehehe 
hehe
woquxizaolehehe 
woquxizaole 
hehehehe 
hehe 
woyaoqugenbierenliaotianle 
wanan
```

### 【输出样例】

```
3 
2
5 
1
```

### 【提示】

【样例解释】 
黑色表示取原意，淡绿色表示取深意。 
第 1组: $hehehe，hehehe，hehehe$ 
第 3组: $hehehehe，hehehehe，hehehehe，hehehehe，hehehehe$ 
【数据规模】   
对于50%的数据，$len(t)≤len(s)≤1000$； 
对于100%的数据，$len(t)≤len(s)≤100000，n≤10$，$s$和$t$仅包含小写字母。
