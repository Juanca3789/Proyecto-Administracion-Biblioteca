#include <iostream>
#include <wchar.h>
#include <locale.h>
#include <chrono>
#include <fstream>
#include <sstream>
using namespace std;

struct Fecha{	//estructura permite almacenar fecha
	int dia, mes, anio;
};

struct Transacciones{ //estructura de cada transacci�n del libro
	bool tipoTransaccion;
	Fecha fechaTransaccion;
	int cantidadTransaccion;
	
};

struct Libro{ //estructura del libro
	string ISBN;
	string titulo;
	int precioCompra;
	int precioVenta;
	int cantidad = 0;
	Transacciones transacciones;
};

//funciones
Fecha obtenerFecha(Fecha &fecha){ //obtiene la fecha actual del computador
	time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    fecha.dia = local->tm_mday;
    fecha.mes = local->tm_mon + 1;
    fecha.anio = local->tm_year + 1900;
    return fecha;
}

void imprimirLibro(Libro libro){ //imprime la informaci�n basica del libro
	cout<<"\t\tISBN: "<<libro.ISBN<<endl;
	cout<<"\t\tTitulo: "<<libro.titulo<<endl;
	cout<<"\t\tPrecio de compra: "<<libro.precioCompra<<endl;
	cout<<"\t\tPrecio de venta: "<<libro.precioVenta<<endl;
	cout<<"\t\tInventario: "<<libro.cantidad<<endl;
}

int buscaIsbn(Libro &libro, string buscar){ //Selecciona un libro desde el archivo por ISBN
	ifstream entrada;
	int contador = 0;
	getline(cin, libro.titulo);
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
					getline(linea, aux, ';'); libro.precioCompra = stoi(aux);
					getline(linea, aux, ';'); libro.precioVenta = stoi(aux);
					getline(linea, aux, ';'); libro.cantidad = stoi(aux);
					imprimirLibro(libro);
					cout<<endl;
		}
	}
	if (contador == 0){
		cout<<"\tNo se han encontrado ning�n libro con el ISBN "<<libro.ISBN<<endl<<endl;
		return 0;
	}
	else{
		return 1;
	}
	entrada.close();
}

