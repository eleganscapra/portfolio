/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;

import java.io.*;
import java.util.List;

public class f_Gestion_Inventario {
    public f_Gestion_Inventario(String rutaArchivo, List<f_Inventario> lista) {
        try (BufferedReader lector = new BufferedReader(new FileReader(rutaArchivo))) {
            String linea;
            while ((linea = lector.readLine()) != null) {
                String[] bloques = linea.split("\\|");
                if (bloques.length == 4) {
                    try {
                        String codigo = bloques[0];
                        String farmaco = bloques[1];
                        int cantidad = Integer.parseInt(bloques[2]);
                        String concentracion = bloques[3];
                        f_Inventario inv = new f_Inventario(codigo, farmaco, cantidad, concentracion);
                        lista.add(inv);
                    } catch (NumberFormatException e) {
                        System.out.println("Error al convertir cantidad: " + bloques[2]);
                    }
                } else {
                    System.out.println("Línea mal formada: " + linea);
                }
            }
        } catch (IOException e) {
            System.out.println("Error al leer el archivo: " + e.getMessage());
        }
    }
}