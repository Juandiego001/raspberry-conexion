#include <Ethernet.h>
#include <SPI.h>

byte ip[] = {192,168,20,50};
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte google[] = { 185, 253, 154, 77 };




EthernetClient client;
String webString = "";

void setup()
{
  Serial.begin(9600);
  String cadenaLeida = "";
  // start the Ethernet connection:
  Serial.println("inicializando red...");
  //Ethernet.begin(mac, ip, DNS, gateway, subnet);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for (;;)
      ;
  }
  else {
    Serial.print("IP asignada por DHCP: ");
    Serial.println(Ethernet.localIP());
  }

  delay(1000);
  Serial.println("MENU");
  Serial.println("1 - Camilo");
  Serial.println("2 - enviar");
  while (Serial.available() == 0) {
  }
  do {
    char caracter_leido = Serial.read();
    cadenaLeida += caracter_leido;
    delay(5);
  }  while (Serial.available() > 0);
  Serial.print("He Leido la cadena: ");
  Serial.println(cadenaLeida);

  int respuesta = cadenaLeida.toInt();

  switch (respuesta) {
    case 1:
      if (client.connect(google, 666)) {
        Serial.println("connected");
        client.println("GET / HTTP/1.0");
        client.println();
      }
      else {
        Serial.println("connection failed");
      }

      break;
    case 2:
      if (client.connect(google, 666)) {
        Serial.println("connected");
        client.println("GET / HTTP/1.0");
        client.println();
      }
      else {
        Serial.println("connection failed");
      }
      break;
    default:
      Serial.println("Opcion incorrecta");
      break;
  }
}

void loop()
{
  if (client.available()) {
    char c = client.read();
    webString += c;
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    Serial.println("Reinicia Arduino para volver a hacer una peticion");
    //Serial.println(webString);
    for (;;)
      ;
  }
}
