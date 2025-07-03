#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

class Archivo {
public:
    int n_registro;
    string fecha;
    string nombre_completo;
    string tipo_archivo;
    Archivo(int n_reg, string f, string nombre, string tipo) {
        n_registro = n_reg;
        fecha = f;
        nombre_completo = nombre;
        tipo_archivo = tipo;
    }
    void mostrar() {
        cout << "Imagen [" << n_registro << "] - " << fecha << " - " << nombre_completo << " - (" << tipo_archivo << ")" << endl;
    }
    string formato_txt() {
        return "Imagen [" + to_string(n_registro) + "] - " + fecha + " - " + nombre_completo + " - (" + tipo_archivo + ").jpg";
    }
};

class Nodo {
public:
    Archivo* archivo;
    Nodo* izq;
    Nodo* der;
    int altura;
    Nodo(Archivo* aux) {
        archivo = aux;
        izq = NULL;
        der = NULL;
        altura = 1;
    }
};

int altura(Nodo* aux) {
    if (aux != NULL) {
        return aux->altura;
    }
    else {
        return 0;
    }
}

int balance(Nodo* aux) {
    if (aux != NULL) {
        return altura(aux->izq) - altura(aux->der);
    }
    else {
        return 0;
    }
}

// ***
/* rotacion para la izquierda y la derecha */
Nodo* rotacion_izq(Nodo* x) {
    Nodo* y = x->der;
    Nodo* T2 = y->izq;
    y->izq = x;
    x->der = T2;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    return y;
}

Nodo* rotacion_der(Nodo* y) {
    Nodo* x = y->izq;
    Nodo* T2 = x->der;
    x->der = y;
    y->izq = T2;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    return x;
}
// ***

Nodo* nodo_min(Nodo* nodo) {
    Nodo* aux = nodo;
    while (aux->izq != NULL)
        aux = aux->izq;
    return aux;
}

Nodo* insertar(Nodo* aux, Archivo* archivo) {
    if (aux == NULL) {
        return new Nodo(archivo);
    }
    if (archivo->n_registro < aux->archivo->n_registro) {
        aux->izq = insertar(aux->izq, archivo);
    }
    else if (archivo->n_registro > aux->archivo->n_registro) {
        aux->der = insertar(aux->der, archivo);
    }
    else {
        return aux;
    }
    // se recalcula la altura para luego balancear el arbol
    aux->altura = 1 + max(altura(aux->izq), altura(aux->der));
    int balanceo = balance(aux);
    // se hacen las rotaciones en caso sean necesarias
    if (balanceo > 1 && archivo->n_registro < aux->izq->archivo->n_registro) {
        return rotacion_der(aux);
    }
    if (balanceo < -1 && archivo->n_registro > aux->der->archivo->n_registro) {
        return rotacion_izq(aux);
    }
    if (balanceo > 1 && archivo->n_registro > aux->izq->archivo->n_registro) {
        aux->izq = rotacion_izq(aux->izq);
        return rotacion_der(aux);
    }
    if (balanceo < -1 && archivo->n_registro < aux->der->archivo->n_registro) {
        aux->der = rotacion_der(aux->der);
        return rotacion_izq(aux);
    }
    return aux;
}

Nodo* eliminar(Nodo* raiz, int n_registro) {
    if (raiz == NULL) {
        return raiz;
    }
    if (n_registro < raiz->archivo->n_registro) {
        raiz->izq = eliminar(raiz->izq, n_registro);
    }
    else if (n_registro > raiz->archivo->n_registro) {
        raiz->der = eliminar(raiz->der, n_registro);
    }
    else {
        // nodo encontrado
        if ((raiz->izq == NULL) || (raiz->der == NULL)) {
            Nodo* temp{};
            if (raiz->izq != NULL) {
                Nodo* temp = raiz->izq;
            }
            else {
                raiz->der;
            }
            if (temp == NULL) {
                // nodo sin hijos
                temp = raiz;
                raiz = NULL;
            }
            else {
                // un hijo
                *raiz = *temp;
            }
            delete temp;
        }
        else {
            // ds hijos
            Nodo* temp = nodo_min(raiz->der);
            raiz->archivo = temp->archivo;
            raiz->der = eliminar(raiz->der, temp->archivo->n_registro);
        }
    }
    if (raiz == NULL) {
        return raiz;
    }
    raiz->altura = 1 + max(altura(raiz->izq), altura(raiz->der));
    int balanceo = balance(raiz);
    if (balanceo > 1 && balance(raiz->izq) >= 0) {
        return rotacion_der(raiz);
    }
    if (balanceo > 1 && balance(raiz->izq) < 0) {
        raiz->izq = rotacion_izq(raiz->izq);
        return rotacion_der(raiz);
    }
    if (balanceo < -1 && balance(raiz->der) <= 0) {
        return rotacion_izq(raiz);
    }
    if (balanceo < -1 && balance(raiz->der) > 0) {
        raiz->der = rotacion_der(raiz->der);
        return rotacion_izq(raiz);
    }
    return raiz;
}

