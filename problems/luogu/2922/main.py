import sys
from array import array


data = iter(map(int, sys.stdin.buffer.read().split()))
message_count, query_count = next(data), next(data)
child_zero = array("i", [0])
child_one = array("i", [0])
subtree_count = array("i", [0])
terminal_count = array("i", [0])

for _ in range(message_count):
    node = 0
    for _ in range(next(data)):
        children = child_one if next(data) else child_zero
        if not children[node]:
            children[node] = len(child_zero)
            child_zero.append(0)
            child_one.append(0)
            subtree_count.append(0)
            terminal_count.append(0)
        node = children[node]
        subtree_count[node] += 1
    terminal_count[node] += 1

answers = []
for _ in range(query_count):
    bits = [next(data) for _ in range(next(data))]
    node = answer = 0
    for bit in bits:
        answer += terminal_count[node]
        node = (child_one if bit else child_zero)[node]
        if not node:
            break
    else:
        answer += subtree_count[node]
    answers.append(str(answer))

print("\n".join(answers))
