// Autor: Professor Bruno P. Campos
// Vídeo - CFB CURSOS: https://www.youtube.com/watch?v=qhM7UwUiXVQ&list=PLx4x_zx8csUgWBTvA-fluHV970SzDJRBw&index=33
// OBS.: Eu Matheus Johann Araújo, somente comentei as instruções abaixo.

#include <LiquidCrystal.h>

// Declaração das portas a serem utilizadas
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Função principal e de execução única
void setup() {
  // Iniciando o display e informando as 16 colunas e 2 linhas
  lcd.begin(16, 2);
  // Limpando o display
  lcd.clear();
}

// Função secundária e de repetição infinita
void loop() {
  // Indica onde o curso deve ficar Coluna 3, Linha 0
  lcd.setCursor(3, 0);
  // Escreve na tela
  lcd.print("CFB CURSOS");
  // Indica onde o curso deve ficar Coluna 4, Linha 1
  lcd.setCursor(4, 1);
  // Escreve na tela
  lcd.print("Arduino");
  // Espera três segundos (1s = 1000ms)
  delay(3000);
  // Laço de repetição, que repete três vezes
  for(int pos = 0; pos < 3; pos++){
    // Desloca o texto no display para a esquerda
    lcd.scrollDisplayLeft();
    // Espera cem milissegundos (1s = 1000ms)
    delay(100);
  }
  // Laço de repetição, que repete seis vezes
  for(int pos = 0; pos < 6; pos++){
    // Desloca o texto no display para a direita
    lcd.scrollDisplayRight();
    // Espera cem milissegundos (1s = 1000ms)
    delay(100);
  }
  // Laço de repetição, que repete três vezes
  for(int pos=0;pos<3;pos++){
    // Desloca o texto no display para a esquerda
    lcd.scrollDisplayLeft();
    // Espera cem milissegundos (1s = 1000ms)
    delay(100);
  }
  // Espera um segundo (1s = 1000ms)
  delay(1000);
  // Desliga o display
  lcd.noDisplay();
  // Espera meio segundo (1s = 1000ms)
  delay(500);
  // Liga o display
  lcd.display();
  // Espera meio segundo (1s = 1000ms)
  delay(500);
  // Desliga o display
  lcd.noDisplay();
  // Espera meio segundo (1s = 1000ms)
  delay(500);
  // Liga o display
  lcd.display();
  // Espera meio segundo (1s = 1000ms)
  delay(500);
}