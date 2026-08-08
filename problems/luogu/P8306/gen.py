#!/usr/bin/env python3
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
#!/usr/bin/env python3
import random
import string
import sys


CHARS = string.digits + string.ascii_uppercase[:4] + string.ascii_lowercase[:4]


def rand_str():
    length = random.randint(1, 5)
    return "".join(random.choice(CHARS) for _ in range(length))


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    T = random.randint(1, 3)
    print(T)
    for _ in range(T):
        n = random.randint(1, 6)
        q = random.randint(1, 6)
        print(n, q)
        for _ in range(n):
            print(rand_str())
        for _ in range(q):
            print(rand_str())


if __name__ == "__main__":
    main()
