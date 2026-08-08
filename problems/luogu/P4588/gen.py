#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    t = random.randint(1, 3)
    print(t)
    for _ in range(t):
        q = random.randint(1, 30)
        mod = random.randint(2, 1000)
        print(q, mod)

        add_positions = []
        for i in range(1, q + 1):
            if not add_positions or random.randint(0, 1) == 0:
                x = random.randint(1, 100)
                print(1, x)
                add_positions.append(i)
            else:
                pos = random.choice(add_positions)
                print(2, pos)
                add_positions.remove(pos)


if __name__ == "__main__":
    main()
