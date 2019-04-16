#include<ESP8266WiFi.h>

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "jinnan"
#define WLAN_PASS       "00000000"
#define light           "off"
WiFiServer server( 80); 
void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode( 14, OUTPUT); // D5 in nodemcu    LIGHT 1
  pinMode( 12, OUTPUT); // D6 in nodemcu   LIGHT 2
  pinMode(5,OUTPUT);//motor 1
  pinMode(4,OUTPUT);//motor 2
  digitalWrite( 14, HIGH); 
  digitalWrite( 12, HIGH); 
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
 
 
  
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  server.begin();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

}

void loop()
{
  WiFiClient client = server.available(); 
  
  if (! client) { return; }
  Serial.println(" new client"); 
  
  while(! client.available())
  { delay( 1); } 
  
  // Read the first line of the request 
  String request = client.readStringUntil('\ r');
  Serial.println( request);
  client.flush(); // Match the request
  if (request.indexOf("l1on") > 0)
  {digitalWrite( 14, LOW);
  Serial.println(" Light on");
  } 
  
  if (request.indexOf("l1off") > 0) 
  { digitalWrite( 14, HIGH);
  Serial.println("Light off");
  } 
  
  if (request.indexOf("l2on") > 0)
  { digitalWrite( 12, LOW);
  Serial.println("POV_FAN on");
  } 
  
  if (request.indexOf("l2off") > 0)
  { digitalWrite( 12, HIGH);
  Serial.println("POV_FAN off");
  } 
  
    if (request.indexOf("don") > 0)
  {
    digitalWrite(5,LOW);
    digitalWrite(4,HIGH);
    Serial.println("door is open");
    delay(2000);
  }
  if (request.indexOf("dof") > 0)
  {
    digitalWrite(5,HIGH);
    digitalWrite(4,LOW);
    Serial.println("door is closed");
    delay(2000);
  }
   
  client.println(" HTTP/ 1.1 200 OK");
  client.println(" Content-Type: text/ html");
  client.println(""); // do not forget this one 
  client.println(" <!DOCTYPE HTML>");
  client.println(" <head>");
  client.println(" </head>"); 
  //client.println(" <body bgcolor = \"#f7e6ec\">"); 
  client.println(" <hr/> <hr>");
  client.println(" <h4> <center>ESTELLA HOME AUTOMATION</center> </h4>");
  client.println(" <hr/> <hr>");
  client.println(" <br> <br>");
  client.println(" <br> <br>");
  client.println(" <center>");
  client.println(" Light"); 
  //client.println("<button onclick=\"funt1()\"> one</button> ");
  //client.println("<script> funtion funt1()");
  if (digitalRead(14))// read digital pin 5 
  {  
    client.println(" <a href =\"/ l1on\"\"><button style =\"background-color:green\"> Turn On </button> </a>");
    client.println(" <a href =\"/ l1off\"\"><button> Turn Off </button> </a> <br/>"); 
  }
  else
  {
     client.println(" <a href =\"/ l1on\"\"><button > Turn On </button> </a>"); 
     client.println(" <a href =\"/ l1off\"\"><button style =\"background-color:red\"> Turn Off </button> </a> <br/>");
  }
  
  client.println(" </center>");
  client.println(" <br> <br>");
  client.println(" <center>");
  client.println("Fan");
  if (digitalRead(12))// read digital pin 4
  {
    client.println(" <a href =\"/ l2on\"\"><button style=\"background-color:green\"> Turn On </button> </a>");
    client.println(" <a href =\"/ l2off\"\"><button> Turn Off </button> </a> <br/>");
  }
  else
  {
    client.println(" <a href =\"/ l2on\"\"><button > Turn On </button> </a>");
    client.println(" <a href =\"/ l2off\"\"><button style=\"background-color:red\"> Turn Off </button> </a> <br/>");
  }

  client.println(" </center>");
  client.println(" <br> <br>");
  client.println(" <center>");
  client.println(" <table border =\" 5\">");
  client.println(" <tr>"); 
  
  if (digitalRead(14))// read digital pin 5 
  {client.print(" <td> Light is OFF </td>"); } 
  else
  { client.print(" <td> Light is ON </td>"); }
  
   
  
  if (digitalRead(12))// read digital pin 4
  { client.print(" <td> Fan is OFF </td>"); }
  else 
  { client.print(" <td> Fan is ON </td>"); } 
  
  client.println(" </tr>"); 
 
  client.println(" </table>");
      client.println(" <br> <br>");
  client.println(" <br> <br>");
  client.println(" <br> <br>");
  client.println("Door Lock");
  if (digitalRead(5)==1 && digitalRead(4)==0)
  {
    client.println("<a href =\"/ don\"\"><button style =\"background-color:green\"> OPEN </button> </a>");
    client.println("<a href =\"/ dof\"\"><button> CLOSE</button> </a> <br/>");
  }
  else{
    client.println(" <a href =\"/ don\"\"><button > OPEN </button> </a>");
      client.println(" <a href =\"/ dof\"\"><button style =\"background-color:red\"> CLOSE </button> </a> <br/>");
  }
  client.println(" </center>");
  client.println(" </html>");
  delay( 1);
  Serial.println(" Client disonnected"); 
  Serial.println(""); 
  }
