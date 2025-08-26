#include <SoftwareSerial.h>
#include <Arduino.h>

// Configuración del módulo Bluetooth HC-05
#define BT_RXPIN 10  // Pin RX del HC-05 (conectar a TX del Arduino)
#define BT_TXPIN 11  // Pin TX del HC-05 (conectar a RX del Arduino)
SoftwareSerial Bluetooth(BT_RXPIN, BT_TXPIN);  // Inicializar comunicación serial software

// Configuración de pines analógicos
#define ANALOG_X_PIN A0  // Pin analógico para eje X
#define ANALOG_Y_PIN A1  // Pin analógico para eje Y
//#define ANALOG_T_PIN A2  // Pin analógico para temperatura

void setup() {
    // Inicializar comunicación serial para monitor serie
    Serial.begin(9600);
    while(!Serial);
    
    // Inicializar comunicación Bluetooth
    Bluetooth.begin(9600);  // Velocidad estándar para HC-05
    while(!Bluetooth);
    //analogReadResolution(12); // Configurar resolución de lectura analógica a 12 bits (0-4095)
    Serial.println("Sistema iniciado - Bluetooth y entradas analógicas listas");
    Bluetooth.println("Sistema iniciado - Conectado via Bluetooth");
    
    // Configurar pines analógicos como entradas
    pinMode(ANALOG_X_PIN, INPUT);
    pinMode(ANALOG_Y_PIN, INPUT);
    //pinMode(ANALOG_T_PIN, INPUT);
}

void loop() {
    long xSum=0, ySum=0;
    const int muestras = 1000;

    // Leer valores analógicos
    for (int i = 0; i < muestras; i++) {
        xSum += analogRead(ANALOG_X_PIN);
        ySum += analogRead(ANALOG_Y_PIN);
        //tSum += analogRead(ANALOG_T_PIN);
        delayMicroseconds(1000);  // Pequeña demora entre lecturas
    }
    int xPromedio = xSum/muestras;
    int yPromedio = ySum/muestras;
    
    //int yValue = analogRead(ANALOG_Y_PIN);
    //int tValue = analogRead(ANALOG_T_PIN);
    
    // Convertir valores a voltaje cambiar el 5 por el que corresponda
    float xVoltage = xPromedio * (3.30 / 4095.0);
    float yVoltage = yPromedio * (3.30 / 4095.0);
    //float tVoltage = tValue * (5.0 / 1023.0);
    float desplazamiendo_UD= 0.6675*xVoltage-1.6919; // Desplazamiento en grados arriba abajo
    float desplazamiendo_LR= 0.6743*yVoltage-1.6896; // Desplazamiento en grados derecha izquierda


    // Mostrar valores por monitor serie
    //Serial.print("Promedio X: "); 
    //Serial.print(xPromedio);
    //Serial.print(" ("); Serial.print(xVoltage, 2); Serial.println("V)");
    
    //Serial.print("Promedio Y: ");
    //Serial.print(yPromedio);
    //Serial.print(" ("); Serial.print(yVoltage, 2); Serial.println("V)");
    
    //Serial.print("T: ");
    //Serial.print(tValue);
    //Serial.print(" ("); Serial.print(tVoltage, 2); Serial.println("V)");
    
    Serial.println("-----");
    
    // Enviar datos por Bluetooth 
    Bluetooth.print(" "); Bluetooth.print(desplazamiendo_UD,4); Bluetooth.print(", "); Bluetooth.print(desplazamiendo_LR,4);Bluetooth.print("\n ");
    //Bluetooth.print(" "); Bluetooth.print(xVoltage,4); Bluetooth.print(", "); Bluetooth.print(yVoltage,4);Bluetooth.print("\n ");
    //Bluetooth.print("Promedio X:"); Bluetooth.print(xPromedio);
    //Bluetooth.print(",Y:"); Bluetooth.print(yPromedio);
    //Bluetooth.print(",T:"); Bluetooth.println(tValue);
    
    delay(1000);  // Espera 1 segundo entre lecturas
}
