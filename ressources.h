/* ressources.h version 1.00 */

#ifndef ressources_h
	#define ressources_h


	#ifndef Arduino_h
	  #include <Arduino.h>
	#endif

	/* Set DEBUG_MODE to 1 to have debug print information */
	#define DEBUG_MODE 1

	#if DEBUG_MODE == 1
	  #define DEBUG_PRINT(x) Serial.print(x)
	#else
	  #define DEBUG_PRINT(x) 
	#endif

	#define NB_DIO 13 // Arduino UNO
	//#define NB_DIO 53 // Arduino DUE & Arduino MEGA

	#define TRUE HIGH
	#define FALSE LOW

	#define ERROR_CALL(x) {\
	                      Serial.println(x);\
	                      Serial.print("\n\t\t ENTER ERROR VOID LOOP.");\
	                      while(1){delay(100);}}


	void GeneralSetup();
#endif
