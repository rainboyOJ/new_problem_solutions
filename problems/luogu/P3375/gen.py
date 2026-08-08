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


def rand_str(n: int, alpha: str = "ABC") -> str:
    return "".join(random.choice(alpha) for _ in range(n))


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    n = random.randint(1, 30)
    m = random.randint(1, 8)
    print(rand_str(n))
    print(rand_str(m))


if __name__ == "__main__":
    main()
