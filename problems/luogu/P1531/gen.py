#!/usr/bin/env python3
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 8)
    m = random.randint(1, 12)
    arr = [random.randint(0, 10) for _ in range(n)]

    print(n, m)
    print(*arr)
    for _ in range(m):
        if random.randint(0, 1) == 0:
            x = random.randint(1, n)
            y = random.randint(0, 10)
            print("U", x, y)
        else:
            l = random.randint(1, n)
            r = random.randint(1, n)
            print("Q", l, r)


if __name__ == "__main__":
    main()
