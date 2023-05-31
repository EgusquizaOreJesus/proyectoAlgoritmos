# Informe

## Introducción

En la actualidad, la necesidad de garantizar la seguridad y la integridad de los datos ha impulsado el desarrollo de tecnologías innovadoras en busca de soluciones confiables y eficientes. Entre estas soluciones revolucionarias destaca el Blockchain. Con el paso del tiempo, esta tecnología ha ganado una gran popularidad al ofrecer una forma segura y confiable de almacenar y gestionar datos.

En el marco de este proyecto, nos enfocaremos en la creación de una aplicación transaccional de interacción de datos basada en un Blockchain implementado en un solo host. Para fortalecer la seguridad y mejorar el rendimiento de la aplicación, utilizaremos estructuras de indexación como B-Tree y Hash.

El Blockchain, inicialmente conocido por ser la base de las criptomonedas, ha evolucionado y se ha convertido en una tecnología versátil y confiable para garantizar la integridad de la información. En este proyecto, aprovecharemos su capacidad para almacenar transacciones de manera segura y transparente, combinándola con estructuras de indexación avanzadas como B-Tree y Hash. Esta combinación nos permitirá mejorar la eficiencia y la velocidad de acceso a los datos, brindando una solución robusta y confiable para la gestión de datos transaccionales.

Nuestra aplicación transaccional no solo ofrecerá seguridad y confiabilidad, sino que también permitirá a los usuarios interactuar de manera rápida y segura con los datos. Además, la implementación de un mecanismo de "proof of work" garantizará la integridad y la confiabilidad de cada transacción realizada en la aplicación.

En resumen, este proyecto busca aprovechar las capacidades del Blockchain y las estructuras de indexación avanzadas para desarrollar una aplicación transaccional de alta calidad. A través de esta solución innovadora, esperamos brindar a los usuarios una experiencia óptima al interactuar con los datos, asegurando su integridad y confiabilidad en todo momento.

## Descripción del caso de estudio

En este proyecto, nuestro enfoque principal es desarrollar una aplicación transaccional basada en la tecnología del Blockchain, con un enfoque específico en las transacciones de Bitcoin. Nuestro objetivo es crear una plataforma segura y confiable para el registro y la gestión de estas transacciones, garantizando la integridad y la seguridad de los datos en un contexto donde el uso de criptomonedas continúa creciendo.

Nuestra aplicación permitirá a los usuarios registrar transacciones de Bitcoin de forma segura, transparente y eficiente. Utilizaremos la tecnología del Blockchain para mantener un historial completo y verificable de todas las operaciones, manteniendo un registro ordenado cronológicamente.

Además, implementaremos estructuras de indexación avanzadas, como el B-Tree y el Hash, para mejorar el rendimiento y la eficiencia en la búsqueda de transacciones específicas. Esto facilitará a los usuarios encontrar y analizar rápidamente la información relevante de las transacciones de Bitcoin.

Para asegurar la integridad de los bloques de transacciones, implementaremos un mecanismo de "proof of work". Esto garantizará que cualquier alteración en un bloque requiera un esfuerzo computacional significativo, añadiendo una capa adicional de seguridad a nuestras transacciones de Bitcoin.

En resumen, nuestro caso de estudio se centra en desarrollar una aplicación transaccional basada en Blockchain para la gestión de las transacciones de Bitcoin. Aprovecharemos las ventajas del Blockchain, junto con estructuras de indexación avanzadas y un mecanismo de "proof of work", para ofrecer una solución confiable, eficiente y segura en la gestión de operaciones con criptomonedas.

## Importancia del Blockchain en el dominio de datos elegido

El blockchain es una tecnología revolucionaria que brinda una amplia gama de beneficios, incluyendo seguridad, transparencia y confiabilidad en el registro y verificación de transacciones digitales. Su capacidad para garantizar la inmutabilidad de los datos y resistir modificaciones lo convierte en una herramienta invaluable en diversos campos, abarcando más allá del ámbito financiero.

En el contexto específico de nuestro proyecto, estamos utilizando el blockchain en el ámbito financiero para registrar y gestionar datos relacionados con las transacciones de los usuarios. Estos datos incluyen información crucial como el monto de las transacciones, el tipo de transacción y la fecha en que se realizaron. Al emplear la tecnología blockchain, estamos facilitando el intercambio de montos digitales, permitiendo la creación de carteras digitales y asegurando un registro exhaustivo de todas las actividades realizadas por los usuarios en fechas específicas.

Esta implementación del blockchain en el ámbito financiero nos brinda una plataforma segura y confiable para llevar a cabo operaciones financieras digitales. Además, nos proporciona un nivel de transparencia y trazabilidad sin precedentes, lo que resulta crucial en la era de la digitalización y la creciente necesidad de confianza en las transacciones realizadas en línea. Con el blockchain, podemos garantizar que cada transacción realizada sea registrada de manera precisa, segura y verificable, estableciendo así una base sólida para el éxito y la confianza en nuestro proyecto financiero.

## Estructura de datos del Blockchain y estrategia de integridad

El Blockchain, como una estructura de datos descentralizada y distribuida, presenta una cadena de bloques enlazados mediante referencias criptográficas. Cada bloque contiene un conjunto de transacciones y un hash único que identifica al bloque anterior. Esta característica fundamental crea una cadena inmutable, donde cualquier alteración en un bloque afecta a todos los bloques siguientes.

