
#ifndef _Application_atApp_Wifi_
#define _Application_atApp_Wifi_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_Wifi.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_Wifi;  
void atApp_Wifi_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_Wifi : public Application
{
public:
  	App_Wifi();
 	~App_Wifi();
protected:
private:
  	static void  App_Wifi_Pend();
	static void  App_Wifi_Start();
	static void  App_Wifi_Restart();
	static void  App_Wifi_Execute();
	static void  App_Wifi_Suspend();
	static void  App_Wifi_Resume();	  
	static void  App_Wifi_End();
} atApp_Wifi ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_Wifi::App_Wifi(/* args */)
{
  	_Pend_User 	     = *App_Wifi_Pend;
	_Start_User 	 = *App_Wifi_Start;
	_Restart_User 	 = *App_Wifi_Restart;
	_Execute_User 	 = *App_Wifi_Execute;
	_Suspend_User	 = *App_Wifi_Suspend;
	_Resume_User	 = *App_Wifi_Resume;
	_End_User	     = *App_Wifi_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"Wifi Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_Wifi::~App_Wifi()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_Wifi::App_Wifi_Pend()
{
    // atService_Wifi.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_Wifi::App_Wifi_Start()
{
	// init atWifi Service in the fist running time
	// atService_Wifi.Run_Service();
		WiFi.mode(WIFI_STA);
		WiFi.disconnect(true);
		Serial.begin(115200);
  		Serial.println("Setup done");
  		scanwifi();
  		delay(1000);
  		conncettowifi();
}  
/**
 * Restart function of SNM  app
 */
void  App_Wifi::App_Wifi_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_Wifi::App_Wifi_Execute()
{	
	// atService_Wifi.Run_Service();
    if(atApp_Wifi.User_Mode == APP_USER_MODE_DEBUG)
    {
		if (Serial.available())
  		{
    		String command = Serial.readString();
    		Serial.print(command);
    		command.trim();
    		if (command == "disconnect" || command == "Disconnect")
    		{
      			disconnectowifi();
      			unsigned long c = millis();
      			while (millis() - c < 3000)
      			{
        			Serial.print(".");
        			delay(1000);
      			}
      			Serial.println("");
      			conncettowifi();
    		}
  		}
    }   
}
void  App_Wifi::App_Wifi_Suspend(){}
void  App_Wifi::App_Wifi_Resume(){}	  
void  App_Wifi::App_Wifi_End(){}
void atApp_Wifi_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_Wifi.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif