#include <SPI.h>
#include <Ethernet2.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <ArduinoJson.h>


int LED = 8;// declaration de la variable LED sur la broche 3
// cette broche est une PWM correspondant au port A sur le motor shield, sur ce port est branchÃ© les leds



byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x03, 0x2A }; //dÃ©claration de l'adresse MAC de la carte Arduino
byte ip[] = { 192, 168, 1, 102 }; //dÃ©claration de l'adresse IP de la carte Arduino
byte passerelle[] = { 192, 168, 1, 1 }; //dÃ©claration de l'adresse IP du routeur
byte masque[] = { 255, 255, 255, 0 }; //dÃ©claration de l'adresse du masque de sous-rÃ©seau

EthernetServer serveurHTTP(80); //crÃ©er un objet serveur en utilisant le port 80 qui est le port HTTP par dÃ©faut
int comptChar = 0;


void setup()   {

Serial.begin(115200); //initialisation de la connexion serie a 115200 bauds

Ethernet.begin(mac, ip, passerelle, masque); //initialisation de la connexion ethernet


serveurHTTP.begin(); //initialisation du serveur


   pinMode(LED, OUTPUT); //initialisation des "LED" en sortie
   digitalWrite (LED, 0); //initialisation des "LED" Ã  zÃ©ro

}

void loop(){
  
  if(!serveurHTTP.available())
    return;

  EthernetClient client = serveurHTTP.available();
  String charClientRead;
  int clientReadString;
  //int comptChar = 0;
  
  // When the client send data
  if (client.available())
  {
    Serial.println("Vous etes connectee");
    
    comptChar = comptChar + 1;
    clientReadString = client.read();
    //String charClientRead = charClientRead + clientReadString;

    if(comptChar >= 180)
    {
      Serial.println("Read Data");
      Serial.println(String(clientReadString));
    }
   char json[] = "";
    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(json);
    

    
    
   }
   
   //Serial.println(comptChar);

  }


