#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "Primitive.h"
#include "Color.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), Bus(NULL)
{
	turn = acceleration = brake = 0.0f;

	//CAMERA
	following_camera = false;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	//// Bus properties ----------------------------------------
	//bus.chassis_size.Set(5, 9, 12);
	//bus.chassis_offset.Set(0, 4.5, 0);
	//bus.mass = 500.0f;
	//bus.suspensionStiffness = 15.88f;
	//bus.suspensionCompression = 0.83f;
	//bus.suspensionDamping = 0.88f;
	//bus.maxSuspensionTravelCm = 1000.0f;
	//bus.frictionSlip = 50.5;
	//bus.maxSuspensionForce = 6000.0f;
	//bus.chasisColor = Purple;
	//
	//// Wheel properties ---------------------------------------
	//float bus_connection_height = 0.6f;
	//float bus_wheel_radius = 1.2f;
	//float bus_wheel_width = 0.8f;
	//float bus_suspensionRestLength = 1.2f;

	//// Don't change anything below this line ------------------

	//float bus_half_width = bus.chassis_size.x * 0.5f;
	//float bus_half_length = bus.chassis_size.z * 0.5f;
	//
	//vec3 bus_direction(0,-1,0);
	//vec3 bus_axis(-1,0,0);
	//
	//bus.num_wheels = 6;
	//bus.wheels = new Wheel[6];

		// Bus properties (small) ----------------------------------------
	bus.chassis_size.Set(4, 5.5, 11.5);
	bus.chassis_offset.Set(0, 2.5, 0);
	bus.mass = 500.0f;
	bus.suspensionStiffness = 15.88f;
	bus.suspensionCompression = 0.83f;
	bus.suspensionDamping = 0.88f;
	bus.maxSuspensionTravelCm = 1000.0f;
	bus.frictionSlip = 50.5;
	bus.maxSuspensionForce = 6000.0f;
	bus.chasisColor = Purple;

	// Wheel properties (small) ---------------------------------------
	float bus_connection_height = 0.6f;
	float bus_wheel_radius = 0.8f;
	float bus_wheel_width = 0.65f;
	float bus_suspensionRestLength = 1.2f;

	// Don't change anything below this line (small) ------------------

	float bus_half_width = bus.chassis_size.x * 0.5f;
	float bus_half_length = bus.chassis_size.z * 0.5f;

	vec3 bus_direction(0, -1, 0);
	vec3 bus_axis(-1, 0, 0);

	bus.num_wheels = 6;
	bus.wheels = new Wheel[6];


	// FRONT-LEFT ------------------------
	bus.wheels[0].connection.Set(bus_half_width - 0.3f * bus_wheel_width, bus_connection_height, bus_half_length * 0.95f - bus_wheel_radius);
	bus.wheels[0].direction = bus_direction;
	bus.wheels[0].axis = bus_axis;
	bus.wheels[0].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[0].radius = bus_wheel_radius;
	bus.wheels[0].width = bus_wheel_width;
	bus.wheels[0].front = true;
	bus.wheels[0].drive = true;
	bus.wheels[0].brake = false;
	bus.wheels[0].steering = true;
	bus.wheels[0].color = Black;

	// FRONT-RIGHT ------------------------
	bus.wheels[1].connection.Set(-bus_half_width + 0.3f * bus_wheel_width, bus_connection_height, bus_half_length * 0.95f - bus_wheel_radius);
	bus.wheels[1].direction = bus_direction;
	bus.wheels[1].axis = bus_axis;
	bus.wheels[1].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[1].radius = bus_wheel_radius;
	bus.wheels[1].width = bus_wheel_width;
	bus.wheels[1].front = true;
	bus.wheels[1].drive = true;
	bus.wheels[1].brake = false;
	bus.wheels[1].steering = true;
	bus.wheels[1].color = Black;

	// REAR-LEFT ------------------------
	bus.wheels[2].connection.Set(bus_half_width - 0.3f * bus_wheel_width - bus_wheel_width, bus_connection_height, -bus_half_length * 0.80f + bus_wheel_radius);
	bus.wheels[2].direction = bus_direction;
	bus.wheels[2].axis = bus_axis;
	bus.wheels[2].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[2].radius = bus_wheel_radius;
	bus.wheels[2].width = bus_wheel_width;
	bus.wheels[2].front = false;
	bus.wheels[2].drive = false;
	bus.wheels[2].brake = true;
	bus.wheels[2].steering = false;
	bus.wheels[2].color = Black;

	// REAR-RIGHT ------------------------
	bus.wheels[3].connection.Set(-bus_half_width + 0.3f * bus_wheel_width + bus_wheel_width, bus_connection_height, -bus_half_length * 0.80f + bus_wheel_radius);
	bus.wheels[3].direction = bus_direction;
	bus.wheels[3].axis = bus_axis;
	bus.wheels[3].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[3].radius = bus_wheel_radius;
	bus.wheels[3].width = bus_wheel_width;
	bus.wheels[3].front = false;
	bus.wheels[3].drive = false;
	bus.wheels[3].brake = true;
	bus.wheels[3].steering = false;
	bus.wheels[3].color = Black;

	// BACK-MID-LEFT ------------------------
	bus.wheels[4].connection.Set(bus_half_width, bus_connection_height, -bus_half_length * 0.80f + bus_wheel_radius);
	bus.wheels[4].direction = bus_direction;
	bus.wheels[4].axis = bus_axis;
	bus.wheels[4].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[4].radius = bus_wheel_radius;
	bus.wheels[4].width = bus_wheel_width;
	bus.wheels[4].front = false;
	bus.wheels[4].drive = false;
	bus.wheels[4].brake = true;
	bus.wheels[4].steering = false;
	bus.wheels[4].color = Black;

	// BACK-MID-RIGHT ------------------------
	bus.wheels[5].connection.Set(-bus_half_width, bus_connection_height, -bus_half_length * 0.80f + bus_wheel_radius);
	bus.wheels[5].direction = bus_direction;
	bus.wheels[5].axis = bus_axis;
	bus.wheels[5].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[5].radius = bus_wheel_radius;
	bus.wheels[5].width = bus_wheel_width;
	bus.wheels[5].front = false;
	bus.wheels[5].drive = false;
	bus.wheels[5].brake = true;
	bus.wheels[5].steering = false;
	bus.wheels[5].color = Black;
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Truck properties ----------------------------------------

	truck.chassis_size.Set(6, 8, 24);
	truck.chassis_offset.Set(0, 4.5, 0);
	truck.mass = 1000.0f;
	truck.suspensionStiffness = 15.88f;
	truck.suspensionCompression = 0.83f;
	truck.suspensionDamping = 0.88f;
	truck.maxSuspensionTravelCm = 1000.0f;
	truck.frictionSlip = 50.5;
	truck.maxSuspensionForce = 6000.0f;
	truck.chasisColor = White;

	// Wheel properties ---------------------------------------
	float truck_connection_height = 0.8f;
	float truck_wheel_radius = 1.2f;
	float truck_wheel_width = 1.2f;
	float truck_suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float truck_half_width = truck.chassis_size.x * 0.5f;
	float truck_half_length = truck.chassis_size.z * 0.5f;

	vec3 truck_direction(0, -1, 0);
	vec3 truck_axis(-1, 0, 0);

	truck.num_wheels = 12;
	truck.wheels = new Wheel[12];

	// FRONT-LEFT ------------------------
	truck.wheels[0].connection.Set(truck_half_width - 0.6f * truck_wheel_width, truck_connection_height, truck_half_length * 0.95f - truck_wheel_radius);
	truck.wheels[0].direction = truck_direction;
	truck.wheels[0].axis = truck_axis;
	truck.wheels[0].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[0].radius = truck_wheel_radius;
	truck.wheels[0].width = truck_wheel_width;
	truck.wheels[0].front = true;
	truck.wheels[0].drive = true;
	truck.wheels[0].brake = false;
	truck.wheels[0].steering = true;
	truck.wheels[0].color = Black;

	// FRONT-RIGHT ------------------------
	truck.wheels[1].connection.Set(-truck_half_width + 0.6f * truck_wheel_width, truck_connection_height, truck_half_length * 0.95f - truck_wheel_radius);
	truck.wheels[1].direction = truck_direction;
	truck.wheels[1].axis = truck_axis;
	truck.wheels[1].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[1].radius = truck_wheel_radius;
	truck.wheels[1].width = truck_wheel_width;
	truck.wheels[1].front = true;
	truck.wheels[1].drive = true;
	truck.wheels[1].brake = false;
	truck.wheels[1].steering = true;
	truck.wheels[1].color = Black;



	// FRONT-BACK-LEFT ------------------------
	truck.wheels[2].connection.Set(truck_half_width - 0.6f * truck_wheel_width, truck_connection_height, truck_half_length * 0.20f + truck_wheel_radius);
	truck.wheels[2].direction = truck_direction;
	truck.wheels[2].axis = truck_axis;
	truck.wheels[2].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[2].radius = truck_wheel_radius;
	truck.wheels[2].width = truck_wheel_width;
	truck.wheels[2].front = false;
	truck.wheels[2].drive = false;
	truck.wheels[2].brake = true;
	truck.wheels[2].steering = false;
	truck.wheels[2].color = Black;

	// FRONT-BACK-RIGHT ------------------------
	truck.wheels[3].connection.Set(-truck_half_width + 0.6f * truck_wheel_width, truck_connection_height, truck_half_length * 0.20f + truck_wheel_radius);
	truck.wheels[3].direction = truck_direction;
	truck.wheels[3].axis = truck_axis;
	truck.wheels[3].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[3].radius = truck_wheel_radius;
	truck.wheels[3].width = truck_wheel_width;
	truck.wheels[3].front = false;
	truck.wheels[3].drive = false;
	truck.wheels[3].brake = true;
	truck.wheels[3].steering = false;
	truck.wheels[3].color = Black;

//

	// REAR-LEFT ------------------------
	truck.wheels[4].connection.Set(truck_half_width - 0.3f * truck_wheel_width - truck_wheel_width, truck_connection_height, -truck_half_length * 0.65f + truck_wheel_radius);
	truck.wheels[4].direction = truck_direction;
	truck.wheels[4].axis = truck_axis;
	truck.wheels[4].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[4].radius = truck_wheel_radius;
	truck.wheels[4].width = truck_wheel_width;
	truck.wheels[4].front = false;
	truck.wheels[4].drive = false;
	truck.wheels[4].brake = true;
	truck.wheels[4].steering = false;
	truck.wheels[4].color = Black;

	// REAR-RIGHT ------------------------
	truck.wheels[5].connection.Set(-truck_half_width + 0.3f * truck_wheel_width + truck_wheel_width, truck_connection_height, -truck_half_length * 0.65f + truck_wheel_radius);
	truck.wheels[5].direction = truck_direction;
	truck.wheels[5].axis = truck_axis;
	truck.wheels[5].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[5].radius = truck_wheel_radius;
	truck.wheels[5].width = truck_wheel_width;
	truck.wheels[5].front = false;
	truck.wheels[5].drive = false;
	truck.wheels[5].brake = true;
	truck.wheels[5].steering = false;
	truck.wheels[5].color = Black;



	// BACK-FRONT-MID-LEFT ------------------------
	truck.wheels[6].connection.Set(truck_half_width, truck_connection_height, -truck_half_length * 0.65f + truck_wheel_radius);
	truck.wheels[6].direction = truck_direction;
	truck.wheels[6].axis = truck_axis;
	truck.wheels[6].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[6].radius = truck_wheel_radius;
	truck.wheels[6].width = truck_wheel_width;
	truck.wheels[6].front = false;
	truck.wheels[6].drive = false;
	truck.wheels[6].brake = true;
	truck.wheels[6].steering = false;
	truck.wheels[6].color = Black;

	// BACK-FRONT-MID-RIGHT ------------------------
	truck.wheels[7].connection.Set(-truck_half_width, truck_connection_height, -truck_half_length * 0.65f + truck_wheel_radius);
	truck.wheels[7].direction = truck_direction;
	truck.wheels[7].axis = truck_axis;
	truck.wheels[7].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[7].radius = truck_wheel_radius;
	truck.wheels[7].width = truck_wheel_width;
	truck.wheels[7].front = false;
	truck.wheels[7].drive = false;
	truck.wheels[7].brake = true;
	truck.wheels[7].steering = false;
	truck.wheels[7].color = Black;



	// BACK-BACK-LEFT ------------------------
	truck.wheels[8].connection.Set(truck_half_width - 0.3f * truck_wheel_width - truck_wheel_width, truck_connection_height, -truck_half_length * 0.90f + truck_wheel_radius);
	truck.wheels[8].direction = truck_direction;
	truck.wheels[8].axis = truck_axis;
	truck.wheels[8].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[8].radius = truck_wheel_radius;
	truck.wheels[8].width = truck_wheel_width;
	truck.wheels[8].front = false;
	truck.wheels[8].drive = false;
	truck.wheels[8].brake = true;
	truck.wheels[8].steering = false;
	truck.wheels[8].color = Black;

	// BACK-BACK-RIGHT ------------------------
	truck.wheels[9].connection.Set(-truck_half_width + 0.3f * truck_wheel_width + truck_wheel_width, truck_connection_height, -truck_half_length * 0.90f + truck_wheel_radius);
	truck.wheels[9].direction = truck_direction;
	truck.wheels[9].axis = truck_axis;
	truck.wheels[9].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[9].radius = truck_wheel_radius;
	truck.wheels[9].width = truck_wheel_width;
	truck.wheels[9].front = false;
	truck.wheels[9].drive = false;
	truck.wheels[9].brake = true;
	truck.wheels[9].steering = false;
	truck.wheels[9].color = Black;



	// BACK-BACK-MID-LEFT ------------------------
	truck.wheels[10].connection.Set(truck_half_width, truck_connection_height, -truck_half_length * 0.90f + truck_wheel_radius);
	truck.wheels[10].direction = truck_direction;
	truck.wheels[10].axis = truck_axis;
	truck.wheels[10].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[10].radius = truck_wheel_radius;
	truck.wheels[10].width = truck_wheel_width;
	truck.wheels[10].front = false;
	truck.wheels[10].drive = false;
	truck.wheels[10].brake = true;
	truck.wheels[10].steering = false;
	truck.wheels[10].color = Black;

	// BACK-BACK-MID-RIGHT ------------------------
	truck.wheels[11].connection.Set(-truck_half_width, truck_connection_height, -truck_half_length * 0.90f + truck_wheel_radius);
	truck.wheels[11].direction = truck_direction;
	truck.wheels[11].axis = truck_axis;
	truck.wheels[11].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[11].radius = truck_wheel_radius;
	truck.wheels[11].width = truck_wheel_width;
	truck.wheels[11].front = false;
	truck.wheels[11].drive = false;
	truck.wheels[11].brake = true;
	truck.wheels[11].steering = false;
	truck.wheels[11].color = Black;


	// Trailer properties ----------------------------------------
	trailer.chassis_size.Set(5, 3, 7);
	trailer.chassis_offset.Set(0, 2.25f, 0);
	trailer.mass = 200.0f;
	trailer.suspensionStiffness = 5.80f;
	trailer.suspensionCompression = 0.63f;
	trailer.suspensionDamping = 0.68f;
	trailer.maxSuspensionTravelCm = 800.0f;
	trailer.frictionSlip = 30.5;
	trailer.maxSuspensionForce = 4000.0f;
	trailer.chasisColor = Green;

	// Wheel properties ---------------------------------------
	float trailer_connection_height = 0.8f;
	float trailer_wheel_radius = 1.2f;
	float trailer_wheel_width = 0.5f;
	float trailer_suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float trailer_half_width = trailer.chassis_size.x * 0.5f;
	float trailer_half_length = trailer.chassis_size.z * 0.5f;

	vec3 trailer_direction(0, -1, 0);
	vec3 trailer_axis(-1, 0, 0);

	trailer.num_wheels = 4;
	trailer.wheels = new Wheel[4];
	
	// FRONT-LEFT ------------------------
	trailer.wheels[0].connection.Set(trailer_half_width - 0.3f * trailer_wheel_width, trailer_connection_height, trailer_half_length * 0.95f - trailer_wheel_radius);
	trailer.wheels[0].direction = trailer_direction;
	trailer.wheels[0].axis = trailer_axis;
	trailer.wheels[0].suspensionRestLength = trailer_suspensionRestLength;
	trailer.wheels[0].radius = trailer_wheel_radius;
	trailer.wheels[0].width = trailer_wheel_width;
	trailer.wheels[0].front = true;
	trailer.wheels[0].drive = false;
	trailer.wheels[0].brake = false;
	trailer.wheels[0].steering = false;
	trailer.wheels[0].color = Black;

	// FRONT-RIGHT ------------------------
	trailer.wheels[1].connection.Set(-trailer_half_width + 0.3f * trailer_wheel_width, trailer_connection_height, trailer_half_length * 0.95f - trailer_wheel_radius);
	trailer.wheels[1].direction = trailer_direction;
	trailer.wheels[1].axis = trailer_axis;
	trailer.wheels[1].suspensionRestLength = trailer_suspensionRestLength;
	trailer.wheels[1].radius = trailer_wheel_radius;
	trailer.wheels[1].width = trailer_wheel_width;
	trailer.wheels[1].front = true;
	trailer.wheels[1].drive = false;
	trailer.wheels[1].brake = false;
	trailer.wheels[1].steering = false;
	trailer.wheels[1].color = Black;

	// REAR-LEFT ------------------------
	trailer.wheels[2].connection.Set(trailer_half_width - 0.3f * trailer_wheel_width, trailer_connection_height, -trailer_half_length * 0.95f + trailer_wheel_radius);
	trailer.wheels[2].direction = trailer_direction;
	trailer.wheels[2].axis = trailer_axis;
	trailer.wheels[2].suspensionRestLength = trailer_suspensionRestLength;
	trailer.wheels[2].radius = trailer_wheel_radius;
	trailer.wheels[2].width = trailer_wheel_width;
	trailer.wheels[2].front = false;
	trailer.wheels[2].drive = false;
	trailer.wheels[2].brake = false;
	trailer.wheels[2].steering = false;
	trailer.wheels[2].color = Black;

	// REAR-RIGHT ------------------------
	trailer.wheels[3].connection.Set(-trailer_half_width + 0.3f * trailer_wheel_width, trailer_connection_height, -trailer_half_length * 0.95f + trailer_wheel_radius);
	trailer.wheels[3].direction = trailer_direction;
	trailer.wheels[3].axis = trailer_axis;
	trailer.wheels[3].suspensionRestLength = trailer_suspensionRestLength;
	trailer.wheels[3].radius = trailer_wheel_radius;
	trailer.wheels[3].width = trailer_wheel_width;
	trailer.wheels[3].front = false;
	trailer.wheels[3].drive = false;
	trailer.wheels[3].brake = false;
	trailer.wheels[3].steering = false;
	trailer.wheels[3].color = Black;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 2, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;
	car.chasisColor = White;

	// Wheel properties ---------------------------------------
	float car_connection_height = 1.2f;
	float car_wheel_radius = 0.6f;
	float car_wheel_width = 0.5f;
	float car_suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float car_half_width = car.chassis_size.x*0.5f;
	float car_half_length = car.chassis_size.z*0.5f;

	vec3 car_direction(0, -1, 0);
	vec3 car_axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(car_half_width - 0.3f * car_wheel_width, car_connection_height, car_half_length - car_wheel_radius);
	car.wheels[0].direction = car_direction;
	car.wheels[0].axis = car_axis;
	car.wheels[0].suspensionRestLength = car_suspensionRestLength;
	car.wheels[0].radius = car_wheel_radius;
	car.wheels[0].width = car_wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;
	car.wheels->color = Blue;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-car_half_width + 0.3f * car_wheel_width, car_connection_height, car_half_length - car_wheel_radius);
	car.wheels[1].direction = car_direction;
	car.wheels[1].axis = car_axis;
	car.wheels[1].suspensionRestLength = car_suspensionRestLength;
	car.wheels[1].radius = car_wheel_radius;
	car.wheels[1].width = car_wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(car_half_width - 0.3f * car_wheel_width, car_connection_height, -car_half_length + car_wheel_radius);
	car.wheels[2].direction = car_direction;
	car.wheels[2].axis = car_axis;
	car.wheels[2].suspensionRestLength = car_suspensionRestLength;
	car.wheels[2].radius = car_wheel_radius;
	car.wheels[2].width = car_wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-car_half_width + 0.3f * car_wheel_width, car_connection_height, -car_half_length + car_wheel_radius);
	car.wheels[3].direction = car_direction;
	car.wheels[3].axis = car_axis;
	car.wheels[3].suspensionRestLength = car_suspensionRestLength;
	car.wheels[3].radius = car_wheel_radius;
	car.wheels[3].width = car_wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// MonsterTruck properties ----------------------------------------
	monsterTruck.chassis_size.Set(6, 5, 7);
	monsterTruck.chassis_offset.Set(0, 4.5, 0);
	monsterTruck.mass = 1500.0f;
	monsterTruck.suspensionStiffness = 15.88f;
	monsterTruck.suspensionCompression = 0.83f;
	monsterTruck.suspensionDamping = 0.88f;
	monsterTruck.maxSuspensionTravelCm = 1000.0f;
	monsterTruck.frictionSlip = 50.5;
	monsterTruck.maxSuspensionForce = 6000.0f;
	monsterTruck.chasisColor = Red;

	// Wheel properties ---------------------------------------
	float monsterTruck_connection_height = 3.2f;
	float monsterTruck_wheel_radius = 3.5f;
	float monsterTruck_wheel_width = 3.5f;
	float monsterTruck_suspensionRestLength = 3.5f;

	// Don't change anything below this line ------------------

	float monsterTruck_half_width = monsterTruck.chassis_size.x*0.5f;
	float monsterTruck_half_length = monsterTruck.chassis_size.z*0.5f;

	vec3 monsterTruck_direction(0, -1, 0);
	vec3 monsterTruck_axis(-1, 0, 0);

	monsterTruck.num_wheels = 4;
	monsterTruck.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	monsterTruck.wheels[0].connection.Set(monsterTruck_half_width + 0.1f * monsterTruck_wheel_width, monsterTruck_connection_height, monsterTruck_half_length + monsterTruck_wheel_radius * 0.2f);
	monsterTruck.wheels[0].direction = monsterTruck_direction;
	monsterTruck.wheels[0].axis = monsterTruck_axis;
	monsterTruck.wheels[0].suspensionRestLength = monsterTruck_suspensionRestLength;
	monsterTruck.wheels[0].radius = monsterTruck_wheel_radius;
	monsterTruck.wheels[0].width = monsterTruck_wheel_width;
	monsterTruck.wheels[0].front = true;
	monsterTruck.wheels[0].drive = true;
	monsterTruck.wheels[0].brake = true;
	monsterTruck.wheels[0].steering = true;
	monsterTruck.wheels->color = Black;

	// FRONT-RIGHT ------------------------
	monsterTruck.wheels[1].connection.Set(-monsterTruck_half_width - 0.1f * monsterTruck_wheel_width, monsterTruck_connection_height, monsterTruck_half_length + monsterTruck_wheel_radius * 0.2f);
	monsterTruck.wheels[1].direction = monsterTruck_direction;
	monsterTruck.wheels[1].axis = monsterTruck_axis;
	monsterTruck.wheels[1].suspensionRestLength = monsterTruck_suspensionRestLength;
	monsterTruck.wheels[1].radius = monsterTruck_wheel_radius;
	monsterTruck.wheels[1].width = monsterTruck_wheel_width;
	monsterTruck.wheels[1].front = true;
	monsterTruck.wheels[1].drive = true;
	monsterTruck.wheels[1].brake = true;
	monsterTruck.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	monsterTruck.wheels[2].connection.Set(monsterTruck_half_width + 0.1f * monsterTruck_wheel_width, monsterTruck_connection_height, -monsterTruck_half_length - monsterTruck_wheel_radius * 0.2);
	monsterTruck.wheels[2].direction = monsterTruck_direction;
	monsterTruck.wheels[2].axis = monsterTruck_axis;
	monsterTruck.wheels[2].suspensionRestLength = monsterTruck_suspensionRestLength;
	monsterTruck.wheels[2].radius = monsterTruck_wheel_radius;
	monsterTruck.wheels[2].width = monsterTruck_wheel_width;
	monsterTruck.wheels[2].front = false;
	monsterTruck.wheels[2].drive = true;
	monsterTruck.wheels[2].brake = true;
	monsterTruck.wheels[2].steeringOposite = true;

	// REAR-RIGHT ------------------------
	monsterTruck.wheels[3].connection.Set(-monsterTruck_half_width - 0.1f * monsterTruck_wheel_width, monsterTruck_connection_height, -monsterTruck_half_length - monsterTruck_wheel_radius * 0.2);
	monsterTruck.wheels[3].direction = monsterTruck_direction;
	monsterTruck.wheels[3].axis = monsterTruck_axis;
	monsterTruck.wheels[3].suspensionRestLength = monsterTruck_suspensionRestLength;
	monsterTruck.wheels[3].radius = monsterTruck_wheel_radius;
	monsterTruck.wheels[3].width = monsterTruck_wheel_width;
	monsterTruck.wheels[3].front = false;
	monsterTruck.wheels[3].drive = true;
	monsterTruck.wheels[3].brake = true;
	monsterTruck.wheels[3].steeringOposite = true;




	vehicleSelected = false;
	trailerAdded = false;

	//timer
	timer.Stop();
	timerOn = false;


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{

	//CAMERA --------------------------------------------------------------------
	{
		// camera set on the beggining of the course, not set on vehicle
		if (!vehicleSelected) following_camera = false;

		// vehicle selected, camera set on vehicle
		else {

			// selected vehicle, following vehicle from now on 
			following_camera = true;

			//------------------- CAR, vehicleSelectedNum == 0 -------------------//
			//vec3 p = vehicle->GetPos();
			//vec3 f = vehicle->GetForwardVector();
			//// setting camera on vehicle
			//float speed_cam = 0.05f;
			//vec3 dist_to_car = { -8.0f, 2.0f, -8.0f };
			//vec3 new_camera_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
			//vec3 camera_disp_vec = new_camera_position - App->camera->Position;
			//App->camera->Look(App->camera->Position + (speed_cam * camera_disp_vec), p);

			//------------------- BUS, vehicleSelectedNum == 1 -------------------//
			if (vehicleSelectedNum == 1) {
				vec3 p = Bus->GetPos();
				vec3 f = Bus->GetForwardVector();
				// setting camera on vehicle
				float speed_cam = 0.05f;
				dist_to_car = { -60.0f, 35.0f, -60.0f };
				vec3 new_camera_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
				vec3 camera_disp_vec = new_camera_position - App->camera->Position;
				App->camera->Look(App->camera->Position + (speed_cam * camera_disp_vec), p);
			}
			//------------------- TRUCK SIMPLE, vehicleSelectedNum == 2 -------------------//
			if (vehicleSelectedNum == 2) {
				vec3 p = Truck->GetPos();
				vec3 f = Truck->GetForwardVector();
				// setting camera on vehicle
				float speed_cam = 0.05f;
				if (trailerAdded) dist_to_car = { -85.0f, 45.0f, -85.0f };
				else dist_to_car = { -75.0f, 40.0f, -75.0f };
				vec3 new_camera_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
				vec3 camera_disp_vec = new_camera_position - App->camera->Position;
				App->camera->Look(App->camera->Position + (speed_cam * camera_disp_vec), p);
			}
			//------------------- TRUCK + TRAILER, vehicleSelectedNum == 3 -------------------//
			//vec3 p = vehicle->GetPos();
			//vec3 f = vehicle->GetForwardVector();
			//// setting camera on vehicle
			//float speed_cam = 0.05f;
			//vec3 dist_to_car = { -8.0f, 2.0f, -8.0f };
			//vec3 new_camera_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
			//vec3 camera_disp_vec = new_camera_position - App->camera->Position;
			//App->camera->Look(App->camera->Position + (speed_cam * camera_disp_vec), p);
		}

		// following vehicle
		if (following_camera)
		{

			//------------------- CAR, vehicleSelectedNum == 0 -------------------//
			//float speed_cam = 0.09;
			//vec3 p = vehicle->GetPos();
			//vec3 f = vehicle->GetForwardVector();
			//vec3 dist_to_car = { -8.0f, 5.0f, -8.0f };
			//vec3 camera_new_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
			//vec3 speed_camera = camera_new_position - App->camera->Position;

			//App->camera->Look(App->camera->Position + (speed_cam * speed_camera), p);

			//------------------- BUS, vehicleSelectedNum == 1 -------------------//
			if (vehicleSelectedNum == 1) {
				float speed_cam = 0.09;
				vec3 p = Bus->GetPos();
				vec3 f = Bus->GetForwardVector();
				dist_to_car = { -8.0f, 5.0f, -8.0f };
				vec3 camera_new_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
				vec3 speed_camera = camera_new_position - App->camera->Position;
				App->camera->Look(App->camera->Position + (speed_cam * speed_camera), p);
			}
			//------------------- TRUCK SIMPLE, vehicleSelectedNum == 2 -------------------//
			if (vehicleSelectedNum == 2) {
				float speed_cam = 0.09;
				vec3 p = Truck->GetPos();
				vec3 f = Truck->GetForwardVector();
				dist_to_car = { -8.0f, 5.0f, -8.0f };
				vec3 camera_new_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
				vec3 speed_camera = camera_new_position - App->camera->Position;

				App->camera->Look(App->camera->Position + (speed_cam * speed_camera), p);
			}
			//------------------- TRUCK + TRAILER, vehicleSelectedNum == 3 -------------------//
			//float speed_cam = 0.09;
			//vec3 p = vehicle->GetPos();
			//vec3 f = vehicle->GetForwardVector();
			//vec3 dist_to_car = { -8.0f, 5.0f, -8.0f };
			//vec3 camera_new_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
			//vec3 speed_camera = camera_new_position - App->camera->Position;

			//App->camera->Look(App->camera->Position + (speed_cam * speed_camera), p);
		}

		// Activate/deactivate camera on car.
		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		{
			following_camera = !following_camera;
		}
	}
	//CAMERA END --------------------------------------------------------------------

	//MUSIC -------------------------------------------------------------------------

	//if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	//{
	//	App->audio->PlayFx(App->audio->accelerateFx);
	//}

	//MUSIC END ---------------------------------------------------------------------ç


	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN && vehicleSelectedNum == 0 && !trailerAdded) { // TRAILER TO CAR
		Trailer = App->physics->AddVehicle(trailer);
		Trailer->SetPos(-72.5, 2, -15);
		App->physics->AddConstraintP2P(*Car, *Trailer, { 0, 0, 0 }, { 0, 0, 10.0f });
		trailerAdded = true;
	}

	 else if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN && vehicleSelectedNum == 1 && !trailerAdded) { // TRAILER TO BUS
		 Trailer = App->physics->AddVehicle(trailer);
		 Trailer->SetPos(-72.5, 2, -20);
		 App->physics->AddConstraintP2P(*Bus, *Trailer, { 0, 0, 0 }, { 0, 0, 12.5f });
		 trailerAdded = true;
	 }

	else if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN && vehicleSelectedNum == 2 && !trailerAdded) { // TRAILER TO TRUCK
		 Trailer = App->physics->AddVehicle(trailer);
		 Trailer->SetPos(-72.5, 2, -25);
		 App->physics->AddConstraintP2P(*Truck, *Trailer, { 0, 0, 0 }, { 0, 0, 17.5f });
		 trailerAdded = true;
	 }

	
	if (!vehicleSelected) {
		if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
			Car = App->physics->AddVehicle(car);
			Car->SetPos(-72.5, 1, -5);
			vehicleSelected = true;
			vehicleSelectedNum = 0;
		}
		else if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) { //BUS
			Bus = App->physics->AddVehicle(bus);
			Bus->SetPos(-72.5, 2, -5);
			vehicleSelected = true;
			vehicleSelectedNum = 1;
		}
		else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) { //
			Truck = App->physics->AddVehicle(truck);
			Truck->SetPos(-72.5, 1, -5);
			vehicleSelected = true;
			vehicleSelectedNum = 2;
		}
		else if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
			MonsterTruck = App->physics->AddVehicle(monsterTruck);
			MonsterTruck->SetPos(-72.5, 1, -5);
			vehicleSelected = true;
			vehicleSelectedNum = 3;
		}
	}

	else if (vehicleSelectedNum == 0) {	// CAR
		turn = acceleration = brake = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)	
			if (Car->GetKmh() < MAX_SPEED) acceleration = MAX_ACCELERATION;

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			if (Car->GetKmh() > 3) brake = BRAKE_POWER;
			else {
				if (Car->GetKmh() > MIN_SPEED)
					acceleration = -BRAKE_POWER;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
			acceleration *= 4;
		}

		Car->ApplyEngineForce(acceleration);
		Car->Turn(turn);
		Car->Brake(brake);
		Car->Render();

		char title[80];
		sprintf_s(title, "%.1f Km/h", Car->GetKmh());
		App->window->SetTitle(title);
	}

	else if (vehicleSelectedNum == 1) {	//BUS
		turn = acceleration = brake = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
				if (Bus->GetKmh() < MAX_SPEED)
					acceleration = MAX_ACCELERATION / 2.5f;
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			if (Bus->GetKmh() > 3) brake = BRAKE_POWER / 3;
			else {
				if (Bus->GetKmh() > MIN_SPEED / 3)
					acceleration = -BRAKE_POWER / 3;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			if (turn < TURN_DEGREES * 0.8)
				turn += TURN_DEGREES * 0.8;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			if (turn > -TURN_DEGREES * 0.8)
				turn -= TURN_DEGREES * 0.8;
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
			acceleration *= 4;
		}

		Bus->ApplyEngineForce(acceleration);
		Bus->Turn(turn);
		Bus->Brake(brake);
		Bus->Render();

		char title[80];
		sprintf_s(title, "%.1f Km/h", Bus->GetKmh());

		App->window->SetTitle(title);
	}


	else if (vehicleSelectedNum == 2) {	//TRUCK
		turn = acceleration = brake = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
			if (Truck->GetKmh() < MAX_SPEED)
			acceleration = MAX_ACCELERATION;
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			if (Truck->GetKmh() > 3) brake = BRAKE_POWER / 5;
			else {
				if (Truck->GetKmh() > MIN_SPEED)
					acceleration = -BRAKE_POWER / 3;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			if (turn < TURN_DEGREES * 2.5) {
				turn += TURN_DEGREES * 2.5;
				acceleration *= 9;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			if (turn > -TURN_DEGREES * 2.5) {
				turn -= TURN_DEGREES * 2.5;
				acceleration *= 9;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
			acceleration *= 4;
		}
		Truck->ApplyEngineForce(acceleration);
		Truck->Turn(turn);
		Truck->Brake(brake);
		Truck->Render();
		if (trailerAdded) Trailer->Render();

		char title[80];
		sprintf_s(title, "%.1f Km/h", Truck->GetKmh());

		App->window->SetTitle(title);
	}

	else if (vehicleSelectedNum == 3) {	// MONSTER TRUCK
		turn = acceleration = brake = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
			if (MonsterTruck->GetKmh() < MAX_SPEED)
				acceleration = MAX_ACCELERATION;
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			if (MonsterTruck->GetKmh() > 3) brake = BRAKE_POWER;
			else {
				if (MonsterTruck->GetKmh() > MIN_SPEED)
					acceleration = -BRAKE_POWER;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			if (turn < TURN_DEGREES) {
				turn += TURN_DEGREES;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			if (turn > -TURN_DEGREES) {
				turn -= TURN_DEGREES;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
			acceleration *= 4;
		}
		MonsterTruck->ApplyEngineForce(acceleration);
		MonsterTruck->Turn(turn);
		MonsterTruck->Brake(brake);
		MonsterTruck->Render();
		if (trailerAdded) Trailer->Render();

		char title[80];
		sprintf_s(title, "%.1f Km/h", MonsterTruck->GetKmh());

		App->window->SetTitle(title);
	}
	return UPDATE_CONTINUE;
}
