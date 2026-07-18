import operator

ops = {
    "a": ("+", operator.add),
    "b": ("-", operator.sub),
    "c": ("*", operator.mul),
}
current = ""

for _ in range(int(input())):
    parts = input().split()
    if len(parts) == 3:
        current, left, right = parts[0], int(parts[1]), int(parts[2])
    else:
        left, right = int(parts[0]), int(parts[1])
    symbol, func = ops[current]
    expression = f"{left}{symbol}{right}={func(left, right)}"
    print(expression)
    print(len(expression))
