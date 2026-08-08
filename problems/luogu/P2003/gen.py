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
    heights = random.sample(range(1, 20), n)
    print(n)
    for h in heights:
        l = random.randint(1, 10)
        r = random.randint(l + 2, 15)
        print(h, l, r)


if __name__ == "__main__":
    main()
