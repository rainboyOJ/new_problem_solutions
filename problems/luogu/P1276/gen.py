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

    L = random.randint(1, 20)
    n = random.randint(1, 12)
    print(L, n)
    for _ in range(n):
        op = random.randint(0, 1)
        l = random.randint(0, L)
        r = random.randint(l, L)
        print(op, l, r)


if __name__ == "__main__":
    main()
