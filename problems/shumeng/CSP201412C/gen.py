#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    lines = random.randint(1, 18)
    active = []
    for line in range(1, lines + 1):
        if active and random.random() < 0.25:
            index = random.choice(active)
            active.remove(index)
            print("cancel", index)
        else:
            operation = random.choice(["buy", "sell"])
            price = random.randint(1, 10000)
            amount = random.randint(1, 100)
            print(operation, price // 100, end="")
            print(".%02d %d" % (price % 100, amount))
            active.append(line)


if __name__ == "__main__":
    main()
