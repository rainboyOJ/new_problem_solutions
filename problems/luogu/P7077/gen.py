#!/usr/bin/env python3
import random

MOD = 998244353


def main():
    random.seed()

    n = random.randint(1, 6)
    a = [random.randint(0, 10) for _ in range(n)]
    m = random.randint(1, 8)

    funcs = [None]
    for i in range(1, m + 1):
        typ = random.randint(1, 3)
        if typ == 1:
            funcs.append((1, random.randint(1, n), random.randint(0, 10)))
        elif typ == 2:
            funcs.append((2, random.randint(0, 5)))
        else:
            candidates = list(range(1, i))
            c = random.randint(0, min(3, len(candidates)))
            random.shuffle(candidates)
            funcs.append((3, candidates[:c]))

    qnum = random.randint(1, 6)
    queries = [random.randint(1, m) for _ in range(qnum)]

    print(n)
    print(*a)
    print(m)
    for i in range(1, m + 1):
        item = funcs[i]
        if item[0] == 1:
            _, p, v = item
            print(1, p, v % MOD)
        elif item[0] == 2:
            _, v = item
            print(2, v % MOD)
        else:
            _, seq = item
            print(3, len(seq), *seq)
    print(qnum)
    print(*queries)


if __name__ == "__main__":
    main()
