#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 8)
    k = random.randint(1, n)

    init = sorted(random.sample(range(1, n + 1), random.randint(1, n)))
    candidates = [x for x in range(1, n + 1) if x not in init]
    random.shuffle(candidates)
    r = random.randint(0, len(candidates))
    chosen = candidates[:r]

    print(n, k, len(init))
    print(*init)
    print(r)
    for v in chosen:
        cnt = random.randint(1, n)
        need = sorted(random.sample(range(1, n + 1), cnt))
        print(v, cnt, *need)


if __name__ == "__main__":
    main()
