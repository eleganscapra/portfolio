/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;

public class g_F_c_habitacion {
    String cod = "";

    public g_F_c_habitacion(String c) {
        this.cod = c;
    }
    
    public String getC() {
        return cod;
    }

    public void setC(String c) {
        this.cod = c;
    }
    
    public boolean empty(String c){
        if (!c.isEmpty()) {
            return false;
        } else {
            return true;
        }
    }
}
