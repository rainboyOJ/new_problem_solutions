#!/usr/bin/env python3
import random

def main() -> None:
    random.seed()
    n = random.randint(1, 6)
    print(n)

if __name__ == "__main__":
    main()
