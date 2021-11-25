
// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "J7";
const char* password = "0987654321@@";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";
String output16State = "off";
String output1State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;
const int output16 = 16;

const int output15 = 15;
const int output3 = 3;
const int output1 = 1;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output16, OUTPUT);

  pinMode(output15, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output1, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output16, LOW);
  digitalWrite(output15, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output1, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
              digitalWrite(output15, HIGH);
              digitalWrite(output16, LOW);
              digitalWrite(output1, LOW);
              digitalWrite(output3, LOW);
              digitalWrite(output4, LOW);
              delay(2000);
              digitalWrite(output5, LOW);
              digitalWrite(output15, LOW);
              digitalWrite(output16, HIGH);
              digitalWrite(output1, HIGH);
              digitalWrite(output3, LOW);
              digitalWrite(output4, LOW);
              delay(3000);
              digitalWrite(output5, LOW);
              digitalWrite(output15, LOW);
              digitalWrite(output16, HIGH);
              digitalWrite(output1, LOW);
              digitalWrite(output3, HIGH);
              digitalWrite(output4, LOW);
              delay(2000);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output15, LOW);
              digitalWrite(output16, LOW);
              digitalWrite(output5, LOW);
              digitalWrite(output1, LOW);
              digitalWrite(output3, LOW);
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
              digitalWrite(output15, HIGH);
              digitalWrite(output16, LOW);
              digitalWrite(output5, LOW);
              digitalWrite(output1, LOW);
              digitalWrite(output3, LOW);
              
        
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
              digitalWrite(output15, LOW);
              digitalWrite(output16, LOW);
              digitalWrite(output5, LOW);
              digitalWrite(output1, LOW);
              digitalWrite(output3, LOW);
              
            }else if (header.indexOf("GET /16/on") >= 0) {
              Serial.println("GPIO 16 on");
              output16State = "on";
              digitalWrite(output16, HIGH);
              digitalWrite(output3, LOW);
              digitalWrite(output4, LOW);
              digitalWrite(output15, LOW);
              digitalWrite(output5, LOW);
              digitalWrite(output1, HIGH);
              
              
            } else if (header.indexOf("GET /16/off") >= 0) {
              Serial.println("GPIO 16 off");
              output16State = "off";
              digitalWrite(output16, LOW);
              digitalWrite(output3, LOW);
              digitalWrite(output4, LOW);
              digitalWrite(output15, LOW);
              digitalWrite(output5, LOW);
              digitalWrite(output1, LOW);
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output1State = "on";
              digitalWrite(output1, LOW);
              digitalWrite(output16, HIGH);
              digitalWrite(output3, HIGH);
              digitalWrite(output4, LOW);
              digitalWrite(output15, LOW);
              digitalWrite(output5, LOW);
              delay(2000);
              digitalWrite(output1, LOW);
              digitalWrite(output16, LOW);
              digitalWrite(output3, LOW);
              digitalWrite(output4, HIGH);
              digitalWrite(output15, HIGH);
              digitalWrite(output5, LOW);
              delay(3000);
              digitalWrite(output1, LOW);
              digitalWrite(output16, LOW);
              digitalWrite(output3, LOW);
              digitalWrite(output4, LOW);
              digitalWrite(output15, HIGH);
              digitalWrite(output5, HIGH);
              delay(2000);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output1State = "off";
              digitalWrite(output1, LOW);
              digitalWrite(output3, LOW);
              digitalWrite(output4, LOW);
              digitalWrite(output15, LOW);
              digitalWrite(output5, LOW);
              digitalWrite(output16, LOW);
              
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: fantasy; display: inline-block;background-image: linear-gradient(to left top, #18ccb780, #f3f3f3, #f5f5f5, #31e6d091);height: 100vh; margin: 0px auto; text-align: center;}");

           client.println(".button { background-color: #afccab; border: 2px red cyan black gold; color: black; padding: 15px 35px; display: inline-block;");
           client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");

            
            client.println(".button2 {background-color: #aebbbd;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Feu-Rouge Deux Voies</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>Feu Orange 1 - Etat " + output5State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>Feu Vert 1 & Feu Rouge 2 - Etat " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
                 // Display current state, and ON/OFF buttons for GPIO 16  
            client.println("<p>Feu Vert 2 & Feu Rouge 1 - Etat " + output5State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output16State=="off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

           
            
             // Display current state, and ON/OFF buttons for GPIO 3  
            client.println("<p>Feu Orange 2 - Etat " + output1State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output1State=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break; 
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
