import sys
from functools import cache

sys.setrecursionlimit(20_000)
row_count, column_count = map(int, input().split())
heights = [list(map(int, input().split())) for _ in range(row_count)]


@cache
def longest_from(row: int, column: int) -> int:
    best = 1
    for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        next_row, next_column = row + dr, column + dc
        if (
            0 <= next_row < row_count
            and 0 <= next_column < column_count
            and heights[next_row][next_column] < heights[row][column]
        ):
            best = max(best, 1 + longest_from(next_row, next_column))
    return best


print(max(longest_from(row, column) for row in range(row_count) for column in range(column_count)))
