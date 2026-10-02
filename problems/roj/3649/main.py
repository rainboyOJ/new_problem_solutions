#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:46
# update_at: 2026-10-02 12:46

import sys
from collections.abc import Iterator

N_SCALE = 10**6  # n 的占位值：n 远大于 100，而正整数边界都小于 100


def bound(token: bytes) -> int:
    """把循环边界换成可比较的整数：n 取大占位值，正整数取原值。"""
    return N_SCALE if token == b"n" else int(token)


def run_program(lines: int, claim: bytes, it: Iterator[bytes]) -> str:
    """按栈语义执行一个程序，比对实际复杂度与声称复杂度，返回 Yes/No/ERR。"""
    alive: set[bytes] = set()                      # 尚未销毁的循环变量
    stack: list[tuple[int, bytes, bool]] = []       # (入栈前层数, 变量名, 入栈前父层是否必不进入)
    depth = 0                                       # 当前已进入的 "常数→n" 循环层数
    best = 0                                        # 历史最大层数，即实际复杂度 O(n^best)
    parent_dead = False                             # 外层必然一次不进：内层一律不贡献复杂度
    err = False

    for _ in range(lines):
        tok = next(it)
        if tok == b"F":
            var, x, y = next(it), next(it), next(it)  # 无论是否已出错都要吃掉整行
            if err:
                continue
            if var in alive:                        # 语法错误②：与存活变量重名
                err = True
                continue
            stack.append((depth, var, parent_dead))
            dead = parent_dead or bound(x) > bound(y)   # 初始值已大于上界：一次都不进
            if not dead and x != b"n" and y == b"n":    # 只有 "常数 → n" 贡献一次幂
                depth += 1
                best = max(best, depth)
            parent_dead = dead
            alive.add(var)
        elif not err:                               # E
            if not stack:                           # 语法错误①：E 没有匹配的 F
                err = True
                continue
            depth, var, parent_dead = stack.pop()   # 弹栈恢复外层状态
            alive.discard(var)

    if err or stack:
        return "ERR"
    expected = 0 if claim == b"O(1)" else int(claim[4:-1])  # 声称的 O(n^w) 指数 w
    return "Yes" if best == expected else "No"


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    T = int(next(data))
    print("\n".join(run_program(int(next(data)), next(data), data) for _ in range(T)))


if __name__ == "__main__":
    solve()
