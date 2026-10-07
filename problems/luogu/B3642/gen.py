#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(1, 12)
    left = [0] * (n + 1)
    right = [0] * (n + 1)

    available = [1]
    for node in range(2, n + 1):
        parent = random.choice(available)
        if left[parent] == 0 and right[parent] == 0:
            if random.randint(0, 1) == 0:
                left[parent] = node
            else:
                right[parent] = node
        elif left[parent] == 0:
            left[parent] = node
        else:
            right[parent] = node

        if left[parent] != 0 and right[parent] != 0:
            available.remove(parent)
        available.append(node)

    print(n)
    for i in range(1, n + 1):
        print(left[i], right[i])


if __name__ == "__main__":
    main()
