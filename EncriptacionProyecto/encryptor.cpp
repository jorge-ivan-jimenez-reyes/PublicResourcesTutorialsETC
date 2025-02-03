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

