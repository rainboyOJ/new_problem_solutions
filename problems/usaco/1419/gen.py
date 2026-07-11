#!/usr/bin/env python3
import random
import sys


def main():
    random.seed()
    max_n = 31
    max_q = 40
    if len(sys.argv) >= 2:
        max_n = int(sys.argv[1])
    if len(sys.argv) >= 3:
        max_q = int(sys.argv[2])

    max_n = max(1, max_n)
    if max_n % 2 == 0:
        max_n -= 1
    n = random.randrange(1, max_n + 1, 2)
    q = random.randint(1, max_q)

    words = []
    for i in range(1, n + 1):
        if i % 2 == 1:
            words.append(random.choice(["true", "false"]))
        else:
            words.append(random.choice(["and", "or"]))

    print(n, q)
    print(" ".join(words))

    bool_positions = list(range(1, n + 1, 2))
    for _ in range(q):
        l = random.choice(bool_positions)
        r = random.choice(bool_positions)
        if l > r:
            l, r = r, l
        want = random.choice(["true", "false"])
        print(l, r, want)


if __name__ == "__main__":
    main()
