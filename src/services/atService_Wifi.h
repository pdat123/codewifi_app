

#ifndef _Service_atService_Wifi_
#define _Service_atService_Wifi_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "Service.h"
#include<Arduino.h>
#include<WiFi.h>

/* _____DEFINETIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
String ssid;
String password;
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_Wifi : public Service
{
public:
    Service_Wifi();
    ~Service_Wifi();
    
protected:
     
private:
    static void  Service_Wifi_Start();
    static void  Service_Wifi_Execute();    
    static void  Service_Wifi_End();
} atService_Wifi ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_Wifi::Service_Wifi(/* args */)
{
    _Start_User      = *Service_Wifi_Start;
    _Execute_User    = *Service_Wifi_Execute;
    _End_User        = *Service_Wifi_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"Wifi Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_Wifi::~Service_Wifi()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_Wifi::Service_Wifi_Start()
{
    
}  

/**
 * Execute fuction of SNM app
 */
void  Service_Wifi::Service_Wifi_Execute()
{   
    if(atService_Wifi.User_Mode == SER_USER_MODE_DEBUG)
    {
        
    }   
}    
void  Service_Wifi::Service_Wifi_End(){}

void scanwifi(){
  int a = WiFi.scanNetworks();
  if (a == 0)
  {
    Serial.println("No Wifi found");
  }
  else
  {
    Serial.println("List of wifi networks:");
    for (int i = 0; i < a; i++)
    {
      Serial.println(String(i+1)+"."+WiFi.SSID(i)+"("+WiFi.RSSI(i)+" dBm)");
      delay(500);
    }    
  }  
}

void conncettowifi()
{
  //enter the wifi name
  bool invalidSSID = true;
  while (invalidSSID)
  {
    Serial.print("Enter the wifi name: ");
    while (!Serial.available())
    {
      //wait for user to enter the wifi name
    }
    ssid = Serial.readString();
    ssid.trim();
    Serial.println(ssid);
    int a = WiFi.scanNetworks();
    for (int i = 0; i < a; i++)
    {
      if (ssid == WiFi.SSID(i))
      {
        invalidSSID = false;
        break;
      }
    }
    if (invalidSSID)
    {
      Serial.print(ssid);
      Serial.println(" isn't in list of wifi.Please try again.");
    }
  }

  //enter the password
  bool invalidpassword = true;
  while (invalidpassword)
  {
    Serial.print("Enter password: ");
    while (!Serial.available())
    {
      //wait for user to enter password
    }
    password = Serial.readString();
    password.trim();
    Serial.println(password);

    Serial.print("connecting to ");
    Serial.print(ssid);
    WiFi.begin(ssid.c_str(),password.c_str());
    unsigned long b = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - b <10000)
    {
      Serial.print(".");
      delay(1000);
    }
    Serial.println("");
    if (WiFi.status() == WL_CONNECTED)
    {
      invalidpassword = false;
      Serial.print("Successfully conncetion to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    }
    else
    {
      Serial.println("Wifi connection failed.Please try again.");
    }
  }
}

void disconnectowifi()
{
  WiFi.disconnect(true);
  Serial.print("Disconnect to wifi");
}

#endif