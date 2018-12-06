/*
  Country: Brasil
  State: Pernambuco
  Developer: Matheus Johann Araújo
  Date: 2018-03-07
*/

#define led 13

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

/*
 * Função que lê uma string da Serial e retorna-a.
 */
String leStringSerial(){
  String conteudo = "";
  char caractere;  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if(caractere != '\n'){
      //Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }    
  /*Serial.print("Recebi: ");
  Serial.println(conteudo);*/
  return conteudo;
}

void loop() {
  String str = leStringSerial();
  if(str == "L"){
    analogWrite(led, 130);
    Serial.println("LED LIGADO!");
    delay(100);
  }else if(str == "D"){
    analogWrite(led, 0); 
    Serial.println("LED DESLIGADO!");
    delay(100);
  }
}
