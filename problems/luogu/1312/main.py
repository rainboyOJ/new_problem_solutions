import sys
from collections import Counter


data = iter(map(int, sys.stdin.buffer.read().split()))
move_limit = next(data)
board = [[0] * 7 for _ in range(5)]
for column in range(5):
    row = 0
    while (color := next(data)):
        board[column][row] = color
        row += 1


def settle(state):
    while True:
        for column in range(5):
            values = [color for color in state[column] if color]
            state[column][:] = values + [0] * (7 - len(values))
        marked = set()
        for x in range(5):
            for y in range(7):
                color = state[x][y]
                if not color:
                    continue
                if x + 2 < 5 and state[x + 1][y] == state[x + 2][y] == color:
                    marked.update(((x, y), (x + 1, y), (x + 2, y)))
                if y + 2 < 7 and state[x][y + 1] == state[x][y + 2] == color:
                    marked.update(((x, y), (x, y + 1), (x, y + 2)))
        if not marked:
            return
        for x, y in marked:
            state[x][y] = 0


def encode(state):
    return tuple(value for column in state for value in column)


def is_empty(state):
    return all(not color for column in state for color in column)


def viable(state):
    return all(amount >= 3 for amount in Counter(
        color for column in state for color in column if color
    ).values())


path = []
failed = set()


def dfs(step, state):
    if step == move_limit:
        return is_empty(state)
    if is_empty(state) or not viable(state):
        return False
    key = step, encode(state)
    if key in failed:
        return False
    for x in range(5):
        for y in range(7):
            if not state[x][y]:
                continue
            for direction in (1, -1):
                target = x + direction
                if not 0 <= target < 5:
                    continue
                if direction == 1 and state[x][y] == state[target][y]:
                    continue
                if direction == -1 and state[target][y] != 0:
                    continue
                next_state = [column[:] for column in state]
                next_state[x][y], next_state[target][y] = next_state[target][y], next_state[x][y]
                settle(next_state)
                path.append((x, y, direction))
                if dfs(step + 1, next_state):
                    return True
                path.pop()
    failed.add(key)
    return False


if dfs(0, board):
    print("\n".join(map(lambda move: " ".join(map(str, move)), path)))
else:
    print(-1)
