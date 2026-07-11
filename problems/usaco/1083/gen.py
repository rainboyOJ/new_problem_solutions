#!/usr/bin/env python3
import random
import string


def main():
    random.seed()
    letters = list(string.ascii_lowercase)
    random.shuffle(letters)
    alphabet = "".join(letters)

    length = random.randint(1, 80)
    heard = []
    for _ in range(length):
        heard.append(random.choice(string.ascii_lowercase))

    print(alphabet)
    print("".join(heard))


if __name__ == "__main__":
    main()