void crearArchivos(){ //Crea los archivos necesarios si aun no existen
	ifstream entrada;
	ofstream salida;
	entrada.open("catalogo.csv", ios::in);
	if(entrada.fail()){
		entrada.close();
		salida.open("catalogo.csv", ios::out);
		salida.close();
	}
	entrada.open("auxiliar.csv", ios::in);
	if(entrada.fail()){
		entrada.close();
		salida.open("auxiliar.csv", ios::out);
		salida.close();
	}
	entrada.open("caja.csv", ios::in);
	if(entrada.fail()){
		entrada.close();
		salida.open("caja.csv", ios::out);
		salida<<1000000<<endl;
		salida.close();
	}
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
void consultarCaja();

int main(){
	crearArchivos();
	principal:
		system("cls");
		int opcion;
		Libro *libro = new Libro;
		setlocale(LC_ALL, "");
		system("title Software administraci�n sistema biblioteca");
		system("color f0");
		cout<<"Bienvenido Administrador"<<endl;
			cout<<"\t Seleccione la opci�n a utilizar:"<<endl;
				cout<<"\t\t 1.Registrar libro"<<endl;
				cout<<"\t\t 2.Eliminar libro"<<endl;
				cout<<"\t\t 3.Buscar libro por titulo"<<endl;
				cout<<"\t\t 4.Buscar libro por ISBN"<<endl;
				cout<<"\t\t 5.Abastecer ejemplares de un libro"<<endl;
				cout<<"\t\t 6.Vender ejemplares de un libro"<<endl;
				cout<<"\t\t 7.Calcular transacciones de abastecimiento de un libro"<<endl;
				cout<<"\t\t 8.Buscar el libro mas costoso"<<endl;
				cout<<"\t\t 9.Buscar el libro menos costoso"<<endl;
				cout<<"\t\t 10.Buscar el libro mas vendido"<<endl;
				cout<<"\t\t 11.Consultar dinero en caja"<<endl;
				cout<<"\t\t 0.Finalizar ejecuci�n"<<endl;
				cout<<"Digite una opci�n: "; cin>>opcion;
		system("cls");
		switch(opcion){
			case 0:
				goto seleccion;
				break;
			case 1:
				registroLibro(*libro);
				break;
			case 2:
				borrarLibro(*libro);
				break;
			case 3:
				buscarTitulo(*libro);
				break;
			case 4:
				buscarIsbn(*libro);
				break;
			case 5:
				abastecerLibro(*libro);
				break;
			case 6:
				venderLibro(*libro);
				break;
			case 7:
				calcularLibro(*libro);
				break;
			case 8:
				masCostoso(*libro);
				break;
			case 9:
				menosCostoso(*libro);
				break;
			case 10:
				masVendido(*libro);
				break;
			case 11:
				consultarCaja();
				break;
			default:
				cout<<"Seleccione una opcion valida"<<endl;
				system("pause");
				goto principal;
		}
		delete libro;
	seleccion:
		cout<<"0.Volver al menu principal"<<endl;
		cout<<"1.Cerrar programa"<<endl;
		int opc;
		cin>>opc;
		if(opc == 0){
			goto principal;
		}
}


void registroLibro(Libro libro){
	ifstream entrada;
	ofstream salida;
	string buscar;
	bool existe = false;
	system("title Software administraci�n sistema biblioteca - Registrar libro");
	cout<<"Digite la informaci�n del libro a registrar: "<<endl;
		getline(cin, libro.ISBN);
		cout<<"\tISBN: "; getline(cin, libro.ISBN);
		cout<<"\tTitulo del libro: "; getline(cin, libro.titulo);
		cout<<"\tPrecio de compra: "; cin>>libro.precioCompra;
		cout<<"\tPrecio de venta: "; cin>>libro.precioVenta;
	entrada.open("catalogo.csv", ios::in);
	while(!entrada.eof()){
		getline(entrada, buscar);
		stringstream linea(buscar);
		getline(linea, buscar, ';');
		if(buscar == libro.ISBN){
			existe = true;
		}
	}
	entrada.close();
	if(existe == false){
		salida.open("catalogo.csv", ios::app);
		salida<<libro.ISBN<<";"<<libro.titulo<<";"<<libro.precioCompra<<";"<<libro.precioVenta<<";"<<libro.cantidad<<";"<<endl;
		salida.close();
		cout<<"Libro registrado correctamente"<<endl<<endl;
	}
	else{
		cout<<"El libro con ISBN "<<libro.ISBN<<" ya se encuentra registrado"<<endl;
	}
}

void borrarLibro(Libro libro){
	system("title Software administraci�n sistema biblioteca - Borrar libro");
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
		cout<<"\tEl ISBN ingresado no corresponde a ning�n ISBN en el sistema"<<endl<<endl;
	}
	else{
		cout<<"\tLibro eliminado correctamente"<<endl<<endl;
	}	
}

void buscarTitulo(Libro libro){
	ifstream entrada;
	string buscar;
	int contador = 0;
	system("title Software administraci�n sistema biblioteca - Buscar libro por titulo");
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
	string buscar;
	system("title Software administraci�n sistema biblioteca - Buscar libro por ISBN");
	buscaIsbn(libro, buscar);
}

