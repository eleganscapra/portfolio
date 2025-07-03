/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;

public class g_C_Medico extends g_C_Persona{
    private int codTrabajador;  //Código de trabajador
    private String salAtencion; //Sala de atención
    private String especialidad;

    public g_C_Medico(int codTrabajador, String salAtencion, String especialidad, String nombre, String apellido, int edad, int dni) {
        super(nombre, apellido, edad, dni);
        this.codTrabajador = codTrabajador;
        this.salAtencion = salAtencion;
        this.especialidad = especialidad;
    }

    public int getCodTrabajador() {
        return codTrabajador;
    }

    public void setCodTrabajador(int codTrabajador) {
        this.codTrabajador = codTrabajador;
    }

    public String getSalAtencion() {
        return salAtencion;
    }

    public void setSalAtencion(String salAtencion) {
        this.salAtencion = salAtencion;
    }

    public String getEspecialidad() {
        return especialidad;
    }

    public void setEspecialidad(String especialidad) {
        this.especialidad = especialidad;
    }
    
}
