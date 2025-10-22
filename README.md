# Cobot-Gripper
Proyecto en el que se desarrolla un gripper colaborativo, partiendo de un cobot EC-63 utilizando comunicaccion de entradas y salidas digitales entre el controlador del cobot y un esp32-C3; controlando un mecanismo accionado por un motor dc N20 y controlado con un puente l9110h

Para la visualisacion de estdos del gripper se integran 2 aros LEDs RGB, los cuales parpadearan en azul durante el proceso de rutina de "Autohoming", En en el estado natural del gripper "Cerrado" se mantendra un color verde solido, durante el proceso de "Apertura" parpadeara el color verde hasta llegar a la apertura maxima se mantendra en amarillo soido para indicar el estado abierto del gripper.

- Librerias utilizadas:.
  Adafruit_NeoPixel.h
  
