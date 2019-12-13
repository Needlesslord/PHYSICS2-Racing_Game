#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "PhysVehicle3D.h"


struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define MAX_SPEED 200
#define MIN_SPEED -50

class ModulePlayer : public Module {
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	VehicleInfo bus;
	VehicleInfo bike;
	VehicleInfo truck;
	VehicleInfo racingCar;

	PhysVehicle3D* Bus;
	PhysVehicle3D* Bike;
	PhysVehicle3D* Truck;
	PhysVehicle3D* RacingCar;
	//STRUCT VEHICLE
	
	bool vehicleSelected;
	uint vehicleSelectedNum; // 0 -> No vehicle selected; 1 -> bus; 2 -> truck; 

	float turn;
	float acceleration;
	float brake;
};