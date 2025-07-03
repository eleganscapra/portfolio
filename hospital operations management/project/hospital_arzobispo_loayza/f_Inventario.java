/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;

public class f_Inventario {

    String codigo,farmaco,concentracion;
    int cantidad;

    public String getCodigo() {
        return codigo;
    }

    public void setCodigo(String codigo) {
        this.codigo = codigo;
    }

    public String getFarmaco() {
        return farmaco;
    }

    public void setFarmaco(String farmaco) {
        this.farmaco = farmaco;
    }

    public String getConcentracion() {
        return concentracion;
    }

    public void setConcentracion(String concentracion) {
        this.concentracion = concentracion;
    }

    public int getCantidad() {
        return cantidad;
    }

    public void setCantidad(int cantidad) {
        this.cantidad = cantidad;
    }

    public f_Inventario(String codigo, String farmaco, int cantidad, String concentracion) {
        this.codigo = codigo;
        this.farmaco = farmaco;
        this.concentracion = concentracion;
        this.cantidad = cantidad;
    }
public void mostrar_Inventario() {
        System.out.println("Codigo: " + this.codigo);
        System.out.println("Farmaco: " + this.farmaco);
        System.out.println("Cantidad: " + this.cantidad);
        System.out.println("Concentracion: " + this.concentracion);
    }
}