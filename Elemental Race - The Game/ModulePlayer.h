#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "PhysVehicle3D.h"
#include "Timer.h"


struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define MAX_SPEED 200
#define MIN_SPEED -50

struct Checkpoint {

	float sizeX;
	float sizeY;
	float sizeZ;

	float posX_left;
	float posY_left;
	float posZ_left;

	float posX_right;
	float posY_right;
	float posZ_right;

	float posX_respawn_point;
	float posY_respawn_point;
	float posZ_respawn_point;
	
	int lap;
	bool activated;
	bool activated_last;
	int colour;			// 0 for red, not activated; 1 for orange, activated 1; 2 for yellow, activated 2; 3 for green, activated 3

	bool isStart = false;
	int num_checkpoint;

};

class ModulePlayer : public Module {
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//NUR
	bool UpdateCheckpoint(Checkpoint originalCheckpoint, Checkpoint nextCheckpoint, int lap, bool started);
	void Respawn(PhysBody3D* respawn_point, Checkpoint activatedCheckpoint);
	void RespawnAtOrigin();

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

	bool following_camera;
	vec3 dist_to_car;

	//timer
	Timer			timer;
	bool			timerOn = false;
	bool			hasWon = false;
	bool			raceFinished = false;
	//NUR
	//checkpoints
	int lap;
	bool started = false;
	int num_checkpoints = 4;

};