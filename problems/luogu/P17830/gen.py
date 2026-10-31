#!/usr/bin/env python3
"""对拍数据生成器：n 张牌、点数取值 1..m，且每种点数至少出现一次。"""
import sys

from cyaron import randint


def emit(a, m):
    print(len(a), m)
    print(*a)


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else "rand"
    if mode == "min":                       # 最小规模，点数只有 1 和 2
        emit([1, 2], 2)
        return
    if mode == "two":                        # m = 2，只有两种点数
        n = randint(2, 30)
        a = [randint(1, 2) for _ in range(n)]
        a[randint(0, n - 1)] = 1
        a[randint(0, n - 1)] = 2
        emit(a, 2)
        return
    if mode == "sorted":                      # 特殊性质 A：序列单调不降
        m = randint(1, 6)
        a = []
        for v in range(1, m + 1):
            a += [v] * randint(1, 4)
        emit(a, m)
        return
    if mode == "block":                       # 特殊性质 B 的味道：连续块很少
        m = randint(2, 5)
        a = list(range(1, m + 1))
        for _ in range(randint(0, 3)):
            a.insert(randint(0, len(a)), randint(1, m))
        emit(a, m)
        return
    m = randint(1, 6)
    n = randint(m, 30)
    a = list(range(1, m + 1))                 # 先保证每种点数出现一次
    while len(a) < n:
        a.append(randint(1, m))
    for i in range(len(a) - 1, 0, -1):        # 打乱顺序
        j = randint(0, i)
        a[i], a[j] = a[j], a[i]
    emit(a, m)


if __name__ == "__main__":
    main()
