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


def rand_word(alpha: str, max_len: int) -> str:
    return "".join(random.choice(alpha) for _ in range(random.randint(1, max_len)))


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    alpha = "ABC"
    m = random.randint(1, 6)
    x = random.randint(1, 25)
    prims = [rand_word(alpha, 4) for _ in range(m)]
    s = "".join(random.choice(alpha) for _ in range(x))

    print(" ".join(prims))
    print(".")
    print(s)


if __name__ == "__main__":
    main()
