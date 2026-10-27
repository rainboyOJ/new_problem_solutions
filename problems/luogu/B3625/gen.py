#!/usr/bin/env python3
import random

def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 8)
    grid = [['#' if random.random() < 0.3 else '.' for _ in range(m)] for _ in range(n)]
    grid[0][0] = '.'
    grid[n - 1][m - 1] = '.'
    print(n, m)
    for row in grid:
        print(''.join(row))

if __name__ == "__main__":
    main()
