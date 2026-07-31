#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    dimension = random.randint(1, 8)
    query_count = random.randint(1, 12)
    print(dimension, query_count)
    for _ in range(dimension):
        x1 = random.randint(1, dimension)
        x2 = random.randint(x1, dimension)
        y1 = random.randint(1, dimension)
        y2 = random.randint(y1, dimension)
        v = random.randint(1, dimension)
        print(x1, x2, y1, y2, v)
    for _ in range(query_count):
        x1 = random.randint(1, dimension)
        x2 = random.randint(x1, dimension)
        y1 = random.randint(1, dimension)
        y2 = random.randint(y1, dimension)
        print(x1, x2, y1, y2)


if __name__ == "__main__":
    main()
