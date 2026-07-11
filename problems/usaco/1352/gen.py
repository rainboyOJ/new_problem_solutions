#!/usr/bin/env python3
import random


def main():
    random.seed()
    c = random.randint(1, 12)
    max_targets = min(2 * c + 1, 10)
    t = random.randint(1, max_targets)
    positions = random.sample(range(-c, c + 1), t)
    commands = "".join(random.choice("LFR") for _ in range(c))

    print(t, c)
    print(*positions)
    print(commands)


if __name__ == "__main__":
    main()