void abastecerLibro(Libro libro){
	ifstream cajaentrada;
	ofstream cajasalida;
	ifstream entradas;
	ofstream salida;
	string buscar;
	string getcaja;
	int contador = 0, caja, existe;
	libro.transacciones.tipoTransaccion = true;
	system("title Software administraci�n sistema biblioteca - Abastecer ejemplares de un libro");
	existe = buscaIsbn(libro, buscar);
	if(existe == 1){
		cajaentrada.open("caja.csv", ios::in);
		getline(cajaentrada, getcaja);
		caja = stoi(getcaja);
		cout<<"Dinero en caja: "<<caja<<endl;
		cout<<"Maximo de libros adquiribles: "<<(caja/libro.precioCompra)<<endl;
		cajaentrada.close();
		cout<<"\tDigite la cantidad de libros adquirir: "; cin>>libro.transacciones.cantidadTransaccion;
		if((libro.transacciones.cantidadTransaccion*libro.precioCompra)>caja){
			cout<<"No hay suficiente dinero en caja para realizar el abastecimiento"<<endl;
		}
		else{
			int confirmacion;
			cout<<"\tEl costo de la transacci�n ser� de: "<<libro.transacciones.cantidadTransaccion*libro.precioCompra<<" �Desea realizar la transacci�n?"<<endl;
			cout<<"\t1.Confrimar transacci�n"<<endl;
			cout<<"\t2.Cancelar transacci�n"<<endl;
			cout<<"\t"; cin>>confirmacion;
			if(confirmacion == 1){
				obtenerFecha(libro.transacciones.fechaTransaccion);
				entradas.open("catalogo.csv", ios::in);
				salida.open("auxiliar.csv", ios::out);
				while(!entradas.eof()){
					string copiar;
					getline(entradas, copiar);
					stringstream linea(copiar);
					getline(linea, buscar, ';');
					linea.seekg(0, linea.beg);
					if(buscar == libro.ISBN){
						while(!linea.eof()){
							getline(linea, copiar, ';');
							if(to_string(libro.cantidad) == copiar){
								libro.cantidad += libro.transacciones.cantidadTransaccion;
								salida<<libro.cantidad<<";";
								salida<<"Transacci�n-"<<libro.transacciones.tipoTransaccion<<"-"<<libro.transacciones.fechaTransaccion.dia<<"/"<<libro.transacciones.fechaTransaccion.mes<<"/"<<libro.transacciones.fechaTransaccion.anio<<"-"<<libro.transacciones.cantidadTransaccion<<";";
							}
							else{
								salida<<copiar<<";";
							}
						}
						salida<<endl;
					}
					else{
						salida<<copiar<<endl;
					}
				}
				entradas.close();
				salida.close();
				entradas.open("auxiliar.csv", ios::in);
				salida.open("catalogo.csv", ios::out);	
				while(!entradas.eof()){
					string copiar;
					getline(entradas, copiar);
					salida<<copiar<<endl;
				}
				entradas.close();
				salida.close();
				cajasalida.open("caja.csv", ios::out);
				caja -= (libro.transacciones.cantidadTransaccion*libro.precioCompra);
				cajasalida<<caja;
				cajasalida.close();
				cout<<"Transaccion realizada correctamente"<<endl;
			}
			else{
				cout<<"Transacci�n cancelada"<<endl;
			}
		}
	}
}

void venderLibro(Libro libro){
	ifstream cajaentrada;
	ofstream cajasalida;
	ifstream entradas;
	ofstream salida;
	string buscar;
	string getcaja;
	int contador = 0, caja, existe;
	libro.transacciones.tipoTransaccion = false;
	system("title Software administraci�n sistema biblioteca - Vender ejemplares de un libro");
	existe = buscaIsbn(libro, buscar);
	if(existe == 1){
		cajaentrada.open("caja.csv", ios::in);
		getline(cajaentrada, getcaja);
		caja = stoi(getcaja);
		cajaentrada.close();
		cout<<"\tDigite la cantidad de libros a vender: "; cin>>libro.transacciones.cantidadTransaccion;
		if(libro.transacciones.cantidadTransaccion > libro.cantidad ){
			cout<<"No hay suficientes unidades en el inventario para realizar esta transacci�n"<<endl;
		}
		else{
			int confirmacion;
			cout<<"\tEl costo de la transacci�n ser� de: "<<libro.transacciones.cantidadTransaccion*libro.precioVenta<<" �Desea realizar la transacci�n?"<<endl;
			cout<<"\t1.Confrimar transacci�n"<<endl;
			cout<<"\t2.Cancelar transacci�n"<<endl;
			cout<<"\t"; cin>>confirmacion;
			if(confirmacion == 1){
				obtenerFecha(libro.transacciones.fechaTransaccion);
				entradas.open("catalogo.csv", ios::in);
				salida.open("auxiliar.csv", ios::out);
				while(!entradas.eof()){
					string copiar;
					getline(entradas, copiar);
					stringstream linea(copiar);
					getline(linea, buscar, ';');
					linea.seekg(0, linea.beg);
					if(buscar == libro.ISBN){
						while(!linea.eof()){
							getline(linea, copiar, ';');
							if(to_string(libro.cantidad) == copiar){
								libro.cantidad -= libro.transacciones.cantidadTransaccion;
								salida<<libro.cantidad<<";";
								salida<<"Transacci�n-"<<libro.transacciones.tipoTransaccion<<"-"<<libro.transacciones.fechaTransaccion.dia<<"/"<<libro.transacciones.fechaTransaccion.mes<<"/"<<libro.transacciones.fechaTransaccion.anio<<"-"<<libro.transacciones.cantidadTransaccion<<";";
							}
							else{
								salida<<copiar<<";";
							}
						}
						salida<<endl;
					}
					else{
						salida<<copiar<<endl;
					}
				}
				entradas.close();
				salida.close();
				entradas.open("auxiliar.csv", ios::in);
				salida.open("catalogo.csv", ios::out);	
				while(!entradas.eof()){
					string copiar;
					getline(entradas, copiar);
					salida<<copiar<<endl;
				}
				entradas.close();
				salida.close();
				cajasalida.open("caja.csv", ios::out);
				caja += (libro.transacciones.cantidadTransaccion*libro.precioVenta);
				cajasalida<<caja;
				cajasalida.close();
				cout<<"Transaccion realizada correctamente"<<endl;
			}
			else{
				cout<<"Transaccion cancelada"<<endl;
			}
		}
	}
}


