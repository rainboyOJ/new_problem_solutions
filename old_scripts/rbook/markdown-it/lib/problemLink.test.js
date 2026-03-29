import MarkdownIt from "markdown-it";
import problemLinkPlugin from "./problemLink.js";

// 创建 markdown-it 实例
const md = new MarkdownIt();

// 应用插件
md.use(problemLinkPlugin);

// 测试用例
const testCases = [
  '这是一个题目链接 [[problem: luogu,P1102]] 的例子',
  '多个链接 [[problem: hdu,5358]] 和 [[problem: poj,2566]]',
  '带空格的链接 [[problem: poj, 2566]]',
  '普通文本不应该被影响'
];

console.log('=== problemLink 插件测试 ===\n');

testCases.forEach((testCase, index) => {
  console.log(`测试 ${index + 1}:`);
  console.log('输入:', testCase);
  console.log('输出:', md.render(testCase));
  console.log('---\n');
});