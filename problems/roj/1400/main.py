# ROJ 1400 统计单词数：按空格切分文章，独立单词忽略大小写与给定单词完全相同才算匹配
import sys, re

def main() -> None:
    w = sys.stdin.readline().strip().lower()            # 给定单词，统一转小写实现忽略大小写
    hits = [m.start() for m in re.finditer(r'\S+', sys.stdin.readline()) if m.group().lower() == w]  # 命中单词首字母下标
    print(f"{len(hits)} {hits[0]}" if hits else -1)

if __name__ == '__main__':
    main()
