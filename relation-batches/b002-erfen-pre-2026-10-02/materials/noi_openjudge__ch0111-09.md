# noi_openjudge ch0111-09 膨胀的木棍

> 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0111-09/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及+/提高；标签：['二分', '几何', 'python']

## 题目解析（原文摘录）

[[TOC]]

### 题意

木棍受热后长度增加，但两端仍固定在原位置。把它看成圆弧，求圆弧中点相对原直线的偏移量。

### 思路

热胀后的弧长为 $S=(1+nC)L$。设圆弧半径为 $r$，弦长为 $L$，圆弧长度是 $2r\arcsin(L/(2r))$。半径越大弧长越小，因此二分半径使弧长等于 $S$，最后偏移量为 $r-\sqrt{r^2-(L/2)^2}$。长度不变时偏移量为零。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

固定进行 200 次二分，时间复杂度和空间复杂度均为 $O(1)$。

### 总结

圆弧模型把“热胀弯曲”转化为单调的几何方程，适合实数二分。

## 代码位置
- `problems/noi_openjudge/ch0111-09/main-cout.cpp`
- `problems/noi_openjudge/ch0111-09/main.cpp`
- `problems/noi_openjudge/ch0111-09/main.py`
