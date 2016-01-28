#include "hazard_area.h"
#include "string"
#include <fstream>


bool	string_to_bool(string strval)
{
	if(strval == "0")
	{
		return false;
	}
	else if(strval == "1")
	{
		return true;
	}
}

// convert enum values to enum strings for display
string	int_to_string(hazard_type target_type)
{
	string	type_value;

	if(target_type == 1)
	{
		type_value = "FIRE";
	}
	else if(target_type == 2)
	{
		type_value = "EARTHQUAKE";
	}
	else if(target_type == 3)
	{
		type_value = "TSUNAMI";
	}
	else if(target_type == 4)
	{
		type_value = "TORNADO";
	}
	else if(target_type == 5)
	{
		type_value = "MUDSLIDE";
	}

	return type_value;
}


hazard_area::hazard_area()
{
	hazard_head = NULL;
	list_length = 0;
}


hazard_area::~hazard_area()
{
	//hazard_item *temp_head;

	//temp_head = hazard_head;

 //	while (temp_head->next_hazard != NULL)
	//{
	//	temp_head->prev_hazard = temp_head->next_hazard;
	//	temp_head->next_hazard = temp_head->next_hazard->next_hazard;
	//	free(temp_head);
	//}

	//Deconstructor Fix
	hazard_item		*temp_hazard;

	temp_hazard = hazard_head;

	if(temp_hazard == NULL)
	{
		cout << "EMPTY LIST" << endl;
	}
	else
	{
		while(temp_hazard)
		{
			hazard_item		*target_hazard = temp_hazard;
			temp_hazard = temp_hazard->next_hazard;
			delete target_hazard;
		}
	}
}

bool	hazard_area::hazard_load()
{
	ifstream		infile("hazards.txt");
	ifstream		line_check("hazards.txt");
	string			line_check_string;
	hazard_item		*curr_hazard;
	string			str_buffer;
	bool			empty;

	if(!infile.is_open() || !line_check.is_open())
	{
		cout << "FILE NOT OPENED" << endl;
		return false;
	}

	streampos		current = infile.tellg();
	infile.seekg (0, infile.end);

	empty = !infile.tellg(); // true if empty file

	if(empty)	// file is empty
	{
		cout << "EMPTY FILE" << endl;
		return false;
	}

	infile.seekg (current, infile.beg);

	curr_hazard = hazard_head;


	do
	{
		getline(line_check, line_check_string);

		if(line_check_string == "") // empty line
		{
			break;
		}

		hazard_item		*new_hazard = new hazard_item;
		
		infile >> str_buffer;
		new_hazard->id = atoi(str_buffer.c_str());
		infile >> str_buffer;
		new_hazard->status = string_to_bool(str_buffer);
		infile >> str_buffer;
		new_hazard->longitude = atof(str_buffer.c_str());
		infile >> str_buffer;
		new_hazard->latitude = atof(str_buffer.c_str());
		infile >> str_buffer;
		new_hazard->radius = atof(str_buffer.c_str());
		infile >> str_buffer;
		new_hazard->type = (hazard_type)atoi(str_buffer.c_str());
		infile >> str_buffer;
		new_hazard->risk_level = atoi(str_buffer.c_str());
		new_hazard->next_hazard = NULL;

		++list_length;
		curr_hazard = hazard_head;

		if(hazard_head == NULL)
		{
			hazard_head = new_hazard;
		}
		else
		{
			while(curr_hazard->next_hazard != NULL)
			{
				curr_hazard = curr_hazard->next_hazard;
			}

			curr_hazard->next_hazard = new_hazard;
		}
	} while(!infile.eof());

	return true;
}


bool	hazard_area::hazard_save()
{
	// store entire linked list into a text file

	if(hazard_head == NULL)		// empty linked list
	{
		perror("EMPTY LIST");
		return false;
	}
	else
	{
		hazard_item		*curr_hazard = hazard_head;
		ofstream		outfile("hazards.txt");

		if(!outfile.is_open())
		{
			cout << "FILE NOT OPENED" << endl;
			return false;
		}

		do
		{
			outfile << curr_hazard->id << " " << curr_hazard->status << " " << curr_hazard->longitude << " " << curr_hazard->latitude
					<< " " << curr_hazard->radius << " " << curr_hazard->type << " " << curr_hazard->risk_level << endl;

			if(curr_hazard->next_hazard == NULL)
			{
				break;
			}
			else
			{
				curr_hazard = curr_hazard->next_hazard;
			}

		} while(true);

		outfile.close();
	}

	return true;
}


