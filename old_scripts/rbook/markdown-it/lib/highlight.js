import Prism from 'prismjs'

import loadLanguages from 'prismjs/components/index.js'
loadLanguages() //加载所有的语言模块

function escapeHtml (html) {
    return html.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/\u00a0/g, ' ')
}

// required to make embedded highlighting work...

function wrap (code, lang) {

    if (lang === 'text') {
        code = escapeHtml(code)
    }
    return `<pre class="language-${lang}"><code>${code}</code></pre>`
}

export default (str, lang) => {
    if (!lang) {
        return wrap(str, 'text',str)
    }
    lang = lang.toLowerCase()
    const rawLang = lang
    if (lang === 'vue' || lang === 'html') {
        lang = 'markup'
    }
    if (lang === 'md') {
        lang = 'markdown'
    }
    if (lang === 'ts') {
        lang = 'typescript'
    }
    if (lang === 'py') {
        lang = 'python'
    }
    if( lang === 'c++' ||  lang === 'c' || lang==="cpp"){
        lang = 'clike'
    }

    //mermaid
    if( lang === 'mermaid')
    {
        let _str = escapeHtml(str)
        return `<pre class="mermaid">${_str}</pre>`
    }

    const viz_reg = /^viz($|-\w+)/
    if(viz_reg.test(lang)){

        let _str = escapeHtml(str)
        return `<pre class="viz ${lang}"><code>${_str}</code></pre>`
    }

    if (!Prism.languages[lang]) {
        try {
            loadLanguages([lang])
        } catch (e) {
            console.error(`[markdown-r] Syntax highlight for language "${lang}" is not supported.`)
        }
    }
    if (Prism.languages[lang]) {
        const code = Prism.highlight(str, Prism.languages[lang], lang)
        return wrap(code, rawLang,str)
    }
    return wrap(str, 'text',str)
}
