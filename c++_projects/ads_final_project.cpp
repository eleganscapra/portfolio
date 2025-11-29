#include <iostream>
#include <fstream>   // manejo de archivos
#include <string>	 // funciones para variables de tipo string
#include <vector>
#include <unordered_map>
#include <algorithm> // se utiliza en la implementacion de BTreeNode
// esto forma parte de las librerias para cargar los datos desde el disco
#include <iomanip>   // setw, setfill
#include <cstdint>   // uint32_t
#include <filesystem>// funciones para archivos (remove(), rename())
#include <chrono>	 // para medir el tiempo de ejecucion de las funciones principales

using namespace std;
namespace fs = std::filesystem;
using namespace std::chrono;

static const int ndigit = 6; // la cantidad de digitos en el prefijo, 0.dat = ndigit : 1 / 00.dat = ndigit : 2, etc

// se implemento una estructura de la direccion, de modo que se pueda tener un formato general para todos los registros:
// ejemplo: [distrito], [ciudad], [provincia], [departamento]
struct Direccion {
    string departamento;
    string provincia;
    string ciudad;
    string distrito;

    string formato() const {
        return distrito + ", " + ciudad + ", " + provincia + ", " + departamento;
    }
};

struct Ciudadano {
    string dni; // a pesar de ser un numero, para evitar problemas con dnis que empiecen con 0, se coloca como un string
    string nombres;
    string nacionalidad;
    string nacimiento;
    Direccion direccion; // formato general explicado hace un momento
    string telefono;
    string correo;
    string estado_civil;
};

/*
Buen dia, el programa funciona usando archivos binarios .dat
la manera en como se almacenan los datos es en que cada dato de texto
como: nombre, nacionalidad, direccion, etc. Se guarda al costado de un numero entero
que indica la longitud de la cadena, esto permite saber exactamente cuantos
byes se deben leer para reconstruir la cadena, de modo que se evita
combinar datos de otras personas, sino se generarian datos combinados
entre una persona A y una persona B dentro del registro de la persona A.
Lo que no es correcto
*/

string leer_cadena(ifstream &f) {
    uint32_t len = 0;
    if (!f.read(reinterpret_cast<char*>(&len), sizeof(len))) {
        return string();
    }
    if (len == 0) return string();
    string s;
    s.resize(len);
    if (!f.read(&s[0], static_cast<std::streamsize>(len))) {
        return string(); // si es que la cadena de texto no contiene nada, devolver la cadena vacia
    }
    return s;
}

Ciudadano leer_ciudadano(ifstream &f) {
    Ciudadano c;
    uint32_t dni_num = 0;
    // leer dni_num (uint32_t)
    if (!f.read(reinterpret_cast<char*>(&dni_num), sizeof(dni_num))) {
        c.dni = ""; // si no se puede leer la cadena, asigna el valor del dni a "", lo que indica un error
        return c;
    }
    // rellenar con 0s a la izquierda en los dnis
    // ejemplo: si existe un dni "48182", no se podria interpretar de esa forma
    // lo que se debe de hacer es colocar 0s a la izquierda para que cumpla con
    // el formato de 8 digitos, lo que lo convierte a "00048182"
    {
        ostringstream oss;
        oss << setw(8) << setfill('0') << dni_num;
        c.dni = oss.str();
    }
	
	// se leen los datos del ciudadano
	// se uso una estructura ternaria por la facilidad y comodidad personal
	// lo que hacen es revisar que el archivo de lectura este operativo, 
	// en caso de que no este disponible, se asigan la cadena al vacio y termina el proceso
	// no deberia pasar, pero es una forma de verificar que todo esta en orden
	c.nombres = leer_cadena(f); if (!f) { c.dni = ""; return c; }
    c.nacionalidad = leer_cadena(f); if (!f) { c.dni = ""; return c; }
    c.nacimiento = leer_cadena(f); if (!f) { c.dni = ""; return c; }
    c.direccion.departamento = leer_cadena(f); if (!f) { c.dni = ""; return c; }
    c.direccion.provincia = leer_cadena(f); if (!f) { c.dni = ""; return c; }
    c.direccion.ciudad = leer_cadena(f); if (!f) { c.dni = ""; return c; }
    c.direccion.distrito = leer_cadena(f); if (!f) { c.dni = ""; return c; }
    c.telefono = leer_cadena(f); if (!f) { c.dni = ""; return c; }
    c.correo = leer_cadena(f); if (!f) { c.dni = ""; return c; }
    c.estado_civil = leer_cadena(f); if (!f) { c.dni = ""; return c; }

    return c;
}

