import sys


MAXIMUM = 100000
input = sys.stdin.buffer.readline
tree = [0] * (MAXIMUM + 1)
end_at = [0] * (MAXIMUM + 1)
active = 0


def add(index, delta):
    while index <= MAXIMUM:
        tree[index] += delta
        index += index & -index


def prefix(index):
    result = 0
    while index:
        result += tree[index]
        index -= index & -index
    return result


def kth(rank):
    index = 0
    step = 1 << (MAXIMUM.bit_length() - 1)
    while step:
        target = index + step
        if target <= MAXIMUM and tree[target] < rank:
            index = target
            rank -= tree[target]
        step >>= 1
    return index + 1


answers = []
for _ in range(int(input())):
    operation = input().split()
    if operation[0] == b"B":
        answers.append(str(active))
        continue
    left, right = map(int, operation[1:])
    removed = 0
    before = prefix(left)
    if before:
        start = kth(before)
        if end_at[start] >= left:
            add(start, -1)
            end_at[start] = 0
            active -= 1
            removed += 1
    while prefix(MAXIMUM) > prefix(left - 1):
        start = kth(prefix(left - 1) + 1)
        if start > right:
            break
        add(start, -1)
        end_at[start] = 0
        active -= 1
        removed += 1
    add(left, 1)
    end_at[left] = right
    active += 1
    answers.append(str(removed))

print("\n".join(answers))
