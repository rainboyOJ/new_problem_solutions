#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:07
# update_at: 2026-10-01 05:07

import sys
from itertools import count

DEG = 360              # 角度取模的模数：转过 359 度后回到 0
MASK = (1 << DEG) - 1  # 360 个角度全为 1 的掩码，用作"所有角度都能对准"的起点
N_WHEELS = 5           # 纺轮个数，透光要求五个轮子在同一角度同时存在缺口


def rot_left(mask: int, k: int) -> int:
    """把 360 位的角度集合在环上整体左移 k 位（k 度），这就是轮子旋转的语义。"""
    k %= DEG
    return (mask << k | mask >> (DEG - k)) & MASK


def run(s: int, length: int) -> int:
    """把缺口 [s, s+length] 写成一个 360 位掩码：落在缺口里的角度对应位为 1。

    题面的长度按闭区间算，缺口含首尾共 length+1 个角度，所以连续 1 的段长是
    length+1；段长到 360 说明缺口绕满整圈，此时每个角度都在缺口里。
    """
    width = length + 1
    if width >= DEG:
        return MASK
    head = (1 << width) - 1  # 从 0 度开始、长 width 的一段 1
    return rot_left(head, s)


def notch_mask(speed: int, notches: list[list[int]], t: int) -> int:
    """第 t 秒这个轮子上的缺口盖住的角度集合。

    每个缺口先铺好自己的连续段，最后整轮一起转过 speed*t 度——旋转对所有缺口
    是同一个位移，挪一次等于逐个挪，省掉 W 次旋转。
    """
    mask = 0
    for s, length in notches:
        mask |= run(s, length)
    return rot_left(mask, speed * t)


def collide(wheels: list[tuple[int, list[list[int]]]]) -> int:
    """最早能让光穿过的秒数，无解返回 -1。

    光走直线，所以可用的角度 d 必须同时落在五个轮子的某个缺口里，即五个轮子的
    缺口集合取交集后非空；交集为空就说明这一秒五个缺口排不到同一条线上。

    时间 t 的整体图案只由五个 (speed*t) mod 360 决定，而 0..359 秒已经穷尽了这
    五个余数的所有组合，因此 t 与 t+360 的图案必然相同；没在一圈内出现过的图案
    永远不会出现，枚举满 360 秒即可判定无解。
    """
    for t in count():  # 无限计数，只取前 360 个时刻
        if t == DEG:
            return -1  # 一整圈都试过了
        common = MASK
        for speed, notches in wheels:
            common &= notch_mask(speed, notches, t)
            if not common:
                break  # 已经排不到同一条线，这个秒数不必再算剩下的轮子
        if common:
            return t


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    wheels: list[tuple[int, list[list[int]]]] = []
    pos = 0
    for _ in range(N_WHEELS):
        speed, surplus = data[pos], data[pos + 1]  # 转速、缺口数 W
        pos += 2
        notches = [[data[pos + 2 * i], data[pos + 2 * i + 1]] for i in range(surplus)]
        wheels.append((speed, notches))
        pos += 2 * surplus

    ans = collide(wheels)
    print("none" if ans < 0 else ans)  # -1 表示转满一圈都没有能对准的时刻


if __name__ == "__main__":
    solve()
