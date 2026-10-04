#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:18
# update_at: 2026-10-01 16:18

# 每秒钟每个格子的石头都在做「乘 0 或 1 后搬到某格」的线性搬运，t ≤ 1e8 秒没法逐秒模拟，
# 但操作序列每秒循环、整张网格的周期只有 lcm(各序列长度) ≤ 60，于是一整秒就是一次矩阵乘法，
# 用矩阵快速幂把 t 秒压成 O(log t) 次乘法。状态里多留一个「外界」下标：
# 数字 0~9 的加石头 = 外界注入，外界恒为 1，所以每格的注入量是常数；
# 推出网格的石头直接消失，不回流，否则外界会被越喂越多、注入量随秒数指数增长。

import sys
from functools import reduce
from math import lcm

DELTA = {'N': (-1, 0), 'S': (1, 0), 'W': (0, -1), 'E': (0, 1)}  # 推石头的四个方向


def mat_mul(a: list[list[int]], b: list[list[int]]) -> list[list[int]]:
    """矩阵乘法 a·b：先把 b 转置成列，再让每个行向量和每个列向量做点积。"""
    cols = list(zip(*b))
    return [[sum(x * y for x, y in zip(row, col)) for col in cols] for row in a]


def apply(mat: list[list[int]], vec: list[int]) -> list[int]:
    """矩阵乘列向量：算出走一步以后每个下标的石头数。"""
    return [sum(a * x for a, x in zip(row, vec)) for row in mat]


def mat_pow(mat: list[list[int]], power: int) -> list[list[int]]:
    """矩阵快速幂 mat^power：把幂按二进制拆成一串平方乘积。"""
    size = len(mat)
    result = [[int(i == j) for j in range(size)] for i in range(size)]
    for bit in range(power.bit_length()):
        if power >> bit & 1:
            result = mat_mul(result, mat)
        mat = mat_mul(mat, mat)
    return result


def second_matrix(grid: str, programs: list[str], rows: int, cols: int, second: int) -> list[list[int]]:
    """第 second 秒的转移矩阵：mat[新下标][旧下标] 是旧格子把石头搬给新格子的比例。

    数字操作写成「原地留一份 + 外界注入一份」，D 让整列保持 0（石头被拿走），
    方向操作把整列搬到相邻格；搬出网格的石头不记进新状态，等于直接丢弃。
    """
    outside = rows * cols  # 外界：只作为 0~9 加石头的恒定来源，值恒为 1
    mat = [[0] * (outside + 1) for _ in range(outside + 1)]
    for pos, cell in enumerate(grid):
        program = programs[int(cell)]
        token = program[second % len(program)]
        if token.isdigit():
            mat[pos][pos] = 1               # 原有石头原地不动
            mat[pos][outside] = int(token)  # 外界每格每秒恒定注入这份石头
        elif token != 'D':
            dr, dc = DELTA[token]
            r, c = divmod(pos, cols)
            row, col = r + dr, c + dc
            if 0 <= row < rows and 0 <= col < cols:
                mat[row * cols + col][pos] = 1  # 整格石头搬到相邻格，越界则整列保持 0
    mat[outside][outside] = 1  # 外界自保持为 1，注入量才是常数
    return mat


def transition_cycle(grid: str, programs: list[str], rows: int, cols: int) -> tuple[list[list[list[int]]], list[list[int]]]:
    """返回 (周期内每秒的转移矩阵, 整周期合成矩阵)：周期长 = 各操作序列长度的最小公倍数。"""
    length = lcm(*(len(program) for program in programs))
    steps = [second_matrix(grid, programs, rows, cols, second) for second in range(length)]
    cycle = reduce(lambda acc, mat: mat_mul(mat, acc), steps)  # 先走第 0 秒，后走的乘在左边
    return steps, cycle


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m, t, act = (int(next(data)) for _ in range(4))
    grid = ''.join(next(data).decode() for _ in range(n))     # 展平成 rows*cols 一行，方便用下标算坐标
    programs = [next(data).decode() for _ in range(act)]

    steps, cycle = transition_cycle(grid, programs, n, m)
    rounds, rest = divmod(t, len(steps))

    vec = [0] * (n * m + 1)
    vec[n * m] = 1  # 初始石头全在外界，由它按各格的操作序列注入
    for mat in [mat_pow(cycle, rounds), *steps[:rest]]:
        vec = apply(mat, vec)

    print(max(vec[:n * m]))  # 只统计真实格子，外界只是记账


if __name__ == "__main__":
    solve()
