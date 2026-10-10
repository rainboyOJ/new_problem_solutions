#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 15:03
# update_at: 2026-10-08 15:03

import sys
from math import floor, hypot

SPEED = 20000  # 铲雪时速度 20 km/h，换算成米/小时


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    start_x, start_y = next(data), next(data)  # 停车点坐标，对最短时间没有影响

    # 每条街道给出 4 个整数 x1 y1 x2 y2；同一个迭代器连取四次就按街道分好组。
    # 街道是双向单车道，拆成一正一反两条有向边后各点入度=出度，图有欧拉回路，
    # 铲雪车能一路铲雪走遍全部车道再回起点，所以总路程 = 单向长度之和 × 2。
    quads = zip(data, data, data, data)  # 迭代器连取四次 => 每项是一条街道的 (x1,y1,x2,y2)
    one_way = sum(hypot(x2 - x1, y2 - y1) for x1, y1, x2, y2 in quads)

    minutes = floor(one_way * 2 / SPEED * 60 + 0.5)  # 总用时换算成分钟，四舍五入
    print(f"{minutes // 60}:{minutes % 60:02d}")


if __name__ == "__main__":
    solve()
