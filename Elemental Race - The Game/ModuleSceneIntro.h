#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

//do we use this??? ------------
struct cubePieces
{
	p2DynArray<PhysBody3D*>		phys_bodies;
	p2DynArray<Cube>			prim_bodies;
};
//do we use this??? ------------

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
	void AddPerson(float posX, float posY, float posZ, int ethnicity);
	Cube AddHead(int ethnicity);
	Cube AddBody(int shirt);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	//obstacles list
	int num_trees;
	int num_rocks;
	int num_fire_archs;
	int num_fireballs;
	int num_people;

};
