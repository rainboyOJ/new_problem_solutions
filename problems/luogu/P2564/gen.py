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

    k = random.randint(1, 5)
    counts = []
    total = 0
    for _ in range(k):
        c = random.randint(1, 4)
        counts.append(c)
        total += c

    print(total, k)
    for c in counts:
        arr = [random.randint(0, 12) for _ in range(c)]
        print(c, *arr)


if __name__ == "__main__":
    main()
