operation_count = int(input())
document = input().strip()

for _ in range(operation_count):
    op, *args = input().split()
    match op:
        case "1":
            document += args[0]
            print(document)
        case "2":
            start, length = map(int, args)
            document = document[start : start + length]
            print(document)
        case "3":
            position = int(args[0])
            document = document[:position] + args[1] + document[position:]
            print(document)
        case "4":
            print(document.find(args[0]))
