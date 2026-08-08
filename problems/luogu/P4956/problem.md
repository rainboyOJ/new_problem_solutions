# P4956 [COCI 2017/2018 #6] Davor
## 题目描述

After successfully conquering the South Pole, Davor is preparing for new challenges. Next up is the Arctic expedition to Siberia, Greenland and Norway. He begins his travels on 31 December 2018, and needs to collect $N$ kunas (Croatian currency) by then. In order to do this, he has decided to put away $X$ ($X \le 100$) kunas every Monday to his travel fund, $X + K$ kunas every Tuesday, $X + 2\times K$ every Wednesday, and so on until Sunday, when he will put away $X + 6\times K$ kunas. This way, he will collect money for 52 weeks, starting with 1 January 2018 (Monday) until 30 December 2018 (Sunday).

If we know the amount of money $N$, output the values $X$ and $K$ so that it is possible to collect the **exact** money amount in the given timespan. The solution will always exist, and if there are multiple, output the one with the greatest $X$ and smallest $K$.

## 输入格式

The first line of input contains the integer $N$ ($1456\le N \le 145600$), the number from the task.

## 输出格式

The first line of output must contain the value of $X$ ($0 \le X \le 100$), and the second the value of $K$ ($K > 0$).

## 输入输出样例 #1

### 输入 #1

```
1456
```

### 输出 #1

```
1
1
```

## 输入输出样例 #2

### 输入 #2

```
6188
```

### 输出 #2

```
14
1
```

## 输入输出样例 #3

### 输入 #3

```
40404
```

### 输出 #3

```
99
4
```
