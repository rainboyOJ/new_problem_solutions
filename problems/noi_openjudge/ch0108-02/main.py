size, row, column = map(int, input().split())

def show(cells):
    print(" ".join(f"({x},{y})" for x, y in cells))

show((row, y) for y in range(1, size + 1))
show((x, column) for x in range(1, size + 1))

steps = min(row - 1, column - 1)
start_row, start_column = row - steps, column - steps
show((start_row + offset, start_column + offset) for offset in range(min(size - start_row, size - start_column) + 1))

steps = min(size - row, column - 1)
start_row, start_column = row + steps, column - steps
show((start_row - offset, start_column + offset) for offset in range(min(start_row - 1, size - start_column) + 1))
