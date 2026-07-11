#!/usr/bin/env python3
import random


def main():
    random.seed()
    k = random.randint(1, 10)
    m = random.randint(1, 6)
    n = random.randint(1, 6)
    positions = random.sample(range(0, 60), k + m)
    random.shuffle(positions)

    patch_pos = positions[:k]
    enemy_pos = positions[k:]

    print(k, m, n)
    for p in patch_pos:
        print(p, random.randint(0, 30))
    for f in enemy_pos:
        print(f)


if __name__ == "__main__":
    main()
