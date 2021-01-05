#include <ESP8266WiFi.h> 
const char* ssid = "PULPSTONE"; //wifi ssid / wifi name
const char* password = "internet"; //wifi password

int ld5 = 14; // Pin D5 esp8266 ~ GPIO14 Arduino
int ld6 = 12; // Pin D6 esp8266 ~ GPIO12 Arduino
int ld7 = 13; // Pin D7 esp8266 ~ GPIO13 Arduino
int ld2 = 4;  // Pin D2 esp8266 ~ GPIO4  Arduino

 int value5 = LOW; 
 int value6 = LOW; 
 int value7 = LOW; 
 int value2 = LOW; 
 
WiFiServer server(80); 
void setup() { 
 Serial.begin(115200); 
 delay(10); 
 pinMode(ld5, OUTPUT); 
 pinMode(ld6, OUTPUT); 
 pinMode(ld7, OUTPUT); 
 pinMode(ld2, OUTPUT); 
 digitalWrite(ld5, LOW); 
 digitalWrite(ld6, LOW); 
 digitalWrite(ld7, LOW); 
 digitalWrite(ld2, LOW);
   
 // Connect to WiFi network 
 Serial.println(); 
 Serial.println(); 
 Serial.print("Connecting to "); 
 Serial.println(ssid); 
 WiFi.begin(ssid, password); 
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
 // Check if a client has connected 
 WiFiClient client = server.available(); 
 if (!client) { 
   return; 
 } 
 // Wait until the client sends some data 
 Serial.println("new client"); 
 while(!client.available()){ 
   delay(1); 
 } 
 // Read the first line of the request 
 String requestd = client.readStringUntil('\r'); 
 Serial.println(requestd); 
  
 client.flush(); 
 // Match the request 

 if (requestd.indexOf("/LED5=ON") != -1)
   {
   digitalWrite(ld5, HIGH); 
   value5 = HIGH; 
   }
 else if (requestd.indexOf("/LED5=OFF") != -1)  
   { 
   digitalWrite(ld5, LOW); 
   value5 = LOW; 
   }
 
 if (requestd.indexOf("/LED6=ON") != -1)
   {
   digitalWrite(ld6, HIGH); 
   value6 = HIGH; 
   }
 else if (requestd.indexOf("/LED6=OFF") != -1)
   {
   digitalWrite(ld6, LOW); 
   value6 = LOW; 
   } 
 
 if (requestd.indexOf("/LED7=ON") != -1) 
   {
   digitalWrite(ld7, HIGH); 
   value7 = HIGH;   
   }
 else if (requestd.indexOf("/LED7=OFF") != -1)  
  {
   digitalWrite(ld7, LOW); 
   value7 = LOW; 
   }  
 
 if (requestd.indexOf("/LED2=ON") != -1) 
   {
   digitalWrite(ld2, HIGH); 
   value2 = HIGH; 
   }
 else if (requestd.indexOf("/LED2=OFF") != -1)  
   { 
   digitalWrite(ld2, LOW); 
   value2 = LOW; 
   }

// Set ledPin according to the request 
//digitalWrite(ledPin, value); 
 // Return the response 
 client.println("HTTP/1.1 200 OK"); 
 client.println("Content-Type: text/html"); 
 client.println(""); //  do not forget this one 
 client.println("<!DOCTYPE HTML>"); 
 client.println("<html>"); 
 client.print("<body style='background: #00979C'>"); 
 client.println("<h1 align ='center'>"); 
 client.println("<font-color='red'>"); 
 client.println("ESP8266 WiFi Relay Control"); 
 client.println("</font>"); 
 client.println("</h1>"); 
 client.println("<bg color ='FFFF33'>"); 
 client.println("</bg>"); 

//load 1 @ pin D5 esp8266
 client.println("<br>"); 
 if (value5 == HIGH) 
 { 
   client.println("<p align ='center'>"); 
   client.println("<font color='lime'><B>ON</B></font>");
   client.println("</p>"); 
 } 
 else if (value5 == LOW) 
 { 
   client.println("<p align ='center'>"); 
   client.println("<font color='red'><B>OFF</B></font>");
   client.println("</p>"); 
 } 
 client.println("<p align ='center'>"); 
 client.println("Lamp 1: "); 
 client.println("<a  href=\"/LED5=ON\"\"><button style=height:65px;width:125px>Turn On </button></a>"); 
 client.println("<a  href=\"/LED5=OFF\"\"><button style=height:65px;width:125px>Turn Off </button></a><br />");   
 client.println("</p>");  

// load 2 @ pin D6 esp8266
 client.println("<br>"); 
 if (value6 == HIGH) 
 { 
   client.println("<p align ='center'>");    
   client.println("<font color='lime'><B>ON</B></font>");
   client.println("</p>"); 
 } 
 else if (value6 == LOW) 
 {
   client.println("<p align ='center'>"); 
   client.println("<font color='red'>OFF</font>");
   client.println("</p>"); 
 }  
 client.println("<p align ='center'>"); 
 client.println("Fan 1: "); 
 client.println("<a  href=\"/LED6=ON\"\"><button style=height:65px;width:125px>Turn On </button></a>"); 
 client.println("<a  href=\"/LED6=OFF\"\"><button style=height:65px;width:125px>Turn Off </button></a><br />");   
 client.println("</p>"); 

// load 3 @ pin D7 esp8266
 client.println("<br>"); 
 if (value7 == HIGH)
 { 
   client.println("<p align ='center'>"); 
   client.println("<font color='lime'><B>ON</B></font>");
   client.println("</p>"); 
 } else if (value7 == LOW)
 { 
   client.println("<p align ='center'>"); 
   client.println("<font color='red'>OFF</font>");
   client.println("</p>"); 
 }  

 client.println("<p align ='center'>"); 
 client.println("Fan 2: "); 
 client.println("<a  href=\"/LED7=ON\"\"><button style=height:65px;width:125px>Turn On </button></a>"); 
 client.println("<a  href=\"/LED7=OFF\"\"><button style=height:65px;width:125px>Turn Off </button></a><br />");   
 client.println("</p>"); 

// load 4 @ pin D2 esp8266
 client.println("<br>"); 
 if (value2 == HIGH) 
 { 
   client.println("<p align ='center'>"); 
   client.println("<font color='lime'><B>ON</B></font>");
   client.println("</p>"); 
 }  
 else if (value2 == LOW)
 { 
   client.println("<p align ='center'>"); 
   client.println("<font color='red'>OFF</font>");
   client.println("</p>"); 
 }  
 client.println("<p align ='center'>"); 
 client.println("Lamp 2: "); 
 client.println("<a  href=\"/LED2=ON\"\"><button style=height:65px;width:125px>Turn On </button></a>"); 
 client.println("<a  href=\"/LED2=OFF\"\"><button style=height:65px;width:125px>Turn Off </button></a><br />");   
 client.println("</p>"); 
 
 client.println("</body>"); 
 client.println("</html>"); 
 delay(1); 
 Serial.println("Client disonnected"); 
 Serial.println("");  
} 
