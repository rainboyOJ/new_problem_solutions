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
├── problem-analysis-workspace/
└── talking_with_ai/
```

`talking_with_ai/` 是可提交的空目录，用于手动保存与 AI 讨论题目的 Markdown 记录。脚本只会确保目录存在，不会生成或覆盖其中的文件。

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
- AtCoder：`atcoder <task>`、`atcoder <contest>/<task>`、原站 URL 或 `vjudge.net/problem/AtCoder-<task>` 都走 VJudge，选版顺序是中文（优先 `trustable`）→ 英文 → 日文；VJudge 拿不到时直接报错，不建空骨架。
- Codeforces：支持 `165E`、`/contest/<id>/problem/<index>`、`/problemset/problem/<id>/<index>` 和 `vjudge.net/problem/CodeForces-<id><index>`。默认走 VJudge 取中文题面（选版规则同 AtCoder），`source` 也指向 VJudge（带 `#author=` 定位到所选题面版本）；VJudge 未登录、未收录或题面抓取失败时回退 Codeforces 原站抓英文题面、限制、样例和 Note，原站也失败时用官方 API 回退标题并创建 skeleton。
- 曙梦 OJ：支持 `shumeng CSP201312A` 和 `https://oj.shumeng.tech/p/CSP201312A`，抓取中文 Markdown 题面、公式和样例；仅支持单题，不支持题单批量抓取。
- VJudge：`vjudge <OJ>-<题号>` 这类旧入口仍只抓标题；AtCoder 和 Codeforces 已经有完整题面/样例抓取，见上面两条。

曙梦 OJ 单题抓取示例：

```bash
fetch_problem shumeng CSP201312A
fetch_problem https://oj.shumeng.tech/p/CSP201312A
```

题单地址（例如 `/p?page=1&q=category:CSP`）不会被当作单题抓取。

`problem.md` 只作为原题面归档，不写题解、不套题解格式、不包含 `@include-code`。

## VJudge 登录态（AtCoder / Codeforces 中文题面）

VJudge 的题面版本列表（`descBriefs`）必须登录才能读，所以 AtCoder、Codeforces 抓题前要先有可用的 VJudge 登录态。凭据放在仓库外的：

```text
~/.config/rbook/vjudge.json
```

```json
{
  "cookie": "JSESSIONID=...; JSESSlONID=...",
  "username": "你的账号",
  "password": "你的密码"
}
```

也可以用环境变量覆盖同名配置，适合 CI 或临时切换账号：

```bash
export VJUDGE_COOKIE='JSESSIONID=...; JSESSlONID=...'
export VJUDGE_USERNAME=... VJUDGE_PASSWORD=...
```

取用顺序与刷新规则：

1. 先用 `cookie`；有效时直接读题面，不会触发登录。
2. cookie 过期（题目页 303 跳 `/?login=1`）时，先试 `POST /user/login` 的账号密码登录。VJudge 这个接口要 Cloudflare Turnstile 的 token，纯 HTTP 一定被拒（`user.error.human_verification_failed`），所以实际靠下面两条。
3. **Camoufox 自动登录（默认）**：Camoufox 是打了补丁的 Firefox，页面级 Cloudflare 检查和 Turnstile 都能过。实测流程是「填账号密码 → 提交（先被判需要人机验证）→ Turnstile 静默发 token，3–6 秒 → 再提交一次 → 登录成功」，全程不需要人。装法（仓库外，可选依赖）：

   ```bash
   python3 -m venv --system-site-packages ~/.local/share/rbook/camoufox-venv
   ~/.local/share/rbook/camoufox-venv/bin/pip install camoufox      # 有 playwright 时可复用系统那份
   ~/.local/share/rbook/camoufox-venv/bin/python -m camoufox fetch  # 下配套定制 Firefox（约 1.3 GB）
   ```

   主进程不需要装 camoufox：`fetch_problem.py` 会自己找 `~/.local/share/rbook/camoufox-venv/bin/python`（或环境变量 `VJUDGE_CAMOUFOX_PYTHON` 指定的解释器）来跑登录助手，凭据走 stdin，不进进程列表。

   `camoufox fetch` 有时会因为 GitHub API/仓库解析失败（提示某个 build "not in official's releases"），此时手动装一个 release zip 即可：

   ```bash
   ver=158.0-beta.40
   mkdir -p ~/.cache/camoufox/browsers/camoufox/$ver
   unzip -q ~/camoufox-$ver-lin.x86_64.zip -d ~/.cache/camoufox/browsers/camoufox/$ver
   # version.json 里写 version/build/prerelease/sha256/interface=1
   # config.json 里写 {"active_version": "browsers/camoufox/$ver", "pinned": "camoufox/$ver"}
   ```

   `pinned` 是必须的：不写它，camoufox 会坚持去拉包内固定的那个 build。
4. **人工登录兜底**：没有 camoufox（或 `VJUDGE_BROWSER=chromium`）时弹 playwright Chromium 窗口，自动填表并提交，Turnstile 由人在窗口里点一下，脚本轮询 `checkLogInStatus` 后自动继续。也可以完全手动：浏览器登录 vjudge.net，把 `JSESSIONID` / `JSESSlONID` 写进 `cookie` 字段。
5. 登录态拿不到，或者 VJudge 上没收录这道题：AtCoder 直接报错不建骨架；Codeforces 回退 `codeforces.com` 抓英文题面，`warnings` 里会写明回退原因。

相关开关：

```bash
fetch_problem codeforces 2183A --vjudge-login   # 抓题前强制先登录一次
export VJUDGE_BROWSER=camoufox                  # auto（默认）/ camoufox / chromium
export VJUDGE_CAMOUFOX_PYTHON=/path/to/python   # 指定装了 camoufox 的解释器
export VJUDGE_BROWSER_LOGIN=0                   # 关掉 cookie 过期时的自动弹窗（CI 用）
```

浏览器 profile 是持久化的（`~/.cache/rbook/vjudge-camoufox`、`~/.cache/rbook/vjudge-browser`），cookie 留在里面，下次可静默取走。

AtCoder、Codeforces 的 `source` 指向 VJudge，成功选到某个题面版本时会追加 `#author=<authorKey>` 定位到该版本。

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

- POJ/HDU 等其它 OJ 在 VJudge 上的完整题面抓取（目前只抓标题）。
- Codeforces 原站 Cloudflare 拦截的绕过。
- POJ/HDU 原站题面抓取。
- 题目标签、时间限制、内存限制的跨 OJ 统一解析。

旧 `scripts/problem-tools/oj.js` 第一版暂不修改。人工写题建议使用 `fetch_problem` shell 函数；agent、脚本和 CI 建议使用 `fetch_problem.py`。
