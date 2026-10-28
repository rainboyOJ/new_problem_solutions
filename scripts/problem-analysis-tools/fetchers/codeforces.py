from __future__ import annotations

from dataclasses import dataclass, field
from html.parser import HTMLParser
import json
import re
from urllib.parse import urljoin

from .base import BaseFetcher, FetchError, FetchResult, ProblemData, Sample, normalize_space
from .vjudge_client import VJudgeClient
from .vjudge_pick import pick_brief, samples_from_fallback
from .vjudge_statement import build_statement


CODEFORCES_ORIGIN = "https://codeforces.com"

# VJudge 上 Codeforces 题目的 OJ 标识。
VJUDGE_OJ = "CodeForces"

VOID_TAGS = {"area", "base", "br", "col", "embed", "hr", "img", "input", "link", "meta", "source", "wbr"}


@dataclass
class HtmlNode:
    tag: str
    attrs: dict[str, str] = field(default_factory=dict)
    children: list[HtmlNode | str] = field(default_factory=list)

    def has_class(self, class_name: str) -> bool:
        return class_name in self.attrs.get("class", "").split()


class HtmlTreeParser(HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.root = HtmlNode("document")
        self.stack = [self.root]

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        node = HtmlNode(tag.lower(), {key: value or "" for key, value in attrs})
        self.stack[-1].children.append(node)
        if node.tag not in VOID_TAGS:
            self.stack.append(node)

    def handle_startendtag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        self.handle_starttag(tag, attrs)
        if tag.lower() not in VOID_TAGS:
            self.handle_endtag(tag)

    def handle_endtag(self, tag: str) -> None:
        lowered = tag.lower()
        for index in range(len(self.stack) - 1, 0, -1):
            if self.stack[index].tag == lowered:
                del self.stack[index:]
                return

    def handle_data(self, data: str) -> None:
        self.stack[-1].children.append(data)


def parse_html_tree(html: str) -> HtmlNode:
    parser = HtmlTreeParser()
    parser.feed(html)
    parser.close()
    return parser.root


def child_nodes(node: HtmlNode) -> list[HtmlNode]:
    return [child for child in node.children if isinstance(child, HtmlNode)]


def find_first(node: HtmlNode, predicate) -> HtmlNode | None:
    if predicate(node):
        return node
    for child in child_nodes(node):
        found = find_first(child, predicate)
        if found is not None:
            return found
    return None


def find_all(node: HtmlNode, predicate) -> list[HtmlNode]:
    found: list[HtmlNode] = []
    if predicate(node):
        found.append(node)
    for child in child_nodes(node):
        found.extend(find_all(child, predicate))
    return found


def find_by_class(node: HtmlNode, class_name: str) -> HtmlNode | None:
    return find_first(node, lambda item: item.has_class(class_name))


def raw_text(node: HtmlNode) -> str:
    parts: list[str] = []
    for child in node.children:
        if isinstance(child, str):
            parts.append(child)
        elif child.tag == "br":
            parts.append("\n")
        elif child.tag not in {"script", "style"}:
            parts.append(raw_text(child))
    return "".join(parts)


def node_text(node: HtmlNode) -> str:
    return normalize_space(raw_text(node))


def absolute_url(value: str) -> str:
    if value.startswith("//"):
        return f"https:{value}"
    return urljoin(f"{CODEFORCES_ORIGIN}/", value)


def normalize_math(text: str) -> str:
    return re.sub(r"\$\$\$([\s\S]*?)\$\$\$", lambda match: f"${match.group(1).strip()}$", text)


def clean_markdown(text: str) -> str:
    text = normalize_math(text)
    text = re.sub(r"[ \t]+\n", "\n", text)
    text = re.sub(r"\n[ \t]+", "\n", text)
    text = re.sub(r"\n{3,}", "\n\n", text)
    return text.strip()


def render_children(node: HtmlNode) -> str:
    return "".join(render_node(child) for child in node.children)


def render_list(node: HtmlNode, ordered: bool) -> str:
    lines: list[str] = []
    item_number = 1
    for child in child_nodes(node):
        if child.tag != "li":
            continue
        nested = [item for item in child_nodes(child) if item.tag in {"ul", "ol"}]
        body_parts = [
            render_node(item)
            for item in child.children
            if not isinstance(item, HtmlNode) or item.tag not in {"ul", "ol"}
        ]
        body = clean_markdown("".join(body_parts)).replace("\n\n", " ")
        prefix = f"{item_number}." if ordered else "-"
        lines.append(f"{prefix} {body}".rstrip())
        for nested_list in nested:
            nested_text = render_list(nested_list, nested_list.tag == "ol")
            lines.extend(f"  {line}" for line in nested_text.splitlines())
        item_number += 1
    return "\n".join(lines) + "\n\n"


def render_node(node: HtmlNode | str) -> str:
    if isinstance(node, str):
        return re.sub(r"\s+", " ", node)
    if node.tag in {"script", "style", "form"}:
        return ""
    if node.tag == "br":
        return "\n"
    if node.tag == "p":
        return render_children(node).strip() + "\n\n"
    if node.tag == "ul":
        return render_list(node, False)
    if node.tag == "ol":
        return render_list(node, True)
    if node.tag == "a":
        label = clean_markdown(render_children(node))
        href = node.attrs.get("href", "")
        return f"[{label}]({absolute_url(href)})" if label and href else label
    if node.tag == "img":
        source = node.attrs.get("src", "")
        alt = node.attrs.get("alt", "")
        return f"![{alt}]({absolute_url(source)})" if source else ""
    if node.tag in {"strong", "b"}:
        return f"**{render_children(node).strip()}**"
    if node.tag in {"em", "i"}:
        return f"*{render_children(node).strip()}*"
    if node.tag in {"code", "tt"} or node.has_class("tex-font-style-tt"):
        value = render_children(node).strip()
        if not value or "$$$" in value or "$" in value:
            return value
        return f"`{value.replace('`', '\\`')}`"
    if node.tag in {"sup", "sub"}:
        return f"<{node.tag}>{render_children(node).strip()}</{node.tag}>"
    if node.tag == "pre":
        return f"```\n{preformatted_text(node).rstrip()}\n```\n\n"
    return render_children(node)


def preformatted_text(node: HtmlNode) -> str:
    example_lines = find_all(node, lambda item: item.has_class("test-example-line"))
    if example_lines:
        return "\n".join(raw_text(line).strip("\r\n") for line in example_lines).strip("\r\n")

    parts: list[str] = []
    for child in node.children:
        if isinstance(child, str):
            parts.append(child)
        elif child.tag == "br":
            parts.append("\n")
        elif child.tag == "div":
            parts.append(raw_text(child))
            parts.append("\n")
        else:
            parts.append(raw_text(child))
    return "".join(parts).strip("\r\n")


def section_body(node: HtmlNode | None) -> str:
    if node is None:
        return ""
    content = "".join(
        render_node(child)
        for child in node.children
        if not isinstance(child, HtmlNode) or not child.has_class("section-title")
    )
    return clean_markdown(content)


def property_value(node: HtmlNode | None) -> str:
    if node is None:
        return ""
    value = "".join(
        raw_text(child) if isinstance(child, HtmlNode) else child
        for child in node.children
        if not isinstance(child, HtmlNode) or not child.has_class("property-title")
    )
    return normalize_space(value)


class CodeforcesFetcher(BaseFetcher):
    """Codeforces 题目抓取器。

    默认走 VJudge：只要维护 VJudge 一个账号，就能拿到社区的中文题面，题目跳转链接
    （``source``）也指向 VJudge。VJudge 不可用（未登录、未收录该题、题面解析失败）时
    回退到 Codeforces 原站抓英文题面。

    ``strict_fetch`` 保持 False：两边都失败时按老行为创建 skeleton，并在 warnings 里说明。
    """

    name = "codeforces"
    aliases = ("cf",)
    site_prefixes = (
        CODEFORCES_ORIGIN,
        "https://www.codeforces.com",
        "https://vjudge.net",
        "http://vjudge.net",
    )

    def __init__(self, client: VJudgeClient | None = None):
        self._client = client

    @property
    def client(self) -> VJudgeClient:
        if self._client is None:
            self._client = VJudgeClient()
        return self._client

    # ---------- 题目标识 ----------

    def match_url(self, url: str) -> bool:
        """只接管 codeforces.com 和 vjudge 上 OJ 前缀为 CodeForces 的 URL。

        不能只看 vjudge 域名，否则 ``vjudge.net/problem/POJ-1000`` 会被它抢走
        （FETCHERS 里它排在 VJudgeFetcher 之前）。
        """

        if url.startswith(("https://codeforces.com", "https://www.codeforces.com")):
            return True
        if url.startswith(("https://vjudge.net", "http://vjudge.net")):
            match = re.search(r"/problem/(?:([A-Za-z0-9_]+)-)?([^/?#]+)", url)
            return bool(match) and (match.group(1) or "").lower() == VJUDGE_OJ.lower()
        return False

    def parse_url(self, url: str) -> tuple[str, str]:
        clean = url.split("?")[0].split("#")[0].rstrip("/")
        if "vjudge.net" in clean:
            match = re.search(r"/problem/(?:([A-Za-z0-9_]+)-)?([^/]+)$", clean)
            if not match:
                raise FetchError(f"无法从 VJudge URL 解析 Codeforces 题号：{url}")
            return self.name, match.group(2)
        patterns = [
            r"/contest/(\d+)/problem/([A-Za-z0-9]+)$",
            r"/problemset/problem/(\d+)/([A-Za-z0-9]+)$",
        ]
        for pattern in patterns:
            match = re.search(pattern, clean)
            if match:
                return self.name, f"{match.group(1)}{match.group(2)}"
        raise FetchError(f"无法从 Codeforces URL 解析题号：{url}")

    def split_problem_id(self, problem_id: str) -> tuple[int, str]:
        match = re.fullmatch(r"(\d+)([A-Za-z][A-Za-z0-9]*)", problem_id)
        if not match:
            raise FetchError(f"无效的 Codeforces 题号：{problem_id}")
        return int(match.group(1)), match.group(2)

    def problem_link(self, problem_id: str) -> str:
        """题目的默认跳转链接：VJudge（能直接看中文题面）。"""

        try:
            contest_id, index = self.split_problem_id(problem_id)
        except FetchError:
            return CODEFORCES_ORIGIN
        return f"https://vjudge.net/problem/{VJUDGE_OJ}-{contest_id}{index}"

    def official_link(self, problem_id: str) -> str:
        """Codeforces 原站链接，抓原站题面和 VJudge 未收录时使用。"""

        try:
            contest_id, index = self.split_problem_id(problem_id)
        except FetchError:
            return CODEFORCES_ORIGIN
        return f"{CODEFORCES_ORIGIN}/contest/{contest_id}/problem/{index}"

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        return ProblemData(
            oj=self.name,
            problem_id=problem_id,
            problem_dir_id=problem_id,
            source=self.problem_link(problem_id),
            title=problem_id,
        )

    # ---------- 抓取 ----------

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        self.split_problem_id(problem_id)
        warnings: list[str] = []
        link = self.vjudge_link(problem_id, warnings)
        try:
            data = self.statement_from_vjudge(problem_id, link)
            data.warnings = warnings + list(data.warnings)
            return FetchResult(data=data, fetched=True, warnings=list(data.warnings))
        except FetchError as exc:
            warnings.append(f"VJudge 题面抓取失败，回退 Codeforces 原站：{exc}")
        return self.statement_from_site(problem_id, link, warnings)

    def fetch_by_url(self, url: str) -> FetchResult:
        """URL 模式也只保留抓取得到的 source，不把 codeforces.com 原样写回去。"""

        oj, problem_id = self.parse_url(url)
        return self.fetch(oj, problem_id)

    def vjudge_link(self, problem_id: str, warnings: list[str]) -> str:
        """确认 VJudge 是否收录该题并给出跳转链接；确认不到就返回空串。"""

        try:
            self.client.problem_info(VJUDGE_OJ, problem_id)
        except FetchError as exc:
            warnings.append(f"VJudge 未确认到该题（{exc}），跳转链接使用 Codeforces 原站。")
            return ""
        return self.problem_link(problem_id)

    def statement_from_vjudge(self, problem_id: str, link: str) -> ProblemData:
        """从 VJudge 取题面：优先中文（trustable），样例缺失时从其它版本借。"""

        client = self.client
        warnings: list[str] = []
        _pid, english_title = client.problem_info(VJUDGE_OJ, problem_id)
        briefs = client.desc_briefs(VJUDGE_OJ, problem_id)

        chosen, note = pick_brief(client, briefs)
        if note:
            warnings.append(note)
        description = client.description(chosen.key)
        statement = build_statement(f"# {problem_id} {english_title}".strip(), description.sections)
        if not statement.body_md.strip():
            raise FetchError(f"VJudge 题面 key={chosen.key} 转成 Markdown 后为空。")

        samples = list(statement.samples)
        if not samples:
            samples, sample_warning = samples_from_fallback(client, briefs, chosen)
            if sample_warning:
                warnings.append(sample_warning)

        source = link or self.problem_link(problem_id)
        if chosen.author_key:
            source += f"#author={chosen.author_key}"
        else:
            warnings.append("VJudge 题面版本缺少 authorKey，来源链接无法定位到所选题面。")

        return ProblemData(
            oj=self.name,
            problem_id=problem_id,
            problem_dir_id=problem_id,
            source=source,
            title=english_title or problem_id,
            statement_md=statement.body_md,
            samples=samples,
            warnings=warnings,
        )

    def statement_from_site(
        self, problem_id: str, link: str, warnings: list[str]
    ) -> FetchResult:
        """回退路径：抓 Codeforces 原站英文题面；失败则退回 skeleton。"""

        official = self.official_link(problem_id)
        source = link or official
        try:
            html = self.http_get(official)
            fetched_data = self.parse_html(html, problem_id)
            fetched_data.source = source
            fetched_data.warnings = warnings + list(fetched_data.warnings)
            return FetchResult(
                data=fetched_data, fetched=True, warnings=list(fetched_data.warnings)
            )
        except FetchError as statement_error:
            warnings.append(f"题面/样例抓取失败，仅创建 skeleton：{statement_error}")

        data = ProblemData(
            oj=self.name,
            problem_id=problem_id,
            problem_dir_id=problem_id,
            source=source,
            title=problem_id,
        )
        try:
            api_title = self.fetch_api_title(problem_id)
            if api_title:
                data.title = api_title
        except FetchError as api_error:
            warnings.append(f"Codeforces API 标题回退失败：{api_error}")
        data.warnings.extend(warnings)
        return FetchResult(data=data, fetched=False, warnings=list(warnings))

    def fetch_api_title(self, problem_id: str) -> str:
        contest_id, index = self.split_problem_id(problem_id)
        raw = self.http_get(f"{CODEFORCES_ORIGIN}/api/problemset.problems")
        try:
            payload = json.loads(raw)
        except json.JSONDecodeError as exc:
            raise FetchError(f"problemset.problems JSON 解析失败：{exc}") from exc
        if payload.get("status") != "OK":
            raise FetchError(payload.get("comment") or "problemset.problems 返回失败状态。")
        for problem in payload.get("result", {}).get("problems", []):
            if problem.get("contestId") == contest_id and problem.get("index") == index:
                return str(problem.get("name") or "")
        raise FetchError(f"problemset.problems 中未找到 {problem_id}。")

    def parse_html(self, html: str, problem_id: str) -> ProblemData:
        _contest_id, index = self.split_problem_id(problem_id)
        root = parse_html_tree(html)
        statement = find_by_class(root, "problem-statement")
        if statement is None:
            raise FetchError("未找到 Codeforces 题面 .problem-statement，页面可能被 Cloudflare 拦截。")

        header = find_by_class(statement, "header")
        title_node = find_by_class(header, "title") if header is not None else None
        raw_title = node_text(title_node) if title_node is not None else ""
        title = re.sub(rf"^{re.escape(index)}\.\s*", "", raw_title, flags=re.I).strip()

        direct_sections = child_nodes(statement)
        description_node = next(
            (
                node
                for node in direct_sections
                if node.tag == "div" and not node.attrs.get("class")
            ),
            None,
        )
        description = section_body(description_node)
        if not title or not description:
            raise FetchError("Codeforces 题面缺少标题或题目描述。")

        input_node = find_by_class(statement, "input-specification")
        output_node = find_by_class(statement, "output-specification")
        note_node = find_by_class(statement, "note")
        time_limit = property_value(find_by_class(header, "time-limit")) if header else ""
        memory_limit = property_value(find_by_class(header, "memory-limit")) if header else ""
        samples, warnings = self.parse_samples(statement)
        statement_md = self.problem_statement_markdown(
            problem_id=problem_id,
            title=title,
            time_limit=time_limit,
            memory_limit=memory_limit,
            description=description,
            input_specification=section_body(input_node),
            output_specification=section_body(output_node),
            samples=samples,
            note=section_body(note_node),
        )
        return ProblemData(
            oj=self.name,
            problem_id=problem_id,
            problem_dir_id=problem_id,
            source=self.official_link(problem_id),
            title=title,
            statement_md=statement_md,
            samples=samples,
            warnings=warnings,
        )

    def parse_samples(self, statement: HtmlNode) -> tuple[list[Sample], list[str]]:
        samples: list[Sample] = []
        warnings: list[str] = []
        sample_nodes = find_all(statement, lambda node: node.has_class("sample-test"))
        for sample_number, sample_node in enumerate(sample_nodes, start=1):
            input_node = find_by_class(sample_node, "input")
            output_node = find_by_class(sample_node, "output")
            input_pre = find_first(input_node, lambda node: node.tag == "pre") if input_node else None
            output_pre = find_first(output_node, lambda node: node.tag == "pre") if output_node else None
            input_text = preformatted_text(input_pre) if input_pre else ""
            output_text = preformatted_text(output_pre) if output_pre else ""
            if input_pre is None or output_pre is None:
                warnings.append(f"Codeforces 样例 #{sample_number} 输入输出不完整，已跳过。")
                continue
            samples.append(Sample(input=input_text, output=output_text))
        return samples, warnings

    def problem_statement_markdown(
        self,
        *,
        problem_id: str,
        title: str,
        time_limit: str,
        memory_limit: str,
        description: str,
        input_specification: str,
        output_specification: str,
        samples: list[Sample],
        note: str,
    ) -> str:
        parts = [f"# {problem_id} {title}".strip()]
        limits: list[str] = []
        if time_limit:
            limits.append(f"- Time limit: {time_limit}")
        if memory_limit:
            limits.append(f"- Memory limit: {memory_limit}")
        if limits:
            parts.append("\n".join(limits))
        parts.append(f"## 题目描述\n\n{description}")
        if input_specification:
            parts.append(f"## 输入格式\n\n{input_specification}")
        if output_specification:
            parts.append(f"## 输出格式\n\n{output_specification}")
        if samples:
            parts.append(self.samples_markdown(samples))
        if note:
            parts.append(f"## 说明\n\n{note}")
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
