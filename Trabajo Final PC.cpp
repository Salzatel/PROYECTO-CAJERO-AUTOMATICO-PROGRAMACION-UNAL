#include <iostream>
#include<string>
#include<fstream>
#include <vector>
using namespace std;

struct Cuenta{
    string nombre;
    string contrasena;
    int saldo;
};
void leerArchivo(vector<Cuenta>& cuentas) {
    
    Cuenta p;
    ifstream archivo("cuentas.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo.\n";
        return;
    }
    string linea;
    while(getline(archivo,linea)){
        p.nombre=linea;
        archivo>>p.contrasena;
        archivo.ignore();
        archivo>>p.saldo;
        archivo.ignore();
        cuentas.push_back(p);
    }
    archivo.close();
}

void mostrarSaldo(const vector<Cuenta>& cuentas, string nombre, string contrasena, int y) {
    if (y>= cuentas.size()) {
        cout << "Nombre o contraseña incorrectos." << endl;
        return;
    }

    Cuenta x = cuentas[y];

    if (x.nombre == nombre && x.contrasena == contrasena) {
        cout << "Saldo: " << x.saldo << endl;
        ofstream archivo("historial.txt", ios::app);
        archivo << "transacción: consultar saldo, hecha por: " << x.nombre << endl;
        archivo.close();
        return;
    }

    mostrarSaldo(cuentas, nombre, contrasena, y + 1);
}
void retirarDinero( vector<Cuenta>& cuentas, const string &nombre, const string&password) {
    ofstream archivo("historial.txt", ios::app);
    ofstream mod("cuentas.txt");
    bool encontrado= false;
    for (  Cuenta &x: cuentas ) {
        if (x.nombre==nombre && x.contrasena == password) {
            int valor;
            cout<<"ingrese valor a retirar"<<endl;
            cin>> valor;
            cin.ignore();
            if(valor<= x.saldo){
                cout<<"transacción exitosa, retiraste: "<<valor<<endl;
                archivo<<"transacción: retirar Dinero, hecha por: "<<x.nombre<<endl;
               
                archivo.close();
                int l;
                l=x.saldo-valor;
                x.saldo=l;
                cout<<"Nuevo saldo: "<<l<<endl;
                cuentas.push_back(x);
                
            }else{
                cout<<"fondos insuficientes "<<endl;
                return;
            }
            encontrado=true;
                
            
        }
        
        mod << x.nombre << endl;
        mod << x.contrasena << endl;
        mod << x.saldo << endl;
    }
    if (!encontrado) {
        cout << "Nombre o contraseña incorrectos." << endl;
    }
    mod.close();  
}
void depositarDinero( vector<Cuenta>& cuentas, const string &nombre, const string&password) {
    ofstream archivo("historial.txt", ios::app);
    ofstream mod("cuentas.txt");
    bool encontrado= false;
    for (  Cuenta &x: cuentas ) {
        if (x.nombre==nombre && x.contrasena == password) {
            int valor;
            cout<<"ingrese valor a depositar"<<endl;
            cin>> valor;
            cin.ignore();
            
            cout<<"transacción exitosa, depositaste: "<<valor<<endl;
            archivo<<"transacción: depositar Dinero, hecha por: "<<x.nombre<<endl;
            archivo.close();
            int l;
            l=x.saldo+valor;
            x.saldo=l;
            cout<<"Nuevo saldo: "<<l<<endl;
            cuentas.push_back(x);
            encontrado=true;
        }
        mod << x.nombre << endl;
        mod << x.contrasena << endl;
        mod << x.saldo << endl;
    }
    if (!encontrado) {
        cout << "Nombre o contraseña incorrectos." << endl;
    }
    mod.close();  
}
int main() {
    int caso;
    string contrasena;
    string nombre;
    int x=0;
    cout<<"Ingrese su nombre"<<endl;
    getline(cin,nombre);
    cout<<"Ingrese su contraseña"<<endl;
    getline(cin,contrasena);
    cout<<"Ingrese numero para transacción 1. Consultar saldo, 2. Retirar dinero,3. Depositar dinero,4. Ver historial de transacciones,5. Validación de fondos insuficientes,6. Guardar la información de la cuenta en archivo"<<endl;
    cin >> caso;
    cin.ignore();
    vector<Cuenta>cuentas;
    leerArchivo(cuentas);
    switch (caso) {
        case 1: mostrarSaldo(cuentas, nombre, contrasena,x); break;
        case 2: retirarDinero(cuentas, nombre, contrasena); break;
        case 3: depositarDinero(cuentas, nombre, contrasena); break;
    }
    return 0;
}