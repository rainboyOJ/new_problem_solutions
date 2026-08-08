#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 40)
    m = random.randint(0, 8)
    k = random.randint(1, 8)

    d = sorted(random.randint(1, 20) for _ in range(n))
    possible_special = list(range(1, max(1, d[-1])))
    random.shuffle(possible_special)
    s = sorted(possible_special[: min(m, len(possible_special))])
    t = sorted(random.sample(range(1, 18), k))

    print(n, len(s), k)
    print(*d)
    if s:
        print(*s)
    else:
        print()
    print(*t)


if __name__ == "__main__":
    main()
