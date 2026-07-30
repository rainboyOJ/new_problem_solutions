row_count, column_count = map(int, input().split())
point_count = int(input())
points = [tuple(map(int, input().split())) for _ in range(point_count)]
point_set = set(points)
answer = 0

for first_row, first_column in points:
    for second_row, second_column in points:
        dr = second_row - first_row
        dc = second_column - first_column
        if dr == 0 and dc == 0:
            continue
        # 只有前一跳已经在稻田外，first 才可能是这条路径的第一株。
        if 1 <= first_row - dr <= row_count and 1 <= first_column - dc <= column_count:
            continue
        row, column = second_row, second_column
        count = 2
        while 1 <= row + dr <= row_count and 1 <= column + dc <= column_count:
            row += dr
            column += dc
            if (row, column) not in point_set:
                break
            count += 1
        if count >= 3:
            answer = max(answer, count)

print(answer)
