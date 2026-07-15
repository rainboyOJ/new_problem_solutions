code = input().strip()
values = {"a": 0, "b": 0, "c": 0}

for statement in code.split(";"):
    if not statement:
        continue
    left = statement[0]
    right = statement[3]
    if right.isdigit():
        values[left] = int(right)
    else:
        values[left] = values[right]

print(values["a"], values["b"], values["c"])