struct BTreeNode {
	// codigo desarrollado en clase
    int t;
    bool leaf;
    vector<string> keys;
    vector<Ciudadano> data;
    vector<BTreeNode*> C;

    BTreeNode(int _t, bool _leaf) : t(_t), leaf(_leaf) {} // constructor
	// destructor: libera recursivamente todos los nodos hijos para evitar fugas de memoria
	~BTreeNode() {
		for (auto child : C) {
			delete child;
		}
	}
	// bool isFull() { return keys.size() == 2 * t - 1; }
    bool isFull() { return keys.size() == static_cast<size_t>(2 * t - 1); }
    // se utilizo el casteo estatico porque mostraba un error en consola

    Ciudadano* search(string k) {
        size_t i = lower_bound(keys.begin(), keys.end(), k) - keys.begin();
        if (i < keys.size() && keys[i] == k) return &data[i];
        if (leaf) return nullptr;
        return C[i]->search(k);
    }

    void insertNotFull(const Ciudadano& c) {
        string k = c.dni;
        if (leaf) {
            auto it = lower_bound(keys.begin(), keys.end(), k);
            if (it != keys.end() && *it == k) return;
            size_t pos = it - keys.begin();
            keys.insert(it, k);
            data.insert(data.begin() + pos, c);
        } else {
            int i = 0;
            while (i < static_cast<int>(keys.size()) && k > keys[i]) i++;
            if (C[i]->isFull()) {
                splitChild(i);
                if (k > keys[i]) i++;
            }
            C[i]->insertNotFull(c);
        }
    }

    void splitChild(int i) {
        BTreeNode* y = C[i];
        BTreeNode* z = new BTreeNode(y->t, y->leaf);
        string mid_key = y->keys[t - 1];
        Ciudadano mid_data = y->data[t - 1];

        z->keys.assign(y->keys.begin() + t, y->keys.end());
        z->data.assign(y->data.begin() + t, y->data.end());
        y->keys.resize(t - 1);
        y->data.resize(t - 1);

        if (!y->leaf) {
            z->C.assign(y->C.begin() + t, y->C.end());
            y->C.resize(t);
        }

        C.insert(C.begin() + i + 1, z);
        keys.insert(keys.begin() + i, mid_key);
        data.insert(data.begin() + i, mid_data);
    }

    void inOrder() { // esta funcion imprime los valores de los nodos
        size_t i = 0;
        for (; i < keys.size(); i++) {
            if (!leaf) C[i]->inOrder();
            cout << keys[i] << " ";
        }
        if (!leaf) C[i]->inOrder();
    }
    
    void remove(string k){
		size_t i = lower_bound(keys.begin(), keys.end(), k) - keys.begin(); // estructura similar que a la funcion de buscar
        if (i < keys.size() && keys[i] == k){
			if (leaf){ // sin embargo, la diferencia entra en que en caso la clave este en el nodo leaf, se borre - Caso I
				keys.erase(keys.begin() + i);
				data.erase(data.begin() + i);
			} else {
				// Caso II - en el caso de que no sea directamente una hoja y este metido entre las ramas,
				// lo que se hizo fue iterar por los nodos
				BTreeNode* tmp = C[i + 1]; // nodo temporal
				while (!tmp->leaf) tmp = tmp->C.front(); // iteramos las subramas del nodo, siempre y cuando no sea hoja, que en este 
														 // caso despues de pasar la anterior condicional, se deberia de cumplir siempre
				keys[i] = tmp->keys.front(); // se actualizan las keys
				data[i] = tmp->data.front(); // se actualiza data
				C[i + 1]->remove(tmp->keys.front());
			}
		} else if (!leaf) {
			C[i]->remove(k); // operacion recursiva para buscar el nodo correcto y eliminarlo
		} else {
			// en caso de que no llegue a existir el registro
			cout << "Ha ocurrido un error, no se encontro el registro a eliminar." << endl;
		}
	}
};

