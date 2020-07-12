#include <ESP8266WebServer.h>   // Include the WebServer library
#include <ArduinoJson.h>

#include "./main.hpp"

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void handleGet() {
  StaticJsonDocument<500> root;
  String json;

  root["state"] = settings.on ? "on" : "off";
  root["hue"] = settings.colour.H * 360;
  root["saturation"] = settings.colour.S * 100;
  root["brightness"] = int(settings.colour.B * 255);

  root["effect"] = settings.showId;

  serializeJson(root, json);
  server.send(200, "text/json", json);
}

void handleSet() {
  if(server.hasArg("hue")) {
    Serial.println("received new hue value, hue:" + server.arg("hue"));
    float hue = server.arg("hue").toFloat();
    settings.colour.H = (hue / 360.0f);
  }

  if(server.hasArg("saturation")) {
    Serial.println("received new saturation value, saturation:" + server.arg("saturation"));
    float saturation = server.arg("saturation").toFloat();
    settings.colour.S = (saturation / 100.0f);
  }

  if(server.hasArg("brightness")) {
    Serial.println("received new brightness value, brightness:" + server.arg("brightness"));
    float brightness = server.arg("brightness").toFloat();
    settings.colour.B = (brightness / 255.0f);
  }

  if(server.hasArg("state")) {
    Serial.println("received new state value, state:" + server.arg("state"));
    if(server.arg("state") == "on") settings.on = true;
    else if(server.arg("state") == "off") settings.on = false;
  }

  if(server.hasArg("effect")) {
    Serial.println("received new effect value, effect:" + server.arg("effect"));
    settings.showId = server.arg("effect").toInt();
  }

  handleGet();
}


void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void setupServer(){
  server.on("/get", HTTP_GET, handleGet);
  server.on("/set", HTTP_GET, handleSet);            // Call the 'handleRoot' function when a client requests URI "/"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loopServer(){
  server.handleClient();                    // Listen for HTTP requests from clients
}
