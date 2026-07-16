m, removal_count = map(int, input().split())
height = 3 * (1 << (m - 2))
width = 2 * height - 1
node_row = [0] * (m + 1)
for level in range(1, m):
    node_row[level] = height - 3 * (1 << (m - level - 1))
node_row[m] = height - 1

deleted = set()


def remove_subtree(node):
    if node >= 1 << m:
        return
    deleted.add(node)
    remove_subtree(node * 2)
    remove_subtree(node * 2 + 1)


for _ in range(removal_count):
    level, index = map(int, input().split())
    remove_subtree((1 << (level - 1)) + index - 1)

canvas = [[" "] * width for _ in range(height)]


def draw(node, level, row, column):
    if node in deleted:
        return
    canvas[row][column] = "o"
    if level == m:
        return

    child_row = node_row[level + 1]
    gap = child_row - row
    for child, direction, slash in ((node * 2, -1, "/"), (node * 2 + 1, 1, "\\")):
        if child in deleted:
            continue
        for step in range(1, gap):
            canvas[row + step][column + direction * step] = slash
        draw(child, level + 1, child_row, column + direction * gap)


draw(1, 1, 0, width // 2)
print("\n".join("".join(row) for row in canvas))
