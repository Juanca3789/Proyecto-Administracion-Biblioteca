#include <iostream>
#include <wchar.h>
#include <locale.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

/* Carlos documente este documento, vago qliao 

using namespace std;

struct Fecha{
	int dia, mes, anio;
};

struct Transacciones{
	bool tipoTransaccion;
	Fecha fechaTransaccion;
	int cantidadTransaccion;
	
};

struct Libro{
	string ISBN;
	string titulo;
	int precioCompra;
	int precioVenta;
	int cantidad = 0;
	Transacciones transacciones;
};

//funciones
Fecha obtenerFecha(Fecha &fecha){
	time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    fecha.dia = local->tm_mday;
    fecha.mes = local->tm_mon + 1;
    fecha.anio = local->tm_year + 1900;
    return fecha;
}

void imprimirLibro(Libro libro){
	cout<<"\t\tISBN: "<<libro.ISBN<<endl;
	cout<<"\t\tTitulo: "<<libro.titulo<<endl;
	cout<<"\t\tPrecio de compra: "<<libro.precioVenta<<endl;
	cout<<"\t\tPrecio de venta: "<<libro.precioCompra<<endl;
	cout<<"\t\tInventario: "<<libro.cantidad<<endl;
}
//Procedimientos
void registroLibro(Libro libro);
void borrarLibro(Libro libro);
void buscarTitulo(Libro libro);
void buscarIsbn(Libro libro);
void abastecerLibro(Libro libro);
void venderLibro(Libro libro);
void calcularLibro(Libro libro);
void masCostoso(Libro libro);
void menosCostoso(Libro libro);
void masVendido(Libro libro);

int main(){
	principal:
		system("cls");
		int opcion;
		Libro libro;
		setlocale(LC_ALL, "");
		system("title Software administración sistema biblioteca");
		system("color f0");
		cout<<"Bienvenido Administrador"<<endl;
			cout<<"\t Seleccione la opción a utilizar:"<<endl;
				cout<<"\t\t 1.Registrar libro"<<endl;
				cout<<"\t\t 2.Eliminar libro"<<endl;
				cout<<"\t\t 3.Buscar libro por titulo"<<endl;
				cout<<"\t\t 4.Buscar libro por ISBN"<<endl;
				cout<<"\t\t 5.Abastecer ejemplares de un libro"<<endl;
				cout<<"\t\t 6.Vender ejemplares de un libro"<<endl;
				cout<<"\t\t 7.Calcular transacciones de un libro"<<endl;
				cout<<"\t\t 8.Buscar el libro mas costoso"<<endl;
				cout<<"\t\t 9.Buscar el libro menos costoso"<<endl;
				cout<<"\t\t 10.Buscar el libro mas vendido"<<endl;
				cout<<"Digite una opción: "; cin>>opcion;
		system("cls");
		switch(opcion){
			case 1:
				registroLibro(libro);
				break;
			case 2:
				borrarLibro(libro);
				break;
			case 3:
				buscarTitulo(libro);
				break;
			case 4:
				buscarIsbn(libro);
				break;
			case 5:
				abastecerLibro(libro);
				break;
			case 6:
				venderLibro(libro);
				break;
			case 7:
				calcularLibro(libro);
				break;
			case 8:
				masCostoso(libro);
				break;
			case 9:
				menosCostoso(libro);
				break;
			case 10:
				masVendido(libro);
				break;
		}
	cout<<"0.Volver al menu principal"<<endl;
	cout<<"1.Cerrar programa"<<endl;
	int opc;
	cin>>opc;
	if(opc == 0){
		goto principal;
	}
}


void registroLibro(Libro libro){
	ofstream salida;
	system("title Software administración sistema biblioteca - Registrar libro");
	cout<<"Digite la información del libro a registrar: "<<endl;
		getline(cin, libro.ISBN);
		cout<<"\tISBN: "; getline(cin, libro.ISBN);
		cout<<"\tTitulo del libro: "; getline(cin, libro.titulo);
		cout<<"\tPrecio de compra: "; cin>>libro.precioCompra;
		cout<<"\tPrecio de venta: "; cin>>libro.precioVenta;
	salida.open("catalogo.csv", ios::app);
		salida<<endl<<libro.ISBN<<";"<<libro.titulo<<";"<<libro.precioCompra<<";"<<libro.precioVenta<<";"<<libro.cantidad<<";";
	salida.close();
	cout<<"Libro registrado correctamente"<<endl<<endl;
}

void borrarLibro(Libro libro){
	system("title Software administración sistema biblioteca - Borrar libro");
	ofstream salida;
	ifstream entrada;
	string eliminar;
	string mantener;
	bool existe = false;
	getline(cin, libro.ISBN);
	cout<<"Digite el ISBN del libro a eliminar: "; getline(cin, libro.ISBN);
	entrada.open("catalogo.csv", ios::in);
	salida.open("auxiliar.csv", ios::out);
	while(!entrada.eof()){
		string comprobacion;
		getline(entrada, eliminar);
		stringstream linea(eliminar);
		getline(linea, comprobacion, ';');
		if(libro.ISBN == comprobacion){
			existe = false;
			break;
		}
		else{
			existe = true;
			eliminar = "";
		}
	}
	entrada.close();
	entrada.open("catalogo.csv", ios::in);
	while(!entrada.eof()){
		getline(entrada, mantener);
		if(mantener != eliminar){
			salida<<mantener<<endl;
		}
	}
	salida.close();
	entrada.close();
	entrada.open("auxiliar.csv", ios::in);
	salida.open("catalogo.csv", ios::out);
	while(!entrada.eof()){
		getline(entrada, mantener);
		salida<<mantener<<endl;
	}
	salida.close();
	entrada.close();
	if (existe == true){
		cout<<"\tEl ISBN ingresado no corresponde a ningún ISBN en el sistema"<<endl<<endl;
	}
	else{
		cout<<"\tLibro eliminado correctamente"<<endl<<endl;
	}	
}

void buscarTitulo(Libro libro){
	ifstream entrada;
	string buscar;
	int contador = 0;
	system("title Software administración sistema biblioteca - Buscar libro por titulo");
	getline(cin, libro.titulo);
	cout<<"Digite el titulo del libro a buscar: "; getline(cin, libro.titulo);
	entrada.open("catalogo.csv", ios::in);
	while(!entrada.eof()){
		string comparar;
		getline(entrada, comparar);
		stringstream linea(comparar);
		for(int i=0; i<2; i++){
			getline(linea, buscar, ';');
		}
		linea.seekg(0, linea.beg);
		if(buscar == libro.titulo){
			contador++;
			cout<<"\tSe ha encontrado ("<<contador<<") libros titulados '"<<libro.titulo<<"'"<<endl;
					string aux;
					getline(linea, libro.ISBN, ';');
					getline(linea, libro.titulo, ';');
					getline(linea, aux, ';'); libro.precioCompra = stoi(aux);
					getline(linea, aux, ';'); libro.precioVenta = stoi(aux);
					getline(linea, aux, ';'); libro.cantidad = stoi(aux);
					imprimirLibro(libro);
					cout<<endl;
		}
	}
	if (contador == 0){
		cout<<"\tNo se han encontrado libros con el titulo "<<libro.titulo<<endl<<endl;
	}
	entrada.close();
}

void buscarIsbn(Libro libro){
	ifstream entrada;
	string buscar;
	int contador = 0;
	getline(cin, libro.titulo);
	system("title Software administración sistema biblioteca - Buscar libro por ISBN");
	cout<<"Digite el ISBN del libro a buscar: "; getline(cin, libro.ISBN);
	entrada.open("catalogo.csv", ios::in);
	while(!entrada.eof()){
		string comparar;
		getline(entrada, comparar);
		stringstream linea(comparar);
		getline(linea, buscar, ';');
		linea.seekg(0, linea.beg);
		if(buscar == libro.ISBN){
			contador++;
			cout<<"\tSe ha encontrado el libro con ISBN '"<<libro.ISBN<<"'"<<endl;
					string aux;
					getline(linea, libro.ISBN, ';');
					getline(linea, libro.titulo, ';');
					getline(linea, aux, ';'); libro.precioVenta = stoi(aux);
					getline(linea, aux, ';'); libro.precioCompra = stoi(aux);
					getline(linea, aux, ';'); libro.cantidad = stoi(aux);
					imprimirLibro(libro);
					cout<<endl;
		}
	}
	if (contador == 0){
		cout<<"\tNo se han encontrado ningún libro con el ISBN "<<libro.ISBN<<endl<<endl;
	}
	entrada.close();
}

void abastecerLibro(Libro libro){
	ifstream cajaentrada;
	ofstream cajasalida;
	ifstream entrada;
	ofstream salida;
	string buscar;
	string getcaja;
	int contador = 0, cantidad, caja, posicion;
	system("title Software administración sistema biblioteca - Abastecer ejemplares de un libro");
	getline(cin, libro.ISBN);
	cout<<"Digite el ISBN del libro a abastecer: "; getline(cin, libro.ISBN);
	entrada.open("catalogo.csv", ios::in);
	while(!entrada.eof()){
		string comparar;
		getline(entrada, comparar);
		stringstream linea(comparar);
		getline(linea, buscar, ';');
		linea.seekg(0, linea.beg);
		if(buscar == libro.ISBN){
			contador++;
			cout<<"\tSe ha encontrado el libro con ISBN '"<<libro.ISBN<<"'"<<endl;
					string aux;
					posicion = entrada.tellg();
					getline(linea, libro.ISBN, ';');
					getline(linea, libro.titulo, ';');
					getline(linea, aux, ';'); libro.precioVenta = stoi(aux);
					getline(linea, aux, ';'); libro.precioCompra = stoi(aux);
					getline(linea, aux, ';'); libro.cantidad = stoi(aux);
					imprimirLibro(libro);
					cout<<endl;
		}
	}
	entrada.close();
	if (contador == 0){
		cout<<"\tNo se han encontrado ningún libro con el ISBN "<<libro.ISBN<<endl<<endl;
	}
	else{
		cajaentrada.open("caja.csv", ios::in);
		getline(cajaentrada, getcaja);
		caja = stoi(getcaja);
		cout<<"Dinero en caja: "<<caja<<endl;
		cout<<"Maximo de libros adquiribles: "<<(caja/libro.precioCompra)<<endl;
		cajaentrada.close();
		cout<<"\tDigite la cantidad de libros adquirir: "; cin>>cantidad;
		if((cantidad*libro.precioCompra)>caja){
			cout<<"No hay suficiente dinero en caja para realizar el abastecimiento"<<endl;
		}
		else{
			int confirmacion;
			cout<<"\tEl costo de la transacción será de: "<<cantidad*libro.precioCompra<<" ¿Desea realizar la transacción?"<<endl;
			cout<<"\t1.Confrimar transacción"<<endl;
			cout<<"\t2. Cancelar transacción"<<endl;
			cout<<"\t\t"; cin>>confirmacion;
			if(confirmacion == 1){
				obtenerFecha(libro.transacciones.fechaTransaccion);
				salida.open("catalogo.csv", ios::app);
				salida.seekp(posicion);
				salida<<"Transacción-Abastecimiento-"<<libro.transacciones.fechaTransaccion.dia<<"/"<<libro.transacciones.fechaTransaccion.mes<<"/"<<libro.transacciones.fechaTransaccion.anio<<"-";
			}
		}
	}
}

void venderLibro(Libro libro){
	system("title Software administración sistema biblioteca - Vender ejemplares de un libro");
}

void calcularLibro(Libro libro){
	system("title Software administración sistema biblioteca - Calcular transacciones de un libro");
}

void masCostoso(Libro libro){
	system("title Software administración sistema biblioteca - Buscar el libro mas costoso");
}

void menosCostoso(Libro libro){
	system("title Software administración sistema biblioteca - Buscar el libro menos costoso");
}

void masVendido(Libro libro){
	system("title Software administración sistema biblioteca - Buscar el libro mas vendido");
}