// busqueda por numero de registro
Nodo* buscar(Nodo* aux, int n_registro) {
    if (aux == NULL) {
        return aux;
    }
    if (aux->archivo->n_registro == n_registro) {
        return aux;
    }
    if (n_registro < aux->archivo->n_registro) {
        return buscar(aux->izq, n_registro);
    }
    else {
        return buscar(aux->der, n_registro);
    }
}

// busqueda por nombre completo
void buscar(Nodo* aux, string name, string apellido, bool& encontrado) {
    if (aux == NULL) {
        return;
    }
    buscar(aux->izq, name, apellido, encontrado);
    if (aux->archivo->nombre_completo == (name + " " + apellido)) {
        aux->archivo->mostrar();
        encontrado = true;
    }
    buscar(aux->der, name, apellido, encontrado);
}

// busqueda por fecha
void buscar(Nodo* aux, int dia, int mes, bool& encontrado) {
    if (aux == NULL) {
        return;
    }
    buscar(aux->izq, dia, mes, encontrado);
    if (aux->archivo->fecha == ("[" + to_string(dia) + "/" + to_string(mes) + "/2025]")) {
        aux->archivo->mostrar();
        encontrado = true;
    }
    buscar(aux->der, dia, mes, encontrado);
}

void mostrar_nodos(Nodo* aux) {
    if (aux == NULL) {
        return;
    }
    mostrar_nodos(aux->izq);
    aux->archivo->mostrar();
    mostrar_nodos(aux->der);
}

void guardar_txt(Nodo* aux, ofstream& archivo) {
    if (aux == NULL) {
        return;
    }
    guardar_txt(aux->izq, archivo);
    archivo << aux->archivo->formato_txt() << endl;
    guardar_txt(aux->der, archivo);
}

// se asignan valores de manera aleatoria para la prueba
void asignacion_archivos(Nodo*& raiz, int cant) {
    string nombre_completo, fecha, tipo;
    string nombres[20] = { "James","Mary","Michael","Patricia","John","Jennifer","Robert","Linda","David","Elizabeth","William","Barbara","Richard","Susan","Joseph","Jessica","Thomas","Karen","Christopher","Sarah" };
    string apellidos[20] = { "Smith","Johnson","Williams","Brown","Jones","Garcia","Miller","Davis","Rodriguez","Martinez","Hernandez","Lopez","Gonzales","Wilson","Anderson","Thomas","Taylor","Moore","Jackson","Martin" };
    string t_archivo[3] = { "Tomografia", "Radiografia", "Resonancia" };
    srand(time(NULL));
    for (int i = 1; i <= cant; i++) {
        string nombre_completo = nombres[rand() % 20] + " " + apellidos[rand() % 20];
        string dia = to_string(rand() % 31 + 1);
        string mes = to_string(rand() % 12 + 1);
        string fecha = "[" + dia + "/" + mes + "/2025]";
        string tipo = t_archivo[rand() % 3];
        raiz = insertar(raiz, new Archivo(i, fecha, nombre_completo, tipo));
    }
}

int conteo(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return (1 + conteo(nodo->izq) + conteo(nodo->der));
}

void subir_archivo(Nodo* raiz, string ruta) {
    ofstream file(ruta);
    guardar_txt(raiz, file);
    file.close();
}

// se cargan los registros a partir de un archivo del sistema
void cargar_archivos(Nodo*& raiz, string ruta) {
    ifstream r_file(ruta);
    string txt;
    regex patron(R"(Imagen \[(\d+)\] - \[(\d{1,2}/\d{1,2}/\d{4})\] - (.+) - \((.+)\).jpg)");
    smatch coincidencias;
    while (getline(r_file, txt)) {
        if (regex_match(txt, coincidencias, patron)) {
            int numero = stoi(coincidencias[1]);
            string fecha = coincidencias[2];
            string nombre = coincidencias[3];
            string tipo = coincidencias[4];
            raiz = insertar(raiz, new Archivo(numero, fecha, nombre, tipo));
        }
    }
}

