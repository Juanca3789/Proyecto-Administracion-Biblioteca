#include <string>
#pragma once
#ifndef LIBRO_H
	#define LIBRO_H
	class Libro{
	private:
		int ISBN{};
		std::string titulo{};
		int precioCompra{};
		int precioVenta{};
		int cantidad{};
		struct Fecha{
			int dia{}, mes{}, anio{};
		};
		class Transaccion{
			private:
				bool tipo{};
				Fecha* fecha;
				int cantidadLibros;
			public:
				Transaccion(bool _tipo, Fecha* _fecha, int _cantidad);
		};
		Fecha* fLibro;
		Transaccion* raiz;
	public:
		Libro();
		void registrarLibro();
		void borrarLibro();
		void comprarLibro();
		void venderLibro();
		int obtenerPrecio();
		Libro* buscarLibroISBN();
		Libro* buscarLibroTitulo();
		Transaccion* transaccionesLibro();
	};
#endif