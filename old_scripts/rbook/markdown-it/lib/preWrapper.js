// markdown-it plugin for wrapping <pre> ... </pre>.
//
// If your plugin was chained before preWrapper, you can add additional eleemnt directly.
// If your plugin was chained after preWrapper, you can use these slots:
//   1. <!--beforebegin-->
//   2. <!--afterbegin-->
//   3. <!--beforeend-->
//   4. <!--afterend-->


const preWrapper= (language,rawCode) => {
    return `<!--beforebegin--><div class="language-${language} extra-class">` +
        `<!--afterbegin-->${rawCode}<!--beforeend--></div><!--afterend-->`
}

module.exports = md => {
    const fence = md.renderer.rules.fence
    md.renderer.rules.fence = (...args) =>{
        const [tokens, idx] = args
        const token = tokens[idx]
        const rawCode = fence(...args)
        const viz_reg = /^viz($|-\w+)/
        if(viz_reg.test(token.info.trim()))
            return `<div class="viz-contain">${rawCode}</div>`

        //mermaid
        if( token.info.trim() === 'mermaid')
        {
            return rawCode;
        }
        return preWrapper(token.info.trim(),rawCode)
    }
}
