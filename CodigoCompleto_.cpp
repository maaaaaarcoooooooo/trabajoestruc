#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    string nombre;
    string id;
    string fechaNacimiento;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(string _nombre, string _id, string _fechaNacimiento) {
        nombre = _nombre;
        id = _id;
        fechaNacimiento = _fechaNacimiento;
        izquierdo = NULL;
        derecho = NULL;
    }
};

Nodo* insertar(Nodo* raiz, Nodo* nuevo) {
    if (raiz == NULL) {
        return nuevo;
    }
    if (nuevo->nombre < raiz->nombre) {
        raiz->izquierdo = insertar(raiz->izquierdo, nuevo);
    } else {
        raiz->derecho = insertar(raiz->derecho, nuevo);
    }
    return raiz;
}

void inorden(Nodo* nodo) {
    if (nodo != NULL) {
        inorden(nodo->izquierdo);
        cout << nodo->nombre << " - " << nodo->id << " - " << nodo->fechaNacimiento << endl;
        inorden(nodo->derecho);
    }
}

Nodo* buscar(Nodo* raiz, const string& id) {
    if (raiz == NULL || raiz->id == id) {
        return raiz;
    }
    if (id < raiz->id) {
        return buscar(raiz->izquierdo, id);
    } else {
        return buscar(raiz->derecho, id);
    }
}

void actualizar(Nodo* raiz, const string& id) {
    Nodo* nodo = buscar(raiz, id);
    if (nodo == NULL) {
        cout << "Miembro no encontrado.\n";
        return;
    }
    cout << "Miembro encontrado: " << nodo->nombre << " - " << nodo->fechaNacimiento << endl;
    cout << "Nuevo nombre: ";
    getline(cin, nodo->nombre);
    cout << "Nueva fecha de nacimiento (YYYY-MM-DD): ";
    getline(cin, nodo->fechaNacimiento);
    cout << "Datos actualizados correctamente.\n";
}

Nodo* encontrarMinimo(Nodo* nodo) {
    while (nodo->izquierdo != NULL) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

Nodo* eliminar(Nodo* raiz, const string& id) {
    if (raiz == NULL) return NULL;

    if (id < raiz->id) {
        raiz->izquierdo = eliminar(raiz->izquierdo, id);
    } else if (id > raiz->id) {
        raiz->derecho = eliminar(raiz->derecho, id);
    } else {
        if (raiz->izquierdo == NULL) {
            Nodo* temp = raiz->derecho;
            delete raiz;
            return temp;
        } else if (raiz->derecho == NULL) {
            Nodo* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        } else {
            Nodo* temp = encontrarMinimo(raiz->derecho);
            raiz->nombre = temp->nombre;
            raiz->id = temp->id;
            raiz->fechaNacimiento = temp->fechaNacimiento;
            raiz->derecho = eliminar(raiz->derecho, temp->id);
        }
    }
    return raiz;
}

int main() {
    Nodo* raiz = NULL;
    int opcion;

    do {
        cout << "\n--- Menu Arbol Genealogico ---\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Mostrar recorrido (inorden)\n";
        cout << "3. Buscar miembro\n";
        cout << "4. Eliminar miembro\n";
        cout << "5. Actualizar miembro\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            string nombre, id, fecha;
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "ID: ";
            getline(cin, id);
            cout << "Fecha de nacimiento (YYYY-MM-DD): ";
            getline(cin, fecha);
            raiz = insertar(raiz, new Nodo(nombre, id, fecha));
            cout << "Miembro insertado con exito.\n";
        } else if (opcion == 2) {
            cout << "\n--- Recorrido Inorden ---\n";
            inorden(raiz);
        } else if (opcion == 3) {
            string id;
            cout << "Ingrese el ID del miembro a buscar: ";
            getline(cin, id);
            Nodo* resultado = buscar(raiz, id);
            if (resultado != NULL) {
                cout << "Miembro encontrado: " << resultado->nombre << " - " << resultado->fechaNacimiento << endl;
            } else {
                cout << "Miembro no encontrado.\n";
            }
        } else if (opcion == 4) {
            string id;
            cout << "Ingrese el ID del miembro a eliminar: ";
            getline(cin, id);
            raiz = eliminar(raiz, id);
            cout << "Miembro eliminado si existía.\n";
        } else if (opcion == 5) {
            string id;
            cout << "Ingrese el ID del miembro a actualizar: ";
            getline(cin, id);
            actualizar(raiz, id);
        } else if (opcion == 6) {
            cout << "Saliendo del programa...\n";
        } else {
            cout << "Opcion invalida. Intente de nuevo.\n";
        }

    } while (opcion != 6);

    return 0;
}


