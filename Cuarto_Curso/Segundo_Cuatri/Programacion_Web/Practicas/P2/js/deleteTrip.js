//////////////////////////
// EVENT LISTENER PARA ADMIN
//////////////////////////

document.addEventListener("DOMContentLoaded",()=>{
    const buttons = document.querySelectorAll('.deleteButton');

    buttons.forEach(button =>{
        button.addEventListener('click',async (e)=>{
            e.preventDefault();
            //Obtenemos la tarjeta y las fechas necesarias
            const card = button.closest('.viajeTipo');
            const dateSelector = card.querySelector('.selectorFecha');
            const valueDate = dateSelector.value;

            if(valueDate==null || valueDate.trim()==="null" || valueDate.trim()===""){
                alert('Por favor, seleccione una fecha');
                return;
            }

            const [departureDate,returnDate] = valueDate.split(';');
            //Obtenemos la info con los data-*
            const continent = button.dataset.continent;
            const country = button.dataset.country;
            const place = button.dataset.place;
            //Pedimos confirmacion
            if(!confirm(`¿Seguro que quieres eliminar  viaje a ${place} del ${departureDate} ?`)){
                return;
            }

            //Hacemos la peticion fetch a la api;
            const endpoint = "../php/api/deleteDestiny.php";
            const response = await fetch(endpoint,{
                method:"POST",
                headers:{"Content-Type":"application/json"},
                body:JSON.stringify({
                    continent:continent,
                    country:country,
                    place:place,
                    departureDate:departureDate,
                    returnDate:returnDate
                })
            });

            if(!response.ok){
                throw new Error(`Error en la red: ${response.status}`);
            }

            //Si tenemos respuesta la obtenemos
            const json = await response.json();

            if(json.success){
                //Lo único que debemos hacer es recargar la página para notar el cambio
                alert(json.message);
                location.reload();
            }
            else{
                alert(json.message);
                window.location.href="../index.php";
            }
            
        });
    });
})