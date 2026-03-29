import rbook from './index.js';
import Markdown from './markdown.js';

// 测试rbook类
console.log('测试rbook类...');
const app = new rbook();
console.log('应用名称:', app.name);
console.log('配置:', app.config);

// 测试Markdown类
console.log('\n测试Markdown类...');
const md = new Markdown();

// 测试简单的Markdown解析
const testContent = `---
title: 测试标题
author: 测试作者
---

# 这是一个测试

这是一个测试段落，包含一些**粗体**和*斜体*文本。

- 列表项1
- 列表项2
- 列表项3
`;

const result = md.matter(testContent);
console.log('FrontMatter数据:', result.data);
console.log('Markdown内容:', result.content);
console.log('HTML内容:', md.html_content);