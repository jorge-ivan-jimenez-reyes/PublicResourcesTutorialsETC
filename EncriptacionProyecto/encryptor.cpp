#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <cctype>     // Para isalpha y toupper
#include <vector>


//funcion para limpiar el texto
//esta funcion resivira el contenido completo y devolvera una version en la que se eliminen
//caracteres no alfabeticos (excepto espacios) y se convierta too a mayusculas

std::string limpiarTexto(const std::string &texto) {
  std::string resultado;
  for (char c : texto) {
   if (std::isalpha(c) || std::isspace(c)) {
     resultado += std::toupper(c);
     }
   }
     return resultado;
}

//funcion para construir el nuevo alfabeto
//la idea es leer el archivo FASTA, buscar lineas que comiencen con >, y usar el parametro offset
//y un saltoo fijo 20 posiciones para extraer caracteres que formaran un arreglo de 26 letras

//si el offset es mayor que la longitud de la linea actual, pasa a la siguiente linea. Si llega al
//final del archivo, vuelve a abrirlo (o reinicia la lectura) hasta completar los 26 caracteres

std::vector<char> construirAlfabeto(const std::string &fastaFileName, int offset, int intentos) {
  std::vector<char> nuevoAlfabeto;
  std::ifstream fasta(fastaFileName);
  if (!fasta.is_open()) {
    std::cerr << "No se pudo abrir el archivo FASTA: " << fastaFileName << std::endl;
    return nuevoAlfabeto;  // vacio
  }

  std::string linea;
  // Recorremos el archivo buscando líneas que empiecen con '>'
  while (std::getline(fasta, linea)) {
    if (!linea.empty() && linea[0] == '>') {
      // Si la línea es lo suficientemente larga para el offset, procesamos esta línea
      if (offset < linea.size()) {
        // Se extraen 26 caracteres, cada uno con salto de 20 posiciones
        for (int i = 0; i < 26; i++) {
          int pos = offset + (i+1) * 20;  // Ejemplo: para A, pos = offset + 20
          // Si el índice se sale de la línea, se puede hacer un ciclo (por ejemplo, usando módulo)
          if (pos >= linea.size())
            pos = pos % linea.size();  // Ajuste simple; se puede refinar según necesidad
          nuevoAlfabeto.push_back(linea[pos]);
        }
        break;  // Salimos después de construir el alfabeto
      }
    }
  }
  fasta.close();

  // Aplicar reglas especiales de equivalencia en el alfabeto
  // Por ejemplo: Z → B, J → X, O → U, U → O, X → J, B → Z
  // Se pueden ajustar las reglas según lo requiera el enunciado
  for (char &c : nuevoAlfabeto) {
    if (c == 'Z') c = 'B';
    else if (c == 'J') c = 'X';
    else if (c == 'O') c = 'U';
    else if (c == 'U') c = 'O';
    else if (c == 'X') c = 'J';
    else if (c == 'B') c = 'Z';
  }

  return nuevoAlfabeto;
}

//funcion para encriptar una letra, la funcion toma una letra (que ya supone en mayusculas) y
//remplaza segun el nuevo alfabeto

char encriptarLetra(char letra, const std::vector<char> &nuevoAlfabeto) {
  if (std::isalpha(letra)) {
    int indice = letra - 'A';
    if (indice >= 0 && indice < nuevoAlfabeto.size()) {
      return nuevoAlfabeto[indice];
    }
  }
  return letra; // En caso de espacios u otros casos, se retorna sin cambios.
}

