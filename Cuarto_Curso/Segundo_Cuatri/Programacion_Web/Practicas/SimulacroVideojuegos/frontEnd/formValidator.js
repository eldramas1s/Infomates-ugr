

let form = document.getElementById("formVj");

if(form){
    const regexText = /^[A-Za-z0-9 ]+$/
    form.addEventListener("submit",(e)=>{
        e.preventDefault();
        let titulo = document.getElementById("titulo");
        let plataforma = document.getElementById("plataforma");
        if(!titulo.value || titulo.value.trim()==="" || !regexText.test(titulo.value)){
            alert("El título debe ser una cadena alfanumérica no vacía");
            location.href=location.href;
        }else if(!plataforma.value || plataforma.value.trim()==="" || !regexText.test(plataforma.value)){
            alert("La plataforma debe ser una cadena alfanumérica no vacía");
            location.href=location.href;
        }else{
            form.submit();
        }
    });
}
