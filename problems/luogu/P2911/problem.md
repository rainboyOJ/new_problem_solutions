# P2911 [USACO08OCT] Bovine Bones G
## 题目描述

Bessie loves board games and role-playing games so she persuaded Farmer John to drive her to the hobby shop where she purchased three dice for rolling. These fair dice have $S_1$, $S_2$, and $S_3$ sides respectively ($2 \le S_1 \le 20; 2 \le S_2 \le 20; 2 \le S_3 \le 40$). 

Bessie rolls and rolls and rolls trying to figure out which three-dice sum appears most often.

Given the number of sides on each of the three dice, determine which three-dice sum appears most frequently. If more than one sum can appear most frequently, report the smallest such sum.

POINTS: $70$

## 输入格式

\* Line 1: Three space-separated integers: $S_1$, $S_2$, and $S_3$.

## 输出格式

\* Line 1: The smallest integer sum that appears most frequently when the dice are rolled in every possible combination.

## 输入输出样例 #1

### 输入 #1

```
3 2 3
```

### 输出 #1

```
5
```

## 说明/提示

Here are all the possible outcomes.

```
1 1 1 -> 3  
1 2 1 -> 4  
2 1 1 -> 4  
2 2 1 -> 5  
3 1 1 -> 5  
3 2 1 -> 6 
1 1 2 -> 4  
1 2 2 -> 5  
2 1 2 -> 5  
2 2 2 -> 6  
3 1 2 -> 6  
3 2 2 -> 7 
1 1 3 -> 5  
1 2 3 -> 6  
2 1 3 -> 6  
2 2 3 -> 7  
3 1 3 -> 7  
3 2 3 -> 8
```
Both 5 and 6 appear most frequently (five times each), so 5 is the answer.
