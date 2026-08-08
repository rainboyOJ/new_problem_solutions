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
    m = random.randint(1, 30)
    caps = [random.randint(1, 20) for _ in range(n)]

    print(n, m)
    print(*caps)

    cur_t = 0
    for _ in range(m):
        cur_t += random.randint(0, 3)
        b = random.randint(1, n)
        c = random.randint(1, 8)
        d = random.randint(1, 10)
        print(cur_t, b, c, d)


if __name__ == "__main__":
    main()
