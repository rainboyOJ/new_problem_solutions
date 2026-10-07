#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 5)
    rows = list(range(1, n + 1))
    cols = list(range(1, n + 1))
    random.shuffle(rows)
    random.shuffle(cols)

    values = list(range(2, 2 * n + 1))
    shuffled = values[:]
    random.shuffle(shuffled)
    rename = {values[i]: shuffled[i] for i in range(len(values))}

    print(n)
    for i in range(n):
        line = []
        for j in range(n):
            before = rows[i] + cols[j]
            line.append(rename[before])
        print(*line)


if __name__ == "__main__":
    main()
