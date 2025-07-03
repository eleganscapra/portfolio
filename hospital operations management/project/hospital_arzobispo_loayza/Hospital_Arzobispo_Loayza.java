package hospital_arzobispo_loayza;
import Interfaces.pagina_inicio;

public class Hospital_Arzobispo_Loayza {

    public static void main(String[] args) {
        g_C_SistemaCitas sistemacitas = new g_C_SistemaCitas();
        g_C_InventarioMedicos invemedico = new g_C_InventarioMedicos();
        pagina_inicio p_incio = new pagina_inicio();
        // Visible
        p_incio.setVisible(true);
        // Centrar
        p_incio.setLocationRelativeTo(null);
        // Maximizar
    }
}
