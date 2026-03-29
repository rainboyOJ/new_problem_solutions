var md = require("..")
var pug = require("pug")
var fs = require("fs")
var pathFn = require("path")
var { exec,spawn} = require("child_process")

let watch_files = ["index.pug",'demo.md']
var debug = console.log

function render(){
        var markdown = fs.readFileSync(`${__dirname}/demo.md`,{
            encoding:'utf-8'
        })
        return md(markdown)
        
        // var html = pug.renderFile(pathFn.join(__dirname,"index.pug"),{
        //     markdown:markdown,
        //     html: md.render(markdown)
        // })
        // debug("渲染 index.html")
        // fs.writeFileSync(__dirname+'/output/index.html', html)
}

let ret = render()
console.log(ret)

// for( let file of watch_files ){
//     fs.watchFile(pathFn.join(__dirname,file),{
//         interval:200
//     }, ()=>{
//         render()
//     })
// }
//
// const staticPath = [
//     pathFn.join(__dirname,'../assets'),
//     pathFn.join(__dirname,'output')
// ]
//
// var ls = spawn('browser-sync',['start','--ss','../../assets','--server',`--files`,`index.html,*.css`,'--no-open'],{
//     cwd:`${__dirname}/output`,
//     stdio:['inherit','inherit','inherit']
// })
//
// const scss = [
// `${__dirname}/style.scss`,
// `${__dirname}/../assets/markdown-r.scss`,
// ]
// spawn('node-sass',[`-w`,scss[1],`-o`,`${__dirname}/../assets`],{
//     stdio:['inherit','inherit','inherit']
// })
//
// spawn('node-sass',[`-w`,scss[1],`-o`,`${__dirname}/output`],{
//     stdio:['inherit','inherit','inherit']
// })
