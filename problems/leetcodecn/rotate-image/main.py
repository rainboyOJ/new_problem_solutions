#!/usr/bin/env python3
from typing import List


class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        n = len(matrix)
        for i in range(n):
            for j in range(i + 1, n):
                matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
        for row in matrix:
            row.reverse()


def main() -> None:
    n = int(input())
    a = [list(map(int, input().split())) for _ in range(n)]
    Solution().rotate(a)
    for row in a:
        print(*row)


if __name__ == "__main__":
    main()
