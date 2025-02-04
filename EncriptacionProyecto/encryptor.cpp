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

int main() {
    // Medir el tiempo de ejecución
    auto inicio = std::chrono::high_resolution_clock::now();

    // Abrir el archivo Original_Document.txt
    std::ifstream entrada("Original_Document.txt");
    if (!entrada.is_open()) {
        std::cerr << "No se pudo abrir Original_Document.txt" << std::endl;
        return 1;
    }

    std::string linea, llave;
    // La primera línea es la llave de encriptación (ejemplo: "#file1.fasta,68,2")
    if (std::getline(entrada, linea)) {
        // Eliminar el carácter '#' si existe
        if (!linea.empty() && linea[0] == '#')
            llave = linea.substr(1);
        else
            llave = linea;
    } else {
        std::cerr << "El archivo está vacío o no contiene llave" << std::endl;
        return 1;
    }

    // Parsear la llave: se espera el formato "file1.fasta,68,2"
    std::istringstream iss(llave);
    std::string fastaFile;
    std::string temp;
    int offset = 0, intentos = 0;
    if (std::getline(iss, fastaFile, ',') &&
        std::getline(iss, temp, ',')) {
        offset = std::stoi(temp);
        if (std::getline(iss, temp, ',')) {
            intentos = std::stoi(temp);
        }
    } else {
        std::cerr << "Formato de llave incorrecto." << std::endl;
        return 1;
    }

    // Leer el resto del archivo (el mensaje a encriptar)
    std::string contenido, parte;
    while (std::getline(entrada, parte)) {
        contenido += parte + "\n";
    }
    entrada.close();

    // Limpiar el texto (quitar caracteres no alfabéticos y pasar a mayúsculas)
    std::string textoLimpio = limpiarTexto(contenido);

    // Guardar el texto limpio en Original_Document.mod
    std::ofstream mod("Original_Document.mod");
    if (!mod.is_open()) {
        std::cerr << "No se pudo crear Original_Document.mod" << std::endl;
        return 1;
    }
    mod << textoLimpio;
    mod.close();

    // Construir el nuevo alfabeto de encriptación a partir del FASTA
    std::vector<char> nuevoAlfabeto = construirAlfabeto(fastaFile, offset, intentos);
    if (nuevoAlfabeto.size() != 26) {
        std::cerr << "No se pudo construir el alfabeto correctamente." << std::endl;
        std::cout << "No se pudo codificar" << std::endl;
        return 1;
    }

    // Encriptar el texto
    std::string textoEncriptado;
    for (char c : textoLimpio) {
        if (std::isspace(c))
            textoEncriptado += c;
        else
            textoEncriptado += encriptarLetra(c, nuevoAlfabeto);
    }

    // Guardar el texto encriptado en Original_Document.cod
    std::ofstream cod("Original_Document.cod");
    if (!cod.is_open()) {
        std::cerr << "No se pudo crear Original_Document.cod" << std::endl;
        return 1;
    }
    cod << textoEncriptado;
    cod.close();

    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;

    std::cout << "Encriptación completada en " << duracion.count() << " segundos." << std::endl;

    return 0;
}