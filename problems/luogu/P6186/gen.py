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

    n = random.randint(2, 8)
    m = random.randint(1, 12)
    a = list(range(1, n + 1))
    random.shuffle(a)

    print(n, m)
    print(*a)
    for _ in range(m):
        op = random.randint(1, 2)
        if op == 1:
            x = random.randint(1, n - 1)
            print(1, x)
        else:
            k = random.randint(0, n + 2)
            print(2, k)


if __name__ == "__main__":
    main()
