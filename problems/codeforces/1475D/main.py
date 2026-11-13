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
        m = int(next(it))

        a = [int(next(it)) for _ in range(n)]
        b = [int(next(it)) for _ in range(n)]

        ones = []
        twos = []
        for x, cost in zip(a, b):
            if cost == 1:
                ones.append(x)
            else:
                twos.append(x)

        ones.sort(reverse=True)
        twos.sort(reverse=True)

        cnt1 = len(ones)
        cnt2 = len(twos)

        # 前缀和
        sum_one = [0] * (cnt1 + 1)
        for i in range(cnt1):
            sum_one[i + 1] = sum_one[i] + ones[i]

        sum_two = [0] * (cnt2 + 1)
        for i in range(cnt2):
            sum_two[i + 1] = sum_two[i] + twos[i]

        if sum_one[cnt1] + sum_two[cnt2] < m:
            out.append("-1")
            continue

        # 双指针扫描
        y = cnt2
        ans = 10**18

        for x in range(cnt1 + 1):
            while y > 0 and sum_one[x] + sum_two[y - 1] >= m:
                y -= 1
            if sum_one[x] + sum_two[y] >= m:
                cost = x + 2 * y
                if cost < ans:
                    ans = cost

        out.append(str(ans))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
