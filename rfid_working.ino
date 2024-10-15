#include <WiFi.h>
#include <HTTPClient.h>

// Define Wi-Fi credentials
const char* ssid = "Galaxy A14";
const char* password = "galaxy12345";

const String endpointURL = "http://192.168.91.54:5000/entry"; // Replace with your endpoint URL
int led_pin = 15;
void setup()
{
   Serial.begin(9600);
    pinMode(led_pin, OUTPUT);
   // Connect to Wi-Fi
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED)
   {
      delay(1000);
      Serial.println("Connecting to WiFi...");
   }

   Serial.println("Connected to WiFi");
}

void loop()
{
   if (Serial.available())
   {
      String inputData = Serial.readString(); // Read the incoming data
      inputData.trim(); // Remove any leading/trailing white spaces
      Serial.println(inputData);
      // Send HTTP request
      HTTPClient http;
      http.begin(endpointURL); // Specify the endpoint URL
      http.addHeader("Content-Type", "application/json"); // Specify the content type as JSON if needed

      // Example payload for the PUT request
      String payload = "{\"rfid\": \"" + inputData + "\"}";

      int httpResponseCode = http.POST(payload);
      if (httpResponseCode == HTTP_CODE_OK)
      {
         Serial.println("HTTP Request Sent Successfully");

         // Read and print the response
         String response = http.getString();
         Serial.println("Response:");
         Serial.println(response);
           digitalWrite(led_pin, HIGH);
         delay(3000);
         digitalWrite(led_pin, LOW);
         // Add code here to handle a successful request
      }
      else
      {
         Serial.print("HTTP Error Code: ");
         Serial.println(httpResponseCode);
         // Add code here to handle an error in the request
      }
      http.end();
   }
}
