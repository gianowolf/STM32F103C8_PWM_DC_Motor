## Sensores de Proximidad

Proxmitmity sensors are sensors that detect the movement/presence of objetctys wishout phyussical contact and  relay that information capturaed into an electrical signal. existen sensores de tipo inductivo, capacitivo y ultrasonicos. Debido a que los de sensores capacitivios e indcutivos proveen un rango de deteccion muy corto, se decide optar por un sensor ultrasoinico.

### Sensores de Proximidad ultrasonicos

Es te tipo de sensores detecta la presencia de objetos emitiendo ondas de alta frecuencia, del rango de las ultrasonicas. Pueden detectar objetos solidos, liquidos y granulares, y se componen unicamente de un par de receptor y transmisor ultrasonicos.

El modo de funcionamiento es muy simple. El tranductor sonico transforma la energia electrica emitiendo ondas de sonido que rebotan en los objetos. La onda que rebota retorna al sensor y se toma la diferencia de tiempo para medir la distancia/proximidad.

HC-SR04

```
insertar imagen del HC-SR04
```

Ademas de los pines de Vcc y GND, el sensor se compone de un pin para la senal de trigger (disparo emitido por el MCU) y otro para el eco que proporciona el sensor

## Control de tiempo

