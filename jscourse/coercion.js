// ===========================================
// COERCIÓN EN JAVASCRIPT
// ===========================================

/**
 * La coerción es el proceso mediante el cual JavaScript convierte
 * automáticamente un tipo de dato en otro cuando se realizan operaciones
 * entre valores de diferentes tipos.
 * 
 * Existen dos tipos principales de coerción:
 * 1. Coerción implícita: ocurre automáticamente
 * 2. Coerción explícita: cuando el desarrollador la realiza intencionalmente
 */

// ===========================================
// COERCIÓN IMPLÍCITA
// ===========================================

// 1. Coerción a String
console.log("--- Coerción implícita a String ---");
console.log("Hola " + 123);            // "Hola 123" (número a string)
console.log("true" + true);            // "truetrue" (booleano a string)
console.log([1, 2, 3] + " elementos"); // "1,2,3 elementos" (array a string)
console.log({} + " objeto");           // "[object Object] objeto"

// 2. Coerción a Número
console.log("--- Coerción implícita a Número ---");
console.log("5" - 2);                  // 3 (string a número)
console.log("5" * 2);                  // 10 (string a número)
console.log("10" / 2);                 // 5 (string a número)
console.log(true + 1);                 // 2 (booleano a número: true → 1)
console.log(false + 5);                // 5 (booleano a número: false → 0)

// 3. Coerción a Booleano (en contextos condicionales)
console.log("--- Coerción implícita a Booleano ---");

// En condiciones if, estos valores se convierten a false (falsy values):
const falsyValues = [0, "", null, undefined, NaN, false];

// En condiciones if, estos valores se convierten a true (truthy values):
const truthyValues = [1, "hello", [], {}, function() {}, true, "0", "false"];

// Demo con if para falsy values
if (0) {
    console.log("Este mensaje no se mostrará");
} else {
    console.log("0 se convierte a false");
}

// Demo con if para truthy values
if ("hello") {
    console.log("'hello' se convierte a true");
}

// ===========================================
// COERCIÓN EXPLÍCITA
// ===========================================

console.log("--- Coerción explícita ---");

// 1. Conversión explícita a String
console.log(String(123));              // "123"
console.log(String(true));             // "true"
console.log(String(null));             // "null"
console.log(String(undefined));        // "undefined"
console.log((123).toString());         // "123"

// 2. Conversión explícita a Número
console.log(Number("123"));            // 123
console.log(Number(""));               // 0
console.log(Number(true));             // 1
console.log(Number(false));            // 0
console.log(parseInt("123.45", 10));   // 123 (sólo la parte entera)
console.log(parseFloat("123.45"));     // 123.45

// 3. Conversión explícita a Booleano
console.log(Boolean(1));               // true
console.log(Boolean(0));               // false
console.log(Boolean("hello"));         // true
console.log(Boolean(""));              // false
console.log(Boolean(null));            // false
console.log(Boolean(undefined));       // false

// ===========================================
// CASOS PRÁCTICOS Y EJEMPLOS COMUNES
// ===========================================

console.log("--- Casos prácticos ---");

// 1. El operador '+' con strings y números
let score = "10";
console.log(score + 5);                // "105" (coerción a string)
console.log(+score + 5);               // 15 (coerción a número con unary '+')

// 2. Comparación con == vs === 
console.log("5" == 5);                 // true (con coerción)
console.log("5" === 5);                // false (sin coerción)

// 3. Operador ternario con coerción a booleano
const message = score ? "Tienes puntos" : "No tienes puntos";
console.log(message);                  // "Tienes puntos" (string no vacío es truthy)

// 4. Ejemplo práctico: validación de entrada
function validarEntrada(input) {
    // Coerción de input a booleano - si es "", 0, null o undefined será false
    if (!input) {
        return "Por favor ingrese un valor";
    }
    return "Valor válido: " + input;
}

console.log(validarEntrada(""));       // "Por favor ingrese un valor"
console.log(validarEntrada("Hola"));   // "Valor válido: Hola"

// 5. Trucos comunes usando coerción
console.log(+"42");                    // 42 (string a número con operador unario +)
console.log(!!0);                      // false (doble negación para convertir a booleano)
console.log(!!1);                      // true
console.log([1, 2, 3] == "1,2,3");     // true (el array se convierte a string "1,2,3")

// 6. Operaciones con objetos
console.log({} + []);                  // "[object Object]" (puede variar según navegador)
console.log([] + {});                  // "[object Object]"

// 7. El caso especial del operador ==
console.log(null == undefined);        // true
console.log("0" == false);             // true (ambos se convierten a 0)

