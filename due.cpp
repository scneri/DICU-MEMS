/* Ejemplo de código, para poder utilizarlo retirarlo de comentarios, en este caso se dejaron ya que 
se programó en VSCODE usando PlatformIO y se tendría que abrir otro proyecto para el DUE.

void setup() {
  analogWriteResolution(12); // Resolución de 12 bits (0-4095)
}

void loop() {
  // Recorremos valores del DAC de 0 a 4095 en pasos de 512 
  for (int valorDAC = 0; valorDAC <= 4095; valorDAC += 512) {
    analogWrite(DAC0, valorDAC);  // Enviar voltaje
    delay(2000);  // Mantener 2 s para medir con multímetro
  }
}

*/