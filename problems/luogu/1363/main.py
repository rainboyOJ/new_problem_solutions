import sys
from array import array


UNVISITED = -2_147_483_648
DIRECTIONS = ((-1, 0), (1, 0), (0, -1), (0, 1))


def can_escape(grid, start):
    n, m = len(grid), len(grid[0])
    total = n * m
    first_x = array("i", [UNVISITED]) * total
    first_y = array("i", [UNVISITED]) * total
    start_x, start_y = start
    start_index = start_x * m + start_y
    first_x[start_index] = start_x
    first_y[start_index] = start_y

    queue_x = array("i", [start_x])
    queue_y = array("i", [start_y])
    head = 0
    while head < len(queue_x):
        x, y = queue_x[head], queue_y[head]
        head += 1
        for dx, dy in DIRECTIONS:
            next_x, next_y = x + dx, y + dy
            row, column = next_x % n, next_y % m
            if grid[row][column] == 35:
                continue
            index = row * m + column
            if first_x[index] == UNVISITED:
                first_x[index] = next_x
                first_y[index] = next_y
                queue_x.append(next_x)
                queue_y.append(next_y)
            elif first_x[index] != next_x or first_y[index] != next_y:
                return True
    return False


def main():
    read = sys.stdin.buffer.readline
    answer = []
    while True:
        header = read().split()
        if not header:
            break
        n, m = map(int, header)
        grid = []
        start = None
        for row in range(n):
            line = read().strip()
            column = line.find(b"S")
            if column != -1:
                start = (row, column)
            grid.append(line)
        answer.append("Yes" if can_escape(grid, start) else "No")
    print("\n".join(answer))


if __name__ == "__main__":
    main()