class BTree {
	// codigo desarrollado en clase
	private:
		BTreeNode* root;
		int t;
	public:
		BTree(int _t) : root(nullptr), t(_t) { // constructor
			if (t < 2) throw runtime_error("El grado minimo debe ser de t >= 2");
		}
		~BTree() { // destructor
			delete root;  // libera todo el arbol desde la raíz
		}				  // de nuevo, eso se usa para luego poder liberar la memoria ram
		void insert(Ciudadano c) {
			if (!root) { // similar al codigo de la clase, en caso el arbol este vacio
				root = new BTreeNode(t, true); // se crea la raiz en un nuevo nodo
				root->keys.push_back(c.dni); // y se agrega el dni de las personas (Ciudadano)
				root->data.push_back(c);
				return;
			}
			if (contains(c.dni)) return; // se verifica si ya existe un registro con aquel dni
			if (root->isFull()) { // cuando se llene el nodo, ejecuta splichild para reordenar los nodos y balancear el arbol
				BTreeNode* s = new BTreeNode(t, false);
				s->C.push_back(root);
				s->splitChild(0);
				int i = (c.dni > s->keys[0]) ? 1 : 0;
				s->C[i]->insertNotFull(c);
				root = s;
			} else {
				root->insertNotFull(c);
			}
		}
	
		bool contains(string dni) {
			if (!root) return false;
			return root->search(dni) != nullptr; // explicado anteriormente, siempre y cuando sea diferente a nullptr
												 // significa que existe algo ahi
		}

		Ciudadano* search(string dni) { // funcion recursiva a la que hace referencia la funcion "contains",
										// se encarga de justamente buscar si esta ahi o no
			if (!root) return nullptr;
			return root->search(dni);
		}

		void imprimir() { // se modifico esta funcion para usarlo como prueba de que funcionaba a menor escala,
						  // pero a estas alturas con 33 millones de datos, dependiendo de la cantidad de modulos
						  // que se use, podria no ser tan util, solo sirve para mostrar lo que hay dentro
			if (!root) { cout << "Arbol vacio" << endl; return; }
			root->inOrder();
			cout << endl;
		}
		
		void remove(string dni) { // funcion para eliminar un registro a partir del dni
            if (!root) {
                cout << "El arbol esta vacio." << endl; // una verificacion para saber que el arbol no esta vacio 
                return;
            }
            root->remove(dni); // funcion recursiva, y en caso en la raiz no quede nada que coincida con el resultado...
            if (root->keys.empty() && !root->leaf) {
                root = root->C[0]; // reajustamos 
            }
        }
};

class Registro {
	private:
		unordered_map<string, BTree*> tabla; // tabla hash en la que el arbol sea la clave, 
											 // y los dos primeros caracteres de un dni sean el indice
		int gradoB;
		string obtener_prefijo(string dni) {
			if (dni.size() < ndigit) return string(ndigit - dni.size(), '0') + dni; // si el DNI es demasiado corto, 
																					// completar a la izquierda con ceros
			return dni.substr(0,ndigit); // se saca los dos primeros caracteres de un dni
		}
	public:
		Registro(int t = 8) : gradoB(t) {} // el grado que se esta usando para el arbol B es 8
		
		void registrar(Ciudadano& c) { // funcion que opera en memoria, no en disco
			string pref = obtener_prefijo(c.dni); // funcion de conseguir los dos primeros caracteres
			if (tabla.find(pref) == tabla.end()) { // para luego verificar si es que no hay nada creado en ese indice todavia
				tabla[pref] = new BTree(gradoB); // y crear justamente un nuevo arbol en ese indice
			}
			tabla[pref]->insert(c); // sino, solamente agregarlo a ese indice
		}

