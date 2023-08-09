const int potPin = 34;
int valor = 0;
float miliVolt = 0;
int soma = 0;
float media = 0;
int i=0;
float temperatura = 0;


void setup() {

  Serial.begin(115200);
  delay(1000);  

}

void loop() {
  
  while(i<555)
  {
    valor = analogRead(potPin);
    soma+=valor;
    i++;
  }
  media = soma/i;
 

 

  miliVolt = media;
  miliVolt *= 0.806;
  temperatura = miliVolt/10;

  Serial.print("Valor AD: ");
  Serial.println(media); 
  Serial.print("miliVolt: ");
  Serial.println(miliVolt);
  Serial.print("Temperatura: ");
  Serial.println(temperatura);


  soma=0;
  i=0;
  Serial.println("");
  delay(100);

}
