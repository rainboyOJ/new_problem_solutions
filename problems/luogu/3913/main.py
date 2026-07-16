import sys


def main():
    read = sys.stdin.buffer.readline
    n, rook_count = map(int, read().split())
    rows = set()
    columns = set()
    for _ in range(rook_count):
        row, column = map(int, read().split())
        rows.add(row)
        columns.add(column)

    attacked_rows = len(rows)
    attacked_columns = len(columns)
    print(n * attacked_rows + n * attacked_columns - attacked_rows * attacked_columns)


if __name__ == "__main__":
    main()
