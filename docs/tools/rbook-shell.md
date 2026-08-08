# rbook-shell.zsh

位置：

```text
scripts/navi/rbook-shell.zsh
```

安装后提供的 shell 函数：

```text
rbook-navi
fetch_problem
rbook_cd_problem
```

作用：给人类写题使用的 shell 函数集合。当前提供：

- `rbook-navi`：打开本仓库 navi cheatsheet，并在当前 shell 执行选中的命令。
- `fetch_problem`：抓取题目后自动进入对应题目目录。
- `rbook_cd_problem`：用 `fzf` 选择 OJ 和题号目录，然后进入题目目录。

## 配置方式

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

确认函数已加载：

```bash
type rbook-navi
type fetch_problem
type rbook_cd_problem
```

## rbook-navi

打开本仓库 navi cheatsheet：

```bash
rbook-navi
rbook-navi --query cd
rbook-navi --query sample
```

`rbook-navi` 会先调用：

```bash
navi --path "$RBOOK_REPO/scripts/navi" --print
```

拿到选中的命令后，再在当前 shell 中执行。这样选中 `rbook_cd_problem` 或 `fetch_problem` 时，命令里的 `cd` 才能保留在当前终端。

不要把它写成下面这种 alias：

```bash
alias rbook-navi='command navi --path "$RBOOK_REPO/scripts/navi"'
```

这种写法会让 navi 在子进程里执行命令，子进程看不到当前 shell 里的函数，也不能改变当前终端目录。

## fetch_problem

抓取 Luogu 题目：

```bash
fetch_problem luogu P1001
```

抓取题目 URL：

```bash
fetch_problem https://www.luogu.com.cn/problem/P1001
```

成功后会自动进入题目目录：

```text
problems/luogu/P1001/
```

## 不会自动跳转的模式

这些模式只转发给底层 `fetch_problem.py`，不会改变当前目录：

```bash
fetch_problem --help
fetch_problem --self-test
fetch_problem luogu P1001 --dry-run
fetch_problem luogu P1001 --json
```

## 和 fetch_problem.py 的区别

`fetch_problem.py` 是普通 Python 脚本，适合 agent、脚本、CI 调用：

```bash
ptool fetch_problem luogu P1001 --json
python3 scripts/problem-analysis-tools/fetch_problem.py luogu P1001 --json
```

普通脚本无法改变父 shell 的当前目录，所以不会自动 `cd`。

`fetch_problem` 是 shell 函数，被当前 shell `source` 后运行，可以在抓题成功后执行 `cd`，适合人类开始写新题时使用。

## rbook_cd_problem

不传参数时，先用 `fzf` 选择 OJ，再选择题号目录：

```bash
rbook_cd_problem
```

指定 OJ，只选择这个 OJ 下的题号目录：

```bash
rbook_cd_problem luogu
```

指定 OJ 和题号，直接进入题目目录：

```bash
rbook_cd_problem luogu P1001
```

这个函数依赖 `fzf`。如果没有安装 `fzf`，仍然可以使用 `rbook_cd_problem <oj> <problem_id>` 直接跳转。

因为普通脚本无法改变父 shell 的当前目录，目录跳转必须通过已经 `source` 到当前 shell 的函数完成。navi 里提供的 `cd-problem` 和 `cd-oj` 入口会调用这个函数；如果你的 navi 执行方式不会在当前 shell 中保留 `cd`，就直接在终端运行 `rbook_cd_problem`。
