/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

package hospital_arzobispo_loayza;

public class f_Medicamentos {
    String medicina,recetado,duracion;
    int cantidad;

    public f_Medicamentos(String medicina, String recetado, int cantidad, String duracion) {
        this.medicina = medicina;
        this.recetado = recetado;
        this.cantidad = cantidad;
        this.duracion = duracion;
        
    }

    public String getRecetado() {
        return recetado;
    }

    public void setRecetado(String recetado) {
        this.recetado = recetado;
    }

    public String getMedicina() {
        return medicina;
    }

    public void setMedicina(String medicina) {
        this.medicina = medicina;
    }

    public int getCantidad() {
        return cantidad;
    }

    public void setCantidad(int cantidad) {
        this.cantidad = cantidad;
    }
    public String getDuracion() {
        return duracion;
    }

    public void setDuracion(String duracion) {
        this.duracion = duracion;
    }

    public void mostrar_Medicamentos() {
        System.out.println("Medicina: " + this.medicina);
        System.out.println("Cantidad: " + this.cantidad);
        System.out.println("Cantidad: " + this.recetado);
        System.out.println("Duracion: " + this.duracion);
    }
}