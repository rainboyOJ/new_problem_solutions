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
    arr = [random.randint(-5, 5) for _ in range(n)]

    print(n, m)
    print(*arr)
    for _ in range(m):
        op = random.randint(1, 2)
        if op == 1:
            x = random.randint(1, n)
            k = random.randint(-5, 5)
            print(1, x, k)
        else:
            l = random.randint(1, n)
            r = random.randint(l, n)
            print(2, l, r)


if __name__ == "__main__":
    main()
