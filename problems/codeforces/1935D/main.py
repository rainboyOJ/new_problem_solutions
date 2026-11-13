#!/usr/bin/env python3
import sys


def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(input_data)

    t = int(next(it))
    out = []

    for _ in range(t):
        n = int(next(it))
        c = int(next(it))
        s = [int(next(it)) for _ in range(n)]

        tot = (c + 1) * (c + 2) // 2

        size_a = 0
        size_b = 0
        cnt_odd = 0
        cnt_even = 0

        for val in s:
            size_a += val // 2 + 1
            size_b += c - val + 1
            if val % 2 != 0:
                cnt_odd += 1
            else:
                cnt_even += 1

        size_ab = cnt_odd * (cnt_odd + 1) // 2 + cnt_even * (cnt_even + 1) // 2
        ans = tot - size_a - size_b + size_ab
        out.append(str(ans))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
