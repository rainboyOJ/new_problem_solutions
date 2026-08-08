#!/usr/bin/env python3
import random


WEEKS = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]


def main():
    random.seed()
    m = random.randint(1, 7)
    n = random.randint(0, m)
    p = random.randint(1, 12)
    print(m, n, p)

    names = [f"P{i}" for i in range(m)]
    for name in names:
        print(name)

    for _ in range(p):
        sp = random.choice(names)
        tp = random.randint(0, 5)
        if tp == 0:
            text = "I am guilty."
        elif tp == 1:
            text = "I am not guilty."
        elif tp == 2:
            text = f"{random.choice(names)} is guilty."
        elif tp == 3:
            text = f"{random.choice(names)} is not guilty."
        elif tp == 4:
            text = f"Today is {random.choice(WEEKS)}."
        else:
            text = "How are you??"
        print(f"{sp}: {text}")


if __name__ == "__main__":
    main()