void calcularLibro(Libro libro){
	system("title Software administraci�n sistema biblioteca - Calcular transacciones de un libro");
	ifstream entradas;
	string buscar;
	int existe, cantidad=0;
	existe = buscaIsbn(libro, buscar);
	if (existe == 1){
		entradas.open("catalogo.csv", ios::in);
		while(!entradas.eof()){
			getline(entradas, buscar);
			stringstream linea(buscar);
			getline(linea, buscar, ';');
			if (buscar == libro.ISBN){
				for(int i=0; i<3; i++){
					getline(linea, buscar, ';');
				}
				while(!linea.eof()){
					string imprimir;
					getline(linea, imprimir, ';');
					if(imprimir != ""){
						stringstream transaccion(imprimir);
							getline(transaccion, imprimir, '-');
							getline(transaccion, imprimir, '-');
							if(stoi(imprimir) == 1){
								cout<<"\tRegistro de transacci�n: "<<endl;
								cout<<"\t\tTipo de transacci�n: ";
								cout<<"Abastecimiento"<<endl;
								getline(transaccion, imprimir, '-');
								cout<<"\t\tFecha de transacci�n: "<<imprimir<<endl;
								getline(transaccion, imprimir, '-');
								cout<<"\t\tCantidad de unidades de transacci�n: "<<imprimir<<endl;
								cantidad++;
							}
					}
				}
			}
		}
		cout<<endl<<"\tTotal de transacciones: "<<cantidad<<endl;
		entradas.close();
	}
}

void masCostoso(Libro libro){
	system("title Software administraci�n sistema biblioteca - Buscar el libro mas costoso");
	ifstream entrada;
	string buscar;
	int mayor;
	mayor = 0;
	entrada.open("catalogo.csv", ios::in);
	while(!entrada.eof()){
		string strPrecio;
		int precio = 0;
		getline(entrada, buscar);
		stringstream linea(buscar);
		for(int i=0; i<4; i++){
			getline(linea, strPrecio, ';');
		}
		if(strPrecio != ""){
			precio = stoi(strPrecio);
		}
		if(precio > mayor){
			mayor = precio;
		}
	}
	entrada.close();
	entrada.open("catalogo.csv", ios::in);
	while(!entrada.eof()){
		string strPrecio;
		int precio;
		getline(entrada, buscar);
		stringstream linea(buscar);
		for(int i=0; i<4; i++){
			getline(linea, strPrecio, ';');
		}
		if(strPrecio != ""){
			precio = stoi(strPrecio);
		}
		linea.seekg(0);
		if(precio == mayor){
			getline(linea, libro.ISBN, ';');
			cout<<"Se ha encontrado el libro de mayor precio con ISBN '"<<libro.ISBN<<"'"<<endl;
					string aux;
					getline(linea, libro.titulo, ';');
					getline(linea, aux, ';'); libro.precioCompra = stoi(aux);
					getline(linea, aux, ';'); libro.precioVenta = stoi(aux);
					getline(linea, aux, ';'); libro.cantidad = stoi(aux);
					imprimirLibro(libro);
					cout<<endl;
					entrada.close();
					break;
		}
	}
}

