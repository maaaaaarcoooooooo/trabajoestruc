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
