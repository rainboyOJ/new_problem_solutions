#!/usr/bin/env python3
class MinStack:
    def __init__(self):
        self.st = []

    def push(self, v):
        self.st.append((v, min(v, self.st[-1][1]) if self.st else v))

    def pop(self):
        self.st.pop()

    def top(self):
        return self.st[-1][0]

    def getMin(self):
        return self.st[-1][1]


def main():
    q = int(input())
    ms = MinStack()
    for _ in range(q):
        op = input().split()
        if op[0] == "push":
            ms.push(int(op[1]))
        elif op[0] == "pop":
            ms.pop()
        elif op[0] == "top":
            print(ms.top(), end=" ")
        else:
            print(ms.getMin(), end=" ")


if __name__ == "__main__":
    main()
