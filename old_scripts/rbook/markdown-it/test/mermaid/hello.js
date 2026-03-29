const mermaid = require('@mermaid-js/mermaid-cli');
const fs = require('fs');

const mermaidCode = `
graph TD;
    A-->B;
    A-->C;
    B-->D;
    C-->D;
`;

mermaid.render('diagram.png', mermaidCode, (err, svg) => {
  if (err) {
    console.error(err);
    return;
  }

  fs.writeFileSync('diagram.png', svg);
  console.log('Diagram saved as diagram.png');
});


