/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JOptionPane;

public class f_SincronizarInventario {
  public static boolean actualizarInventario(String medicamento, int cantidadARestar, String rutaInventario) {
        List<String> lineas = new ArrayList<>();
        boolean encontrado = false;

        try (BufferedReader br = new BufferedReader(new FileReader(rutaInventario))) {
            String linea;

            while ((linea = br.readLine()) != null) {
                String[] partes = linea.split("\\|");
                if (partes.length >= 3 && partes[1].equalsIgnoreCase(medicamento)) {
                    encontrado = true;
                    int cantidadActual = Integer.parseInt(partes[2]); 
                    if (cantidadActual < cantidadARestar) {
                        JOptionPane.showMessageDialog(null, "No hay suficiente cantidad en el inventario para " + medicamento,
                                "Error", JOptionPane.ERROR_MESSAGE);
                        return false;
                    }                 
                    partes[2] = String.valueOf(cantidadActual - cantidadARestar);
                    linea = String.join("|", partes);
                }

                lineas.add(linea); 
            }
        } catch (IOException e) {
            System.err.println("Error al leer el archivo de inventario: " + e.getMessage());
        }
        // Si no se encontró el medicamento, mostrar error
        if (!encontrado) {
            JOptionPane.showMessageDialog(null, "El medicamento " + medicamento + " no se encuentra en el inventario.",
                    "Error", JOptionPane.ERROR_MESSAGE);
            return false;
        }
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(rutaInventario))) {
            for (String linea : lineas) {
                bw.write(linea);
                bw.newLine();
            }
        } catch (IOException e) {
            System.err.println("Error al escribir en el archivo de inventario: " + e.getMessage());
            return false;
        }

        return true; 
    }
}