		void buscar(string dni) {
			string pref = obtener_prefijo(dni); // mismo procedimiento
			if (tabla.find(pref) == tabla.end()) {
				cout << "No existe el registro para el DNI: " << dni << endl; // se verifica si realmente existe un prefijo o no
				return;														  // sino retornar
			}
			Ciudadano* persona = tabla[pref]->search(dni); // busca el dni de la persona y lo asigna a una variable temporal "persona" 
														   // esto para extraer sus datos
			if (persona) { // verificar que exista, realmente deberia de existir
				cout << "--- Datos ---" << endl;
				cout << "DNI: " << persona->dni << endl;
				cout << "Nombres completos: " << persona->nombres << endl;
				cout << "Nacionalidad: " << persona->nacionalidad << endl;
				cout << "Lugar de nacimiento: " << persona->nacimiento << endl;
				cout << "Telefono: " << persona->telefono << endl;
				cout << "Correo: " << persona->correo << endl;
				cout << "Estado civil: " << persona->estado_civil << endl;
				cout << "Direccion: " << persona->direccion.formato() << endl;
				cout << "-------------" << endl;
			} else {
				cout << "No existe el registro para el DNI: " << dni << endl; // y sino, significa que ocurrio un error
			}
		}
		
		void imprimir(string pref) {
			auto aux = tabla.find(pref);
			if (aux == tabla.end()) { // verificacion
				cout << "No existe ningun arbol cargado con el prefijo " << pref << endl;
				return;
			}
			cout << "--- DNI's almacenados en el modulo " << pref << " ---" << endl;
			aux->second->imprimir();
			cout << "----------------------------------------------" << endl;
		}
		
		bool cargar_modulo(int pref) {
			ostringstream oss;								// las siguientes 3 lineas se encargan de rellanar un numero con ceros
			oss << setw(ndigit) << setfill('0') << pref;	// a la izquierda, cosa que si el modulo fuese 12, y usamos un prefijo de 4
			string filename = oss.str() + ".dat";			// se transforma en 0012.dat, evitando errores al leer un modulo 12.dat que no existe
			
			if (!fs::exists(filename)) {
				cout << "El archivo " << filename << " no existe." << endl;
				return false;
			}
			ifstream f(filename, ios::binary);				
			cout << "Cargando " << filename << " ..." << endl;
			while (true) {
				// leer registro
				Ciudadano c = leer_ciudadano(f);
				if (c.dni.empty()) break;
				registrar(c); // sobreescribe las lineas,
							  // esto incluye tambien cuando se ha agregado un nuevo registro, actualiza el dato desde memoria al archivo local
			}
			f.close();
			cout << "Archivo " << filename << " cargado en memoria" << endl;
			return true;
		}
		
		// funcion para ahorrar memoria ram, liberando los modulos
		void liberar_modulo(string pref) {
			auto mod_tmp = tabla.find(pref);
			if (mod_tmp == tabla.end()) { // verificacion si se esta eliminando un modulo (arbol) que no existe realmente
				cout << "No existe ningun modulo cargado con prefijo " << pref << endl;
				return;
			}

			// libera la memoria del arbol B en el indice correspondiente
			delete mod_tmp->second;

			// y luego elimina el hash map
			tabla.erase(mod_tmp);
			cout << "Modulo " << pref << " liberado de memoria correctamente." << endl;
		}
		
