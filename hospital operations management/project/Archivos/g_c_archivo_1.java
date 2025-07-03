/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Archivos;
import hospital_arzobispo_loayza.g_C_Citas;
import hospital_arzobispo_loayza.g_C_SistemaCitas;
import java.io.*;

public class g_c_archivo_1 {
    private String ruta;
    private String encabezados;

    public g_c_archivo_1(String ruta) {
        this.ruta = ruta;
    }
    
    public void crearArchivo(String encabezados) {
        try {
            File archivo = new File(this.ruta); //File: Es lo que permite la operación de los archivos.
            if (!archivo.exists()) {
                archivo.createNewFile();
                try (BufferedWriter bw = new BufferedWriter(new FileWriter(archivo))) {
                    // BufferedWriter: Permite escribir textos
                    // FileWriter: Escribe en los archivo de textos
                    bw.write(encabezados);
                    bw.newLine();
                }
                this.encabezados = encabezados;
            }
        } catch (IOException e) {
            System.out.println("Error al crear el archivo: " + e.getMessage());
        }
    }
    
    public void guardarDatos(g_C_SistemaCitas sistemaCitas) {
        if (sistemaCitas.getScitas() == null || sistemaCitas.getScitas().isEmpty()) {
            System.out.println("No hay citas para guardar.");
            return;
        }
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(new File(this.ruta), true))) {
            for (g_C_Citas cita : sistemaCitas.getScitas()) {
                bw.write("Paciente: " + cita.getPaciente().getNombre() + " " + cita.getPaciente().getApellido());
                bw.newLine();
                bw.write("Especialidad: " + cita.getEspecialidad());
                bw.newLine();
                bw.write("Fecha: " + cita.getFecha());
                bw.newLine();
                bw.write("Hora: " + cita.getHora());
                bw.newLine();
                bw.write("\n"); // Separación entre citas
            }
        } catch (IOException ex) {
            System.out.println("Error al guardar datos: " + ex.getMessage());
        }
    }
    
    public String mostrarCitas() {
        String mensaje = "";
        File archivo = new File(this.ruta); // Ruta del archivo donde se guardan las citas
        if (!archivo.exists()) {
            return "No hay citas guardadas en el archivo.";
        }
        try (BufferedReader br = new BufferedReader(new FileReader(archivo))) {
            //BufferedReader: Permite leer lo escrito
            //FileReader: Lee los archivos de texto
            String linea;
            while ((linea = br.readLine()) != null) {
                mensaje += linea + "\n";  // Añadimos cada línea leída al mensaje
            }
        } catch (IOException ex) {
            System.out.println("Error al leer el archivo: " + ex.getMessage());
            return "Error al cargar las citas.";
        }
        return mensaje.isEmpty() ? "No hay citas para mostrar." : mensaje;
        //Si el mensaje es vacío, imprimirá el lo escrito entre comillas, si no retornara la variable mensaje 
    }
}