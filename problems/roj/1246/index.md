---
oj: "roj"
problem_id: "1246"
title: "膨胀的木棍"
description: "弧长与弦长唯一确定圆弧：消元得关于圆心角的单调方程，实数二分求角后用弓形高公式直接得出偏移。"
difficulty: "普及-"
date: 2026-09-30 01:32
updated: 2026-09-30 01:40
toc: true
tags: ["数学", "二分", "计算几何", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1246
---

[[TOC]]

## 形式化题目

给定木棍原长 $L$、温度变化 $n$、热膨胀系数 $C$（均为非负实数，且
$L' = (1+nC)\cdot L \leqslant 1.5L$）。木棍受热后变为一段圆弧，其弦恰为原位置的
线段（长 $L$）。求弧中点到弦的垂直距离，保留三位小数。

## 正解

### 思路

#### 几何建模

受热前木棍是长 $L$ 的弦，受热后是弧长 $L' = (1+nC)L$ 的圆弧。设弧所在圆的半径为
$r$、圆心角为 $\theta$，弓形高（即所求偏移）为 $h$，三个量之间有：

$$L' = r\theta, \qquad L = 2r\sin\frac{\theta}{2}, \qquad h = r\left(1-\cos\frac{\theta}{2}\right)$$

五个量的几何关系如下图：

```text
                _____ 弧 L'（受热后的木棍）
             .°     °.
           °     |     °        A
          °      |h      °     / \
         °       |         °  /    \ r
        °        |          °/      \
        ●────────┴──────────°───────●  ← 弦 L（原位置，两端嵌在墙里）
        (圆心 O 在弦下方 h' = r·cos(θ/2) 处)
```

- 圆心角 $\theta$ 对应弧 $L'$，圆心到弦的距离为 $r\cos(\theta/2)$；
- 弧中点在弦上方 $h = r - r\cos(\theta/2)$ 处，这就是答案。

#### 消元与二分

由 $r = L'/\theta$ 代入弦长公式，得到关于 $\theta$ 的方程：

$$g(\theta) := \frac{2L'\sin(\theta/2)}{\theta} = L$$

这是超越方程，没有闭式解，但 $g(\theta)$ 在 $(0, \pi]$ 上**严格递减**——角度越大，
同样的弧长"折"得越厉害、弦越短。端点值 $g(0^+) = L' \geqslant L$，
而 $g(\pi) = 2L'/\pi < L$（题目保证 $L' \leqslant 1.5L < \frac{\pi}{2}L$），
所以解存在且唯一，可以实数二分：

- 弦偏长（$g(\text{mid}) > L$）⇒ 还不够弯 ⇒ 角度调大（`lo = mid`）；
- 否则 ⇒ 角度调小（`hi = mid`）；
- 二分到精度 $10^{-12}$（约 41 次迭代），远超三位小数的要求。

最后代回 $r = L'/\theta$，输出 $h = r(1-\cos(\theta/2))$。

**样例核对**：$L=1000,\ n=100,\ C=0.0001$ 时 $L' = 1010$，解得
$\theta \approx 0.24595$，$r \approx 4106.7$，
$h \approx 4106.7 \times (1-\cos 0.12298) \approx 61.329$，与样例一致。

### 代码

@include-code(./main.py, python)

### 复杂度

时间：二分 $O(\log \frac{\pi}{\varepsilon}) \approx 41$ 次迭代，每次 $O(1)$。
空间：$O(1)$。

## 总结

- 物理图景 → 几何模型：**弧长与弦长同时固定，圆弧唯一确定**；
- 消元得到关于圆心角 $\theta$ 的单调方程，**严格单调 ⇒ 实数二分**；
- 解出 $\theta$ 后弓形高有闭式 $h = \frac{L'}{\theta}(1-\cos\frac{\theta}{2})$；
- 精度取 $10^{-12}$，对三位小数的输出要求有充分余量；
- 题目保证 $L' \leqslant 1.5L$ 恰好保证 $\theta$ 落在 $(0, \pi]$ 内，
  二分上界取 $3.15 > \pi$ 即可。
