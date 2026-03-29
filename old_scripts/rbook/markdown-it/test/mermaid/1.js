var md = require("./index.js")
var fs = require("fs")

var t = fs.readFileSync("./1.md",{encoding:"utf8"})
console.log(t)

var tt = md.render(t)
console.log(tt)
