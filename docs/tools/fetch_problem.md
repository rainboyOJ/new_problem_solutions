# fetch_problem.py / fetch_problem

位置：

```text
scripts/problem-analysis-tools/fetch_problem.py
scripts/navi/rbook-shell.zsh
```

作用：把在线 OJ 题目抓取到当前电子书的新题目目录结构中。

`fetch_problem.py` 是底层脚本入口，适合 agent、脚本、CI 使用，不会改变当前 shell 目录。

`fetch_problem` 是给人类使用的 shell 函数，定义在 `scripts/navi/rbook-shell.zsh`。它会调用 `fetch_problem.py`，成功后自动进入对应题目目录，方便马上开始写 `main.cpp`。

## 基本用法

人类写题推荐先配置 shell 函数，然后使用：

```bash
fetch_problem luogu P1001
fetch_problem https://www.luogu.com.cn/problem/P1001
fetch_problem https://atcoder.jp/contests/abs/tasks/practice_1
```

执行成功后会进入：

```text
problems/luogu/P1001/
```

如果还没有配置 shell 函数，或者你是在脚本/agent 里调用，使用底层脚本：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu P1001
python3 scripts/problem-analysis-tools/fetch_problem.py https://www.luogu.com.cn/problem/P1001
python3 scripts/problem-analysis-tools/fetch_problem.py https://atcoder.jp/contests/abs/tasks/practice_1
```

脚本默认会创建或补齐题目目录，不需要额外传 `--init`：

```text
problems/<oj>/<problem_id>/
├── index.md
├── problem.md
├── main.cpp
├── brute.cpp
├── gen.py
├── in1
├── out1
└── problem-analysis-workspace/
```

Luogu 数字题目录统一使用 `P` 前缀：

```text
luogu P1001 -> problems/luogu/P1001/
```

但 `index.md` 中的 `problem_id` 仍然写 `P1001`。

新建的 `index.md` 会包含标准 frontmatter 字段 `description: ""` 和 `recommend: []`。抓题阶段不会自动编造解法摘要，也不会自动编外部推荐；最终写题解时由 `oj-problem-analysis-writer` 填写 `description`，推荐练习由 `oj-problem-relation-writer` 维护。

## 配置 fetch_problem 函数

在仓库目录内执行：

```bash
repo="$(git rev-parse --show-toplevel)"
cat >> ~/.zshrc <<EOF
export RBOOK_REPO="$repo"
export PATH="\$RBOOK_REPO/bin:\$RBOOK_REPO/scripts/navi:\$RBOOK_REPO/scripts/problem-analysis-tools:\$RBOOK_REPO/scripts/problem-tools:\$PATH"
source "\$RBOOK_REPO/scripts/navi/rbook-shell.zsh"
EOF
source ~/.zshrc
```

确认函数可用：

```bash
type fetch_problem
```

注意：只有被当前 shell `source` 的函数才能在命令执行后改变当前目录。直接运行 `fetch_problem.py` 或通过 `ptool fetch_problem` 都不能让你的终端自动进入题目目录。

## 支持能力

第一版支持：

- Luogu：抓取标题、题面 `problem.md`、样例 `in1/out1`，并生成 `in`。
- AtCoder：支持原站 `https://atcoder.jp/contests/<contest>/tasks/<task>` URL，抓取标题、英文题面 `problem.md`、样例 `in1/out1`，并生成 `in`。
- Codeforces：支持 `165E`、`/contest/<id>/problem/<index>` 和 `/problemset/problem/<id>/<index>`，从原站抓取英文题面、限制、样例和 Note；HTML 失败时使用官方 API 回退标题并创建 skeleton。
- 曙梦 OJ：支持 `shumeng CSP201312A` 和 `https://oj.shumeng.tech/p/CSP201312A`，抓取中文 Markdown 题面、公式和样例；仅支持单题，不支持题单批量抓取。
- VJudge：支持 `poj/hdu/atcoder/openj_bailian` 等旧入口能力，尽量抓标题，暂不抓完整题面和样例。

曙梦 OJ 单题抓取示例：

```bash
fetch_problem shumeng CSP201312A
fetch_problem https://oj.shumeng.tech/p/CSP201312A
```

题单地址（例如 `/p?page=1&q=category:CSP`）不会被当作单题抓取。

`problem.md` 只作为原题面归档，不写题解、不套题解格式、不包含 `@include-code`。

## 覆盖策略

默认不覆盖手写文件：

```text
index.md
main.cpp
brute.cpp
gen.py
problem-analysis-workspace/*.md
```

默认也不覆盖已经存在的抓取产物：

```text
problem.md
in1/out1
in2/out2
in
```

需要重新写抓取产物时使用：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu P1001 --force-statement
python3 scripts/problem-analysis-tools/fetch_problem.py luogu P1001 --force-samples
```

只更新 `index.md` frontmatter 里的 `title/source`，不修改正文：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu P1001 --force-index-meta
```

## 预览和 JSON

只预览将要写入的路径：

```bash
fetch_problem luogu P1001 --dry-run
python3 scripts/problem-analysis-tools/fetch_problem.py luogu P1001 --dry-run
```

给 agent 或脚本使用结构化输出：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu P1001 --json
```

`fetch_problem --dry-run`、`fetch_problem --json`、`fetch_problem --self-test` 和 `fetch_problem --help` 不会自动进入题目目录。

JSON 会包含：

```text
ok
fetched
oj
problem_id
problem_dir
created
skipped
written
warnings
```

## 抓取失败行为

如果已经能确定 OJ 和题号，例如：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu P1001
```

即使网络失败，也会创建或补齐 skeleton，并在输出里提示题面/样例抓取失败。

如果输入 URL 无法识别 OJ 或题号，脚本直接失败，不创建目录。

## 自测

运行离线 fixture 自测：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py --self-test
```

自测会使用 Luogu fixture，在临时目录中验证解析、建目录和写入 `problem.md/in1/out1`，不会修改真实 `problems/`。

## 第一版未实现

- VJudge 代理页面里的完整题面抓取。
- VJudge 代理页面里的样例抓取。
- 各 OJ 的登录态、Cookie、反爬失败重试。
- POJ/HDU 原站题面抓取。
- 题目标签、时间限制、内存限制的跨 OJ 统一解析。

旧 `scripts/problem-tools/oj.js` 第一版暂不修改。人工写题建议使用 `fetch_problem` shell 函数；agent、脚本和 CI 建议使用 `fetch_problem.py`。
