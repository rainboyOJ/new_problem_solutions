#!/usr/bin/env python3
import random


def main():
    random.seed()
    cows = [
        "Beatrice",
        "Belinda",
        "Bella",
        "Bessie",
        "Betsy",
        "Blue",
        "Buttercup",
        "Sue",
    ]

    lineup = cows[:]
    random.shuffle(lineup)

    possible = []
    for i in range(7):
        a = lineup[i]
        b = lineup[i + 1]
        if random.randint(0, 1) == 0:
            possible.append((a, b))
        else:
            possible.append((b, a))

    random.shuffle(possible)
    n = random.randint(1, 7)
    constraints = possible[:n]

    print(n)
    for a, b in constraints:
        print(f"{a} must be milked beside {b}")


if __name__ == "__main__":
    main()
