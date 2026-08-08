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

    v = random.randint(1, 25)
    p = random.randint(1, v)
    arr = sorted(random.sample(range(1, 200), v))

    print(v, p)
    print(*arr)


if __name__ == "__main__":
    main()
