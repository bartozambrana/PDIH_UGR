#Establecemos el escritorio de ejecución

setwd("C:/Users/UX430U/OneDrive/CUARTO_CURSO/PDIH/Practicas_y_Seminarios/P5")

#Cargamos las librerías
install.packages("tuneR")
install.packages("seewave")
install.packages("audio")
library(tuneR)
library(seewave)
library(audio)


# Leemos el audio del perro.
perro <- readWave('S-varios-sonidos/perro.wav')

# Leemos el audio del gato.
gato  <- readMP3('./S-varios-sonidos/gato.mp3')

#Obtenemos la duración de cada audio.
duracion_perro <- round(length(perro@left) / perro@samp.rate, 3)
duracion_gato  <- round(length(gato@left) / gato@samp.rate, 3)

#Dibujamos la forma de onda del gato
longitud_gato <- gato@right
plot(extractWave(gato,from = 1, to = length(longitud_gato)))

#Dibujamos la forma de onda del perro
longitud_perro <- perro@right
plot(extractWave(perro,from = 1, to = length(longitud_perro)))

#Información de cabecera gato.
str(gato)

#Información de cabecera perro.
str(perro)

# Unimos ambos sonidos.
unido <- pastew(perro,gato,output = "Wave")

#Cabecera del unido
str(unido)

#Comprobamos que coinciden en longitud
if(length(unido@left) == length(longitud_gato) + length(longitud_perro)){
  
  print("coinciden en longitud")
  
}else{
  
  print("no coinciden en longitud") 

  }

#Mostramos la onda de los unidos.
plot(extractWave(unido,from = 1, to = length(unido@left)))


# 6 Pasarle un filtro de frecuencia para eliminar las frecuencias entre 10000Hz y
# 20000Hz
unido_filtrado <- bwfilter(unido, n=1, from = 10000, to = 20000,
                           bandpass = TRUE, listen = FALSE, output = "Wave")
plot(extractWave(unido_filtrado, from = 1, to = length(unido_filtrado@left)))

# 7. Almacenar la señal obtenida como un fichero WAV denominado "mezcla.wav".
writeWave(unido_filtrado, file.path("S-varios-sonidos/mezcla.wav"))

# 8. Cargar un nuevo archivo de sonido, aplicarle eco y a continuación darle la
# vuelta al sonido. Almacenar la señal obtenida como un fichero WAV
# denominado "alreves.wav"
sicut <- readMP3("S-varios-sonidos/sicut_locutus_est.mp3")
sicutECO <- echo(sicut,f=22050,
                amp=c(0.8,0.4,0.2),
                delay=c(1,2,3), 
                output="Wave")
sicutECO@left <- 10000 * sicutECO@left
# listen(sicutECO , f= 22050)
# str(sicutECO)

# dar la vuelta al sonido
alreves <- revw(sicutECO, output = "Wave")

# escribir en un nuevo WAV el resultado
writeWave(alreves, file.path("S-varios-sonidos/alreves.wav"))

