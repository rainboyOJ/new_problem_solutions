from __future__ import annotations

import ast
import json
import re
from urllib.parse import unquote, urlparse

from .base import BaseFetcher, FetchError, FetchResult, ProblemData, Sample


class ShumengFetcher(BaseFetcher):
    name = "shumeng"
    site_prefixes = ("https://oj.shumeng.tech/",)

    def normalize_id(self, problem_id: str) -> str:
        problem_id = unquote(problem_id).strip()
        if not problem_id or problem_id in {".", ".."}:
            raise FetchError(f"无效的曙梦 OJ 题号：{problem_id}")
        if any(ord(char) < 32 or char in "/\\?#" for char in problem_id):
            raise FetchError(f"曙梦 OJ 题号不能包含路径或 URL 分隔符：{problem_id}")
        return problem_id

    def problem_link(self, problem_id: str) -> str:
        return f"https://oj.shumeng.tech/p/{problem_id}"

    def parse_url(self, url: str) -> tuple[str, str]:
        parsed = urlparse(url)
        if parsed.scheme != "https" or parsed.hostname != "oj.shumeng.tech":
            raise FetchError(f"无法从曙梦 OJ URL 解析题号：{url}")
        parts = [unquote(part) for part in parsed.path.split("/") if part]
        if len(parts) != 2 or parts[0] != "p":
            raise FetchError(f"曙梦 OJ URL 必须是单题地址 /p/<题号>：{url}")
        return self.name, self.normalize_id(parts[1])

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        problem_id = self.normalize_id(problem_id)
        return ProblemData(
            oj=self.name,
            problem_id=problem_id,
            problem_dir_id=problem_id,
            source=self.problem_link(problem_id),
            title=problem_id,
        )

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        data = self.build_data_from_id(oj, problem_id)
        html = self.http_get(data.source)
        fetched_data = self.parse_html(html, problem_id)
        fetched_data.source = data.source
        return FetchResult(data=fetched_data, fetched=True, warnings=list(fetched_data.warnings))

    def fetch_by_url(self, url: str) -> FetchResult:
        oj, problem_id = self.parse_url(url)
        result = self.fetch(oj, problem_id)
        result.data.source = url
        return result

    def parse_html(self, html: str, problem_id: str) -> ProblemData:
        context = self.extract_ui_context(html)
        pdoc = context.get("pdoc")
        if not isinstance(pdoc, dict):
            raise FetchError("曙梦 OJ 页面中缺少 pdoc 数据。")

        requested_id = self.normalize_id(problem_id)
        page_id = str(pdoc.get("pid") or context.get("problemId") or requested_id).strip()
        page_id = self.normalize_id(page_id)
        if page_id.lower() != requested_id.lower():
            raise FetchError(f"页面题号与请求不一致：请求 {requested_id}，页面为 {page_id}")

        title = str(pdoc.get("title") or page_id).strip()
        statement = self.select_statement(pdoc.get("content"))
        samples, warnings = self.parse_samples(statement)
        return ProblemData(
            oj=self.name,
            problem_id=page_id,
            problem_dir_id=page_id,
            source=self.problem_link(page_id),
            title=title,
            statement_md=statement,
            samples=samples,
            warnings=warnings,
        )

    def extract_ui_context(self, html: str) -> dict[str, object]:
        match = re.search(r"window\.UiContextNew\s*=\s*(['\"])", html)
        if not match:
            raise FetchError("未找到 window.UiContextNew 数据。")

        quote = match.group(1)
        start = match.end()
        escaped = False
        end = -1
        for index in range(start, len(html)):
            char = html[index]
            if escaped:
                escaped = False
            elif char == "\\":
                escaped = True
            elif char == quote:
                end = index
                break
        if end == -1:
            raise FetchError("window.UiContextNew 字符串未闭合。")

        literal = quote + html[start:end] + quote
        try:
            decoded = ast.literal_eval(literal)
        except (SyntaxError, ValueError) as exc:
            raise FetchError(f"window.UiContextNew 字符串解析失败：{exc}") from exc
        if not isinstance(decoded, str):
            raise FetchError("window.UiContextNew 不是 JSON 字符串。")
        try:
            context = json.loads(decoded)
        except json.JSONDecodeError as exc:
            raise FetchError(f"window.UiContextNew JSON 解析失败：{exc}") from exc
        if not isinstance(context, dict):
            raise FetchError("window.UiContextNew JSON 根节点不是对象。")
        return context

    def select_statement(self, raw_content: object) -> str:
        content = raw_content
        if isinstance(content, str):
            try:
                content = json.loads(content)
            except json.JSONDecodeError:
                if content.strip():
                    return content.strip() + "\n"
                raise FetchError("曙梦 OJ 题面内容为空。")

        if isinstance(content, dict):
            candidates = [content.get("zh")]
            candidates.extend(content.values())
            for candidate in candidates:
                if isinstance(candidate, str) and candidate.strip():
                    return candidate.strip() + "\n"
        raise FetchError("曙梦 OJ 中没有可用的题面 Markdown。")

    def parse_samples(self, statement: str) -> tuple[list[Sample], list[str]]:
        pattern = re.compile(
            r"```[ \t]*(input|output)([1-9][0-9]*)[ \t]*\r?\n"
            r"([\s\S]*?)\r?\n?[ \t]*```"
        )
        inputs: dict[int, str] = {}
        outputs: dict[int, str] = {}
        warnings: list[str] = []
        for match in pattern.finditer(statement):
            kind = match.group(1)
            number = int(match.group(2))
            value = match.group(3)
            if kind == "input":
                target = inputs
            else:
                target = outputs
            if number in target:
                warnings.append(f"样例 {number} 的 {kind} 块重复，使用最后一个。")
            target[number] = value

        samples: list[Sample] = []
        for number in sorted(set(inputs) | set(outputs)):
            if number not in inputs or number not in outputs:
                warnings.append(f"样例 {number} 缺少 input 或 output，已跳过。")
                continue
            samples.append(Sample(input=inputs[number], output=outputs[number]))
        return samples, warnings
