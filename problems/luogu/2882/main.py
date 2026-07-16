import sys


data = sys.stdin.buffer.read().split()
n = int(data[0])
cows = data[1:]


def operations(window):
    ends = bytearray(n + 1)
    flipped = moves = 0
    for i, cow in enumerate(cows):
        flipped ^= ends[i]
        if (cow == b"B") ^ bool(flipped):
            if i + window > n:
                return n + 1
            moves += 1
            flipped ^= 1
            ends[i + window] ^= 1
    return moves


best_window, best_moves = min(
    ((window, operations(window)) for window in range(1, n + 1)),
    key=lambda result: result[1],
)
print(best_window, best_moves)
