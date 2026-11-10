#!/usr/bin/env python3
"""duipai checker：独立校验 main 的输出，而不是与 brute 逐字节比对。

main 的多解：总时间必须等于 brute 的最优值，且给出的顺序必须是 1..n 的一个排列，
按该顺序重新模拟能复现该总时间。

用法（duipai --checker）：
    checker.py input.txt user.out brute.out
退出码 0 通过，非 0 失败并打印原因。
"""
import sys


def read_input(path):
    with open(path) as f:
        data = f.read().split()
    it = iter(data)
    n = int(next(it))
    a = [int(next(it)) for _ in range(n)]
    b = [int(next(it)) for _ in range(n)]
    return n, a, b


def simulate(order, a, b):
    finish_a = 0
    finish_b = 0
    for idx in order:
        finish_a += a[idx]
        finish_b = max(finish_b, finish_a) + b[idx]
    return finish_b


def main():
    inp, got_path, want_path = sys.argv[1:4]
    n, a, b = read_input(inp)

    with open(want_path) as f:
        want = f.read().split()
    want_time = int(want[0])

    with open(got_path) as f:
        got = f.read().split()
    if not got:
        print("empty output")
        sys.exit(1)

    got_time = int(got[0])
    if got_time != want_time:
        print(f"time mismatch: got {got_time}, expected {want_time}")
        sys.exit(1)

    if len(got) < 1 + n:
        print(f"order too short: need {n}, got {len(got) - 1}")
        sys.exit(1)

    order = [int(x) for x in got[1:1 + n]]
    if sorted(order) != list(range(1, n + 1)):
        print(f"order is not a permutation of 1..{n}: {order}")
        sys.exit(1)

    # 用 0 基下标重算，复现总时间
    recompute = simulate([x - 1 for x in order], a, b)
    if recompute != got_time:
        print(f"order does not achieve claimed time: recompute {recompute}, claimed {got_time}")
        sys.exit(1)

    sys.exit(0)


if __name__ == "__main__":
    main()
