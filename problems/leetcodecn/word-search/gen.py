#!/usr/bin/env python3
import random

def main() -> None:
    random.seed()
    m = random.randint(1, 4)
    n = random.randint(1, 4)
    letters = [chr(random.randint(65, 68)) for _ in range(m * n)]
    grid = [letters[i*n:(i+1)*n] for i in range(m)]
    k = random.randint(1, 6)
    word = ''.join(random.choice(letters) for _ in range(k))
    print(m, n)
    for row in grid:
        print(*row)
    print(word)

if __name__ == "__main__":
    main()
