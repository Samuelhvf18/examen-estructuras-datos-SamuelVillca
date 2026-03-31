#include <iostream>
#include <string>

using namespace std;

// Estructura para los datos del estudiante
struct Estudiante {
    string nombre;
    string codigo;
};

// Estructura del Nodo para la Lista Doblemente Enlazada
struct Nodo {
    Estudiante dato;
    Nodo* siguiente;
    Nodo* anterior;
};

class GestionTurnos {
private:
    Nodo* frente;
    Nodo* final;

public:
    GestionTurnos() {
        frente = nullptr;
        final = nullptr;
    }

    // 1. Registrar estudiante (Insertar al final)
    void registrarEstudiante() {
        string nom, cod;
        cout << "Ingrese nombre del estudiante: ";
        cin.ignore();
        getline(cin, nom);
        cout << "Ingrese codigo del estudiante: ";
        cin >> cod;

        Nodo* nuevo = new Nodo();
        nuevo->dato.nombre = nom;
        nuevo->dato.codigo = cod;
        nuevo->siguiente = nullptr;
        nuevo->anterior = nullptr;

        if (frente == nullptr) {
            frente = nuevo;
            final = nuevo;
        } else {
            final->siguiente = nuevo;
            nuevo->anterior = final;
            final = nuevo;
        }
        cout << "Estudiante registrado correctamente." << endl;
    }

    // 2. Atender estudiante (Eliminar el primero - FIFO)
    void atenderEstudiante() {
        if (frente == nullptr) {
            cout << "No hay estudiantes en la cola." << endl;
            return;
        }

        Nodo* temp = frente;
        cout << "Atendiendo a: " << temp->dato.nombre << " [" << temp->dato.codigo << "]" << endl;

        frente = frente->siguiente;
        if (frente != nullptr) {
            frente->anterior = nullptr;
        } else {
            final = nullptr;
        }

        delete temp;
    }

    // 3. Mostrar estudiantes en espera
    void mostrarEstudiantes() {
        if (frente == nullptr) {
            cout << "La cola esta vacia." << endl;
            return;
        }

        int op;
        cout << "1. Mostrar en orden de llegada (Normal)\n";
        cout << "2. Mostrar en orden inverso (Punto Extra)\n";
        cout << "Seleccione: ";
        cin >> op;

        if (op == 2) {
            // Recorrido hacia atras (Usa el puntero anterior)
            Nodo* actual = final;
            cout << "\n--- Estudiantes (Orden Inverso) ---" << endl;
            while (actual != nullptr) {
                cout << "Nombre: " << actual->dato.nombre << " | Codigo: " << actual->dato.codigo << endl;
                actual = actual->anterior;
            }
        } else {
            // Recorrido hacia adelante
            Nodo* actual = frente;
            cout << "\n--- Estudiantes (Orden de llegada) ---" << endl;
            while (actual != nullptr) {
                cout << "Nombre: " << actual->dato.nombre << " | Codigo: " << actual->dato.codigo << endl;
                actual = actual->siguiente;
            }
        }
    }

    // 4. Buscar estudiante por nombre
    void buscarEstudiante() {
        if (frente == nullptr) {
            cout << "No hay nadie en la cola." << endl;
            return;
        }

        string nombreBuscado;
        cout << "Nombre a buscar: ";
        cin.ignore();
        getline(cin, nombreBuscado);

        Nodo* actual = frente;
        int pos = 1;
        bool encontrado = false;

        while (actual != nullptr) {
            if (actual->dato.nombre == nombreBuscado) {
                cout << "Estudiante encontrado!" << endl;
                cout << "Nombre: " << actual->dato.nombre << " | Posicion: " << pos << endl;
                encontrado = true;
                break;
            }
            actual = actual->siguiente;
            pos++;
        }

        if (!encontrado) cout << "El estudiante no existe en la lista." << endl;
    }

    // Destructor para liberar memoria al cerrar el programa
    ~GestionTurnos() {
        while (frente != nullptr) {
            Nodo* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }
};

int main() {
    GestionTurnos cola;
    int opcion;

    do {
        cout << "\n--- SISTEMA DE TURNOS ---" << endl;
        cout << "1. Registrar estudiante" << endl;
        cout << "2. Atender estudiante" << endl;
        cout << "3. Mostrar estudiantes en espera" << endl;
        cout << "4. Buscar estudiante por nombre" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: cola.registrarEstudiante(); break;
            case 2: cola.atenderEstudiante(); break;
            case 3: cola.mostrarEstudiantes(); break;
            case 4: cola.buscarEstudiante(); break;
            case 5: cout << "Saliendo del sistema..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 5);

    return 0;
}
