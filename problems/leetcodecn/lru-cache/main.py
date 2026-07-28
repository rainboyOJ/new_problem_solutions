#!/usr/bin/env python3
from collections import OrderedDict


class LRUCache:
    def __init__(self, capacity: int):
        self.cap = capacity
        self.cache = OrderedDict()

    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        self.cache.move_to_end(key)
        return self.cache[key]

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self.cache[key] = value
            self.cache.move_to_end(key)
            return
        if len(self.cache) == self.cap:
            self.cache.popitem(last=False)
        self.cache[key] = value


def main() -> None:
    cap, ops = map(int, input().split())
    cache = LRUCache(cap)
    for _ in range(ops):
        parts = input().split()
        if parts[0] == "get":
            print(cache.get(int(parts[1])), end=" ")
        else:
            cache.put(int(parts[1]), int(parts[2]))


if __name__ == "__main__":
    main()
