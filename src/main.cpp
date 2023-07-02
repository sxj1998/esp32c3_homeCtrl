#include <Arduino.h>
#include <WebServer.h>

#include <WiFi.h>
// #include <string>
const char *ssid = "2-517-5G";
const char *password = "11111111";
WebServer server(80);

String indexHtml = String("") + "<!DOCTYPE html>" +
                   "<html>" +
                   "	<head>" +
                   "		<meta charset=\"utf-8\">" +
                   "		<title>ESP32 WebController</title>" +
                   "	</head>" +
                   "	<body>" +
                  //  "		<h1>Web Controller</h1>" +
                  //  "    <p> door</p>"                   
                   "	<button onclick=\"test()\" > <font size=\"100\">on " +
                   "  <button onclick=\"test()\" > <font size=\"100\">off " +                      
                   "	</body>" +  
                   "	<body>" +
                    "<button id=\"tb1\" onclick=\"tab(1)\" class=\"active\">状态</button>"
                    "<button id=\"tb2\" onclick=\"tab(2)\">联网</button>"
                    "<button id=\"tb6\" onclick=\"tab(6)\">MQTT</button>"
                    "<button id=\"tb3\" onclick=\"tab(3)\">控制</button>"
                    "<button id=\"tb4\" onclick=\"tab(4)\">关于</button>"
                    "<br/><button id=\"tb5\" onclick=\"tab(5)\">日志</button>"      
                    "<br/><button type=\"button\"   >下载HA配置文件</button></td></tr></tbody></table>"
                                      
                   


                   
                                   
                   "	<script type=\"text/javascript\">" +
                   "		function test() {" +
                   "			var ajax = new XMLHttpRequest();" +
                   "			ajax.open(\'get\', \'/test\');" +
                   "			ajax.send();" +
                   "			ajax.onreadystatechange = function() {" +
                   "				if (ajax.readyState == 4 && ajax.status == 200) {" +
                   "					console.log(ajax.responseText);" +
                   "				}" +
                   "			}" +
                   "		}" +
                   "	</script>" +
                   "</html>";


                   

void indexHandler()
{
  server.send(200, "text/html", indexHtml);
}

void testHandler()
{
  server.send(200, "text/html", "test seccess");
  Serial.print("test Controller | Time:");
  Serial.println(millis());
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(2000);
    Serial.println(WiFi.status());
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.status());
  Serial.println("Connected.");
  Serial.println(WiFi.localIP().toString());

  server.on("/", indexHandler);
  server.on("/test", testHandler);
  server.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  server.handleClient();
}
