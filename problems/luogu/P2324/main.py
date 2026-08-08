import sys


target = b"111110111100*110000100000"
moves = [tuple(nr * 5 + nc for dr, dc in ((1, 2), (1, -2), (-1, 2), (-1, -2),
                                          (2, 1), (2, -1), (-2, 1), (-2, -1))
               if 0 <= (nr := i // 5 + dr) < 5 and 0 <= (nc := i % 5 + dc) < 5)
         for i in range(25)]


def solve(start):
    board = bytearray(start)
    blank = board.index(42)

    def heuristic():
        return sum(value != 42 and value != target[i] for i, value in enumerate(board))

    def dfs(blank_position, previous_blank, remaining, seen):
        estimate = heuristic()
        if estimate == 0:
            return True
        if estimate > remaining:
            return False
        state = bytes(board)
        if seen.get(state, -1) >= remaining:
            return False
        seen[state] = remaining
        for other in moves[blank_position]:
            if other == previous_blank:
                continue
            board[blank_position], board[other] = board[other], board[blank_position]
            if dfs(other, blank_position, remaining - 1, seen):
                return True
            board[blank_position], board[other] = board[other], board[blank_position]
        return False

    for limit in range(16):
        if dfs(blank, -1, limit, {}):
            return limit
    return -1


input = sys.stdin.buffer.readline
answers = []
for _ in range(int(input())):
    answers.append(str(solve(b"".join(input().strip() for _ in range(5)))))
print("\n".join(answers))
