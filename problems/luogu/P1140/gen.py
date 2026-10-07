#!/usr/bin/env python3
import random


def rand_gene(length):
    alphabet = "ACGT"
    return "".join(random.choice(alphabet) for _ in range(length))


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 8)
    print(n, rand_gene(n))
    print(m, rand_gene(m))


if __name__ == "__main__":
    main()
