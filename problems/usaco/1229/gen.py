#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 7)
    have = [random.randint(0, 4) for _ in range(n)]

    possible_targets = list(range(2, n + 1))
    random.shuffle(possible_targets)
    k = random.randint(1, n - 1)
    targets = sorted(possible_targets[:k])

    recipes = []
    for target in targets:
        m = random.randint(1, min(3, target - 1))
        ingredients = random.sample(range(1, target), m)
        recipes.append((target, ingredients))

    print(n)
    print(*have)
    print(len(recipes))
    for target, ingredients in recipes:
        print(target, len(ingredients), *ingredients)


if __name__ == "__main__":
    main()
