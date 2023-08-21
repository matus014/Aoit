// Example testing sketch for various DHT humidity/temperature sensors written by ladyada
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 14
#define DHTTYPE DHT11 // DHT 11
#define Led 25

/*intruções
N= aumenta temperatura maxima
n= diminui a temperatura maxima

temperatura minima nunca >= temperatura maxima

B= aumenta temperatura minima
b= diminui a temperatura minima

a= Modo automatico
realiza a leitura da temperatura  atual e:

temperatura atual > temperatura maxima = led (1) e só desliga quanto temperatura atual passar a ser = temperatura maxima - 5

temperatura atual < temperatura minima = led (1) e só desliga quanto temperatura atual passar a ser = temperatura minima + 5

m= Modo manual

somente no modo manual
l = ligar ventilador
d = desligar ventilador

*/

// temperatura
float TempMax = 23;
float TempMin = 15;
char recebido;
char modo;
int fl = 0;
int ff = 0;
// char nome[] = "bla"

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    modo = 'a';
    Serial.begin(115200);
    Serial.println(F("DHTxx test!"));
    pinMode(Led, OUTPUT);
    dht.begin();
}

void loop()
{

    delay(2000);

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(hic);
    Serial.println(F("°F"));
    Serial.print(F("Modo :"));

    if (modo == 'a')
    {
        Serial.println("Automatico");
    }
    if (modo == 'm')
    {
        Serial.println("Manual");
    }

    if (modo == 'a')
    {
        Serial.print(F("°C Temp.Max: "));
        Serial.println(TempMax);
        Serial.print(F("°C Temp.Min: "));
        Serial.println(TempMin);
    }
    Serial.println("---------------------------------------------------------------");
    //--------------------------------------------------------------//
    if (Serial.available())
    {
        recebido = Serial.read();
    }
    //--------------------------------------------------------------//

    if (recebido == 'l' && modo == 'm')
    {
        digitalWrite(Led, 1);
    }
    if (recebido == 'd' && modo == 'm')
    {
        digitalWrite(Led, 0);
    }

    //--------------------------------------------------------------//

    if (modo == 'a' && t > TempMax)
    {
        digitalWrite(Led, 1);
        Serial.println("a");
        fl = 1;
    }
    if(modo == 'a' && t  < (TempMax -2) && fl == 1)
    {
        fl = 0;
        digitalWrite(Led, 0);
    }

     if (modo == 'a' && t < TempMin)
    {
        digitalWrite(Led, 1);
        Serial.println("B");
        ff = 1;
    }
    if(modo == 'a' && t  > (TempMin +2) && ff == 1)
    {
        ff = 0;
        digitalWrite(Led, 0);
    }


    //--------------------------------------------------------------//
    if (recebido == 'N')
    {
        TempMax += 1;
    }
    if (recebido == 'n')
    {
        TempMax -= 1;
    }
    //--------------------------------------------------------------//

    if (recebido == 'B')
    {
        TempMin += 1;
    }
    if (recebido == 'b')
    {
        TempMin -= 1;
    }
    //--------------------------------------------------------------//
    if (recebido == 'a')
    {
        modo = 'a';
    }
    if (recebido == 'm')
    {
        modo = 'm';
    }

    //--------------------------------------------------------------//
}