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

    n = random.randint(1, 8)
    t = 0
    for i in range(1, n + 1):
        t += random.randint(0, 4)
        run = random.randint(1, 8)
        priority = random.randint(1, 6)
        print(i, t, run, priority)


if __name__ == "__main__":
    main()
