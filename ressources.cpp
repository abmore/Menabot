#include "ressources.h"

/****************************** variables ************************************/

/****************************************************************************/

/****************************** GENERAL SETUP *******************************/
void GeneralSetup()
{
	#if DEBUG_MODE == 1
		Serial.begin(115200);
	#endif
	DEBUG_PRINT("end GeneralSetup\n");
}
/****************************************************************************/

/****************************** ReadAllSerial	******************************/
void ReadAllSerial(char *output_ptr)
{
	char read_char;
	int pending_char;
	int cpt;
	String tmp_str;

	tmp_str = "";

	pending_char = Serial.available();


	if(pending_char != 0)
	{	
		for(cpt = 0; (cpt<15) && (cpt<pending_char); cpt++)
		{
			*(output_ptr + cpt) = Serial.read();
			tmp_str = tmp_str + *(output_ptr + cpt);
		}

		for(cpt = pending_char; (cpt<15); cpt++)
		{
			*(output_ptr + cpt) = 0;
		}

		DEBUG_PRINT("\nRecieved : ");
		DEBUG_PRINT(tmp_str);
	}
	else
	{
		*output_ptr = -1;
	}
}

/****************************************************************************/



/****************************** UserCmdExe	******************************/
void UserCmdExe(char *user_cmd)
{
	String tmp_cmd;
	String tmp_cmd_value;
	short u, v;
	unsigned int tmp_val;
	bool EndOfCmd,EndOfVal;


	/* here we consider that a command uses a maximum of 15 char. */
	EndOfCmd = FALSE;
	EndOfVal = FALSE;
	tmp_cmd="";
	tmp_cmd_value="";

	/*get the type of command */



	for( u=0; (u<15) && (user_cmd[u] >1) && (EndOfCmd == FALSE); u++)
	{
		if((user_cmd[u]!='(') && (EndOfCmd==FALSE))
		{
			/*DEBUG_PRINT("\nuser_cmd[");
			DEBUG_PRINT(u);
			DEBUG_PRINT("] :");
			DEBUG_PRINT(user_cmd[u]);*/

			tmp_cmd = tmp_cmd +user_cmd[u];

			/*DEBUG_PRINT("\t tmp_cmd:");
			DEBUG_PRINT(tmp_cmd);
			DEBUG_PRINT(".");*/
		}
		else if(EndOfCmd==FALSE)
		{
			/*DEBUG_PRINT("\nEndOfCmd\nuser_cmd[");
			DEBUG_PRINT(u);
			DEBUG_PRINT("] :");
			DEBUG_PRINT(user_cmd[u]);*/

			EndOfCmd = TRUE;
			v=u+1;
		}
	}

	DEBUG_PRINT("\n tmp_cmd:");
	DEBUG_PRINT(tmp_cmd);
	DEBUG_PRINT(".\n");

	/* get the optional value of the command*/
	for( u=v; (u<15) && (user_cmd[u] != 0) && (EndOfVal==FALSE); u++)
	{
		if((user_cmd[u]!=')') && (EndOfVal==FALSE))
		{
			/*DEBUG_PRINT("\nuser_cmd[");
			DEBUG_PRINT(u);
			DEBUG_PRINT("] :");
			DEBUG_PRINT(user_cmd[u]);*/

			tmp_cmd_value = tmp_cmd_value + user_cmd[u];

		/*	DEBUG_PRINT("\t tmp_cmd_value:");
			DEBUG_PRINT(tmp_cmd_value);
			DEBUG_PRINT(".");*/
		}
		else if(EndOfVal==FALSE)
		{
			DEBUG_PRINT("\nEnfOfVal\nuser_cmd[");
			DEBUG_PRINT(u);
			DEBUG_PRINT("] :");
			DEBUG_PRINT(user_cmd[u]);
			EndOfVal = TRUE;
			v=u;
		}
	}

	if ( (EndOfVal = TRUE) && (EndOfCmd = TRUE) )
	{
		/* there can't ben"switch" operand on String, so only if and else if are used */


		/*SetPinOn*/
		if(tmp_cmd=="SetPinOn")
		{
			if((tmp_cmd_value.toInt()>=0)||(tmp_cmd_value.toInt()<=NB_DIO))
			{
				digitalWrite(tmp_cmd_value.toInt(),HIGH);
				DEBUG_PRINT("\nPin Set ON : ");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(" .\n");
			}
			else
			{
				DEBUG_PRINT("\nInvalid PIN :");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(".\n");
			}
		}
		/*SetPinOff*/
		else if(tmp_cmd=="SetPinOff")
		{
			if((tmp_cmd_value.toInt()>=0)||(tmp_cmd_value.toInt()<=NB_DIO))
			{
				digitalWrite(tmp_cmd_value.toInt(),LOW);
				DEBUG_PRINT("\nPin Set OFF : ");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(" .\n");
			}
			else
			{
				DEBUG_PRINT("\nInvalid PIN :");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(".\n");
			}
		}
		/*PulsePin*/
		else if(tmp_cmd=="PulsePin")
		{
			if((tmp_cmd_value.toInt()>=0)||(tmp_cmd_value.toInt()<=NB_DIO))
			{
				digitalWrite(tmp_cmd_value.toInt(),LOW);
				DEBUG_PRINT("\nPin Set OFF : ");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(" .\n");

				digitalWrite(tmp_cmd_value.toInt(),HIGH);
				DEBUG_PRINT("\nPin Set OFF : ");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(" .\n");
				
				delayMicroseconds(10);

				digitalWrite(tmp_cmd_value.toInt(),LOW);
				DEBUG_PRINT("\nPin Set OFF : ");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(" .\n");
			}
			else
			{
				DEBUG_PRINT("\nInvalid PIN :");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(".\n");
			}
		}
		/*GetAnalog*/
		else if(tmp_cmd=="GetAnalog")
		{
			DEBUG_PRINT("\nAnalog Read : ");
			DEBUG_PRINT(analogRead(0));
			DEBUG_PRINT(" .\n");
		}
		/* not supported cmd */
		else
		{

				DEBUG_PRINT("\nInvalid command :");
				DEBUG_PRINT(tmp_cmd);
				DEBUG_PRINT(".\n");
		}

	}
}
