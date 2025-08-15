# 🏗️ CPP Module 09 – STL, Ford-Johnson y Números de Jacobsthal

> ✅ **Objetivo:** Dominar el uso de la STL de C++, containers estándar y algoritmos avanzados como Ford-Johnson Merge-Insertion Sort, con especial atención al uso de la secuencia de Jacobsthal en optimización de inserciones.  
> ✅ **Nivel:** Avanzado  
> ✅ **Temas clave:** STL (`std::vector`, `std::list`, etc.), manejo eficiente de containers, algoritmos de ordenación avanzados, Ford-Johnson (Merge-Insertion Sort), secuencia de Jacobsthal, eficiencia y benchmarking.

---

## 📚 Tabla de Contenidos

1. [¿Qué es la STL y por qué es importante?](#-qué-es-la-stl-y-por-qué-es-importante)
2. [Reglas Específicas del Módulo](#-reglas-específicas-del-módulo)
3. [Ejercicio 00 – Bitcoin Exchange](#ejercicio-00--bitcoin-exchange)
4. [Ejercicio 01 – Reverse Polish Notation](#ejercicio-01--reverse-polish-notation-rpn)
5. [Ejercicio 02 – PmergeMe (Ford-Johnson y Jacobsthal)](#ejercicio-02--pmergeme-ford-johnson-y-jacobsthal)
6. [Tabla Resumen de Containers y Algoritmos](#-tabla-resumen-de-containers-y-algoritmos)
7. [Errores Comunes](#-errores-comunes)
8. [Buenas Prácticas](#-buenas-prácticas)

---

## ✨ ¿Qué es la STL y por qué es importante?

La **STL (Standard Template Library)** es el corazón de la programación moderna en C++. Proporciona:
- **Containers**: estructuras de datos genéricas como `std::vector`, `std::list`, `std::map`, `std::deque`, etc.
- **Algoritmos**: funciones para ordenar, buscar, modificar y manipular datos eficientemente.
- **Iteradores**: punteros genéricos que permiten recorrer cualquier container de manera uniforme.

**Ventajas de la STL:**
- Código más seguro, eficiente y reutilizable.
- Gran variedad de estructuras optimizadas.
- Separación clara entre almacenamiento y manipulación.

---

## 🔹 Reglas Específicas del Módulo

- Es obligatorio usar al menos un container STL diferente por ejercicio (en PmergeMe, usar dos containers diferentes).
- Una vez uses un container para validar un ejercicio, no puedes volver a usarlo en el módulo.
- El Makefile debe compilar con las reglas estándar y no relinkear.
- Lee todo el subject antes de empezar: los requisitos a veces se descubren en los ejemplos o detalles.

---

## Ejercicio 00 – **Bitcoin Exchange**

- **Objetivo:** Leer una base de datos de precios de bitcoin y calcular el valor de una cantidad dada en una fecha concreta.
- **Container sugerido:** `std::map` para asociar fechas y precios.
- **Requisitos:**
  - El programa se llama `btc` y recibe un archivo como argumento.
  - Procesa líneas formato `"date | value"`.
  - Valida fechas y valores, maneja errores.
  - Si la fecha no está en la base de datos, usa la más próxima inferior disponible.
- **Ejemplo de uso:**
  ```
  $> ./btc input.txt
  2011-01-03 => 3 = 0.9
  Error: bad input => 2001-42-42
  ```

---

## Ejercicio 01 – **Reverse Polish Notation (RPN)**

- **Objetivo:** Calculadora que procesa expresiones en notación polaca inversa usando un container estándar.
- **Container sugerido:** `std::stack` o `std::deque`.
- **Requisitos:**
  - El programa se llama `RPN`.
  - Toma la expresión como argumento.
  - Soporta `+ - / *`.
  - Maneja errores y muestra mensajes claros.
- **Ejemplo:**
  ```
  $> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
  42
  ```

---

## Ejercicio 02 – **PmergeMe (Ford-Johnson y Jacobsthal)**

### 🔥 Algoritmo Merge-Insertion Sort (Ford-Johnson)

El objetivo es implementar el **algoritmo Ford-Johnson** (también conocido como **Merge-Insertion Sort**), uno de los algoritmos de ordenación más eficientes en el número de comparaciones.  
**Referencia:** Knuth, "The Art of Computer Programming", Vol.3, Merge Insertion, pág. 184.

### 🧮 ¿Cómo funciona Ford-Johnson (Merge-Insertion Sort) + Jacobsthal?

**Resumen:**  
El algoritmo Ford-Johnson ordena una secuencia de números minimizando el número de comparaciones. Se basa en agrupar elementos en parejas, ordenar cada pareja, construir una lista parcialmente ordenada y luego insertar los elementos “pendientes” en posiciones calculadas usando la secuencia de Jacobsthal.

---

#### **Mini ejemplo: ordenar [7, 3, 2, 8, 5]**

1. **Emparejar y ordenar**  
   - Agrupa los elementos en parejas (si hay un impar, uno queda solo):  
     Pares: (7, 3), (2, 8), [5]  
   - Ordena cada pareja internamente:  
     (3, 7), (2, 8), [5]  
   - Separa los menores (“pendientes”) y los mayores (“ordenados”):  
     - Ordenados (mayores): [7, 8]  
     - Pendientes (menores): [3, 2]  
     - [5] queda pendiente porque no tenía pareja.

2. **Ordena los “ordenados”**  
   - Ordena la lista de mayores:  
     [7, 8] → [7, 8] (ya está ordenado, pero en general se hace un sort recursivo si hay más de dos)

3. **Inserta los “pendientes” usando Jacobsthal**  
   - La secuencia de Jacobsthal para 3 elementos pendientes es: 1°, 3°, 2° (índices relativos).
   - Inserta los pendientes en el orden Jacobsthal sobre la lista ordenada:
     - Inserta 3 → [3, 7, 8]
     - Inserta 2 → [2, 3, 7, 8]
     - Inserta 5 → [2, 3, 5, 7, 8]

4. **Resultado final:**  
   - [2, 3, 5, 7, 8]

---

#### **¿Qué hace la secuencia de Jacobsthal?**

La secuencia de Jacobsthal determina el orden en que se insertan los elementos pendientes para minimizar comparaciones.  
Por ejemplo, para 3 elementos pendientes, el orden óptimo es: primero el 1°, luego el 3°, luego el 2°.

---

**Resumen visual del proceso:**
```
Original: [7, 3, 2, 8, 5]
Pares ordenados: (3, 7), (2, 8), [5]
Ordenados: [7, 8]
Pendientes: [3, 2, 5]
Jacobsthal: inserta en orden 1°, 3°, 2°
Resultado final: [2, 3, 5, 7, 8]
```

### 📐 Uso de la Secuencia de Jacobsthal

- **¿Por qué la secuencia de Jacobsthal?**
  - Determina el orden óptimo de inserciones entre los elementos "pendientes" durante el merge-insert.
  - Minimiza el número de comparaciones y mejora la eficiencia.
  - La secuencia de Jacobsthal se define recursivamente:
    ```
    J(0) = 0
    J(1) = 1
    J(n) = J(n-1) + 2*J(n-2) para n > 1
    ```
  - Esta secuencia se utiliza para decidir en qué posiciones se deben insertar los elementos sobrantes del proceso de emparejamiento.

### 🧑‍💻 Detalles del ejercicio

- El programa se llama `PmergeMe` y recibe una secuencia de enteros positivos como argumentos.
- Debe usar **dos containers diferentes** (por ejemplo, `std::vector` y `std::deque`).
- Ordena la secuencia usando el Ford-Johnson y muestra:
  - La secuencia original.
  - La secuencia ordenada.
  - El tiempo usado con cada container (con precisión suficiente para comparar).
- Debe ser capaz de manejar al menos 3000 elementos de forma eficiente.
- La implementación del algoritmo debe estar separada y optimizada para cada container (no genérica).

**Ejemplo de uso:**
```
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00031 us
Time to process a range of 5 elements with std::deque : 0.00014 us
```

---

## 📊 Tabla Resumen de Containers y Algoritmos

| Ejercicio        | Container principal  | Algoritmo clave                      | Restricción especial                    |
|------------------|---------------------|--------------------------------------|-----------------------------------------|
| Bitcoin Exchange | `std::map`          | Búsqueda por clave                   | No reutilizable en otros ejercicios     |
| RPN              | `std::stack`/`deque`| Stack arithmetic                     | No reutilizable en otros ejercicios     |
| PmergeMe         | `vector`, `deque`   | Ford-Johnson (Merge-Insertion) + Jacobsthal | Dos containers distintos, implementaciones separadas |

---

## 🔹 Errores Comunes

❌ Repetir containers en diferentes ejercicios  
❌ No manejar errores de input o duplicados  
❌ No medir con precisión el tiempo de ejecución  
❌ Implementar PmergeMe de forma genérica (debe estar duplicado para cada container)  
❌ No usar la secuencia de Jacobsthal en las inserciones  
❌ Acceder fuera de los límites del container

---

## 🔹 Buenas Prácticas

✅ Comentar y documentar el algoritmo Ford-Johnson  
✅ Mostrar cómo y para qué se usa Jacobsthal  
✅ Medir tiempos de forma clara y repetible  
✅ Separar claramente las implementaciones por container  
✅ Gestionar errores y mensajes de usuario correctamente  
✅ Usar iteradores de la STL para mayor eficiencia

---

## Autor 🤝💡📬

<div align="center">
  <a href="https://github.com/jfercode">
    <img src="https://github.com/jfercode.png" width="100px" alt="Javier Fernández Correa" />
    <br />
    <sub><b>Javier Fernández Correa</b></sub>
  </a>
</div>

---

## Licencia 📜✅🗝️

Este proyecto está bajo la licencia MIT.
