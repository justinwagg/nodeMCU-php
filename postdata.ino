void post_data() {


  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
 
  client.println(url);
  delay(500);

  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  client.stop(); //Stopping client

}
