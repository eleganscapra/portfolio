/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;

public class g_C_Citas {
    private g_C_Paciente paciente;
    private String especialidad;
    private String fecha;
    private String hora;

    public g_C_Citas(g_C_Paciente paciente, String especialidad, String fecha, String hora) {
        this.paciente = paciente;
        this.especialidad = especialidad;
        this.fecha = fecha;
        this.hora = hora;
    }

    public String getHora() {
        return hora;
    }

    public void setHora(String hora) {
        this.hora = hora;
    }

    public String getFecha() {
        return fecha;
    }

    public void setFecha(String fecha) {
        this.fecha = fecha;
    }

    public g_C_Paciente getPaciente() {
        return paciente;
    }

    public void setPaciente(g_C_Paciente paciente) {
        this.paciente = paciente;
    }

    public String getEspecialidad() {
        return especialidad;
    }

    public void setEspecialidad(String especialidad) {
        this.especialidad = especialidad;
    }
    

}
