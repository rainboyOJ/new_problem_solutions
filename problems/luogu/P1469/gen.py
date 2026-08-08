#!/usr/bin/env python3
import os
import random


def main():
    random.seed(int(os.environ.get("DUPAI_SEED", "0")))

    pair_count = random.randint(0, 40)
    lengths = []
    for _ in range(pair_count):
        length = random.randint(1, 100)
        lengths.extend((length, length))

    lengths.append(random.randint(1, 100))
    random.shuffle(lengths)

    print(len(lengths))
    print(*lengths)


if __name__ == "__main__":
    main()