		void eliminar_registro(string dni) {
            string pref = dni.substr(0,ndigit);
            if (tabla.find(pref) == tabla.end()) {
                cout << "No existe un modulo cargado con prefijo " << pref << endl; // verificacion
                return;
            }
            if (!tabla[pref]->contains(dni)) {
                cout << "No se encontro el registro para el DNI " << dni << endl; // se valida si es existe el registro con aquel dni
                return;
            }
            // funcion recursiva remove
            tabla[pref]->remove(dni);
			// se reescribe el archivo .data obviando ese registro
			// lo anterior fue para eliminarlo de la estructura del arbol b, pero ahora para hacerlo oficial
			// debemos de eliminarlo tambien del archivo local, por lo que se hace una copia del archivo
			ostringstream oss;									// mismo procedimiento para rellenar de ceros el numero de modulo
			oss << setw(ndigit) << setfill('0') << stoi(pref);
			string filename = oss.str() + ".dat";
            string temp_filename = pref + "_temp.dat";
            ifstream fin(filename, ios::binary);
            ofstream fout(temp_filename, ios::binary);
            while (true) {
                Ciudadano c = leer_ciudadano(fin);
                if (c.dni.empty()) break;
                if (c.dni != dni) {
                    // copiamos los que no sean el registro a eliminar
                    uint32_t dni_num = stoi(c.dni);
                    fout.write(reinterpret_cast<char*>(&dni_num), sizeof(dni_num));

                    auto escribir_cadena = [&](const string& s) {
                        uint32_t len = s.size();
                        fout.write(reinterpret_cast<char*>(&len), sizeof(len));
                        fout.write(s.c_str(), len);
                    };
                    escribir_cadena(c.nombres);
                    escribir_cadena(c.nacionalidad);
                    escribir_cadena(c.nacimiento);
                    escribir_cadena(c.direccion.departamento);
                    escribir_cadena(c.direccion.provincia);
                    escribir_cadena(c.direccion.ciudad);
                    escribir_cadena(c.direccion.distrito);
                    escribir_cadena(c.telefono);
                    escribir_cadena(c.correo);
                    escribir_cadena(c.estado_civil);
                }
            }
            fin.close();
            fout.close();
            fs::remove(filename); // se elimina el archivo
            fs::rename(temp_filename, filename); // se reescribe el archivo, mediante un cambio de nombre del temporal al nuevo archivo 
            cout << "Registro con DNI " << dni << " eliminado correctamente." << endl;
        }
        
        // esta funcion hace que el nuevo registro creado se guarde dentro de los archivos .dat, que se usara en la siguiente funcion
		void guardar_registro(const Ciudadano& c) {
			string filename = c.dni.substr(0, ndigit) + ".dat";
			ofstream f(filename, ios::binary | ios::app); // al estar usando un metodo de guardado binario, necesitamos agregar estas opciones
														  // para hacer que f tenga acceso a escribir
			if (!f.is_open()) {
				cerr << "Ha ocurrido un error, no se pudo abrir el archivo para guardar el archivo " << filename << endl;
				return;
			}
			uint32_t dni_num = stoi(c.dni);
			f.write(reinterpret_cast<char*>(&dni_num), sizeof(dni_num));
			auto escribir_cadena = [&](const string& s) {
				uint32_t len = s.size();
				f.write(reinterpret_cast<char*>(&len), sizeof(len));
				f.write(s.c_str(), len);
			};
			escribir_cadena(c.nombres);
			escribir_cadena(c.nacionalidad);
			escribir_cadena(c.nacimiento);
			escribir_cadena(c.direccion.departamento);
			escribir_cadena(c.direccion.provincia);
			escribir_cadena(c.direccion.ciudad);
			escribir_cadena(c.direccion.distrito);
			escribir_cadena(c.telefono);
			escribir_cadena(c.correo);
			escribir_cadena(c.estado_civil);
			f.close();
		}
		
