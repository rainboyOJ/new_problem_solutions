import sys


def main():
    parent = {}
    current_parent = None
    answer = []

    def find(name):
        parent.setdefault(name, name)
        path = []
        while parent[name] != name:
            path.append(name)
            name = parent[name]
        for person in path:
            parent[person] = name
        return name

    for line in sys.stdin.buffer:
        operation = line[:1]
        if operation == b"$":
            break
        name = line[1:].strip()
        if operation == b"#":
            current_parent = name
            parent.setdefault(name, name)
        elif operation == b"+":
            parent[name] = current_parent
        else:
            answer.append(name.decode() + " " + find(name).decode())

    print("\n".join(answer))


if __name__ == "__main__":
    main()
