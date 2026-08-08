code = input().strip()
values = dict.fromkeys("abc", 0)

for statement in filter(None, code.split(";")):
    left, right = statement[0], statement[3]
    values[left] = int(right) if right.isdigit() else values[right]

print(values["a"], values["b"], values["c"])
