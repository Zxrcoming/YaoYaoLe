#include "sea_esp32_qspi.h"
#include "SimpleDHT.h"
#include "string.h"
#include "WiFi.h"
#include "AWS_IOT.h"

#include <spartan-edge-esp32-boot.h>
#include "ESP32IniFile.h"

// initialize the spartan_edge_esp32_boot library
spartan_edge_esp32_boot esp32Cla;

const size_t bufferLen = 80;
char buffer[bufferLen];
char buffer1[bufferLen];



AWS_IOT hornbill;

char WIFI_SSID[] = "MERCURY_3E15";
char WIFI_PASSWORD[] = "147258369";
char HOST_ADDRESS[] = "ai75bgnyilhc6-ats.iot.us-east-1.amazonaws.com";
char CLIENT_ID[] = "ESP32client";
char TOPIC_NAME[] = "gaming";
char aws_root_ca_pem[] = "-----BEGIN CERTIFICATE-----\n\
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\
rqXRfboQnoZsG4q5WTP468SQvvG5\
-----END CERTIFICATE-----\n";

char certificate_pem_crt[] = "-----BEGIN CERTIFICATE-----\n\
MIIDWTCCAkGgAwIBAgIUQg1cskeTXLCFiSjpZ1EyOkpswbswDQYJKoZIhvcNAQEL\
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMDcyNzEwMzYy\
MloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL0a56Uq1ulDYSpUeuQx\
kgFc4HCHfoqUATU1yO4kUGDOoc/PHQ9qWwU5OQLOYO4KRWXDh/XxzsefG6oGV682\
78uyP20YrzSdWtvcT0MbAFeq5GEQd507EoVQffgonu9CG35ztWDCOWZW5bfQa8P2\
igUukQ3smeoud33D9E4gykp5Itk1DySqSgt4E+UGHaiYdoU1nAOyrxaXsLj8oaZO\
yrjRrQPmhKlv7gnMiiYM5WYbyBO/3dlgTezjddCv8YCptm73VIMazEdygE6ba/FR\
kZHxUtZYl39INmrUIKI5N2QAsOy+PM4cQIhq3pgk+DnaaPH5XMIpBnc0aIMmwXo/\
rY8CAwEAAaNgMF4wHwYDVR0jBBgwFoAUeaGAnYoROU/uEzv5Iskcp8OueT0wHQYD\
VR0OBBYEFMqDa3iMEgDZ6TqZWl8gTGLf3WwiMAwGA1UdEwEB/wQCMAAwDgYDVR0P\
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBp/1eUP54G9CT+R6PGf9cDNKEF\
r2wLEo2pIkWgGQcFWfVZAEbKZaarH2gRl/I/U+vrR49nAh7Clkstl1wDaQFYGV+A\
AUsuA8aG2uPLzVQ6A8IJOLKV82ftuCIHI7pA3LANPvJ9HB2ZLyF+t6UfPu8a2gYt\
Iw6insv8s+JKkGpieCgQxlrnZU3pouCBdR7xQlRG01y1y9JBPUDeJkKXh5DMB8d7\
usY41sM5HU8rqS4l+ErVa0DbRSg19Xy4EeM+3Lt9cWbz5ApBVLe818/0B177QgIa\
M+povFrleDZV4jBi7C3Js4vKWRSJVu/sWraYCzFqyd8SohHU8loUJzoPoF8w\
-----END CERTIFICATE-----\n";

