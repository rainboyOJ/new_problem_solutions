#!/usr/bin/env python3
class Trie:
    def __init__(self):
        self.next = {}
        self.end = False

    def insert(self, word: str) -> None:
        cur = self
        for ch in word:
            if ch not in cur.next:
                cur.next[ch] = Trie()
            cur = cur.next[ch]
        cur.end = True

    def search(self, word: str) -> bool:
        cur = self
        for ch in word:
            if ch not in cur.next:
                return False
            cur = cur.next[ch]
        return cur.end

    def startsWith(self, prefix: str) -> bool:
        cur = self
        for ch in prefix:
            if ch not in cur.next:
                return False
            cur = cur.next[ch]
        return True


def main():
    q = int(input())
    t = Trie()
    for _ in range(q):
        op, s = input().split()
        if op == "insert":
            t.insert(s)
        elif op == "search":
            print(t.search(s), end=" ")
        else:
            print(t.startsWith(s), end=" ")


if __name__ == "__main__":
    main()
