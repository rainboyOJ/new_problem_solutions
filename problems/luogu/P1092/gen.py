#!/usr/bin/env python3
import random


def solve_count(n, s1, s2, s3, limit=2):
    val = [-1] * n
    used = [False] * n
    s1r = s1[::-1]
    s2r = s2[::-1]
    s3r = s3[::-1]
    total = 0

    def dfs(pos, step, carry):
        nonlocal total
        if total >= limit:
            return
        if pos < 0:
            if carry == 0:
                total += 1
            return

        if step == 0:
            x = ord(s1r[pos]) - 65
            if val[x] != -1:
                dfs(pos, 1, carry)
                return
            for d in range(n):
                if used[d]:
                    continue
                val[x] = d
                used[d] = True
                dfs(pos, 1, carry)
                used[d] = False
                val[x] = -1
                if total >= limit:
                    return
            return

        if step == 1:
            y = ord(s2r[pos]) - 65
            if val[y] != -1:
                dfs(pos, 2, carry)
                return
            for d in range(n):
                if used[d]:
                    continue
                val[y] = d
                used[d] = True
                dfs(pos, 2, carry)
                used[d] = False
                val[y] = -1
                if total >= limit:
                    return
            return

        x = ord(s1r[pos]) - 65
        y = ord(s2r[pos]) - 65
        z = ord(s3r[pos]) - 65
        s = val[x] + val[y] + carry
        digit = s % n
        new_carry = s // n
        if pos == 0 and new_carry != 0:
            return
        if val[z] != -1:
            if val[z] != digit:
                return
            dfs(pos - 1, 0, new_carry)
            return
        if used[digit]:
            return
        val[z] = digit
        used[digit] = True
        dfs(pos - 1, 0, new_carry)
        used[digit] = False
        val[z] = -1

    dfs(n - 1, 0, 0)
    return total


def random_instance():
    n = random.randint(3, 7)
    letters = [chr(65 + i) for i in range(n)]
    digits = list(range(n))
    random.shuffle(digits)

    letter_to_digit = {letters[i]: digits[i] for i in range(n)}
    digit_to_letter = {digits[i]: letters[i] for i in range(n)}

    # 先保证所有字母至少在前两行出现一次。
    pool = letters[:]
    while len(pool) < 2 * n:
        pool.append(random.choice(letters))
    random.shuffle(pool)

    s1 = ''.join(pool[:n])
    s2 = ''.join(pool[n:2 * n])

    carry = 0
    out = ['A'] * n
    for i in range(n - 1, -1, -1):
        x = letter_to_digit[s1[i]]
        y = letter_to_digit[s2[i]]
        s = x + y + carry
        out_digit = s % n
        carry = s // n
        out[i] = digit_to_letter[out_digit]

    if carry != 0:
        return None

    s3 = ''.join(out)
    return n, s1, s2, s3


def main():
    random.seed()
    while True:
        data = random_instance()
        if data is None:
            continue
        n, s1, s2, s3 = data
        if solve_count(n, s1, s2, s3, limit=2) == 1:
            print(n)
            print(s1)
            print(s2)
            print(s3)
            return


if __name__ == "__main__":
    main()