// "The private key of the thing". The public key is not needed here.
char private_pem_key[] = "-----BEGIN RSA PRIVATE KEY-----\n\
MIIEowIBAAKCAQEAvRrnpSrW6UNhKlR65DGSAVzgcId+ipQBNTXI7iRQYM6hz88d\
D2pbBTk5As5g7gpFZcOH9fHOx58bqgZXrzbvy7I/bRivNJ1a29xPQxsAV6rkYRB3\
nTsShVB9+Cie70IbfnO1YMI5Zlblt9Brw/aKBS6RDeyZ6i53fcP0TiDKSnki2TUP\
JKpKC3gT5QYdqJh2hTWcA7KvFpewuPyhpk7KuNGtA+aEqW/uCcyKJgzlZhvIE7/d\
2WBN7ON10K/xgKm2bvdUgxrMR3KATptr8VGRkfFS1liXf0g2atQgojk3ZACw7L48\
zhxAiGremCT4Odpo8flcwikGdzRogybBej+tjwIDAQABAoIBAEBzKv/f2d8mV7dV\
k4yyWFCelt/DTh1s0/yOmCyRs9NKmVt5+y2F0f+1wPhz3hVC6uQEABKSlybx0zvf\
bYMJ9jA2T+eewhfsiUrlix4T1coLNErgkePEfktxY31wWrqwjS5LwUV47Jc0hpZf\
MltXazLY7BcSzGJD8/WpE1qNUmSOznwjijD0rzdXYhWmT0bBgwSLuJTY/fLPM4W1\
4fYlJwzL+AykJxpLcoT9coKMD9DNsg/0nhKxK7D81kdY6mb3qvSfrPghj/wAs140\
jRNhKHNhBuEHLSLI+xPD+fO0IZsvVUqY3qjskF9ePOn0Fucal4KX9lmfOyQ2INhl\
RNfBlgECgYEA5HkzfHusHe+EYKSZcWJDmTK3bWQhoX5PZYjVDUjZSzqY2tFpVMDY\
jzSZ3rAVDoXICR/M89pYrDWRj5p7TVlhHEAhQeDXC58Mcqh2uR1RqRkW5Is7rlq4\
5ACT+64Y0qJA8Mh87TJAOWNdA7mh42zpzumGmomavoQg1w28oAX+Mq0CgYEA0+N3\
mQblmOZUO+eSZJs6WHwihkXgDu04c0rSCTlvS5Loz7bvBh2PJ6FNLI+oaIRMYLjS\
2E7PKzooAU3e+3G2bO4qCwaXSAVdcQ3YpkRut9L31m4pN+HsIyPX06C1yc7CIQlR\
tYxTq1FDz8W+fKY6tBr5ztsmnbt/Vpw4pkGRpKsCgYAmHip+3EtM+0cEsLGA/znz\
90gvEgOiY+ZvNDMHcl3+dRpHd6SxJTN8QPRi+NGqiJtlGk8haA5fPNi6MrXbo8vV\
4MUrro1yPOjgwEZ+f+u94Je3LZuZbT1nnMkTtmohyjw3b9uX30hjyrYcBv6BaQxh\
Hwj8A3Uzz+uCtaIAuL8+SQKBgHG1Zl9G5jvRj26+bT90VjFaHKT2JrGb+GlWw7ST\
j/h8lFe0Ej2z6zkXRPUe+v9r0Bkv1mailGbcRM++XGWPtphqj0Fvfgv2ZRjgl11S\
6B/aJYp7f78vjKum9pHpcuUkAeX8vE6zSctsRvnfYsQ96M7ykxDBZs3K6yEtoPEH\
ywMVAoGBAMWn7uXiHTVYEv/cTZjNzh5ndPPQmOA+CNDqnoT+YmBQ5ci14N/IRKzb\
QtDqwIG7jtNpF+WfZBL969A2jsfvDbYLHwDi7AjM4MGY5Y2zqXDpBlq1rP9RJmFH\
fgVeWtfnuM1/RQI8UUcz7lz9A2ELULR95qoRujTIXTvUNil/UDyb\
-----END RSA PRIVATE KEY-----\n";


int status = WL_IDLE_STATUS;
int tick = 0, msgCount = 0, msgReceived = 0, tick1 = 0;
char payload[512];
char rcvdPayload[512];
uint8_t data1[4] = {41, 42, 43, 44};
uint8_t data2[32];
void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
  strncpy(rcvdPayload, payLoad, payloadLen);
  rcvdPayload[payloadLen] = 0;
  msgReceived = 1;
}


