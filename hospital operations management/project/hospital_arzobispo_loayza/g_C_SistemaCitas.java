/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;
import java.util.ArrayList;

public class g_C_SistemaCitas {
    ArrayList<g_C_Citas> scitas;

    public g_C_SistemaCitas() {
        scitas = new ArrayList<g_C_Citas>();
    }

    public ArrayList<g_C_Citas> getScitas() {
        return scitas;
    }

    public void setScitas(ArrayList<g_C_Citas> scitas) {
        this.scitas = scitas;
    }
    
    public void agregarCita (g_C_Citas cita){
        if(cita != null){
            scitas.add(cita);
        } else {
            System.out.println("La cita no es válida");
        }
    }
    
    public String mostrarCitas(){
        String mensaje = "";
        System.out.println("Lista de Citas:");
        for(g_C_Citas cita: scitas){
            mensaje += "Paciente: " + cita.getPaciente().getNombre() + " " + cita.getPaciente().getApellido() + "\n"
                 + "Especialidad: " + cita.getEspecialidad() + "\n"
                 + "Fecha: " + cita.getFecha() + "\n"
                 + "Hora: " + cita.getHora() + "\n\n";
        }
        return mensaje;
    }
}
