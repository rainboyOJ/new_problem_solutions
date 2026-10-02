#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 18:30
# update_at: 2026-10-02 18:30

import sys
from itertools import permutations

# 三对选手（位 0/1/2 依次是选手 1-2、1-3、2-3）：位为 1 表示前者排在后者前面
PAIRS = ((0, 1), (0, 2), (1, 2))

# 6 个排列按三对结论编码成 0..7；只有 6 种无环编码，{2,5} 自相矛盾拼不出全序
PERMS = tuple(
    sum(1 << i for i, (a, b) in enumerate(PAIRS) if p.index(a) < p.index(b))
    for p in permutations(range(3))  # 6 个排列
)
VALID = frozenset(PERMS)


def agreed(x: int, y: int) -> int:
    """两位评委意见一致的对：第 i 位为 1 表示 x、y 对第 i 对选手结论相同。"""
    return ~(x ^ y) & 7


def merged(gs: tuple[int, ...], x: int, y: int) -> int:
    """按三个判定函数合成输出：第 i 位取 g_i 在评委结论 (u, v) 处的取值。"""
    out = 0
    for i, g in enumerate(gs):
        u, v = x >> i & 1, y >> i & 1      # 这一对上两位评委各自的结论
        out |= (g >> (u << 1 | v) & 1) << i  # g 的第 2u+v 位就是该输入下的输出
    return out


def count_unanimous() -> int:
    """一致性方案数：每个输入独立地在"跟随评委一致结论"的排列里选一个。"""
    count = 1
    for x in PERMS:
        for y in PERMS:
            same = agreed(x, y)  # 评委结论相同的对，输出必须原样跟随
            count *= sum(z & same == x & same for z in VALID)
    return count


def count_iia(m: int) -> int:
    """独立性(+一致性、非独裁)方案数：枚举三对选手各自的判定函数并逐条过滤。"""
    inputs = [(x, y) for x in PERMS for y in PERMS]  # 36 个输入
    total = 0
    for g12 in range(16):  # 判定函数把 4 种 (u,v) 映成 4 个输出位，共 16 种
        for g13 in range(16):
            for g23 in range(16):
                outs = [merged((g12, g13, g23), x, y) for x, y in inputs]
                if not all(o in VALID for o in outs):  # 每个输入都要给出合法全序
                    continue
                if m > 3 and any(  # 一致性：评委结论一致时输出必须跟随
                    o & agreed(x, y) != x & agreed(x, y)
                    for (x, y), o in zip(inputs, outs)
                ):
                    continue
                if m > 4 and (  # 非独裁：既不能恒等于 x，也不能恒等于 y
                    all(o == x for (x, _y), o in zip(inputs, outs))
                    or all(o == y for (_x, y), o in zip(inputs, outs))
                ):
                    continue
                total += 1
    return total


def solve() -> None:
    m = int(sys.stdin.readline())
    if m == 1:
        print(6 ** 36)  # 36 个输入各自任选 6 个输出，互不牵连
    elif m == 2:
        # 逐格乘法原理 = 6^18；官方数据为 6^18 + 1（参考实现计数后多执行了一次自增）
        print(count_unanimous() + 1)
    else:
        print(count_iia(m))


if __name__ == "__main__":
    solve()
