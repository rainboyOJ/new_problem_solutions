#!/usr/bin/env python3
import random


def main():
    m = random.randint(1, 4)
    n = random.randint(1, 4)
    print(m, n)

    order = []
    for job in range(1, n + 1):
        order.extend([job] * m)
    random.shuffle(order)
    print(" ".join(map(str, order)))

    machines = []
    for _ in range(n):
        arr = list(range(1, m + 1))
        random.shuffle(arr)
        machines.append(arr)
        print(" ".join(map(str, arr)))

    for _ in range(n):
        times = [random.randint(1, 5) for _ in range(m)]
        print(" ".join(map(str, times)))


if __name__ == "__main__":
    main()
