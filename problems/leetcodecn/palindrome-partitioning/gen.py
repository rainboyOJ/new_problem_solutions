#!/usr/bin/env python3
import random

def main() -> None:
    random.seed()
    n = random.randint(1, 8)
    s = ''.join(random.choices('abc', k=n))
    print(s)

if __name__ == "__main__":
    main()
