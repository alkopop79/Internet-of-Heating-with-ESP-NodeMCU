#include <ESP8266WiFi.h>

const char* ssid = "network-name";
const char* password = "password";

int ledPin = D0;

IPAddress ip(192, 168, 0, 11); //Node static IP
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
// haz client connected?
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
// tell us more!
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int value = HIGH;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D0, HIGH);
    value = LOW;
    Serial.println("ON");
    delay(100);
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D0, LOW);
    value = HIGH;
    Serial.println("OFF");
    delay(100);
  }

  client.println("HTTP/1.1 200 OK");
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>\" stuff \"</title><meta charset=\"utf-8\" /><meta name=\"viewport\" content=\"width=device-width\" /><link href='https://fonts.googleapis.com/css?family=Advent+Pro' rel=\"stylesheet\" type=\"text/css\"><style>\n");
  client.println("<style>");
  client.println("html {height: 100%;}");

  if (value == HIGH) {
    client.println("body {background:powderblue;}");
  }
  else
  {
    client.println("body {background:#ff7b23;}");
  }
  client.println(".button1{display:block;font-size: 120px;text-decoration: none;text-align: center;display: block;color: white;font-family: 'Advent Pro';}");
  client.println(".button2{display:block;font-size: 120px;text-decoration: none;text-align: center;display: block;color: white;font-family: 'Advent Pro';}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div>");
  client.println("<a href=\"/LED=ON\"\" class=\"button1\">ON</a><br />");
  client.println("</div>");
  client.println("<div>");
  client.println("<a href=\"/LED=OFF\"\" class=\"button2\">OFF</a><br />");
  client.println("</div>");
  client.println("<body>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED){
      
    
  }
  
  }