bool	hazard_area::hazard_display()
{
	hazard_item		*curr_hazard;

	if(hazard_head == NULL)
	{
		cout << "EMPTY LIST" << endl;
		return false;
	}
	else
	{
		curr_hazard = hazard_head;

		while(curr_hazard)
		{
			cout << "HAZARD #" << curr_hazard->id << ": " << endl;
			cout << "\tSTATUS: ";

			if(curr_hazard->status == true) 
				cout << "ACTIVE" << endl;
			else 
				cout << "INACTIVE" << endl;

			cout << "\tPOSITION: (" << curr_hazard->longitude << ", " << curr_hazard->latitude << ")" << endl;
			cout << "\tRADIUS: " << curr_hazard->radius << endl;
			cout << "\tTYPE: " << int_to_string(curr_hazard->type) << endl;
			cout << "\tRISK LEVEL: " << curr_hazard->risk_level << endl;
			cout << "------------------------------------------------" << endl;

			curr_hazard = curr_hazard->next_hazard;
		}
	}

	return true;
}

bool	hazard_area::hazard_create()
{
	hazard_item		*tmp_ptr;
	hazard_item	*new_hazard = new hazard_item;

	new_hazard->id = list_length + 1;
	new_hazard->status = true;
	new_hazard->latitude = (float)(rand() % 122 + 110);
	new_hazard->longitude = (float)(rand() % 42 + 30);
	new_hazard->radius = (float)(rand() % 20 + 1);
	new_hazard->type = (hazard_type)(rand() % 5 + 1);
	new_hazard->risk_level = rand() % 3 + 1;
	new_hazard->next_hazard = NULL;

	cout << "HAZARD #" << new_hazard->id << endl;
	cout << "\tSTATUS: ";

	if(new_hazard->status == true) 
		cout << "ACTIVE" << endl;
	else 
		cout << "INACTIVE" << endl;

	cout << "\tPOSITION: (" << new_hazard->longitude << ", " << new_hazard->latitude << ")" << endl;
	cout << "\tRADIUS: " << new_hazard->radius << endl;
	cout << "\tTYPE: " << int_to_string(new_hazard->type) << endl;
	cout << "\tRISK LEVEL: " << new_hazard->risk_level << endl;
	cout << "------------------------------------------------" << endl;

	tmp_ptr = hazard_head;

	if (tmp_ptr == NULL)
	{
		//empty list
		hazard_head = new_hazard;
	}
	else
	{
		while (tmp_ptr->next_hazard != NULL)
		{
			tmp_ptr = tmp_ptr->next_hazard;
		}

		tmp_ptr->next_hazard = new_hazard;
	}

	list_length++;
	return true;
}

bool	hazard_area::hazard_delete(int hazard_id)
{
	//hazard_item *del_hazard = hazard_find(hazard_id);

	//// When the item was found
	//if (del_hazard != NULL)
	//{
	//	// When deleting item is the head
	//	if (del_hazard == *hazard_head)
	//	{
	//		// Set deleting item's next as head
	//		*hazard_head = del_hazard->next_hazard;
	//		// When there is at least one node
	//		if ((*hazard_head) != NULL)
	//		{
	//			// Set header's previous item as NULL
	//			(*hazard_head)->prev_hazard = NULL;
	//		}
	//	}
	//	// When deleting item is NOT the head
	//	else
	//	{
	//		hazard_item *tmp_hazard = del_hazard;

	//		// Replace previous node's next node
	//		del_hazard->prev_hazard->next_hazard = tmp_hazard->next_hazard;

	//		// When deleting item is not the last node
	//		if (del_hazard->next_hazard != NULL)
	//		{
	//			// Replace next node's previous node
	//			tmp_hazard->next_hazard->prev_hazard = del_hazard->prev_hazard;
	//		}
	//	}

	//	// Delete the item
	//	delete del_hazard;

	//	// Reduce total length
	//	list_length--;

	//	return 0;
	//}
	//// When the item was NOT found
	//else
	//{
	//	return -1;
	//}

	//DELETE FIX
	hazard_item		*prev_hazard = NULL;
	hazard_item		*curr_hazard = NULL;
	bool			found = false;

	if(hazard_head == NULL)		//empty list
	{
		cout << "EMPTY LIST" << endl;
	}
	else
	{
		prev_hazard = curr_hazard = hazard_head;

		for(int i = 0; i < list_length; ++i)
		{
			if((curr_hazard->id == hazard_id) && (i == 0))	// beginning of list
			{
				hazard_head = curr_hazard->next_hazard;
				found = true;
				break;
			}
			else if((curr_hazard->id == hazard_id) && (i == (list_length - 1)))		// end of list
			{
				prev_hazard->next_hazard = NULL;
				curr_hazard = NULL;
				found = true;
				break;
			}
			else if((curr_hazard->id == hazard_id) && (i > 0))	// middle of list
			{
				prev_hazard->next_hazard = curr_hazard->next_hazard;
				curr_hazard = NULL;
				found = true;
				break;
			}
			
			prev_hazard = curr_hazard;
			curr_hazard = curr_hazard->next_hazard;
		}
	}

	if(!found)
	{
		cout << "HAZARD NOT FOUND" << endl;
	}

	return found;
}


