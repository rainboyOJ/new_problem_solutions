module.exports = function(md){

    md.renderer.rules.heading_open= function(tokens,idx){
        return `<${tokens[idx].tag} class="">`

    }
    md.renderer.rules.heading_close = function(tokens,idx){
        return `</${tokens[idx].tag}>`
    }
}
