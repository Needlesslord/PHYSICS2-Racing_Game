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
	VehicleInfo car;
	VehicleInfo bus;
	VehicleInfo bike;
	VehicleInfo truck;
	VehicleInfo trailer;
	VehicleInfo racingCar;
	VehicleInfo monsterTruck;
	VehicleInfo bigTruck;
	VehicleInfo bigTrailer;
	VehicleInfo mini;

	PhysVehicle3D* Car;
	PhysVehicle3D* Bus;
	PhysVehicle3D* Bike;
	PhysVehicle3D* Truck;
	PhysVehicle3D* Trailer;
	PhysVehicle3D* RacingCar;
	PhysVehicle3D* MonsterTruck;
	PhysVehicle3D* BigTruck;
	PhysVehicle3D* BigTrailer;
	PhysVehicle3D* Mini;
	//STRUCT VEHICLE
	
	bool vehicleSelected;
	uint vehicleSelectedNum; // 0 -> car; 1 -> bus; 2 -> truck; 3 -> racingCar; 4 -> mosterTruck; 5 -> bigTruck; 6 -> mini; T -> add Trailer 
	bool trailerAdded;

	float turn;
	float acceleration;
	float brake;

	bool  following_camera;
	vec3 dist_to_car;

};