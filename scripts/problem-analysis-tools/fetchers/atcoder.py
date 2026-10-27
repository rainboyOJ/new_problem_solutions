from __future__ import annotations

from html import unescape
import re

from .base import BaseFetcher, FetchError, FetchResult, ProblemData, Sample
from .vjudge_client import CONFIG_PATH, VJudgeClient
from .vjudge_statement import build_statement

# VJudge 上 AtCoder 题目的 OJ 标识。
VJUDGE_OJ = "AtCoder"

# 选版优先级：中文（trustable 优先，见 pick_brief）→ 英文 → 日文。
LANG_PRIORITY = ("zh", "en", "ja")


def strip_tags(html: str) -> str:
    text = re.sub(r"<!--[\s\S]*?-->", "", html)
    text = re.sub(r"<br\s*/?>", "\n", text, flags=re.I)
    text = re.sub(r"</(p|div|section|ul|ol|li)>", "\n", text, flags=re.I)
    text = re.sub(r"<[^>]+>", "", text)
    text = unescape(text)
    lines = [re.sub(r"[ \t\r\f\v]+", " ", line).strip() for line in text.splitlines()]
    return "\n".join(line for line in lines if line).strip()


def inline_text(html: str) -> str:
    return re.sub(r"\s+", " ", strip_tags(html)).strip()


def extract_pre(html: str) -> str:
    match = re.search(r"<pre[^>]*>([\s\S]*?)</pre>", html, flags=re.I)
    if not match:
        return ""
    text = re.sub(r"<[^>]+>", "", match.group(1))
    return unescape(text).strip("\n")


def section_to_markdown(html: str) -> str:
    html = re.sub(
        r"<li[^>]*>([\s\S]*?)</li>",
        lambda match: "\n- " + inline_text(match.group(1)) + "\n",
        html,
        flags=re.I,
    )
    parts: list[str] = []
    pos = 0
    for match in re.finditer(r"<pre[^>]*>([\s\S]*?)</pre>", html, flags=re.I):
        before = strip_tags(html[pos:match.start()])
        if before:
            parts.append(before)
        code = re.sub(r"<[^>]+>", "", match.group(1))
        parts.append("```\n" + unescape(code).strip("\n") + "\n```")
        pos = match.end()
    after = strip_tags(html[pos:])
    if after:
        parts.append(after)
    return "\n\n".join(part for part in parts if part).strip()


def extract_tag_with_class(html: str, tag: str, class_name: str) -> str:
    start_re = re.compile(rf"<{tag}\b[^>]*class=[\"'][^\"']*\b{re.escape(class_name)}\b[^\"']*[\"'][^>]*>", re.I)
    start = start_re.search(html)
    if not start:
        return ""

    token_re = re.compile(rf"</?{tag}\b[^>]*>", re.I)
    depth = 1
    pos = start.end()
    for token in token_re.finditer(html, pos):
        if token.group(0).startswith("</"):
            depth -= 1
            if depth == 0:
                return html[pos:token.start()]
        else:
            depth += 1
    return ""


def parse_title(html: str) -> str:
    match = re.search(r"<title[^>]*>([\s\S]*?)</title>", html, flags=re.I)
    if not match:
        return ""
    return inline_text(match.group(1))


def parse_h3_sections(html: str) -> list[tuple[str, str]]:
    matches = list(re.finditer(r"<h3[^>]*>([\s\S]*?)</h3>", html, flags=re.I))
    sections: list[tuple[str, str]] = []
    for index, match in enumerate(matches):
        heading = inline_text(match.group(1))
        start = match.end()
        end = matches[index + 1].start() if index + 1 < len(matches) else len(html)
        sections.append((heading, html[start:end]))
    return sections


def sample_number(heading: str) -> int:
    match = re.search(r"(\d+)", heading)
    if match:
        return int(match.group(1))
    return 1


def is_input_sample(heading: str) -> bool:
    lower = heading.lower()
    return lower.startswith(("input example", "sample input")) or "入力例" in heading


def is_output_sample(heading: str) -> bool:
    lower = heading.lower()
    return lower.startswith(("output example", "sample output")) or "出力例" in heading


def is_solution_section(heading: str) -> bool:
    lower = heading.lower()
    return lower.startswith("example of ") or "での解答例" in lower


def normalized_section_title(heading: str) -> str:
    mapping = {
        "problem": "题目描述",
        "constraints": "约束",
        "input": "输入格式",
        "output": "输出格式",
        "notice": "说明",
        "notes": "说明",
        "references": "补充说明",
        "問題文": "题目描述",
        "制約": "约束",
        "入力": "输入格式",
        "出力": "输出格式",
        "注意": "说明",
        "補足": "补充说明",
    }
    return mapping.get(heading.strip().lower(), mapping.get(heading.strip(), heading.strip()))


