values = {"a": 0, "b": 0, "c": 0}
for statement in filter(None, input().strip().split(";")):
    left, _, right = statement.partition(":=")
    values[left] = int(right) if right.isdigit() else values[right]
print(values["a"], values["b"], values["c"])
