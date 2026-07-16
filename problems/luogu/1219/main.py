n = int(input())
full = (1 << n) - 1
path = []
first_solutions = []
total = 0


def dfs(columns, left_diagonals, right_diagonals):
    global total
    if columns == full:
        total += 1
        if len(first_solutions) < 3:
            first_solutions.append(" ".join(map(str, path)))
        return

    available = full & ~(columns | left_diagonals | right_diagonals)
    while available:
        position = available & -available
        available -= position
        path.append(position.bit_length())
        dfs(
            columns | position,
            (left_diagonals | position) << 1 & full,
            (right_diagonals | position) >> 1,
        )
        path.pop()


dfs(0, 0, 0)
print(*first_solutions, total, sep="\n")
