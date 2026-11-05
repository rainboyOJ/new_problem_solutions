// RBook 题目复习卡模板（黑白省墨版）
// 由 build.py 生成的 cards.typ 通过 #import "template.typ": * 使用。
// 设计约束：只用灰度 + 细线 + ● 填充数表难度，黑白/省墨打印不丢信息。

#let conf = (
  ink: luma(40),
  band: luma(236),
  strip: luma(246),
  rule: luma(150),
  muted: luma(85),
  faint: luma(170),
  mono: ("Menlo", "DejaVu Sans Mono", "Songti SC", "PingFang SC"),   // 带 CJK 回退，样例里出现中文才不会变空白
)

// ---------- 页面与全局样式 ----------
#let doc(batch-name, body) = {
  set page(
    paper: "a4",
    margin: (x: 11mm, y: 11mm),
    footer: context align(center, text(size: 7pt, fill: conf.faint)[
      #batch-name · 第 #counter(page).display("1") 页 / 共 #counter(page).final().first() 页
    ]),
  )
  set text(font: ("Songti SC", "Heiti SC"), size: 8.4pt, lang: "zh", region: "cn", fill: conf.ink)
  set par(leading: 0.6em, justify: true, spacing: 0.85em)
  set list(indent: 0.85em, body-indent: 0.45em, spacing: 0.35em, marker: text(fill: conf.muted)[•])
  set enum(indent: 0.9em, body-indent: 0.45em, spacing: 0.35em)
  show raw: set text(font: conf.mono, size: 7.4pt)
  set heading(numbering: none)
  body
}

#let lab(s) = text(font: "Heiti SC", weight: "bold", size: 7.4pt, fill: conf.ink)[#s]
#let tiny(s) = text(size: 7.4pt, fill: conf.muted)[#s]

// 难度：5 个方块，填充数 = 档位（函数名避开 typst 内置 dots，否则数学模式里 $a dots.h b$ 会解析成字段访问）
#let diff-mark(n) = {
  let full = calc.clamp(int(n), 0, 5)
  let marks = range(5).map(i => if i < full { "■" } else { "□" }).join(" ")
  text(size: 7.2pt, fill: conf.ink)[#marks]
}

// ---------- 卡片部件 ----------
#let card-header(title, meta, dots-n, sid) = block(
  width: 100%,
  fill: conf.band,
  inset: (x: 3.2mm, y: 1.6mm),
  {
    set par(justify: false, leading: 0.4em)
    grid(
      columns: (1fr, auto),
      align: (left + horizon, right + horizon),
      text(font: "Heiti SC", weight: "bold", size: 10.8pt)[#title],
      diff-mark(dots-n),
    )
    v(-0.6mm)
    grid(
      columns: (1fr, auto),
      align: (left + horizon, right + horizon),
      tiny(meta),
      tiny(sid),
    )
  },
)

