#pragma once
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
using namespace std;

// stackoverflow.com/questions/20817420/creating-linked-list-in-c

//Some sort of file handling function for final draft.


enum hazard_type
{
	fire, earthquake, tsunami, tornado, mudslide
};

struct hazard_item
{
	int				id;
	bool			status;
	float			longitude;
	float			latitude;
	float			position[2]; // {longitude, latitude };
	float			radius;
	hazard_type		type;
	int				risk_level;
	hazard_item		*next_hazard;
	//hazard_item		*prev_hazard;
};

class hazard_area
{
public:
	hazard_area();
	~hazard_area();

	bool			hazard_load();
	bool			hazard_save();
	bool			hazard_display();
	bool			hazard_create();
	bool			hazard_delete(int hazard_id); // Kevin's portion
	bool			hazard_update(hazard_item *target_hazard, hazard_item *new_hazard_values);

	bool			get_status(int hazard_id);
	float			get_radius(int hazard_id);
	float*			get_position(int hazard_id);
	hazard_type		get_type(int hazard_id);
	int				get_risk_level(int hazard_id);
	void			set_status(bool new_status, int hazard_id);
	void			set_radius(float new_radius, int hazard_id);
	void			set_position(float* new_position, int hazard_id);
	void			set_type(hazard_type new_type, int hazard_id);
	void			set_risk_level(int new_risk_level, int hazard_id);

	hazard_item*	hazard_find(int hazard_id);//Traverses the list and spits out the found node.

private:
	int				list_length;  // everytime we add a node, increment this.
	hazard_item		*hazard_head;
};

