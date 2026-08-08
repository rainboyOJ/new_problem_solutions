operation_count = int(input())
document = input().strip()

for _ in range(operation_count):
    parts = input().split()
    operation = parts[0]

    if operation == "1":
        document += parts[1]
        print(document)
    elif operation == "2":
        start = int(parts[1])
        length = int(parts[2])
        document = document[start:start + length]
        print(document)
    elif operation == "3":
        position = int(parts[1])
        fragment = parts[2]
        document = document[:position] + fragment + document[position:]
        print(document)
    else:
        print(document.find(parts[1]))
