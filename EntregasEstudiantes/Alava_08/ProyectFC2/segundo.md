# **Introducción**

El magnetismo es una de las fuerzas fundamentales de la naturaleza, manifestándose a través de los campos magnéticos que permean el espacio e interactúan con la materia. Una de sus aplicaciones, es la manipulación y el confinamiento de la materia sin contacto físico, lo que da lugar a las trampas magnéticas. El principio de estas trampas se basa en la interacción entre un campo magnético no uniforme y el momento magnético de un objeto, ya sea intrínseco o inducido.

  

Todos los materiales responden de alguna manera a los campos magnéticos. En particular, los materiales diamagnéticos son repelidos por las regiones de campo magnético intenso y atraídos hacia los mínimos de campo. Esta propiedad permite diseñar configuraciones de imanes que generan un punto de equilibrio estable donde un objeto diamagnético puede levitar.

  

Este proyecto se centra en el análisis de una configuración magnética en particular, un sistema compuesto por dos líneas paralelas de dipolos magnéticos. Esta disposición, que puede construirse utilizando un par de imanes cilíndricos con magnetización diametral, genera una forma de energía potencial muy singular en el espacio intermedio. La característica más notable es la formación de un potencial de confinamiento unidimensional con una estructura de "doble joroba" o "camelback". Este potencial no solo atrapa un objeto diamagnético en una posición de levitación estable, sino que también lo confina a lo largo del eje del sistema, permitiendo un movimiento oscilatorio bien definido.

  

El estudio detallado de la dinámica de un objeto dentro de esta trampa permite establecer una conexión directa entre sus parámetros de movimiento observables (como el período de oscilación) y sus propiedades magnéticas intrínsecas. Además, las características del campo magnético generado lo convierten en un candidato ideal para ser adaptado a técnicas de medición avanzadas, como la caracterización de materiales semiconductores mediante el efecto Hall.

  

## **Objetivos del Proyecto**

El propósito de este proyecto es desarrollar un modelo computacional para investigar a fondo este sistema magnético. Los objetivos específicos son:

  

Modelar el Sistema y Caracterizar el Potencial de Confinamiento: Desarrollar una implementación numérica para calcular el campo magnetostático del sistema. Se utilizará este modelo para analizar la estructura del potencial de energía resultante y caracterizar sus propiedades como trampa para objetos diamagnéticos.

  

Simular la Dinámica y Explorar Métodos de Medición: Simular el movimiento clásico de un objeto cilíndrico dentro de la trampa. El objetivo es investigar su comportamiento oscilatorio y establecer una relación cuantitativa entre los parámetros de su movimiento (como el período) y sus propiedades magnéticas intrínsecas (como la susceptibilidad).

  

Desarrollar una Herramienta de Procesamiento de Señales: Implementar un algoritmo de detección lock-in numérico. Se utilizarán datos sintéticos para demostrar la capacidad de esta técnica para extraer señales periódicas débiles que se encuentran ocultas por un ruido de fondo considerable.

# **Marco Teórico**

### **Campo Magnético de un Imán Diametral**

El bloque de construcción fundamental de nuestro sistema es un imán cilíndrico con una magnetización uniforme $$\vec{M}$$ a lo largo de su diámetro (por ejemplo, en la dirección $$\hat{x}$$). El campo magnético $$\vec{B}$$ en un punto arbitrario del espacio $$(x, y, z)$$ generado por un solo imán de radio $$a$$ y longitud $$L$$, centrado en el origen, se puede calcular a partir del potencial escalar magnético. La expresión vectorial exacta es:

  
  

$$\vec{B}_{DM}(x,y,z) = \frac{\mu_{0}Ma}{4\pi} \int_{0}^{2\pi} \sum_{n=1,2} \frac{(-1)^{n}\cos\phi}{u_{n}^{2}+s^{2}+u_{n}\sqrt{u_{n}^{2}+s^{2}}} \times \begin{bmatrix} x-a\cos\phi \\ y-a\sin\phi \\ u_{n}+\sqrt{u_{n}^{2}+s^{2}} \end{bmatrix} d\phi$$

  
  

donde:

 $$\mu_0$$ es la permeabilidad del vacío.

$$M$$ es la magnitud de la magnetización del imán.

$$s^2 = (x-a\cos\phi)^2 + (y-a\sin\phi)^2$$ es la distancia radial al cuadrado desde el punto de evaluación a un elemento en la superficie del imán.

$$u_{1,2} = z \pm L/2$$ representa las distancias a los extremos del imán.

La integral se realiza sobre la coordenada acimutal $$\phi$$ de la superficie del cilindro.

  

El campo total del sistema de par de imanes (DMP) se obtiene por el principio de superposición, sumando los campos de dos de estos imanes centrados en $$(\pm a, 0, 0)$$.

  
  
  

### **Energía Potencial y Fuerza sobre un Objeto Diamagnético**

  

Un objeto diamagnético, como una varilla de grafito, al ser colocado en un campo magnético externo $$\vec{B}_T$$, desarrolla una magnetización inducida $$\vec{M}_R$$ opuesta al campo. Para una varilla cilíndrica con susceptibilidad magnética $$\chi$$, esta magnetización es:

  

$$\vec{M}_R = \frac{2\chi}{\mu_0(2+\chi)} \vec{B}_T$$

  

La energía potencial magnética por unidad de volumen ($$U'_M$$) de la varilla en el campo magnético se deriva de esta magnetización inducida y es proporcional al cuadrado de la magnitud del campo:

  

$$U'_{M}(y_0,z) = -\frac{\chi}{\mu_0(2+\chi)} B_{T}^{2}(y_0,z)$$

  

Dado que para un material diamagnético $$\chi < 0$$, la energía potencial es mínima donde la magnitud del campo magnético $$B_T$$ es mínima.El objeto es, por lo tanto, empujado hacia las regiones de campo débil. La fuerza magnética total sobre la varilla se obtiene del gradiente de la energía potencial total ($$U_M = U'_M \cdot V_{R}$$). La condición de levitación estable se alcanza cuando la fuerza magnética equilibra la fuerza gravitacional. En la altura de equilibrio $$y_0$$, la fuerza neta vertical es cero.

  

### **Dinámica del Objeto Atrapado**

  

Una vez atrapada, si la varilla se desplaza ligeramente de su posición de equilibrio central ($$z=0$$), experimentará una fuerza restauradora que la hará oscilar. Para pequeñas amplitudes, el potencial ``camelback'' en la dirección $$z$$ puede aproximarse por una parábola, $$U_z(z) \approx \frac{1}{2} k_z z^2$$, comportándose como un oscilador armónico.

  

La ``constante de resorte'' efectiva del potencial magnético, $$k'_z$$, es la segunda derivada de la energía potencial en el punto de equilibrio:

  

$$k'_{z} = \frac{\partial^2 U'_{M}(y_0, z)}{\partial z^2} \bigg|_{z=0}$$

  

La dinámica de la varilla de densidad $$\rho$$ está gobernada por esta constante de resorte. El período de oscilación $$T_z$$ se puede expresar como:

  

$$T_z = 2\pi\sqrt{\frac{\rho}{k'_{z}}}$$

  

Midiendo el período $$T_z$$, y conociendo la geometría del sistema y la densidad de la varilla, se puede despejar la susceptibilidad magnética $$\chi$$ de la varilla, lo que constituye la base del método de medición propuesto en el artículo.