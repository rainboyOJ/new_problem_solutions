#!/usr/bin/env python3
import sys


def read_ints(path):
    with open(path, "r", encoding="utf-8") as f:
        return [int(x) for x in f.read().split()]


def eval_plan(n, d, h, days):
    if len(days) != n:
        return None
    last = 1
    for day in days:
        if day < last or day > d:
            return None
        last = day

    happy = 0
    mn = 10**30
    idx = 0
    for day in range(1, d + 1):
        while idx < n and days[idx] == day:
            happy += h[idx]
            idx += 1
        mn = min(mn, happy)
        happy //= 2
    if idx != n:
        return None
    return mn


def main():
    if len(sys.argv) != 4:
        return 2

    inp = read_ints(sys.argv[1])
    user = read_ints(sys.argv[2])
    brute = read_ints(sys.argv[3])

    if len(inp) < 2 or len(brute) < 1 or len(user) < 1:
        return 1

    n, d = inp[0], inp[1]
    h = inp[2:2 + n]
    if len(h) != n:
        return 1

    optimal = brute[0]
    claimed = user[0]
    days = user[1:]
    val = eval_plan(n, d, h, days)
    if val is None:
        print("invalid plan")
        return 1
    if claimed != optimal:
        print(f"claimed value {claimed} != optimal {optimal}")
        return 1
    if val < claimed:
        print(f"plan minimum {val} < claimed {claimed}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
