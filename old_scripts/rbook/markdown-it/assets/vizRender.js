//var viz = new Viz();
const viz_engine_list = [
    "viz-circo",
    "viz-dot",
    "viz-fdp",
    "viz-neato",
    "viz-osage",
    "viz-twopi"
]

$('pre.viz').each( function(){
    var viz = new Viz();
    var a = $(this).text()

    var Tdom = $(this)

    let list = Tdom.attr('class').split(/\s+/)
    let engine = 'dot'

    if( list[1]  && viz_engine_list.indexOf(list[1]) !== -1)
        engine = list[1].replace('viz-','')



    viz.renderSVGElement(a,{
            engine
    }).then(function(element) {
            //document.body.appendChild(element);
            Tdom.replaceWith(element)
    }).catch(error => {
            // Create a new Viz instance (@see Caveats page for more info)

            Tdom.before(`<p class="viz-error">${error.toString()}</p>`)
            // Possibly display the error
            console.error(error);
    });
})
