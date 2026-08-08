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


def rand_name():
    length = random.randint(1, 5)
    return "".join(random.choice(string.ascii_lowercase[:4]) for _ in range(length))


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 8)
    m = random.randint(1, 12)

    names = set()
    while len(names) < n:
        names.add(rand_name())
    names = list(names)

    print(n)
    for s in names:
        print(s)

    print(m)
    for _ in range(m):
        if random.randint(0, 1) == 0:
            print(random.choice(names))
        else:
            print(rand_name())


if __name__ == "__main__":
    main()
