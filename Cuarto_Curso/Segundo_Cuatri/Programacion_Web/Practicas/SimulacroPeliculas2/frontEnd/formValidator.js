
/////
//validacion del formulario
/////


let form = document.getElementById('formPelicula');
if(form){
    form.addEventListener("submit",(e)=>{
        e.preventDefault();

        let titulo = document.getElementById('titulo');
        const regexTitle = /^[A-Za-z0-9 ]+$/;
        
        if(!titulo.value || titulo.value.trim()==="" || !regexTitle.test(titulo.value)){
            alert("El título que ha introducido no es alfanumérico o está vacío");
            location.href = location.href;
        }else{
            form.submit();
        }
        
    })
}