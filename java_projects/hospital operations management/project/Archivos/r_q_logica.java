/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Archivos;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.JOptionPane;
import java.io.BufferedReader;
import java.io.FileReader;



public class r_q_logica {
    public String nombres;
    public String apellidos;
    public String dni;
    public String fecha;

    // Constructor
    public r_q_logica(String nombres, String apellidos, String dni, String fecha) {
        this.nombres = nombres;
        this.apellidos = apellidos;
        this.dni = dni;
        this.fecha = fecha;
    }

    public static r_q_logica buscarPersonaEnArchivo(String rutaArchivo, String nombreBuscado) {
        try (BufferedReader lector = new BufferedReader(new FileReader("proyect_logs\\Área de Limpieza.txt"))) {
            String line;
            String nombres = "", apellidos = "", dni = "", fecha = "";
            while ((line = lector.readLine()) != null) {
                System.out.println("Leyendo línea: " + line);
                if (line.startsWith("Nombres: ")) {
                    nombres = line.substring(9).trim();
                    System.out.println("Nombres encontrados: " + nombres);
                } else if (line.startsWith("Apellidos: ")) {
                    apellidos = line.substring(11).trim();
                    System.out.println("Apellidos encontrados: " + apellidos);
                } else if (line.startsWith("DNI: ")) {
                    dni = line.substring(5).trim();
                    System.out.println("DNI encontrado: " + dni);
                } else if (line.startsWith("Fecha: ")) {
                    fecha = line.substring(7).trim();
                    System.out.println("Fecha encontrada: " + fecha);
                    if (!fecha.matches("\\d{2}/\\d{2}/\\d{4}")) {
                        System.out.println("Fecha inválida encontrada: " + fecha);
                        fecha = "";
                    }
                } else if (line.startsWith("---------------------------------")) {
                    if (nombres.equalsIgnoreCase(nombreBuscado.trim())) {
                        System.out.println("Persona encontrada: " + nombres + ", " + apellidos + ", " + dni + ", " + fecha);
                        return new r_q_logica(nombres, apellidos, dni, fecha);
                    }
                    nombres = "";
                    apellidos = "";
                    dni = "";
                    fecha = "";
                }
            }
        } catch (IOException e) {
            System.err.println("Error al leer el archivo: " + e.getMessage());
        }
        // Retornar null si no se encuentra la persona
        System.out.println("Persona no encontrada.");
        return null;
    }
    
    public static void registrarDatos(String nombres, String apellidos, String dni, String fecha) {
        r_q_logica logica = new r_q_logica(nombres, apellidos, dni, fecha);
        if (logica.guardarEnArchivo("proyect_logs\\Área de Limpieza.txt")) {
            JOptionPane.showMessageDialog(null, "Datos registrados correctamente.");
        } else {
            JOptionPane.showMessageDialog(null, "Error al guardar los datos.");
        }
    }
    
    public boolean guardarEnArchivo(String rutaArchivo) {
        try (BufferedWriter escritor = new BufferedWriter(new FileWriter(rutaArchivo, true))) {
            escritor.write("Nombres: " + nombres);
            escritor.newLine();
            escritor.write("Apellidos: " + apellidos);
            escritor.newLine();
            escritor.write("DNI: " + dni);
            escritor.newLine();
            escritor.write("Fecha: " + fecha);
            escritor.newLine();
            escritor.write("---------------------------------");
            escritor.newLine();
            return true;
        } catch (IOException e) {
            System.err.println("Error al guardar la información: " + e.getMessage());
            return false;
        }
    }
}