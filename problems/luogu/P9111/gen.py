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
    vals = [random.randint(-20, 20) for _ in range(n)]
    parent = []
    for i in range(2, n + 1):
        parent.append(random.randint(1, i - 1))

    print(n)
    print(*vals)
    if n >= 2:
        print(*parent)


if __name__ == "__main__":
    main()
