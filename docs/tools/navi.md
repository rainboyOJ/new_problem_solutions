# Navi Cheatsheet

位置：

```text
scripts/navi/problem-tools.cheat
```

作用：给人类使用的 OJ 写题工具 cheatsheet，通过 `navi` 搜索和执行常用工具命令，减少记忆压力。

## 使用方式

先在仓库目录内用 `git` 生成真实路径，然后把仓库脚本目录加入 shell `PATH`：

```bash
repo="$(git rev-parse --show-toplevel)"
cat >> ~/.zshrc <<EOF
export RBOOK_REPO="$repo"
export PATH="\$RBOOK_REPO/bin:\$RBOOK_REPO/scripts/navi:\$RBOOK_REPO/scripts/problem-analysis-tools:\$RBOOK_REPO/scripts/problem-tools:\$PATH"
source "\$RBOOK_REPO/scripts/navi/rbook-shell.zsh"
EOF
source ~/.zshrc
```

确认 `rbook`、`ptool`、`rbook-navi`、`fetch_problem` 和 `rbook_cd_problem` 可用：

```bash
rbook --help
ptool --help
type rbook-navi
type fetch_problem
type rbook_cd_problem
```

推荐使用 `rbook-navi` 打开本仓库 cheatsheet：

```bash
rbook-navi
```

`rbook-navi` 会用 `navi --print` 取出选中的命令，再在当前 shell 里执行。这样选中 `rbook_cd_problem` 或 `fetch_problem` 时，命令里的 `cd` 才能保留在当前终端。

不要把 `rbook-navi` 配成下面这种 alias：

```bash
alias rbook-navi='command navi --path "$RBOOK_REPO/scripts/navi"'
```

这种写法会让 navi 在子进程里执行命令，子进程看不到当前 shell 里的 `rbook_cd_problem` / `fetch_problem` 函数，也不能改变当前终端目录。`rbook-navi` 已由 `scripts/navi/rbook-shell.zsh` 提供；如果你以前配置过这个 alias，重新 `source "$RBOOK_REPO/scripts/navi/rbook-shell.zsh"` 会自动清理它。

cheatsheet 使用 short name 作为 navi 的 tag。界面中左侧是 short name，中间是中文说明，右侧是实际命令。例如：

```cheat
% cd-problem
# 用 fzf 选择 OJ 和题号目录，并进入题目目录
rbook_cd_problem

% fetch-problem
# 抓取题面和样例，并进入题目目录
fetch_problem <oj> <problem_id>
```

带查询词：

```bash
rbook-navi --query duipai
rbook-navi --query sample
rbook-navi --query graph
```

只打印命令不执行：

```bash
navi --path scripts/navi --print
```

## 约定

cheatsheet 中的分析工具命令通过 `ptool` 定位当前 Git 仓库根目录，并代理执行。抓题和跳转目录入口使用 shell 函数，因为只有 shell 函数才能在命令结束后改变当前终端目录：

```bash
rbook_cd_problem
rbook_cd_problem luogu
ptool check_sample problems/luogu/P1001
fetch_problem luogu P1001
ptool --cd problems/luogu/P1001 duipai-human
```

`ptool`、`fetch_problem` 和 `rbook_cd_problem` 都会自动查找当前所在的 Git 仓库根目录，因此可以在项目根目录或任意题目目录中调用，只要当前位置仍在这个 Git 仓库内。设置 `RBOOK_REPO` 后，也可以从任意目录调用。

常用能力：

```bash
ptool list-problems
ptool list-ojs
ptool <problem-analysis-tool> [arguments...]
ptool --cd <problem_dir> <problem-analysis-tool> [arguments...]
ptool --cd <problem_dir> old <problem-tool> [arguments...]
```

`ptool` 专属说明见 [`ptool.md`](ptool.md)。
`fetch_problem` / `rbook_cd_problem` shell 函数说明见 [`rbook-shell.md`](rbook-shell.md)。

## 推荐样式

如果希望 navi 三列更清晰，可以把下面配置写入 `navi info config-path` 指向的文件：

```yaml
style:
  tag:
    color: green
    width_percentage: 20
    min_width: 15
  comment:
    color: cyan
    width_percentage: 30
    min_width: 20
  snippet:
    width_percentage: 50
    min_width: 30
```

## 覆盖工具

- `ptool`
- `rbook_cd_problem`
- `new-problem.py`
- `fetch_problem.py`
- `problem_status.py`
- `check_problem.py`
- `check_relations.py`
- `list_tags.py`
- `check_sample.py`
- `data_tool.py`
- `gen_random.py`
- `tree_draw.py`
- `duipai.py`
- `duipai-human.py`
- `shrink_failed.py`
- `b`
- `luogu.py`
- `input2dot.py`
- `dot2png.py`
- `r-lldb`
- `r-cgdb`
- `nvimsizer`
