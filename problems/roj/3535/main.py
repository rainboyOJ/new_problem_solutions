#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:07
# update_at: 2026-10-02 06:30

import sys
from itertools import permutations


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))

    # 三行都按低位在前重排列：从最高位往低位搜索，出进位先已知（最高位固定为 0），
    # 本列的入进位由等式反解出来，恰好等于下一列的出进位，进位链因此一路传到个位。
    cols = list(
        zip(*([ord(ch) - 65 for ch in next(data).decode()[::-1]] for _ in range(3)))
    )
    val = [-1] * n       # 字母 -> 数字；-1 表示还没定
    used = [False] * n   # 数字是否已被认领
    ans: list[int] = []

    # 热路径变量走形参默认值：递归调用点少传参，闭包变量也变成本地变量
    def dfs(pos: int, carry_out: int, cols=cols, n=n, val=val, used=used) -> bool:
        """从最高位列 pos 向低位搜（carry_out 是本列出进位），进位链接回个位且无多余进位时返回 True。"""
        if pos < 0:
            ans[:] = val  # 每列等式都成立、进位链两端都是 0，得到唯一解
            return True

        a, b, c = cols[pos]
        v_a, v_b, v_c = val[a], val[b], val[c]
        carries = (0,) if pos == 0 else (0, 1)  # 个位的入进位必为 0
        n_co = n * carry_out

        # 三个字母都已定：等式必须对某个入进位成立，直接验证，不建任何枚举结构
        if v_a >= 0 and v_b >= 0 and v_c >= 0:
            base = v_a + v_b - v_c
            for carry_in in carries:
                if base == n_co - carry_in and dfs(pos - 1, carry_in):
                    return True
            return False

        # 本列未定字母的系数：出现在加数位记 +1，出现在结果位记 -1，两边都出现则抵消成 0；
        # 已定字母折进常数项 base，方程化为 Σ 系数×字母 = n*出进位 - 入进位 - base
        coeff: dict[int, int] = {}
        base = 0
        for ch, vc in ((a, v_a), (b, v_b)):
            if vc < 0:
                coeff[ch] = coeff.get(ch, 0) + 1
            else:
                base += vc
        if v_c < 0:
            coeff[c] = coeff.get(c, 0) - 1
        else:
            base -= v_c

        pivots = [l for l, w in coeff.items() if w]  # 方程能解出的字母
        zero = [l for l, w in coeff.items() if not w]  # 被抵消的字母：本列方程管不到

        # 没有可解字母（未定字母全被抵消）：等式必须直接成立，否则先剪掉该进位组合
        if not pivots:
            for carry_in in carries:
                if n_co - carry_in != base:
                    continue
                for combo in permutations([d for d in range(n) if not used[d]], len(zero)):
                    for l, d in zip(zero, combo):
                        val[l] = d
                        used[d] = True
                    if dfs(pos - 1, carry_in):
                        return True
                    for l, d in zip(zero, combo):
                        val[l] = -1
                        used[d] = False
            return False

        # 只留一个字母最后解方程，枚举维度少一维
        pivot = pivots.pop()
        free = zero + pivots
        wp = coeff[pivot]
        rest = [d for d in range(n) if not used[d]]

        for carry_in in carries:
            rhs = n_co - carry_in - base
            for combo in permutations(rest, len(free)):
                got = 0
                for l, d in zip(free, combo):
                    w = coeff[l]
                    if w:
                        got += w * d
                rem = rhs - got
                if rem % wp:
                    continue
                digit = rem // wp  # 由方程唯一解出的最后一个字母
                if not 0 <= digit < n or used[digit] or digit in combo:
                    continue
                val[pivot] = digit
                used[digit] = True
                for l, d in zip(free, combo):
                    val[l] = d
                    used[d] = True
                if dfs(pos - 1, carry_in):  # 本列入进位就是下一列的出进位
                    return True
                for l, d in zip(free, combo):  # 回溯：撤销本列的赋值
                    val[l] = -1
                    used[d] = False
                val[pivot] = -1
                used[digit] = False
        return False

    dfs(n - 1, 0)
    print(' '.join(map(str, ans)))


if __name__ == "__main__":
    solve()
