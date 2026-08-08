question_count = int(input())
current_operation = ""
symbols = {"a": "+", "b": "-", "c": "*"}

for _ in range(question_count):
    parts = input().split()
    if len(parts) == 3:
        current_operation = parts[0]
        left = int(parts[1])
        right = int(parts[2])
    else:
        left = int(parts[0])
        right = int(parts[1])

    symbol = symbols[current_operation]
    if current_operation == "a":
        result = left + right
    elif current_operation == "b":
        result = left - right
    else:
        result = left * right

    expression = f"{left}{symbol}{right}={result}"
    print(expression)
    print(len(expression))
