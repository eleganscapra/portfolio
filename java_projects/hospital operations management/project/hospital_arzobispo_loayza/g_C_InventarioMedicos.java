/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;

import java.util.ArrayList;

public class g_C_InventarioMedicos {
    ArrayList<g_C_Medico> listMedico;

    public g_C_InventarioMedicos() {
        listMedico = new ArrayList <g_C_Medico>();
    }
    
    public void agregarMedico(g_C_Medico medico){
        if(medico != null){
            listMedico.add(medico);
            System.out.println("La persona se agrego de forma exitosa");
            System.out.println("Médico: " + medico.getNombre() + " " + medico.getApellido() + " " + medico.getCodTrabajador() + " " + medico.getSalAtencion() + ".");
        } else {
            System.out.println("La cita no es válida");
        }
    }
    
    
    public void mostrarMedico(){
        System.out.println("Los médicos asociados al hospital: ");
        for(g_C_Medico medico: listMedico){
            System.out.println("- " + medico.getNombre() + " " + medico.getApellido() + " " + medico.getCodTrabajador() + " " + medico.getSalAtencion() + ".");
        }
    }
}
