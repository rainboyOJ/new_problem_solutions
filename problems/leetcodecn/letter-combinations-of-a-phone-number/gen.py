#!/usr/bin/env python3
import random

def main() -> None:
    random.seed()
    # digits.length <= 4 for brute feasibility
    k = random.randint(0, 4)
    digits = ''.join(str(random.randint(2, 9)) for _ in range(k))
    print(digits)

if __name__ == "__main__":
    main()
