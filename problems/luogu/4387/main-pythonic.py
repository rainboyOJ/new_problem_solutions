import sys

tokens = iter(map(int, sys.stdin.buffer.read().split()))
answers = []

for _ in range(next(tokens)):
    n = next(tokens)
    pushed = [next(tokens) for _ in range(n)]
    popped = [next(tokens) for _ in range(n)]
    stack = []
    next_pop = 0

    for value in pushed:
        stack.append(value)
        while stack and next_pop < n and stack[-1] == popped[next_pop]:
            stack.pop()
            next_pop += 1

    answers.append("Yes" if not stack else "No")

print("\n".join(answers))
