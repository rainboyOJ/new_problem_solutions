#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 17:25
# update_at: 2026-10-02 17:25

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    values = [next(data) for _ in range(n)]

    # 按"窗口长度"下标做差分：d 是差分数组，前缀和后 d[L] 即第 L 窗口值。
    # a_i <= 100，答案上界 1e5 * 100^2 = 1e9，直接输出，无需取模。
    d = [0] * (n + 3)

    # 两个单调栈存 (值, 下标)，栈内下标从栈顶往栈底递减：
    # max 栈的值严格递减、min 栈的值严格递增，元素即"左端点左移时极值发生变化的位置"。
    max_stack: list[tuple[int, int]] = []
    min_stack: list[tuple[int, int]] = []

    for i, x in enumerate(values):
        while max_stack and max_stack[-1][0] <= x:
            max_stack.pop()
        while min_stack and min_stack[-1][0] >= x:
            min_stack.pop()
        max_stack.append((x, i))
        min_stack.append((x, i))

        cur_max = cur_min = x      # 只含 a[i] 这一个左端点时的极值
        left = i                   # 当前已登记的最左左端点
        p_max = len(max_stack) - 2  # 指针停在栈顶的下一层：下一个极值变化点
        p_min = len(min_stack) - 2

        # 左端点从 i 往 0 走，逐个吞并两栈的变化点：
        # 每一步 (cur_max, cur_min) 在左端点 (nxt, left] 上不变，把这段按长度差分入账。
        while p_max >= 0 or p_min >= 0:
            # 两栈都还有变化点时，先走下标更大的那个：更靠近 i 的变化先发生；
            # 同一下标同时是 max/min 变化点时会退化出一段空区间，加减抵消，不影响答案。
            take_max = p_max >= 0 and (p_min < 0 or max_stack[p_max][1] >= min_stack[p_min][1])
            if take_max:
                value, nxt = max_stack[p_max]
                p_max -= 1
            else:
                value, nxt = min_stack[p_min]
                p_min -= 1

            prod = cur_max * cur_min
            d[i - left + 1] += prod  # 左端点 left 对应的窗口长度 = i-left+1
            d[i - nxt + 1] -= prod   # 左端点越过 nxt 后这对极值失效
            left = nxt
            if take_max:
                cur_max = value
            else:
                cur_min = value

        # 剩下左端点 [0, left] 全部落在同一对极值上，长度区间到 i+1 为止。
        prod = cur_max * cur_min
        d[i - left + 1] += prod
        d[i + 2] -= prod

    out: list[str] = []
    total = 0
    for length in range(1, n + 1):
        total += d[length]
        out.append(str(total))
    sys.stdout.write(' '.join(out))


if __name__ == "__main__":
    solve()
