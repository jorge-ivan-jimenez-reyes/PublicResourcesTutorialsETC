//desencrpitador

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>

//reconstruir el alfabeto original
//Esta función leerá el archivo FASTA indicado en las instrucciones (del archivo Intruction_to_decode.txt), utilizando el offset y un parámetro (por ejemplo, el número de líneas a procesar).

//    Nota: Puedes reutilizar la lógica de construirAlfabeto del encriptador, ajustándola si las instrucciones para desencriptar requieren procesar, por ejemplo, las primeras 30 líneas.
std::vector<char> reconstruirAlfabeto(const std::string &fastaFileName, int offset, int numLineas) {
    std::vector<char> alfabeto;
    std::ifstream fasta(fastaFileName);
    if (!fasta.is_open()) {
        std::cerr << "No se pudo abrir el archivo FASTA: " << fastaFileName << std::endl;
        return alfabeto;
    }

    std::string linea;
    int lineasProcesadas = 0;
    // Se procesan las primeras numLineas que sean encabezados (inician con '>')
    while (std::getline(fasta, linea) && lineasProcesadas < numLineas) {
        if (!linea.empty() && linea[0] == '>') {
            // Extraer 26 caracteres con la misma lógica de desplazamiento de 20
            for (int i = 0; i < 26; i++) {
                int pos = offset + (i+1) * 20;
                if (pos >= linea.size())
                    pos = pos % linea.size();
                alfabeto.push_back(linea[pos]);
            }
            lineasProcesadas++;
        }
    }
    fasta.close();

    // Aplicar nuevamente las reglas especiales para obtener el alfabeto original
    for (char &c : alfabeto) {
        if (c == 'Z') c = 'B';
        else if (c == 'J') c = 'X';
        else if (c == 'O') c = 'U';
        else if (c == 'U') c = 'O';
        else if (c == 'X') c = 'J';
        else if (c == 'B') c = 'Z';
    }

    // Para este ejemplo, se asume que se usa solo la primera reconstrucción (26 caracteres)
    if (alfabeto.size() > 26)
        alfabeto.resize(26);

    return alfabeto;
}

//b) Función para Desencriptar una Letra
//Esta función hará la búsqueda inversa: dada una letra encriptada, se localiza en el nuevo alfabeto y se determina cuál es la letra original (basándose en la posición).
char desencriptarLetra(char letra, const std::vector<char> &alfabetoOriginal) {
    // Se busca el índice en el alfabeto encriptado
    for (int i = 0; i < alfabetoOriginal.size(); i++) {
        if (alfabetoOriginal[i] == letra)
            return 'A' + i; // Retorna la letra original correspondiente
    }
    return letra; // Si no se encuentra (o es espacio), se retorna sin cambios
}
//funcion main
int main() {
    // Abrir el archivo encriptado
    std::ifstream cod("Original_Document.cod");
    if (!cod.is_open()) {
        std::cerr << "No se pudo abrir Original_Document.cod" << std::endl;
        return 1;
    }
    std::stringstream buffer;
    buffer << cod.rdbuf();
    std::string textoEncriptado = buffer.str();
    cod.close();

    // Abrir el archivo de instrucciones para desencriptar
    std::ifstream instrucciones("Intruction_to_decode.txt");
    if (!instrucciones.is_open()) {
        std::cerr << "No se pudo abrir Intruction_to_decode.txt" << std::endl;
        return 1;
    }

    std::string lineaInstruccion;
    std::getline(instrucciones, lineaInstruccion);
    instrucciones.close();

    // Se espera un formato similar a "file1.fasta,68,30"
    std::istringstream iss(lineaInstruccion);
    std::string fastaFile;
    std::string temp;
    int offset = 0, numLineas = 0;
    if (std::getline(iss, fastaFile, ',') &&
        std::getline(iss, temp, ',')) {
        offset = std::stoi(temp);
        if (std::getline(iss, temp, ',')) {
            numLineas = std::stoi(temp);
        }
    } else {
        std::cerr << "Formato de instrucciones incorrecto." << std::endl;
        return 1;
    }

    // Reconstruir el alfabeto original usando las instrucciones
    std::vector<char> alfabetoOriginal = reconstruirAlfabeto(fastaFile, offset, numLineas);
    if (alfabetoOriginal.size() != 26) {
        std::cerr << "No se pudo reconstruir el alfabeto correctamente." << std::endl;
        return 1;
    }

    // Desencriptar el texto
    std::string textoDesencriptado;
    for (char c : textoEncriptado) {
        if (std::isspace(c))
            textoDesencriptado += c;
        else
            textoDesencriptado += desencriptarLetra(c, alfabetoOriginal);
    }

    // Guardar el texto desencriptado en un nuevo archivo
    std::ofstream salida("Original_Document_recuperado.txt");
    if (!salida.is_open()) {
        std::cerr << "No se pudo crear Original_Document_recuperado.txt" << std::endl;
        return 1;
    }
    salida << textoDesencriptado;
    salida.close();

    std::cout << "Desencriptación completada." << std::endl;
    return 0;
}