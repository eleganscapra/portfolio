/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package hospital_arzobispo_loayza;
import java.util.ArrayList;

public class g_C_Hospital {
    private final String nomInstitucion;
    private final String direccion;
    private final int numTelefono;
    private final String correo;
    

    public g_C_Hospital() {
        this.nomInstitucion = "Arzobispo_Loayza";
        this.direccion = "Av.Alfonso_Ugarte_848";
        this.numTelefono = 5094800;
        this.correo = "mesadepartes@hospitalloayza.gob.pe";
        
    }

    public String getCorreo() {
        return correo;
    }


    public String getNomInstitucion() {
        return nomInstitucion;
    }


    public String getDireccion() {
        return direccion;
    }


    public int getNumtelfono() {
        return numTelefono;
    }

    
    public String mostrarDatos(){
        String datos = "Institución: " + nomInstitucion + "\n" +
                       "Dirección: " + direccion + "\n" +
                       "Teléfono: " + numTelefono + "\n" +
                       "Correo: " + correo;
        return datos;
    }
    
    
}
