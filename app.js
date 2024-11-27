const express = require("express");
const mongoose = require("mongoose");
const cors = require("cors");

const app = express();


// Middleware
app.use(cors());

// Conectar a MongoDB
mongoose.connect("mongodb://localhost:27017/ciudades", {
  useNewUrlParser: true,
  useUnifiedTopology: true,
});

// Verificar conexión
mongoose.connection.on("connected", () => {
  console.log("Conectado a MongoDB");
});

mongoose.connection.on("error", (err) => {
  console.error("Error de conexión a MongoDB:", err);
});


// Definir el esquema para la colección `aeropuerto`
const AeropuertoSchema = new mongoose.Schema({
  _id: mongoose.Schema.Types.ObjectId,
  coordinates: {
    latitude: Number, // Latitud
    longitude: Number, // Longitud
  },
  country: String, // País
  distance_km: Number, // Distancia en kilómetros
  flight_hours: Number, // Horas de vuelo
  name: String, // Nombre de la ciudad o aeropuerto
  ticket_price_euros: Number, // Precio del boleto en euros
});

const Aeropuerto = mongoose.model("Aeropuerto", AeropuertoSchema, "aeropuerto");

// Endpoint para obtener los aeropuertos
app.get("/aeropuertos", async (req, res) => {
  try {
    const aeropuertos = await Aeropuerto.find();
    res.json(aeropuertos);
  } catch (error) {
    console.error("Error al obtener aeropuertos:", error);
    res.status(500).json({ error: "Error al obtener los aeropuertos" });
  }
});

// Iniciar servidor
app.listen(3001, () => {
  console.log(`Servidor corriendo en http://localhost:3001`);
});
