import sys


def main():
    data = sys.stdin.buffer.read().split()
    q = int(data[0])
    pos = 1
    students = {}
    answer = []

    for _ in range(q):
        operation = int(data[pos])
        pos += 1
        if operation == 1:
            name, score = data[pos], int(data[pos + 1])
            pos += 2
            students[name] = score
            answer.append("OK")
        elif operation == 2:
            name = data[pos]
            pos += 1
            answer.append(str(students[name]) if name in students else "Not found")
        elif operation == 3:
            name = data[pos]
            pos += 1
            if name in students:
                del students[name]
                answer.append("Deleted successfully")
            else:
                answer.append("Not found")
        else:
            answer.append(str(len(students)))

    print("\n".join(answer))


if __name__ == "__main__":
    main()