		void agregar_registro(){
			Ciudadano c; // variable temporal que simula al nuevo ciudadano, el cual nos servira para registrar sus datos
			cout << "Bienvenido al panel de insercion de un nuevo dato.\nIngrese el numero de DNI que desea agregar o 'exit' para salir: ";
			cin >> c.dni;
			if (c.dni == "exit" || c.dni == "EXIT"){
				cout << "Volviendo al menu principal..." << endl;
				return; // salir del programa, y no quedar encerrado agregando registros
			}
			if (c.dni.size() != 8) { // misma comprobacion que al momento de buscar un dni, solo para verificar que el dni es correcto
				cout << "DNI debe tener 8 digitos, intente de nuevo" << endl;
				return;
			}
			if (cargar_modulo(stoi(c.dni.substr(0, ndigit))) == false){ // se carga el modulo en el que el dni esta,
																		// y a la vez se comprueba si hay algun error
				cout << "Ha ocurrido un error al cargar el archivo. Verifique la integridad de los archivos." << endl;
				return;
			}
			string pref = obtener_prefijo(c.dni); // mismo procedimiento
			if (tabla[pref]->contains(c.dni)) { // verifica si el registro ya existe
				int opc_tmp;
				do {
					cout << "Ya existe un registro para el DNI: " << c.dni << endl;
					cout << "Desea reescribir este registro?" << endl;
					cout << "(1) Si\n(2) No\nSu decision: ";
					cin >> opc_tmp;
					if (opc_tmp == 1) {
						eliminar_registro(c.dni);
						break;
					} else if (opc_tmp == 2) {
						cout << "No se reescribirá ningún registro. Regresando..." << endl;
						return;
					}
				} while (opc_tmp != 1 && opc_tmp != 2);
			}			
			// desde aqui empieza a solicitar todos los demas datos
			/*
			 * dni (dni)
			 * nombres completos (nombres)
			 * nacionalidad (nac)
			 * lugar de nacimiento (l_nacimiento)
			 * telefono (telefono)
			 * correo (correo)
			 * estado civil (e_civil)
			 * direccion (dir) - con formato : [distrito], [ciudad], [provincia], [departamento]
			*/
			cin.ignore();
			cout << "Nombres completos: ";
			getline(cin, c.nombres);
			cout << "Nacionalidad: ";
			getline(cin, c.nacionalidad);
			cout << "Lugar de nacimiento: ";
			getline(cin, c.nacimiento);
			cout << "--- Direccion ---" << endl;
			cout << "Departamento: "; getline(cin, c.direccion.departamento);
			cout << "Provincia: "; getline(cin, c.direccion.provincia);
			cout << "Ciudad: "; getline(cin, c.direccion.ciudad);
			cout << "Distrito: "; getline(cin, c.direccion.distrito);
			cout << "-----------------" << endl;
			
			cout << "Telefono: "; getline(cin, c.telefono);
			cout << "Correo: "; getline(cin, c.correo);
			int opc_e_civil; // para evitar que se ingrese cualquier texto dentro de estado civil
							 // se creo un switch para elegir entre los 4 estados civiles
			cout << "--- Estado civil ---" << endl;
			cout << "(1) Soltero(a)" << endl;
			cout << "(2) Casado(a)" << endl;
			cout << "(3) Divorciado(a)" << endl;
			cout << "(4) Viudo(a)" << endl;
			cout << "Su decision: "; cin >> opc_e_civil;
			cout << "--------------------" << endl;
			
			switch (opc_e_civil){
				case 1:
					c.estado_civil = "Soltero(a)";
					break;
				case 2:
					c.estado_civil = "Casado(a)";
					break;
				case 3:
					c.estado_civil = "Divorciado(a)";
					break;
				case 4:
					c.estado_civil = "Viudo(a)";
					break;
				default:
					cout << "Ha ocurrido un error. Intente mas tarde" << endl;
					break;
			}
			
			auto start_registro = high_resolution_clock::now();					
			registrar(c);
			guardar_registro(c);
			auto end_registro = high_resolution_clock::now();
			liberar_modulo(c.dni.substr(0, ndigit));
			cout << "Se ha registrado y guardado correctamente. Buen dia" << endl;
			auto duracion_registro = duration_cast<nanoseconds>(end_registro-start_registro);
			cout << "Tiempo para agregar un registro en ns: " << duracion_registro.count() << endl;
		}
};

