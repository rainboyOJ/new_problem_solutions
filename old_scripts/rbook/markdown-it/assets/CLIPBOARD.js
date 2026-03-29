window.CLIPBOARD = function(self){
    let content = self.parentElement.children[1].textContent
    clipboard.writeText(content).then(function(){

        self.innerHTML = 'copied!'
        setTimeout(function(){
            self.innerHTML = 'copy'
        },1000)

    },function(){
        self.innerHTML = 'copy failed!'
    })
}
