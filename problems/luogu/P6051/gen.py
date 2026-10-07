#!/usr/bin/env python3
import random
import string


SEP = list(" .,:;!?-\t") + list(string.ascii_letters)


def make_num():
    x = random.randint(-20, 20)
    return str(x)


def main():
    random.seed()
    lines = []
    m = random.randint(1, 6)
    for _ in range(m):
        if random.randint(1, 5) == 1:
            lines.append("".join(random.choice(SEP) for _ in range(random.randint(0, 12))))
            continue

        parts = []
        k = random.randint(1, 6)
        for i in range(k):
            if i:
                parts.append("".join(random.choice(SEP) for _ in range(random.randint(1, 4))))
            parts.append(make_num())
        if random.randint(0, 1):
            parts.append("".join(random.choice(SEP) for _ in range(random.randint(0, 5))))
        lines.append("".join(parts))
    print("\n".join(lines))


if __name__ == "__main__":
    main()
