let destinos = [];
let destinosSeleccionados = [];

async function cargarDestinos() {
    try {
        const response = await fetch('ciudades_europeas_tsp(in).csv');
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        const data = await response.text();
        console.log('Contenido del CSV:', data);
        
        const rows = data.split('\n').slice(1);
        
        rows.forEach((row) => {
            const [ciudad, pais] = row.split(',').slice(0, 2);
            
            if (ciudad && pais) {
                destinos.push({
                    ciudad: ciudad.trim(),
                    pais: pais.trim(),
                });
            }
        });

        console.log('Destinos cargados:', destinos);
        mostrarDestinos(destinos);
    } catch (error) {
        console.error('Error al cargar destinos:', error);
    }
}

function mostrarDestinos(destinosFiltrados) {
    const contenedor = document.getElementById('destinosDisponibles');
    contenedor.innerHTML = '';

    destinosFiltrados.forEach((destino, index) => {
        const item = document.createElement('div');
        item.className = 'destino-item';
        item.draggable = true;
        item.ondragstart = (e) => drag(e, index);
        
        item.innerHTML = `<h6>${destino.ciudad}</h6><p>${destino.pais}</p>`;
        contenedor.appendChild(item);
    });
}

function allowDrop(event) {
    event.preventDefault();
}

function drag(event, index) {
    event.dataTransfer.setData('index', index);
}

function drop(event) {
    event.preventDefault();
    const index = event.dataTransfer.getData('index');
    
    if (destinosSeleccionados.length < 50) {
        destinosSeleccionados.push(destinos[index]);
        actualizarSeleccionados();
    } else {
        alert('Máximo 50 destinos seleccionados');
    }
}

function actualizarSeleccionados() {
    const contenedor = document.getElementById('destinosSeleccionados');
    contenedor.innerHTML = '';

    destinosSeleccionados.forEach((destino) => {
        const item = document.createElement('div');
        item.className = 'destino-item';
        
        item.innerHTML = `
            <h6>${destino.ciudad}</h6>
            <p>${destino.pais}</p>
        `;
        contenedor.appendChild(item);
    });

    document.getElementById('contador').textContent = destinosSeleccionados.length;

    if (destinosSeleccionados.length === 0) {
        contenedor.innerHTML = '<p class="text-muted">No se seleccionaron destinos</p>';
    }
}

document.getElementById('search').addEventListener('input', (e) => {
    const query = e.target.value.toLowerCase();
    const resultados = destinos.filter((destino) =>
        destino.ciudad.toLowerCase().includes(query) || destino.pais.toLowerCase().includes(query)
    );
    mostrarDestinos(resultados);
});

cargarDestinos();
