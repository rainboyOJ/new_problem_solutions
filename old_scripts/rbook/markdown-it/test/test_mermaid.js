import {md} from '../index.js';

const result = md.render(`
\`\`\`mermaid
graph TD
  A[Client] --> B[Load Balancer]
  B --> C[Server01]
  B --> D[Server02]
\`\`\`
`);

// 输出结果为 HTML 格式，其中包含 Mermaid 图表的渲染结果
console.log(result);