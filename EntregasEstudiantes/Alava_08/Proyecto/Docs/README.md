# **Dinámica de una varilla diamagnética dentro de una trampa PDL**
David Fernando Alava Maya
David Alejandro Vásquez Franco


## **Introducción**

El magnetismo es una de las fuerzas fundamentales de la naturaleza, manifestándose a través de los campos magnéticos que permean el espacio e interactúan con la materia. Una de sus aplicaciones, es la manipulación y el confinamiento de la materia sin contacto físico, lo que da lugar a las trampas magnéticas. El principio de estas trampas se basa en la interacción entre un campo magnético no uniforme y el momento magnético de un objeto, ya sea intrínseco o inducido.

  

Todos los materiales responden de alguna manera a los campos magnéticos. En particular, los materiales diamagnéticos son repelidos por las regiones de campo magnético intenso y atraídos hacia los mínimos de campo. Esta propiedad permite diseñar configuraciones de imanes que generan un punto de equilibrio estable donde un objeto diamagnético puede levitar.

  

Este proyecto se centra en el análisis de una configuración magnética en particular, un sistema compuesto por dos líneas paralelas de dipolos magnéticos. Esta disposición, que puede construirse utilizando un par de imanes cilíndricos con magnetización diametral, genera una forma de energía potencial muy singular en el espacio intermedio. La característica más notable es la formación de un potencial de confinamiento unidimensional con una estructura de "doble joroba" o "camelback". Este potencial no solo atrapa un objeto diamagnético en una posición de levitación estable, sino que también lo confina a lo largo del eje del sistema, permitiendo un movimiento oscilatorio bien definido.

  

El estudio detallado de la dinámica de un objeto dentro de esta trampa permite establecer una conexión directa entre sus parámetros de movimiento observables (como el período de oscilación) y sus propiedades magnéticas intrínsecas. Además, las características del campo magnético generado lo convierten en un candidato ideal para ser adaptado a técnicas de medición avanzadas, como la caracterización de materiales semiconductores mediante el efecto Hall.

## **Descripción del Problema y Motivación**
El control preciso de los campos magnéticos es una herramienta que permite la manipulación de materia sin contacto físico a través de trampas magnéticas. Este proyecto se enfoca en el análisis computacional de una configuración particular: un sistema compuesto por un par de imanes cilíndricos con magnetización diametral.

Esta disposición genera un campo magnético mínimo y estable en el espacio entre los imanes, lo que permite la levitación de materiales diamagnéticos. El objetivo principal de este trabajo fue desarrollar un modelo computacional para:

- Calcular y visualizar el campo magnético y el paisaje de energía potencial del sistema.

- Simular la dinámica de un objeto (una varilla de grafito) atrapado en este potencial.

- Verificar si el comportamiento dinámico observable (como el período de oscilación) puede usarse para determinar propiedades intrínsecas del material (su susceptibilidad magnética), validando así un método de medición virtual.


## **Marco Teórico**

### **Campo Magnético de un Imán Diametral**

El bloque de construcción fundamental de nuestro sistema es un imán cilíndrico con una magnetización uniforme $$\vec{M}$$ a lo largo de su diámetro (por ejemplo, en la dirección $$\hat{x}$$). El campo magnético $$\vec{B}$$ en un punto arbitrario del espacio $$(x, y, z)$$ generado por un solo imán de radio $$a$$ y longitud $$L$$, centrado en el origen, que se puede calcular a partir del potencial escalar magnético.  El campo total del sistema de par de imanes (DMP) se obtiene por el principio de superposición, sumando los campos de dos de estos imanes centrados en $$(\pm a, 0, 0)$$.


$$\vec{B}_{DM}(x,y,z) = \frac{\mu_{0}Ma}{4\pi} \int_{0}^{2\pi} \sum_{n=1,2} \frac{(-1)^{n}\cos\phi}{u_{n}^{2}+s^{2}+u_{n}\sqrt{u_{n}^{2}+s^{2}}} \times \begin{bmatrix} x-a\cos\phi \\ y-a\sin\phi \\ u_{n}+\sqrt{u_{n}^{2}+s^{2}} \end{bmatrix} d\phi$$


### **Energía Potencial y Fuerza sobre un Objeto Diamagnético**

  

Un objeto diamagnético, como una varilla de grafito, al ser colocado en un campo magnético externo $$\vec{B}_T$$, desarrolla una magnetización inducida $$\vec{M}_R$$ opuesta al campo. Para una varilla cilíndrica con susceptibilidad magnética $$\chi$$, esta magnetización es:

  

$$\vec{M}_R = \frac{2\chi}{\mu_0(2+\chi)} \vec{B}_T$$
