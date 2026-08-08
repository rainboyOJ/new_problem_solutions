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
    arr = [random.randint(1, 30) for _ in range(n)]

    print(n)
    print(*arr)


if __name__ == "__main__":
    main()
