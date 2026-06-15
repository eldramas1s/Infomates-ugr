////////////////
// Gestionar el borrado
////////////////
let buttons = document.querySelectorAll(".eliminar");

if(buttons.length>0){
    buttons.forEach(button => {
        button.addEventListener("click",(e)=>{
            if(!confirm("¿Seguro que quieres borrar este videojuego?")){
                e.preventDefault();
                location.href = location.href;
            }
        })
    })
}