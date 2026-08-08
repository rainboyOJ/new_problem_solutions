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
    seed = None
    if len(sys.argv) > 1:
        seed = int(sys.argv[1])
        random.seed(seed)

    n = random.randint(1, 9)
    k = random.randint(1, n)
    x = random.randint(1, n)

    edges = []
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        edges.append((p, i))

    print(n, k, x)
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