void setup()
{

  // xfpga
  // initialization
  esp32Cla.begin();

  // check the .ini file exist or not
  const char *filename = "/board_config.ini";
  IniFile ini(filename);
  if (!ini.open()) {
    Serial.print("Ini file ");
    Serial.print(filename);
    Serial.println(" does not exist");
    return;
  }
  Serial.println("Ini file exists");

  // check the .ini file valid or not
  if (!ini.validate(buffer, bufferLen)) {
    Serial.print("ini file ");
    Serial.print(ini.getFilename());
    Serial.print(" not valid: ");
    return;
  }

  // Fetch a value from a key which is present
  if (ini.getValue("Overlay_List_Info", "Overlay_Dir", buffer, bufferLen)) {
    Serial.print("section 'Overlay_List_Info' has an entry 'Overlay_Dir' with value ");
    Serial.println(buffer);
  }
  else {
    Serial.print("Could not read 'Overlay_List_Info' from section 'Overlay_Dir', error was ");
  }

  // Fetch a value from a key which is present
  if (ini.getValue("Board_Setup", "overlay_on_boot", buffer1, bufferLen)) {
    Serial.print("section 'Board_Setup' has an entry 'overlay_on_boot' with value ");
    Serial.println(buffer1);
  }
  else {
    Serial.print("Could not read 'Board_Setup' from section 'overlay_on_boot', error was ");
  }

  // Splicing characters
  strcat(buffer, buffer1);

  // XFPGA pin Initialize
  esp32Cla.xfpgaGPIOInit();

  // loading the bitstream
  esp32Cla.xlibsSstream(buffer);

  delay(2000);

  // AWS-connection
  Serial.begin(115200);
  SeaTrans.begin();
  //SeaTrans.write(0, data1, 4);
  //SeaTrans.read(0, data2, 4);
  //Serial.printf("%d %d %d %d\r\n",data2[0],data2[1],data2[2],data2[3]);
  delay(2000);

  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // wait 5 seconds for connection:
    delay(5000);
  }

  Serial.println("Connected to wifi");

  if (hornbill.connect(HOST_ADDRESS, CLIENT_ID,
                       aws_root_ca_pem, certificate_pem_crt, private_pem_key) == 0)
  {
    Serial.println("Connected to AWS");
    delay(1000);

    if (0 == hornbill.subscribe(TOPIC_NAME, mySubCallBackHandler))
    {
      Serial.println("Subscribe Successfully");
    }
    else
    {
      Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
      while (1);
    }
  }
  else
  {
    Serial.println("AWS connection failed, Check the HOST Address");
    while (1);
  }

  delay(2000);

}

void loop()
{
  uint8_t i;
  //SeaTrans.write(0, data1, 4);
  /*
    //result in uart
    SeaTrans.read(0, data2, 32);
    for (i=0;i<=31;i=i+2)
    {
    Serial.printf("data2[%d:%d] = %2x%2x \r\n",i+1,i,data2[i+1],data2[i]);
    }

    if(msgReceived == 1)
    {
      msgReceived = 0;
      Serial.print("Received Message:");
      Serial.println(rcvdPayload);
    }
  */
  if (tick >= 5)  // publish to topic every 5seconds
  {
    tick = 0;
    //result in lot
    SeaTrans.read(0, data2 , 16);
    //UART
    /*
      for (i=0;i<=16;i=i+1)
      {
      Serial.printf("%02x ",[i]);
      }
    */
    Serial.print("\r\n");

    //sprintf(payload,"Hello from hornbill ESP32 : %d",msgCount++);
    //sprintf(payload,"[%d:%d] = %2x %2x \r\n",i+1,i,[i+1],data2[i]);
    //sprintf(payload," ");
    /*
      for (i=0;i<16;i=i+1)
      {
      payload[i] = data1[i];
      }
    */

    sprintf(payload, "{\
    \"Temprature\": \"%.2x%.2x\",\
    \"Attitude_angle_data\":{\
        \"X\":\"%.2x%.2x\",\
        \"Y\":\"%.2x%.2x\",\
        \"Z\":\"%.2x%.2x\"\
    },\
    \"Accelaration_data\": {\
        \"X\":\"%.2x%.2x\",\
        \"Y\":\"%.2x%.2x\",\
        \"Z\":\"%.2x%.2x\"\
    }\
}", data2[1], data2[0], data2[3], data2[2], data2[5], data2[4], data2[7], data2[6], data2[9], data2[8], data2[11], data2[10], data2[13], data2[12]);
    if (hornbill.publish(TOPIC_NAME, payload) == 0)
    {
      Serial.println("Publish successfully!");
      Serial.println(payload);
    }
    else
    {
      Serial.println("Publish failed!");
    }
  }
  msgReceived = 0;
  vTaskDelay(10 / portTICK_RATE_MS);
  //msgReceived = 0;
  tick++;
}
