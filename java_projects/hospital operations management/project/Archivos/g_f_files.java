/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Archivos;
import java.io.*;

public class g_f_files {
    String ruta, encabezado;

    public g_f_files(String ruta) {
        this.ruta = ruta;
    }
    
    public void crearArchivo(String encabezado){
        try { //manejo de excepciones
            File archivo = new File(this.ruta); //Enlace al archivo
            // Si el archivo no existe es creado
            if (!archivo.exists()) {
                archivo.createNewFile(); //Creamos el archivo
                FileWriter fw = new FileWriter(archivo); //Escribir en el archivo
                BufferedWriter bw = new BufferedWriter(fw);
                bw.write(encabezado); //Se agregan los encabezados
                bw.close(); //Cerrar el archivo
                this.encabezado = encabezado;
            }
        } catch (Exception e) {
            System.out.println("Error al crear el archivo");
        }
    }
    
    public void guardarDatos(String datos) {
        //Para 
        try {
            File archivo = new File(this.ruta); //Enlace al archivo
            FileWriter fw = new FileWriter(archivo, true); //guardar siempre en la última línea
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write("\n");
            bw.write(datos);
            bw.close();
            
        } catch (IOException ex) {
            System.out.println("Error al guardar datos");
        }
    }
    
    public String getRuta() {
        return ruta;
    }

    public void setRuta(String ruta) {
        this.ruta = ruta;
    }

    public String getEncabezado() {
        return encabezado;
    }

    public void setEncabezado(String encabezado) {
        this.encabezado = encabezado;
    }
    
    
}