class AtCoderFetcher(BaseFetcher):
    """AtCoder 题目抓取器。

    默认走 VJudge：这样只需要维护 VJudge 一个账号，并且能拿到社区的中文题面。
    原站抓取逻辑保留在 ``fetch_from_atcoder_site``，但默认不再调用。

    ``strict_fetch``：VJudge 拿不到题面时直接报错，不再降级创建 skeleton，
    避免“命令成功但什么都没抓到”。
    """

    name = "atcoder"
    aliases = ("at",)
    site_prefixes = ("https://atcoder.jp", "http://atcoder.jp", "https://vjudge.net")
    strict_fetch = True

    def __init__(self, client: VJudgeClient | None = None):
        self._client = client

    @property
    def client(self) -> VJudgeClient:
        if self._client is None:
            self._client = VJudgeClient()
        return self._client

    # ---------- 题目标识 ----------

    def match_url(self, url: str) -> bool:
        """只接管 atcoder.jp 和 vjudge 上 OJ 前缀为 AtCoder 的 URL。

        不能只看域名，否则 ``vjudge.net/problem/POJ-1000`` 会被 AtCoderFetcher
        抢走（FETCHERS 里它排在 VJudgeFetcher 之前）。
        """

        if url.startswith(("https://atcoder.jp", "http://atcoder.jp")):
            return True
        if url.startswith(("https://vjudge.net", "http://vjudge.net")):
            match = re.search(r"/problem/(?:([A-Za-z0-9_]+)-)?([^/?#]+)", url)
            return bool(match) and (match.group(1) or "").lower() == "atcoder"
        return False

    def fetch_by_url(self, url: str) -> FetchResult:
        """按 URL 抓取，但保留“具体用了哪个题面版本”的 source。"""

        oj, problem_id = self.parse_url(url)
        return self.fetch(oj, problem_id)

    def parse_url(self, url: str) -> tuple[str, str]:
        if url.startswith(("https://vjudge.net", "http://vjudge.net")):
            clean = url.split("?")[0].split("#")[0]
            match = re.search(r"/problem/(?:([A-Za-z0-9_]+)-)?([^/]+)$", clean)
            if not match:
                raise FetchError(f"无法从 VJudge URL 解析题号：{url}")
            return self.name, match.group(2)
        clean = url.split("?")[0].split("#")[0]
        match = re.search(r"/contests/([^/]+)/tasks/([^/]+)$", clean)
        if not match:
            raise FetchError(f"无法从 AtCoder URL 解析 contest/task：{url}")
        return self.name, f"{match.group(1)}/{match.group(2)}"

    def split_problem_id(self, problem_id: str) -> tuple[str, str | None]:
        if "/" in problem_id:
            contest, task = problem_id.split("/", 1)
            return task, contest
        return problem_id, None

    def task_id(self, problem_id: str) -> str:
        """取出 AtCoder 的 task 名（单段或 contest/task 都可以）。"""

        task, _contest = self.split_problem_id(problem_id)
        return task

    def problem_link(self, problem_id: str) -> str:
        task = self.task_id(problem_id)
        return f"https://vjudge.net/problem/{VJUDGE_OJ}-{task}"

    # ---------- 数据构建 ----------

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        task = self.task_id(problem_id)
        return ProblemData(
            oj=self.name,
            problem_id=task,
            problem_dir_id=task,
            source=self.problem_link(problem_id),
            title=task,
        )

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        task = self.task_id(problem_id)
        if not task:
            raise FetchError("AtCoder 题号不能为空。")

        client = self.client
        warnings: list[str] = []
        _pid, english_title = client.problem_info(VJUDGE_OJ, task)
        briefs = client.desc_briefs(VJUDGE_OJ, task)

        chosen, note = self.pick_brief(client, briefs)
        if note:
            warnings.append(note)
        description = client.description(chosen.key)
        statement = build_statement(f"# {english_title}", description.sections)

        samples = list(statement.samples)
        if not samples:
            samples, sample_warning = self.samples_from_fallback(client, briefs, chosen)
            if sample_warning:
                warnings.append(sample_warning)

        source = f"{self.problem_link(problem_id)}#desc={chosen.key}"
        data = ProblemData(
            oj=self.name,
            problem_id=task,
            problem_dir_id=task,
            source=source,
            title=english_title or task,
            statement_md=statement.body_md,
            samples=samples,
            warnings=warnings,
        )
        return FetchResult(data=data, fetched=True, warnings=list(warnings))

    def pick_brief(self, client: VJudgeClient, briefs: list) -> tuple:
        """按 zh(trustable) → zh → en → ja 选版，返回 (brief, 说明文字)。

        trustable 不在 descBriefs 里，只在正文 JSON 里，所以要逐个取正文才能排序。
        正文有进程内缓存，同一版本不会被重复拉取。
        """

        by_lang: dict[str, list] = {}
        for brief in briefs:
            by_lang.setdefault(brief.lang, []).append(brief)

        zh_briefs = by_lang.get("zh") or []
        if zh_briefs:
            for brief in zh_briefs:
                if client.description(brief.key).trustable:
                    others = len(zh_briefs) - 1
                    note = (
                        f"使用 VJudge 中文题面（{brief.author}，trustable，版本 {brief.key}）"
                    )
                    if others:
                        note += f"；该题另有 {others} 个中文版本"
                    return brief, note
            return zh_briefs[0], (
                f"使用 VJudge 中文题面（{zh_briefs[0].author}，"
                f"版本 {zh_briefs[0].key}），未找到标记为 trustable 的中文版本"
            )

        for lang in ("en", "ja"):
            candidates = by_lang.get(lang) or []
            if candidates:
                main = next((b for b in candidates if b.main_official), candidates[0])
                return main, f"该题在 VJudge 上没有中文题面，已回退到 {lang} 版本（{main.author}）"

        brief = briefs[0]
        return brief, f"该题在 VJudge 上只有 {brief.lang} 版本，已使用（{brief.author}）"

    def samples_from_fallback(
        self, client: VJudgeClient, briefs: list, chosen
    ) -> tuple[list[Sample], str]:
        """选中版本没有样例表时，从其它版本（优先 en main）补样例。"""

        others = [b for b in briefs if b.key != chosen.key]
        others.sort(key=lambda b: (b.lang != "en", not b.main_official))
        for brief in others:
            try:
                fallback = client.description(brief.key)
            except FetchError:
                continue
            statement = build_statement("# fallback", fallback.sections)
            if statement.samples:
                return statement.samples, (
                    f"所选题面版本（{chosen.lang}/{chosen.author}，{chosen.key}）没有样例，"
                    f"样例取自 {brief.lang}/{brief.author} 版本（{brief.key}）"
                )
        return [], "所选题面及所有备用版本都没有抓到样例。"

    # ---------- 以下为 AtCoder 原站抓取，默认不再调用 ----------

    def fetch_from_atcoder_site(self, oj: str, problem_id: str) -> FetchResult:
        task, contest = self.split_problem_id(problem_id)
        if not contest:
            raise FetchError("AtCoder 原站抓取需要使用题目 URL，或使用 problem_id 形如 contest/task。")

        source = f"https://atcoder.jp/contests/{contest}/tasks/{task}"
        html = self.http_get(source)
        data = self.parse_site_html(html, problem_id)
        data.source = source
        return FetchResult(data=data, fetched=True, warnings=list(data.warnings))

    def parse_site_html(self, html: str, problem_id: str) -> ProblemData:
        """解析 AtCoder 原站题面 HTML（保留给测试与手动使用）。

        ``parse_html`` 是历史名称，保留为别名以免旧脚本/测试失效。
        """
        task, _contest = self.split_problem_id(problem_id)
        lang_html = extract_tag_with_class(html, "span", "lang-en")
        if not lang_html:
            lang_html = extract_tag_with_class(html, "span", "lang-ja")
        if not lang_html:
            raise FetchError("未找到 AtCoder 题面语言块。")

        title = parse_title(html) or task
        sections = parse_h3_sections(lang_html)
        if not sections:
            raise FetchError("未能解析 AtCoder 题面小节。")
        samples = self.parse_samples(sections)
        statement_md = self.problem_statement_markdown(task, title, sections, samples)
        task_name, contest = self.split_problem_id(problem_id)
        link = (
            f"https://atcoder.jp/contests/{contest}/tasks/{task_name}"
            if contest
            else "https://atcoder.jp"
        )
        return ProblemData(
            oj=self.name,
            problem_id=task,
            problem_dir_id=task,
            source=link,
            title=title,
            statement_md=statement_md,
            samples=samples,
        )

    def parse_samples(self, sections: list[tuple[str, str]]) -> list[Sample]:
        inputs: dict[int, str] = {}
        outputs: dict[int, str] = {}
        for heading, content in sections:
            if is_input_sample(heading):
                inputs[sample_number(heading)] = extract_pre(content)
            elif is_output_sample(heading):
                outputs[sample_number(heading)] = extract_pre(content)

        samples: list[Sample] = []
        for index in sorted(set(inputs) | set(outputs)):
            samples.append(Sample(input=inputs.get(index, ""), output=outputs.get(index, "")))
        return samples

    def problem_statement_markdown(
        self,
        task: str,
        title: str,
        sections: list[tuple[str, str]],
        samples: list[Sample],
    ) -> str:
        parts = [f"# {task} {title}".strip()]
        sample_written = False
        for heading, content in sections:
            if is_solution_section(heading):
                break
            if is_input_sample(heading) or is_output_sample(heading):
                if not sample_written and samples:
                    parts.append(self.samples_markdown(samples))
                    sample_written = True
                continue
            body = section_to_markdown(content)
            if body:
                parts.append(f"## {normalized_section_title(heading)}\n\n{body}")
        return "\n\n".join(part.rstrip() for part in parts if part.strip()).rstrip() + "\n"

    def samples_markdown(self, samples: list[Sample]) -> str:
        parts: list[str] = []
        for index, sample in enumerate(samples, start=1):
            parts.append(
                "\n".join(
                    [
                        f"## 输入输出样例 #{index}",
                        "",
                        f"### 输入 #{index}",
                        "",
                        "```",
                        sample.input.rstrip(),
                        "```",
                        "",
                        f"### 输出 #{index}",
                        "",
                        "```",
                        sample.output.rstrip(),
                        "```",
                    ]
                )
            )
        return "\n\n".join(parts) + "\n"

    # 历史名称，避免旧脚本与测试失效。
    parse_html = parse_site_html
