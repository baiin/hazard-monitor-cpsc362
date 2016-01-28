#include <iostream>
#include "hazard_area.h"
using namespace std;


hazard_item*	copy_hazard(hazard_item *target_hazard)
{
	hazard_item		*new_hazard = new hazard_item;

	new_hazard->id = target_hazard->id;
	new_hazard->status = target_hazard->status;
	new_hazard->longitude = target_hazard->longitude;
	new_hazard->latitude = target_hazard->latitude;
	new_hazard->radius = target_hazard->radius;
	new_hazard->type = target_hazard->type;
	new_hazard->risk_level = target_hazard->risk_level;

	return new_hazard;
}


int		main(void)
{
	hazard_area  hazard_list;
	
	bool	done = false;
	char	option;

	while(!done)
	{
		cout << "----------------------------------" << endl;
		cout << "|       HAZARD AREA SYSTEM       |" << endl;
		cout << "----------------------------------" << endl;
		cout << "| A) LOAD HAZARDS FROM DATABASE  |" << endl;
		cout << "| B) CREATE NEW HAZARD           |" << endl;
		cout << "| C) DELETE SPECIFIC HAZARD      |" << endl;
		cout << "| D) SAVE HAZARDS INTO DATABASE  |" << endl;
		cout << "| E) UPDATE SPECIFIC HAZARD      |" << endl;
		cout << "| F) DISPLAY ALL HAZARDS IN LIST |" << endl;
		cout << "| G) QUIT                        |" << endl;
		cout << "----------------------------------" << endl;
		cout << "INPUT: ";
		cin  >> option;

		option = toupper(option);

		switch(option)
		{
		case 'A':
			system("cls");
			if(hazard_list.hazard_load())
				cout << "SUCCESS" << endl;
			else
				cout << "FAILED" << endl;
			break;
		case 'B':
			system("cls");
			if(hazard_list.hazard_create())
				cout << "SUCCESS" << endl;
			else
				cout << "FAILED" << endl;
			break;
		case 'C':
			cin.sync();
			cin.clear();
			system("cls");

			int		target_id;
			cout << "ENTER HAZARD ID TO BE DELETED: ";
			cin  >> target_id;

			if(hazard_list.hazard_delete(target_id))
				cout << "SUCCESS" << endl;
			else
				cout << "FAILED" << endl;
			break;
		case 'D':
			if(hazard_list.hazard_save())
				cout << "SUCCESS" << endl;
			else
				cout << "FAILED" << endl;
			break;

		case 'E':
			// prompt user for hazard to change
			hazard_item		*new_hazard_value;
			int				updated_hazard_id;

			cin.sync();
			cin.clear();
			system("cls");
			cout << "ENTER HAZARD ID FOR HAZARD TO BE UPDATED: ";
			cin  >> updated_hazard_id;

			// copy the hazard targeted for an update
			if(hazard_list.hazard_find(updated_hazard_id) == NULL)
			{
				cout << "HAZARD ID " << updated_hazard_id << " IS NOT IN LIST" << endl;
			}
			else
			{
				new_hazard_value = copy_hazard(hazard_list.hazard_find(updated_hazard_id));
				char	property_input;

				cin.sync();
				cin.clear();
				system("cls");
				// if hazard exist, prompt user for property to change
				cout << "----------------------------------" << endl;
				cout << "|       PROPERTY TO MODIFY       |" << endl;
				cout << "----------------------------------" << endl;
				cout << "| A) HAZARD STATUS               |" << endl;
				cout << "| B) HAZARD RADIUS               |" << endl;
				cout << "| C) HAZARD TYPE                 |" << endl;
				cout << "| D) HAZARD RISK LEVEL           |" << endl;
				cout << "| E) CANCEL                      |" << endl;
				cout << "----------------------------------" << endl;
				cout << "INPUT: ";
				cin  >> property_input;

				property_input = toupper(property_input);

				switch(property_input)
				{
				case 'A':
					char	new_status;

					cin.sync();
					cin.clear();
					system("cls");
					cout << "ENTER NEW STATUS (T/F): ";
					cin  >> new_status;

					new_status = toupper(new_status);

					if(new_status == 'T')
					{
						new_hazard_value->status = true;
						
						if(hazard_list.hazard_update(hazard_list.hazard_find(updated_hazard_id), new_hazard_value))
						{
							cout << "SUCCESFUL MODIFICATION" << endl;
						}
						else
						{
							cout << "REDUNDANT MODIFICATION" << endl;
						}
					}
					else if(new_status == 'F')
					{
						new_hazard_value->status = false;
						
						if(hazard_list.hazard_update(hazard_list.hazard_find(updated_hazard_id), new_hazard_value))
						{
							cout << "SUCCESFUL MODIFICATION" << endl;
						}
						else
						{
							cout << "REDUNDANT MODIFICATION" << endl;
						}
					}
					else
					{
						cout << "FAILED INPUT" << endl;
					}

					break;
				case 'B':
					float	new_radius;
					
					cin.sync();
					cin.clear();
					system("cls");
					cout << "ENTER NEW RADIUS (1 - 100): ";
					cin  >> new_radius;

					if(new_radius <= 100 && new_radius >= 1)
					{
						new_hazard_value->radius = new_radius;

						if(hazard_list.hazard_update(hazard_list.hazard_find(updated_hazard_id), new_hazard_value))
						{
							cout << "SUCCESFUL MODIFICATION" << endl;
						}
						else
						{
							cout << "REDUNDANT MODIFICATION" << endl;
						}
					}
					else
					{
						cout << "FAILED INPUT" << endl;
					}
					
					break;
				case 'C':
					int		new_hazard_type;

					cin.sync();
					cin.clear();
					system("cls");
					cout << "----------------------------------" << endl;
					cout << "|     SELECT NEW HAZARD TYPE     |" << endl;
					cout << "----------------------------------" << endl;
					cout << "| 1) FIRE                        |" << endl;
					cout << "| 2) EARTHQUAKE                  |" << endl;
					cout << "| 3) TSUNAMI                     |" << endl;
					cout << "| 4) TORNADO                     |" << endl;
					cout << "| 5) MUDSLIDE                    |" << endl;
					cout << "| 6) CANCEL                      |" << endl;
					cout << "----------------------------------" << endl;
					cout << "INPUT: ";
					cin  >> new_hazard_type;

					if(new_hazard_type <= 5 && new_hazard_type >= 1)
					{
						new_hazard_value->type = (hazard_type)new_hazard_type;

						if(hazard_list.hazard_update(hazard_list.hazard_find(updated_hazard_id), new_hazard_value))
						{
							cout << "SUCCESFUL MODIFICATION" << endl;
						}
						else
						{
							cout << "REDUNDANT MODIFICATION" << endl;
						}
					}
					else
					{
						cout << "FAILED INPUT" << endl;
					}

					break;
				case 'D':
					int		new_risk_level;

					cin.sync();
					cin.clear();
					system("cls");
					cout << "ENTER NEW RISK LEVEL (1 - 10): " << endl;
					cin  >> new_risk_level;

					if(new_risk_level <= 10 && new_risk_level >= 1)
					{
						new_hazard_value->risk_level = new_risk_level;

						if(hazard_list.hazard_update(hazard_list.hazard_find(updated_hazard_id), new_hazard_value))
						{
							cout << "SUCCESFUL MODIFICATION" << endl;
						}
						else
						{
							cout << "REDUNDANT MODIFICATION" << endl;
						}
					}
					else
					{
						cout << "FAILED INPUT" << endl;
					}

					break;
				case 'E':
					break;
				default:
					cout << "FAILED INPUT" << endl;
					break;
				}
			}	

			break;
		case 'F':
			system("cls");
			if(hazard_list.hazard_display())
				cout << "SUCCESS" << endl;
			else
				cout << "FAILED" << endl;
			break;
		case 'G':
			done = true;
			break;
		}

		system("pause");
		system("cls");
	}

	return 0;
}