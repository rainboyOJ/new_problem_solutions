#!/usr/bin/env python3
import os
import random


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is not None:
        random.seed(int(seed_text))
    else:
        random.seed()

    print(random.randint(3, 500))


if __name__ == "__main__":
    main()