int main() {
    Registro registro;
    string aux;
    int opc; // variable temporal para el menu
    do{
		cout << endl;
		cout << "Bienvenido al panel de manejo de datos. Que desea hacer hoy?" << endl;
		cout << "(1) Busqueda por DNI" << endl;
		cout << "(2) Agregar un registro" << endl;
		cout << "(3) Eliminar un registro" << endl;
		cout << "(4) Imprimir un modulo" << endl;
		cout << "(5) Salir" << endl;
		cout << "Su decision: ";
		cin >> opc;
		cout << endl;
		switch (opc){
			case 1:
				// busqueda por dni
				while (true){
					aux = "";
					cout << "Ingrese el DNI (8 digitos) que desea buscar o 'exit' para salir: ";
					cin >> aux;
					if (aux == "exit" || aux == "EXIT") {
						cout << "Volviendo al menu principal..." << endl;
						break;
					}
					if (aux.size() != 8) {
						cout << "DNI debe tener 8 digitos, intente de nuevo" << endl;
						continue;
					}
					auto start_carga_b = high_resolution_clock::now();
					// se carga el modulo en el que el dni esta, y a la vez se comprueba si hay algun error
					if (registro.cargar_modulo(stoi(aux.substr(0, ndigit))) == false){
						cout << "Ha ocurrido un error al cargar el archivo. Verifique la integridad de los archivos." << endl;
						break;
					}
					auto end_carga_b = high_resolution_clock::now();
					// esta es la parte de la accion, lo demas solo son verificaciones y manejo de errores
					auto start_busqueda = high_resolution_clock::now();
					registro.buscar(aux);
					auto end_busqueda = high_resolution_clock::now();
					// elimina el modulo cargado para ahorrar memoria
					registro.liberar_modulo(aux.substr(0, ndigit));
					auto duracion_carga_b = duration_cast<nanoseconds>(end_carga_b-start_carga_b);
					auto duracion_busqueda = duration_cast<nanoseconds>(end_busqueda-start_busqueda);
					cout << "Tiempo de la carga del modulo en ns: " << duracion_carga_b.count() << endl;
					cout << "Tiempo de la busqueda en ns: " << duracion_busqueda.count() << endl;
					cout << endl;
				}
				break;
	        case 2:
				// agregar un registro
				registro.agregar_registro();
				break;
			case 3:
				// eliminar un registro
				while (true){
					aux = "";
					cout << "Ingrese el DNI (8 digitos) que desea eliminar o 'exit' para salir: ";
                    cin >> aux;
                    if (aux == "exit" || aux == "EXIT") {
                        cout << "Volviendo al menu principal..." << endl;
                        break;
                    }
					if (aux.size() != 8) {
						cout << "DNI debe tener 8 digitos, intente de nuevo" << endl;
						continue;
					}
					// se carga el modulo en el que el dni esta, y a la vez se comprueba si hay algun error
					if (registro.cargar_modulo(stoi(aux.substr(0, ndigit))) == false){
						cout << "Ha ocurrido un error al cargar el archivo. Verifique la integridad de los archivos." << endl;
						break;
					}
					// accion
					auto start_eliminacion = high_resolution_clock::now();
					registro.eliminar_registro(aux);
					auto end_eliminacion = high_resolution_clock::now();
					// elimina el modulo cargado para ahorrar memoria
					registro.liberar_modulo(aux.substr(0, ndigit));
					auto duracion_eliminacion = duration_cast<nanoseconds>(end_eliminacion-start_eliminacion);
					cout << "Tiempo de la eliminacion en ns: " << duracion_eliminacion.count() << endl;
					cout << endl;
				}
				break;
			case 4:{
				// impresion de un modulo
				aux = "";
				int max_modulo = 1;									// no hay funcion practica de esto, es meramente estetico
				for (int i = 0; i < ndigit; i++) max_modulo *= 10;	// cosa que si el numero de digitos es 2, el modulo mas grande seria 99
				max_modulo--;										// 3 = 999, 4 = 9999, etc.
				cout << "Bienvenido a la funcion de impresion. Ingrese el modulo que desea imprimir (0 - " << max_modulo << ") o 'exit' para salir: ";
				cin >> aux;
				if (aux == "exit" || aux == "EXIT") {
					cout << "Volviendo al menu principal..." << endl;
					break;
				}
				ostringstream oss;
				oss << setw(ndigit) << setfill('0') << stoi(aux);
				// ^- las lineas de arriba se encargan de formatear mediante rellenando de ceros el numero de modulo a cargar para que
				// coincida con el formato necesario. En caso de que se busque el modulo "12", se intentara buscar el modulo 12.dat,
				// el cual no existe, entonces se completa con ceros para coincidir con la cantidad de digitos necesaria
				string tmp = oss.str();
				// se carga el modulo en el que el dni esta, y a la vez se comprueba si hay algun error
				if (registro.cargar_modulo(stoi(aux)) == false){
					cout << "Ha ocurrido un error al cargar el archivo. Verifique la integridad de los archivos." << endl;
					break;
				}
				// imprime el modulo completo
				registro.imprimir(tmp);
				// elimina el modulo cargado para ahorrar memoria
				registro.liberar_modulo(tmp);
				break;
			}
			case 5:
				// salida
				cout << "Muchas gracias por su consulta. Saliendo..." << endl;
				break;
		}
	} while (opc != 5);
}
