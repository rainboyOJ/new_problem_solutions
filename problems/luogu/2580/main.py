import sys


data = iter(sys.stdin.buffer.read().split())
valid = {next(data) for _ in range(int(next(data)))}
called = set()
answers = []

for _ in range(int(next(data))):
    name = next(data)
    if name not in valid:
        answers.append("WRONG")
    elif name in called:
        answers.append("REPEAT")
    else:
        called.add(name)
        answers.append("OK")

print("\n".join(answers))
