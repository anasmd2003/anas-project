#include <GSM.h>

GSM gsmAccess;   // Create an instance of the GSM class
GSMClient client; // Create an instance of the GSMClient class

char apn[] = "internet"; // Airtel APN
char user[] = "";        // GPRS Username (leave blank)
char pass[] = "";        // GPRS Password (leave blank)

void setup() {
  Serial.begin(9600); // Start Serial communication with PC
  Serial2.begin(9600); // Start Serial communication with GSM module

  // Connect to GSM network
  if (gsmAccess.begin() != GSM_READY) {
    Serial.println("GSM not ready");
    while (true);
  }

  // Attach GPRS
  if (gprs.attachGPRS(apn, user, pass) != GPRS_READY) {
    Serial.println("GPRS not ready");
    while (true);
  }

  Serial.println("GSM and GPRS ready");
}

void loop() {
  // Simulated GPS data (replace with actual GPS data)
  double lat = 12.9716; // Example latitude
  double lng = 77.5946; // Example longitude

  // Send data to the cloud
  sendDataToCloud(lat, lng);
  
  delay(10000); // Wait 10 seconds before sending again
}

void sendDataToCloud(double lat, double lng) {
  if (client.connect("your_backend_url.com", 80)) { // Replace with your backend URL
    String postData = "latitude=" + String(lat, 6) + "&longitude=" + String(lng, 6);
    
    // Send HTTP POST request
    client.println("POST /api/update_location HTTP/1.1"); // Adjust endpoint if necessary
    client.println("Host: your_backend_url.com"); // Replace with your backend URL
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println(); // End of headers
    client.print(postData); // Send data
    client.stop(); // Close the connection

    Serial.println("Data sent to cloud");
  } else {
    Serial.println("Connection to cloud failed");
  }
}
