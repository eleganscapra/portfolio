/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;

public class g_C_Paciente extends g_C_Persona{
    private int numTelefono;     //Número de teléfono
    private String drcDomicilio; // Dirección de domicilio
    // Al poner private, usamos encapsulamiento
    
    public g_C_Paciente(int numTelefono, String drcDomicilio, String nombre, String apellido, int edad, int dni) {
        super(nombre, apellido, edad, dni);
        this.numTelefono = numTelefono;
        this.drcDomicilio = drcDomicilio;
    }

    public int getNumTelefono() {
        return numTelefono;
    }

    public void setNumTelefono(int numTelefono) {
        this.numTelefono = numTelefono;
    }

    public String getDrcDomicilio() {
        return drcDomicilio;
    }

    public void setDrcDomicilio(String drcDomicilio) {
        this.drcDomicilio = drcDomicilio;
    }

    @Override
    public String getNombre() {
        return super.getNombre();
    }

    @Override
    public void setNombre(String nombre) {
        super.setNombre(nombre);
    }

    @Override
    public String getApellido() {
        return super.getApellido();
    }

    @Override
    public void setApellido(String apellido) {
        super.setApellido(apellido);
    }

    @Override
    public int getEdad() {
        return super.getEdad();
    }

    @Override
    public void setEdad(int edad) {
        super.setEdad(edad);
    }

    @Override
    public int getDni() {
        return super.getDni();
    }

    @Override
    public void setDni(int dni) {
        super.setDni(dni);
    }
    
    
}