#let card-notes(approach, approach-note, complexity, points, pitfall) = block(
  width: 100%,
  inset: (x: 3.2mm, y: 1.3mm),
  {
    set par(justify: false, leading: 1.15em, spacing: 0.25em)
    line(length: 100%, stroke: 0.4pt + conf.faint)
    v(0.7mm)
    if approach != none {
      [#lab("做法")　#approach #if approach-note != none { text(size: 7pt, style: "italic", fill: conf.muted)[（#approach-note）] }]
    } else {
      [#lab("做法")　#text(size: 7.6pt, fill: conf.faint)[待补]]
    }
    linebreak()
    if complexity != none {
      [#lab("复杂度")　#complexity]
      linebreak()
    }
    if points.len() > 0 {
      [#lab("考察")　#points.join(" · ")]
      linebreak()
    }
    if pitfall != none {
      [#lab("典型坑")　#pitfall]
      linebreak()
    }
  },
)

// 用剩余空间画「复盘笔记」横线（只用于固定高度卡，把空白变成可写区）
#let notes-fill() = layout(size => {
  let row-h = 5mm
  let n = calc.floor(size.height / row-h)
  if n < 2 { return [] }
  block(width: 100%, {
    v(0.8mm)
    text(size: 6.4pt, fill: conf.faint)[✎ 复盘笔记]
    for i in range(n - 1) {
      v(0.6mm)
      line(length: 100%, stroke: 0.25pt + luma(200))
      v(row-h - 0.8mm)
    }
  })
})

// 样例块：左侧小标签 + 等宽原文
#let sample(label, code) = block(
  width: 100%,
  fill: luma(247),
  stroke: 0.3pt + luma(205),
  radius: 0.8mm,
  inset: (x: 1.8mm, y: 0.8mm),
  {
    set par(justify: false, leading: 0.32em)
    text(font: ("Heiti SC",), size: 6.8pt, fill: conf.muted)[#label]
    linebreak()
    text(font: conf.mono, size: 6.9pt, raw(code))
  },
)

// 输入/输出并排的样例块（两边都短的时候用，省一半高度）
#let sample-pair(lin, cin, lout, cout) = block(
  width: 100%,
  fill: luma(247),
  stroke: 0.3pt + luma(205),
  radius: 0.8mm,
  inset: (x: 1.8mm, y: 0.8mm),
  {
    set par(justify: false, leading: 0.32em)
    grid(
      columns: (1fr, 1fr),
      column-gutter: 2.4mm,
      {
        text(font: ("Heiti SC",), size: 6.8pt, fill: conf.muted)[#lin]
        linebreak()
        text(font: conf.mono, size: 6.9pt, raw(cin))
      },
      {
        text(font: ("Heiti SC",), size: 6.8pt, fill: conf.muted)[#lout]
        linebreak()
        text(font: conf.mono, size: 6.9pt, raw(cout))
      },
    )
  },
)

#let card-strip(sid) = block(
  width: 100%,
  fill: conf.strip,
  inset: (x: 3.2mm, y: 1.2mm),
  {
    set par(justify: false)
    text(size: 7.2pt, fill: conf.muted)[☐ 未做　☐ 会做　☐ 需回看　　用时 \_\_\_\_\_ 分　得分 \_\_\_\_\_　日期 \_\_\_\_\_\_]
  },
)

// ---------- 固定高度卡（一页两张） ----------
#let card-fixed(
  title: "", meta: "", dots-n: 0, sid: "",
  body: none, approach: none, approach-note: none,
  complexity: none, points: (), pitfall: none,
  height: 131mm,
) = block(
  width: 100%,
  height: height,
  stroke: 0.7pt + conf.ink,
  radius: 1mm,
  clip: true,
  inset: 0pt,
  grid(
    rows: (auto, 1fr, auto, auto),
    card-header(title, meta, dots-n, sid),
    block(inset: (x: 3.2mm, y: 1.4mm), {
      body
      notes-fill()
    }),
    card-notes(approach, approach-note, complexity, points, pitfall),
    card-strip(sid),
  ),
)

// ---------- 流式卡（一页一张，允许跨页） ----------
#let card-flow(
  title: "", meta: "", dots-n: 0, sid: "",
  body: none, approach: none, approach-note: none,
  complexity: none, points: (), pitfall: none,
) = block(
  width: 100%,
  stroke: 0.7pt + conf.ink,
  radius: 1mm,
  inset: 0pt,
  breakable: true,
  {
    card-header(title, meta, dots-n, sid)
    block(inset: (x: 3.2mm, y: 1.4mm), body)
    card-notes(approach, approach-note, complexity, points, pitfall)
    card-strip(sid)
  },
)

// ---------- 组页 ----------
#let card-pair(a, b) = {
  grid(columns: 1, rows: 2, gutter: 5mm, a, b)
}

#let card-solo(c) = {
  c
}

// ---------- 封面 ----------
#let cover(name, date, count, source, pending, note) = {
  v(1fr)
  block(width: 100%, {
    text(font: "Heiti SC", weight: "bold", size: 26pt)[#name]
    v(2mm)
    line(length: 100%, stroke: 1pt + conf.ink)
    v(2mm)
    set par(justify: false, leading: 0.9em)
    grid(
      columns: (auto, 1fr),
      column-gutter: 6mm,
      row-gutter: 2.2mm,
      lab("日期"), date,
      lab("题数"), [#count 题],
      lab("来源"), source,
      lab("待补"), if pending == 0 { "无（全部字段齐备）" } else { text(fill: conf.ink)[#pending 项字段待补，见索引表 ✎] },
    )
    if note != "" {
      v(4mm)
      text(size: 8pt, fill: conf.muted)[#note]
    }
    v(4mm)
    text(size: 7.6pt, fill: conf.faint)[
      用法：先在纸上独立完成，再对照「做法 / 考察 / 典型坑」复盘，最后勾选右侧掌握度并记录用时与得分。\
      题面已按「输入输出格式 / 样例 / 数据范围 原文照搬」压缩，完整题面见索引表链接。
    ]
  })
  v(1fr)
  pagebreak()
}

// ---------- 索引表 ----------
#let index-table(rows) = {
  text(font: "Heiti SC", weight: "bold", size: 13pt)[题目索引]
  v(1.5mm)
  tiny("题号 → 完整题面链接。卡片底部只印短标识，需要回连屏幕时查这张表。")
  v(2.5mm)
  set text(size: 8pt)
  table(
    columns: (auto, auto, 1fr, auto),
    inset: (x: 2.2mm, y: 1.4mm),
    align: (left, left, left, left),
    stroke: (x, y) => (top: if y == 0 { 0.6pt + conf.ink } else { 0pt }, bottom: 0.3pt + conf.faint),
    table.header(
      [*题号*], [*难度*], [*题面链接*], [*待补*],
    ),
    ..rows.map(r => (
      text(font: "Heiti SC", weight: "bold")[#r.sid],
      r.diff,
      link(r.url)[#r.url],
      if r.pending > 0 { text(fill: conf.muted)[#r.pending 项] } else { [—] },
    )).flatten(),
  )
  pagebreak()
}