bool	hazard_area::hazard_update(hazard_item *target_hazard, hazard_item *new_hazard_values)
{
	bool			changed = false;


	if(target_hazard->status != new_hazard_values->status)
	{
		target_hazard->status = new_hazard_values->status;
		changed = true;
	}

	if(target_hazard->radius != new_hazard_values->radius)
	{
		target_hazard->radius = new_hazard_values->radius;
		changed = true;
	}

	if(target_hazard->type != new_hazard_values->type)
	{
		target_hazard->type = new_hazard_values->type;
		changed = true;
	}

	if(target_hazard->risk_level != new_hazard_values->risk_level)
	{
		target_hazard->risk_level = new_hazard_values->risk_level;
		changed = true;
	}

	return changed;
}


bool	hazard_area::get_status(int hazard_id)
{
	hazard_item *tmp_hazard = hazard_find(hazard_id);

	return tmp_hazard->status;
}	//traverse list; return status; call's hazard_find

float	hazard_area::get_radius(int hazard_id)
{
	hazard_item *tmp_hazard = hazard_find(hazard_id);
	return tmp_hazard->radius;
}  //same as status

float*	hazard_area::get_position(int hazard_id)
{
	hazard_item *tmp_hazard = hazard_find(hazard_id);
	return tmp_hazard->position;
}

hazard_type	hazard_area::get_type(int hazard_id)
{
	hazard_item *tmp_hazard = hazard_find(hazard_id);
	return tmp_hazard->type;
} //same as status

int hazard_area::get_risk_level(int hazard_id)
{
	hazard_item *tmp_hazard = hazard_find(hazard_id);
	return tmp_hazard->risk_level;
}  //same as status

void hazard_area::set_status(bool new_status, int hazard_id)
{
	hazard_item *tmp_hazard = hazard_find(hazard_id);
	tmp_hazard->status = new_status;
}

void hazard_area::set_radius(float new_radius, int hazard_id)
{
	hazard_item *tmp_hazard = hazard_find(hazard_id);
	tmp_hazard->radius = new_radius;
}

void hazard_area::set_position(float* new_position, int hazard_id)
{
	hazard_item *tmp_hazard = hazard_find(hazard_id);
	tmp_hazard->position[0] = new_position[0];
	tmp_hazard->position[1] = new_position[1];
}

void hazard_area::set_type(hazard_type new_type, int hazard_id)
{
	hazard_item *tmp_hazard = hazard_find(hazard_id);
	tmp_hazard->type = new_type;
}

void hazard_area::set_risk_level(int new_risk_level, int hazard_id)
{
	hazard_item *tmp_hazard = hazard_find(hazard_id);
	tmp_hazard->risk_level = new_risk_level;
}

hazard_item*	hazard_area::hazard_find(int hazard_id)
{
	hazard_item		*tmp_ptr;
	bool			found = false;

	tmp_ptr = hazard_head;

	if (tmp_ptr == NULL)
	{
		//empty list
		cout << "HAZARD NOT FOUND" << endl;
	}
	else
	{
		while (tmp_ptr != NULL)
		{
			if (tmp_ptr->id == hazard_id)
			{
				found = true;
				break;
			}

			tmp_ptr = tmp_ptr->next_hazard;
		}

	}

	if (found)
		return tmp_ptr;
	else
		return NULL;
}


