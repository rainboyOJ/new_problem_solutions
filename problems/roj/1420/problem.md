# Dijkastra(II)

### 【题目描述】

给定一个无向连通图，求从1到n的最短路。

### 【输入】

第一行两个整数n,m,代表点数和边数；

接下来m行，每行三个整数s,t,d,代表从s到t有一条长度为d的无向边。

### 【输出】

输出一个整数表示最短距离。

### 【输入样例】

```
2 3
1 2 1
1 2 3
2 2 0
```

### 【输出样例】

```
1
```

### 【提示】

【数据规模及约定】

N≤200000,M≤400000,1≤S,T≤N,0≤D≤10^9

> 题面来源：https://blog.csdn.net/qq_59414216/article/details/119861667
> （原站 http://ybt.ssoier.cn:8088/problem_show.php?pid=1420 显示「题目正在建设中」，题面自网络题解重建。）
>
> 交叉验证（三个独立来源题面、数据范围完全一致）：
> - https://blog.csdn.net/lybc2019/article/details/128441918（含时间 1000 ms / 内存 131072 KB 限制）
> - https://blog.csdn.net/qq_59414216/article/details/119861667
> - https://www.jianshu.com/p/be597719474a（含提交数/通过数统计，证明当时原站题面真实存在过）
>
> 姊妹题模板佐证：1419【SPFA(II)】（https://blog.csdn.net/lybc2019/article/details/128441900 、
> https://www.jianshu.com/p/98601505aeb8 ）与 1421【Floyd】
> （https://blog.csdn.net/lybc2019/article/details/128441961 ）为同一题面模板的
> 三道最短路系列题（输入/输出格式逐字相同，仅描述、数据范围与样例不同），
> 佐证本题为该系列中「无向图 + 堆优化 Dijkstra」的一道，非独立臆造题面。
