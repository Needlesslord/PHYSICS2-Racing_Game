#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

struct cubePieces
{
	p2DynArray<PhysBody3D*>		phys_bodies;
	p2DynArray<Cube>			prim_bodies;
};

enum Steps {
	SelectVehicle,
	LockVehicle,
	Running,
	GameOver
};
class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	uint course_index = 0;
	Cube CreateObject_BorderCourse(float posX, float posY, float posZ);
	uint Mario_size;
	bool CreateCourse(float list[], uint size);
	Cube* Course[440]; //MIGHT NEED TO BE BIGGER

	void AddCheckpoint(float posX, float posY, float posZ);
	bool CreateCheckpoints(float list[], uint size);
	uint checkpoint_index = 0;
	bool checkpointActivated[4] = { false,false,false,false };
	uint checkpoints_list_size;
	p2DynArray<PhysBody3D*>		Checkpoints;

	//to add all the obstacles
	void AddObstacles(int zone);
	void AddBridge();

	Cube* up;
	Cube* flat;
	Cube* down;
	void AddPerson(float posX, float posY, float posZ, int ethnicity);
	Cube AddHead(int ethnicity);
	Cube AddBody(int shirt);
	Cube* water_lake;
	PhysBody3D* start_line;
	Cube* start_line_cube;
	PhysBody3D* mid_line;
	Cube* mid_line_cube;
	bool startActivated;
	bool midActivated;
	uint lap;

	Cube* left_1;
	Cube* top_1;
	Cube* right_1;
	Cube* left_2;
	Cube* top_2;
	Cube* right_2;
	Cube* left_3;
	Cube* top_3;
	Cube* right_3;
	Cube* left_4;
	Cube* top_4;
	Cube* right_4;

	void AddFireArch();
	
	Steps currentStep;
public:
	//obstacles list
	int num_trees;
	int num_rocks;
	int num_fire_archs;
	int num_fireballs;
	int num_people;

};
