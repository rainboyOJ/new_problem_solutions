import sys


values = list(map(int, sys.stdin.buffer.read().split()))
FULL = (1 << 9) - 1
row = [0] * 9
column = [0] * 9
block = [0] * 9
empty = []
score = 0
valid = True

for position, digit in enumerate(values):
    r, c = divmod(position, 9)
    weight = 10 - max(abs(r - 4), abs(c - 4))
    if not digit:
        empty.append((r, c, weight))
        continue
    bit = 1 << (digit - 1)
    box = r // 3 * 3 + c // 3
    if row[r] & bit or column[c] & bit or block[box] & bit:
        valid = False
    row[r] |= bit
    column[c] |= bit
    block[box] |= bit
    score += digit * weight

best = -1


def dfs(index, current_score):
    global best
    if index == len(empty):
        best = max(best, current_score)
        return
    chosen = index
    chosen_mask = 0
    minimum = 10
    for i in range(index, len(empty)):
        r, c, _ = empty[i]
        mask = FULL & ~(row[r] | column[c] | block[r // 3 * 3 + c // 3])
        count = mask.bit_count()
        if not count:
            return
        if count < minimum:
            minimum, chosen, chosen_mask = count, i, mask
            if count == 1:
                break
    empty[index], empty[chosen] = empty[chosen], empty[index]
    r, c, weight = empty[index]
    box = r // 3 * 3 + c // 3
    for digit in range(9, 0, -1):
        bit = 1 << (digit - 1)
        if chosen_mask & bit:
            row[r] |= bit
            column[c] |= bit
            block[box] |= bit
            dfs(index + 1, current_score + digit * weight)
            row[r] ^= bit
            column[c] ^= bit
            block[box] ^= bit
    empty[index], empty[chosen] = empty[chosen], empty[index]


if valid:
    dfs(0, score)
print(best)
