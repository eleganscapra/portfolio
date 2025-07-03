/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;

public class g_F_compras {
    String nombre;
    int precio, q;
    double imp_pago;

    public g_F_compras(String nombre, int precio, int q, double imp_pago) {
        this.nombre = nombre;
        this.precio = precio;
        this.q = q;
        this.imp_pago = imp_pago;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public int getPrecio() {
        return precio;
    }

    public void setPrecio(int precio) {
        this.precio = precio;
    }

    public int getQ() {
        return q;
    }

    public void setQ(int q) {
        this.q = q;
    }

    public double getImp_pago() {
        return imp_pago;
    }

    public void setImp_pago(double imp_pago) {
        this.imp_pago = imp_pago;
    }
    
    
}
