# new-problem.py

位置：

```text
scripts/problem-analysis-tools/new-problem.py
```

作用：按新题目结构创建题目目录。

如果需要从 OJ 抓取题面和样例，可以直接传题目 URL：

```bash
python3 scripts/problem-analysis-tools/new-problem.py https://atcoder.jp/contests/abs/tasks/practice_1
```

URL 模式会复用 `fetch_problem.py` 的抓题和建题逻辑。也可以直接使用：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu P1001
```

## 基本用法

```bash
python3 scripts/problem-analysis-tools/new-problem.py luogu P1001
python3 scripts/problem-analysis-tools/new-problem.py https://atcoder.jp/contests/abs/tasks/practice_1
```

如果已经通过 `scripts/install-problem-tools.sh` 安装到 `~/.local/bin`，可以使用：

```bash
new-problem luogu P1001
new-problem https://atcoder.jp/contests/abs/tasks/practice_1
```

## 生成结构

```text
problems/<oj>/<problem_id>/
├── index.md
├── main.cpp
├── brute.cpp
├── gen.py
└── problem-analysis-workspace/
```

新建的 `index.md` 会包含 `description: ""` 和 `recommend: []`。`description` 是题解核心思路摘要的占位字段，最终写题解时应改成非空的一句话说明；`recommend` 用于后续记录跨 OJ 推荐练习。

## 常用参数

```bash
python3 scripts/problem-analysis-tools/new-problem.py luogu P1001 --title "A+B Problem" --source https://example.com
python3 scripts/problem-analysis-tools/new-problem.py luogu P1001 --no-brute --no-gen
python3 scripts/problem-analysis-tools/new-problem.py luogu P1001 --no-workspace
```

脚本不会覆盖已有文件。
