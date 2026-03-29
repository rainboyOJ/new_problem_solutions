// let katex = require("katex")
// katex.defaultOptions.strict = 'throwOnError';
// let tt = katex.renderToString("中",{throwOnError:true,strict:true})
// console.log(tt)
//
import md from '../index.js'
import fs from 'fs'

let content = fs.readFileSync("./1.txt",{encoding:"utf-8"})
console.log(content)

let tt = md.render(content)
console.log(tt)
