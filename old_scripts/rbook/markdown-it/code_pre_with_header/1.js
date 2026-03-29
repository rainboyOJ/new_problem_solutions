var md = require("../index.js")
const fs = require("fs")
 
let raw = fs.readFileSync("./code.md",{encoding:'utf8'})
console.log(raw)

let html = md.render(raw).content
console.log(html)
