# P9723 [EC Final 2022] Chinese Checker
## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/krp4wk8f.png)

Prof. Pang is playing Chinese Checkers. The game board is the same as the figure shown above. There are $n$ checkers on the board. Prof. Pang wants to know how many different moves there are on the current board.

One **move** consists of several **steps**. At first, Prof. Pang needs to choose one checker $a$ to move. In each step, Prof. Pang needs to choose another checker $b$ as the pivot, and move the checker $a$ to the symmetrical position about the checker $b$. (In one move, Prof. Pang cannot change his choice of $a$ between steps. **If after a step, the checker $a$ will return to its position before the move, this step is not allowed.**) There are several conditions about the pivot $b$:

- The segment connecting $a$ and $b$ needs to be parallel to one of the coordinate axis. Note: There are three axes on the hexagonal board. One of them is horizontal and any pair of axes intersect at an angle of $\pi/3$.
- $a$ and $b$ **do not** need to be adjacent.
- There cannot be extra checkers other than $b$ on the segment connecting $a$ and its symmetrical position.
- The symmetrical position should be on the hexagonal board and is not occupied by any other checker.

A move must have at least one step. After the first step, Prof. Pang can stop at any time he wants. And Prof. Pang can choose any checker on the board as the moving checker. Output the number of different moves Prof. Pang can make. Two moves are different if and only if the sets of positions of all checkers are different after these two moves, i.e., the checkers are indistinguishable.

## 输入格式

The first line contains an integer $T~(1\leq T\leq 100)$ -- the number of test cases.

For each test case, the first line contains an integer $n~(1\leq n\leq 121)$ -- the number of checkers.

Each of the following $n$ lines contains two integers, indicating the position of a checker. The first number indicates which row it is in, and the second number indicates which one of this row it is. They are counting from top to bottom and left to right, starting from $1$.

It is guaranteed that checkers' positions are different.

## 输出格式

For each test case, output one integer in a line -- the number of different moves.

## 输入输出样例 #1

### 输入 #1

```
5
1
1 1
2
1 1
2 1
2
9 4
9 6
10
1 1
2 1
2 2
3 1
3 2
3 3
4 1
4 2
4 3
4 4
10
1 1
2 1
2 2
5 7
3 2
3 3
4 1
4 2
4 3
4 4
```

### 输出 #1

```
0
1
2
6
13
```
