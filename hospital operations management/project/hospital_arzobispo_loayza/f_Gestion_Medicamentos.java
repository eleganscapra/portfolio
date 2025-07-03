/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;

import java.io.*;
import java.util.*;

public class f_Gestion_Medicamentos {
    public void leerArchivo(String rutaArchivo, List<f_Medicamentos> lista) {
        try {
            BufferedReader lector = new BufferedReader(new FileReader(rutaArchivo));
            String linea;
            while ((linea = lector.readLine()) != null) {
                String[] bloques = linea.split("\\|");
                if (bloques.length == 4) {
                    try {
                        String medicina = bloques[0];
                        String recetado = bloques[1];
                        int cantidad = Integer.parseInt(bloques[2]);
                        String duracion = bloques[3]; 
                        if (medicina.equalsIgnoreCase("Seleccionar") || 
                            recetado.equalsIgnoreCase("Seleccionar") || 
                            cantidad <= 0 || 
                            duracion.equalsIgnoreCase("Seleccionar") || 
                            duracion.equalsIgnoreCase("null")) {
                            System.out.println("Línea inválida ignorada: " + linea);
                            continue; 
                        }
                        f_Medicamentos med = new f_Medicamentos(medicina, recetado, cantidad, duracion);
                        lista.add(med);
                    } catch (NumberFormatException e) {
                        System.out.println("Error al convertir cantidad: " + bloques[2]);
                    }
                } 
            }
            lector.close();
        } catch (IOException a) {
            System.out.println("Error al leer el archivo: " + a.getMessage());
        }
    }
}