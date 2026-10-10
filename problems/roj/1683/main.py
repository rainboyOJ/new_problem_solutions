#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:17
# update_at: 2026-10-07 15:17

import sys
from functools import cache

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Group = dict[str, int]  # 一组的 字母 -> 数字 部分映射（题面保证组内是一一对应）
type Masks = list[int]       # 相容掩码：masks[i] 的第 j 位为 1 ⟺ 第 i 组与第 j 组能同时成立


def compatible(first: Group, second: Group) -> bool:
    """两组能否同时成立：公共字母取值一致，且合并后不同字母不共用数字。"""
    shared = first.keys() & second.keys()
    if any(first[ch] != second[ch] for ch in shared):
        return False
    # 合并后的映射是单射 ⟺ 用到的不同数字个数 == 用到的不同字母个数
    return len(set(first.values()) | set(second.values())) == len(first) + len(second) - len(shared)


def build_masks(groups: list[Group]) -> Masks:
    """算出所有两两相容关系，返回对称的相容掩码表。"""
    masks = [0] * len(groups)
    for i in range(len(groups)):
        for j in range(i + 1, len(groups)):
            if compatible(groups[i], groups[j]):
                masks[i] |= 1 << j  # 关系对称，两边都要登记
                masks[j] |= 1 << i
    return masks


def max_clique_size(masks: Masks) -> int:
    """相容图上的最大团大小：候选集只存"还能选哪些组"，按编号从小到大做选/不选 DP。"""

    @cache
    def best(cand: int) -> int:
        """cand 里最多能同时选多少组（选出的组必须两两相容）。"""
        if not cand:
            return 0  # 没有候选组了，这一支只能贡献 0
        bit = cand & -cand
        index = bit.bit_length() - 1  # 最低位对应的组编号
        rest = cand ^ bit             # 不选它：剩下的组编号都大于 index
        keep = rest & masks[index]    # 选它：剩下的只能从它的相容集合里挑
        return max(best(rest), 1 + best(keep))

    return best((1 << len(masks)) - 1)


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    n = int(next(tokens))  # N：数字与字母的个数，只限定值域，算法本身用不到
    m = int(next(tokens))  # M：组的个数

    groups: list[Group] = []
    for _ in range(m):
        word = next(tokens).decode()  # 本组的文字段
        length = len(word)            # 数列的数字个数，题面保证等于字符数
        numbers = [int(next(tokens)) for _ in range(length)]
        groups.append(dict(zip(word, numbers)))

    print(max_clique_size(build_masks(groups)))


if __name__ == "__main__":
    solve()
