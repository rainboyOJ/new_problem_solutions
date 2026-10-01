#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:59
# update_at: 2026-10-02 04:59

import math
import sys

EPS = 1e-4    # 题目容差：球与车的水平距离不超过它就算接住
FUDGE = 1e-7  # 浮点误差护栏：整数恰好压在边界上时不算漏接


def solve() -> None:
    height, head_pos, speed, car_len, car_h, ball_num = map(float, sys.stdin.read().split())
    n = int(ball_num)

    # d = 0.5*g*t² = 5t²：球落到地面、落到车顶高度 K 各需要的时间
    t_ground = math.sqrt(height / 5)
    t_roof = math.sqrt(max(height - car_h, 0) / 5)  # K ≥ H 时球一开始就在车顶高度附近

    # 车头朝原点以速度 V 前进，t 时刻车身占据 [head_pos - Vt, head_pos - Vt + L]。
    # 球只有在 t ∈ [t_roof, t_ground]（高度夹在车顶与地面之间）才可能被接住；
    # 这段时间里滑动区间扫过的并集仍是连续一段，只需取两个端点：
    lo = head_pos - speed * t_ground - EPS   # 最晚时刻车头扫到的最左位置
    hi = head_pos - speed * t_roof + car_len + EPS  # 最早时刻车尾扫到的最右位置

    # 落在 [lo, hi] 内、编号 0..n-1 的球全部被接住，数一下整数个数
    left = max(0, math.ceil(lo - FUDGE))
    right = min(n - 1, math.floor(hi + FUDGE))
    print(max(0, right - left + 1))


if __name__ == "__main__":
    solve()
