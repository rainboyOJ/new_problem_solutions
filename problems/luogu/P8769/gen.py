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


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    x = random.randint(1, 8)
    n = random.randint(1, 6)
    print(x, n)
    for _ in range(n):
        a = random.randint(1, 20)
        b = random.randint(1, x + 2)
        c = random.randint(1, 4)
        print(a, b, c)


if __name__ == "__main__":
    main()