En nuestro caso, hemos implementado una estructura de datos de Blockchain en un solo host, aprovechando las ventajas de las estructuras B-Tree y Hash. El B-Tree se utiliza para organizar eficientemente las transacciones, permitiendo una búsqueda y recuperación rápidas. Por otro lado, el Hash se emplea para calcular una representación criptográfica única de cada bloque, garantizando así la integridad de su contenido.

Al emplear estas sólidas estructuras de datos, nuestra aplicación transaccional garantiza la seguridad y la confiabilidad en el registro y la gestión de las transacciones de Bitcoin. La combinación del Blockchain, el B-Tree, el Hash y el mecanismo de prueba de trabajo crea una solución robusta y resistente a manipulaciones. Asimismo, es importante destacar que existen otros pares en la red que tienen una copia exacta del Blockchain, lo que permite realizar comparaciones y detectar cualquier cambio no autorizado.

En resumen, nuestra aplicación transaccional se basa en una estructura de datos de Blockchain, potenciada por el uso eficiente del B-Tree y el Hash. Esta combinación garantiza la seguridad y la integridad de las transacciones de Bitcoin, proporcionando un entorno confiable para interactuar con los datos de manera segura y confiable.

## Estructuras de datos utilizadas en la aplicación

Se están utilizando tres estructuras de datos con el objetivo de almacenar información y realizar consultas eficientes sobre las transacciones. Estas estructuras son fundamentales para garantizar un almacenamiento organizado y un acceso rápido a los datos transaccionales.

![Ejemplo de imagen](https://media.discordapp.net/attachments/996002132891271188/1113317306651660368/image.png?width=1025&height=316)

1. **Hash:**
   - Indexamos al usuario y a la transacción.
   - Objetivo: Acceder rápidamente al linked list correspondiente.

2. **LinkedList:**
   - Indexamos las transacciones con información como el ID, emisor, receptor, monto y fecha.
   - Objetivo: Almacenar la información de la transacción con la indexación de hash.

3. **Btree:**
   - Indexamos las transacciones por fecha.
   - Utilizado para realizar búsquedas por rango entre fechas A y B.
   - Objetivo: Poder realizar consultas de tipo fecha eficientemente.

## Análisis de la complejidad en notación Big O

| Método                  | Complejidad |
|-------------------------|-------------|
| Buscar bloque (id)      | O(1)        |
| Buscar fecha            | O(log(n))   |
| Buscar por rango de fechas | O(log(n)) |
| Insertar Bloque         | O(log(n))   |
| Buscar usuario          | O(1)        |
| Buscar transacción      | O(1)        |


## Tabla comparativa de Blockchain con índices vs sin índices

|                     | Con índices | Sin índices |
|---------------------|-------------|-------------|
| Buscar bloque (id)  | O(1)        | O(n)        |
| Buscar fecha        | O(log(n))   | O(n*k)      |
|                     |             | Siendo “k” la media de número de transacciones en un blockchain. |
| Buscar por rango de fechas | O(log(n)) | O(n) |
| Insertar bloque     | O(log(n))   | O(1)        |
| Buscar usuario      | O(1)        | O(n)        |
| Buscar transacción  | O(1)        | O(n)        |


## Conclusiones

En esta sección, se presentan las conclusiones clave del estudio realizado, resumiendo los resultados obtenidos y destacando los puntos más relevantes relacionados con el uso del Blockchain en el dominio de datos elegido.

Hemos aprendido que la construcción de un blockchain puede realizarse mediante el uso de una lista enlazada. Sin embargo, también hemos comprendido que, para lograr consultas más eficientes y específicas, es esencial incorporar estructuras de datos adicionales, como el hash o el árbol B.

La implementación adecuada de estas estructuras de datos nos permite optimizar el rendimiento de nuestro software, evitando ineficiencias y mejorando la usabilidad del sistema en su conjunto. Con conocimientos sólidos sobre cómo estructurar la información y hacer uso eficiente de las estructuras de datos, podemos alcanzar resultados notables y aprovechar al máximo las capacidades de la computación.

## Referencias bibliográficas

Se incluye una lista de las referencias bibliográficas utilizadas durante el proceso de investigación y elaboración del informe.

## Actividades concluidas por cada integrante del grupo

En este apartado, se presenta una lista detallada de las actividades concluidas por cada integrante del grupo, lo cual permite destacar las contribuciones individuales y resaltar el trabajo en equipo.

A continuación, se muestra un resumen de las actividades realizadas por cada miembro del grupo:

| Integrantes del Grupo          | Actividades Realizadas               |
|--------------------------------|--------------------------------------|
| Fabricio, Jesús, Ximena y Edgar| Investigación y estudio de problemas |
| Fabricio, Jesús, Ximena y Edgar| Diseño y desarrollo de algoritmos    |
| Fabricio y Jesús               | Programación y desarrollo de software| 
| Fabricio, Jesús, Ximena y Edgar| Análisis de datos y modelado         |
| Fabricio, Jesús, Ximena y Edgar| Diseño de sistemas y arquitectura    |
| Ximena y Edgar                 | Documentación y presentación         |
| Fabricio y Jesús               | Pruebas y evaluación                 |



