#!/usr/bin/env python3
import random


def main():
    random.seed()
    rows = random.randint(1, 7)
    columns = random.randint(1, 7)
    horizontal_parts = random.randint(1, rows)
    vertical_parts = random.randint(1, columns)

    print(rows, columns, horizontal_parts, vertical_parts)
    for _ in range(rows):
        row = [str(random.randint(0, 20)) for _ in range(columns)]
        print(" ".join(row))


if __name__ == "__main__":
    main()
