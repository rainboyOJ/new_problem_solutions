#!/usr/bin/env python3
import random


triples = [
    (3, 4, 5),
    (5, 12, 13),
    (6, 8, 10),
    (7, 24, 25),
    (8, 15, 17),
    (9, 12, 15),
    (20, 21, 29),
]


def main():
    random.seed()
    t = list(random.choice(triples))
    random.shuffle(t)
    print(*t)


if __name__ == "__main__":
    main()
