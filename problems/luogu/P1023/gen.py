#!/usr/bin/env python3
import random


def main():
    random.seed()
    target = random.randint(20, 40)
    cost = random.randint(10, target)
    m = random.randint(2, 5)

    xs = sorted(random.sample(range(cost, cost + 10), m))
    ys = []
    cur = random.randint(50, 100)
    ys.append(cur)
    for _ in range(1, m):
        cur -= random.randint(1, 10)
        ys.append(cur)

    print(target)
    for x, y in zip(xs, ys):
        print(x, y)
    print(-1, -1)
    print(random.randint(1, 10))


if __name__ == "__main__":
    main()