void menosCostoso(Libro libro){
	system("title Software administraci�n sistema biblioteca - Buscar el libro menos costoso");
	ifstream entrada;
	string buscar;
	int menor = 0, contador = 0;
	entrada.open("catalogo.csv", ios::in);
	while(!entrada.eof()){
		string strPrecio;
		int precio;
		getline(entrada, buscar);
		stringstream linea(buscar);
		for(int i=0; i<4; i++){
			getline(linea, strPrecio, ';');
		}
		if(strPrecio != ""){
			precio = stoi(strPrecio);
		}
		if(contador == 0){
			menor = precio;
			contador++;
		}
		if(precio < menor){
			menor = precio;
		}
	}
	entrada.close();
	entrada.open("catalogo.csv", ios::in);
	while(!entrada.eof()){
		string strPrecio;
		int precio;
		getline(entrada, buscar);
		stringstream linea(buscar);
		for(int i=0; i<4; i++){
			getline(linea, strPrecio, ';');
		}
		if(strPrecio != ""){
			precio = stoi(strPrecio);
		}
		linea.seekg(0);
		if(precio == menor){
			getline(linea, libro.ISBN, ';');
			cout<<"Se ha encontrado el libro de menor precio con ISBN '"<<libro.ISBN<<"'"<<endl;
					string aux;
					getline(linea, libro.titulo, ';');
					getline(linea, aux, ';'); libro.precioCompra = stoi(aux);
					getline(linea, aux, ';'); libro.precioVenta = stoi(aux);
					getline(linea, aux, ';'); libro.cantidad = stoi(aux);
					imprimirLibro(libro);
					cout<<endl;
					entrada.close();
					break;
		}
	}
}

void masVendido(Libro libro){
	system("title Software administraci�n sistema biblioteca - Buscar el libro mas vendido");
	ifstream entrada;
	string buscar, libroM, seleccionar;
	int contadorM=0, contador = 0;
	entrada.open("catalogo.csv", ios::in);
	while(!entrada.eof()){
		getline(entrada, libroM);
		stringstream linea(libroM);
		for(int i=0; i<5; i++){
			getline(linea, buscar, ';');
		}
		while(!linea.eof()){
			getline(linea, buscar, ';');
			stringstream transaccion(buscar);
			getline(transaccion, buscar, '-');
			getline(transaccion, buscar, '-');
			if(buscar == "0"){
				contador++;
			}
		}
		if(contadorM == 0 || (contadorM < contador)){
			contadorM = contador;
			seleccionar = libroM;
		}
	}
	stringstream linea(seleccionar);
	getline(linea, libro.ISBN, ';');
	if(libro.ISBN == ""){
		cout<<"Aun no se realizan transacciones de venta con ning�n libro"<<endl;
	}
	else{
		cout<<"Se ha encontrado el libro mas vendido con ISBN '"<<libro.ISBN<<"'"<<endl;
			string aux;
			getline(linea, libro.titulo, ';');
			getline(linea, aux, ';'); libro.precioCompra = stoi(aux);
			getline(linea, aux, ';'); libro.precioVenta = stoi(aux);
			getline(linea, aux, ';'); libro.cantidad = stoi(aux);
			imprimirLibro(libro);
			cout<<endl;
	}
	entrada.close();
}

void consultarCaja(){
	system("title Software administraci�n sistema biblioteca - Consultar dinero en caja");
	ifstream entrada;
	string valorCaja;
	entrada.open("caja.csv", ios::in);
	getline(entrada, valorCaja);
	entrada.close();
	cout<<"Dinero en caja: $"<<valorCaja<<endl;
}
