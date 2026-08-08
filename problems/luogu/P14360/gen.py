#!/usr/bin/env python3
import random
import sys

def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else random.randint(3, 15)
    max_val = int(sys.argv[2]) if len(sys.argv) > 2 else 10
    print(n)
    a = [random.randint(1, max_val) for _ in range(n)]
    print(' '.join(map(str, a)))

if __name__ == "__main__":
    main()