int main() {
    int cant, num, opc_proda, opc, opc_search, opc_eliminar, opc_visualizacion, dia, mes;
    string name, apellido;
    int dia_tmp, mes_tmp;
    string name_tmp, apellido_tmp, tipo_tmp;
    bool encon_nombre = false, encon_fecha = false;
    Nodo* raiz = NULL;
    Nodo* resultado;
    string ruta = "tomografias.txt";
    int opcion = 0;
    do {
        cout << "Desea empezar de cero o cargar un archivo de registros?\n(1) Desde cero\n(2) Cargar desde un archivo\nSu decision: ";
        cin >> opc_proda;
        switch (opc_proda) {
        case 1:
            cout << "Ingrese la cantidad de archivos para la prueba: ";
            cin >> cant;
            asignacion_archivos(raiz, cant);
            break;
        case 2:
            cout << "Se esta cargando los archivos de la ruta \"tomografias.txt\"... " << endl;
            cargar_archivos(raiz, ruta);
            break;
        default:
            cout << "Ha ocurrido un error. Intente de nuevo." << endl;
            cout << endl;
            break;
        }
    } while (opc_proda != 1 && opc_proda != 2);
    do {
        do {
            cout << "Bienvenido al menu del hospital, que desea hacer hoy?\nOpciones:\n(1) Buscar archivos\n(2) Agregar un archivo\n(3) Eliminar un archivo\n(4) Visualizar archivos\n(0) Salir\nSu decision: ";
            cin >> opc;
            cout << endl;
            switch (opc) {
            case 1:
                // opcion de buscar
                do {
                    cout << "Bienvenido al panel de busqueda, que archivo desea buscar hoy?\nBuscar por: \n(1) Numero de registro\n(2) Fecha\n(3) Nombres y apellidos\n(0) Salir\nSu decision: ";
                    cin >> opc_search;
                    switch (opc_search) {
                    case 0:
                        cout << endl;
                        break;
                    case 1:
                        // numero de registro
                        cout << "Ingrese el numero de la imagen que desea buscar: ";
                        cin >> num;
                        cout << endl;
                        resultado = buscar(raiz, num);
                        if (resultado != NULL) {
                            resultado->archivo->mostrar();
                        }
                        else {
                            cout << "Archivo no encontrado. No existe un archivo registrado con el numero: " << num << endl;
                        }
                        resultado = NULL;
                        cout << endl;
                        break;
                    case 2:
                        // fecha
                        cout << "Ingrese el dia: ";
                        cin >> dia;
                        cout << "Ingrese el mes: ";
                        cin >> mes;
                        cout << endl;
                        buscar(raiz, dia, mes, encon_fecha);
                        if (!encon_fecha) {
                            cout << "Archivo(s) no encontrado. No existe un archivo registrado con la fecha: [" << dia << "/" << mes << "/2025]" << endl;;
                        }
                        cout << endl;
                        break;
                    case 3:
                        // nombres y apellidos
                        cout << "Ingrese el nombre: ";
                        cin >> name;
                        cout << "Ingrese el apellido: ";
                        cin >> apellido;
                        cout << endl;
                        buscar(raiz, name, apellido, encon_nombre);
                        if (!encon_nombre) {
                            cout << "Archivo(s) no encontrado. No existe un archivo registrado con el nombre completo del paciente: " << name << " " << apellido << endl;
                        }
                        cout << endl;
                        break;
                    default:
                        cout << "Opcion invalida. Intente de nuevo." << endl;
                        cout << endl;
                        break;
                    }
                } while (opc_search != 1 && opc_search != 2 && opc_search != 3 && opc_search != 0);
                break;
            case 2:
                // opcion de agregar
                cout << "Bienvenido al panel de insercion de archivos. \nIngrese el dia: ";
                cin >> dia_tmp;
                cout << "Ingrese el mes: ";
                cin >> mes_tmp;
                cout << "Ingrese el nombre de la persona: ";
                cin >> name_tmp;
                cout << "Ingrese el apellido de la persona: ";
                cin >> apellido_tmp;
                cout << "Ingrese el tipo de archivo: ";
                cin >> tipo_tmp;
                insertar(raiz, new Archivo(conteo(raiz) + 1, "[" + to_string(dia_tmp) + "/" + to_string(mes_tmp) + "/2025]", name_tmp + " " + apellido_tmp, tipo_tmp));
                subir_archivo(raiz, ruta);
                cout << endl;
                break;
            case 3:
                // opcion de eliminar
                cout << "Bienvenido al panel de eliminacion de archivos\nIngrese el numero de registro [X] que desee eliminar: ";
                cin >> opc_eliminar;
                cout << endl;
                raiz = eliminar(raiz, opc_eliminar);
                subir_archivo(raiz, ruta);
                cout << "Archivo eliminado con exito." << endl;
                cout << endl;
                break;
            case 4:
                // ver archivos
                cout << "Bienvenido al panel de visualizacion de archivos\nActualmente se encuentran registrados [" << conteo(raiz) << "] archivos. Desea visualizarlos?\n(1) Si\n(2) No\nSu decision: ";
                cin >> opc_visualizacion;
                cout << endl;
                if (opc_visualizacion == 1) {
                    mostrar_nodos(raiz);
                    cout << endl;
                    break;
                }
                else if (opc_visualizacion == 2) {
                    break;
                }
                else {
                    cout << "Ha ocurrido un error. Intente de nuevo." << endl;
                    break;
                }
            case 0:
                cout << "Gracias por su preferencia. Hasta luego." << endl;
                subir_archivo(raiz, ruta);
                cout << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                cout << endl;
                break;
            }
        } while (opc != 1 && opc != 2 && opc != 3 && opc != 0);
    } while (opc != 0);
}