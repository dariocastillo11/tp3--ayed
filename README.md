# Algoritmos y Estructuras de Datos
# Enunciado Tercer Parcial A˜no 2024 - Promocion

## Planificaci´on de vuelo de un drone

Se dispone de una imagen de un campo de siembra captada por un sat´elite que ha sido procesada por un programa de an´alisis de im´agenes para el
filtrado de malezas y representada por medio de una matriz de ceros, unos y
un valor indeterminado (X), donde el cero representa las posiciones sin maleza, el uno para la presencia de malezas y el valor indeterminado tiene una
funci´on que se explica m´as adelante. La imagen contiene 100 x 100 pixeles.

El objetivo del proyecto es planificar el vuelo de un drone que llegue hasta
los puntos donde hay malezas y aplique un herbicida. Como los puntos blancos son aquellos donde hay malezas, implica que el drone deber´a pasar por
ese punto. Sin embargo, dado que el herbicida tiene un costo importante, solo
ser´a aplicado en lugares donde haya una presencia importante de malezas, lo
cual se representa por una superficie cuadrada de 3x3 puntos, donde figure
el valor 1. Es decir, ud. dispone de un mapa de manchas con valores 1, las
cuales pueden ser peque˜nas (de superficie menor a 3x3) o significativas (de
superficie igual a 3x3 para simplificar el caso).


Para encontrar las manchas de malezas deber´a aplicar un filtro de 3x3
formado por unos, de forma tal que encuentre una mancha de tama˜no m´ınimo
por medio de las operaciones de conjuntos implementados como mapas de
bits y al mover el filtro. Al encontrar una mancha de esta forma, deber´a
definir su posici´on dentro de la imagen en un sistemas de ejes cartesianos 2D
como la posici´on del punto del centro de la matriz de 3x3. La unidad es el
pixel el cual se representa con un valor dentro de la matriz de la imagen.


El punto de partida del vuelo del drone es la coordenada (1,1) que se
representa en la esquina superior izquierda del eje de coordenadas cartesianas. El drone deber´a realizar el vuelo y volver al mismo punto de partida.
Las coordenadas (X,Y) representan fila,columna partiendo desde arriba hacia
abajo para el eje vertical y de izquierda a derecha para el eje horizontal.
1
Una vez determinadas la posiciones de las manchas, deber´a planificar
el recorrido del drone que pase por todas las manchas. La distancia entre
manchas ser´a calculada como el m´odulo vectorial entre puntos dentro de
un sistema de coordenadas 2D. Sin embargo, y a los efectos de poner mayor
realismo al caso, los valores indeterminados en la imagen representan barreras
entre los puntos de las manchas, lo cual implica que no hay una camino
posible entre dos manchas que tienen una barrera entre medio. Las barreras
se representan como filas o columnas de X’s de longitud 4 como m´ınimo.


Ejemplo de una fracci´on de la imagen:

0000000111000110000010001110
0111000111001000011100001110
0111000111000110011100001110
0111000000001000011100000000
00000000000000000000xxxxxxx1
00000111000x0001110000000000
00000111000x0001110000000000
00000111000x0001110000000000
00000000000x0000000000000000
1110000000000000000000000111
1110000000000000000000000111
1110000000000000000000000111
la cual representa 8 manchas con dos barreras que impiden el vuelo entre
algunas de las manchas.


Para resolver el recorrido m´as corto de vuelo, represente las manchas y
distancias como un grafo no dirigido con peso igual a la distancia euclidiana.


El problema se llama ciclo ”Hamiltoneano” ya que debe pasar por todos los
v´ertices una sola vez (salvo el inicio-final), lo cual implica la ausencia de
ciclos en la parte media del camino. Ud. debe determinar la mejor opci´on
para el recorrido, es decir, el ciclo Hamiltoneado de costo m´ınimo. Para ello
deber´a implementar la b´usqueda del ciclo ´optimo aplicando un algoritmo de
b´usqueda en amplitud. En este algoritmo deber´a utilizar una cola de datos.


El programa deber´a leer la imagen desde un archivo, detectar las manchas
y las barreras, calcular la distancia entre las manchas y las opciones de ciclos
y el ciclo Hamiltoneano mas corto detectado.


Se recomienda que el mapa no tenga mas de 10 manchas a recorrer porque el algoritmo del ciclo Hamiltoneado tiene una complejidad alta. Para
determinar si una barrera corta el camino entre dos nodos puede consultar sobre como detectar si dos segmentos de recta en un plano 2D se intersectan en: https://living-sun.com/es/c/223211-how-to-find-whether-two2
line-segmentnottwo-straight-lines-intersect-c-algorithm-computational-geometryxlib-x11.html
3
