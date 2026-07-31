#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 "
    shuffled = list(alphabet)
    random.shuffle(shuffled)
    n = len(alphabet)
    initial = "".join(random.choice(alphabet) for _ in range(random.randint(1, 20)))
    print('#' + initial + '#')
    print(n)
    for source, target in zip(alphabet, shuffled):
        print('#' + source + target + '#')
    query_count = random.randint(1, 20)
    print(query_count)
    print(*[random.randint(1, 30) for _ in range(query_count)])


if __name__ == "__main__":
    main()
