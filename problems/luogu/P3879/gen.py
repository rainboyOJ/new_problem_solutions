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


CHARS = string.ascii_lowercase[:4]


def rand_word():
    length = random.randint(1, 5)
    return "".join(random.choice(CHARS) for _ in range(length))


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 6)
    print(n)
    words = []
    for _ in range(n):
        cnt = random.randint(1, 6)
        arr = [rand_word() for _ in range(cnt)]
        words.extend(arr)
        print(cnt, *arr)

    m = random.randint(1, 8)
    print(m)
    for _ in range(m):
        if words and random.randint(0, 1) == 0:
            print(random.choice(words))
        else:
            print(rand_word())


if __name__ == "__main__":
    main()
