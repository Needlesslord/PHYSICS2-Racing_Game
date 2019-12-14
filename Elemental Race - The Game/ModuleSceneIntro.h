#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

//NUR
struct cubePieces
{
	p2DynArray<PhysBody3D*>		phys_bodies;
	p2DynArray<Cube>			prim_bodies;
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
	Cube CreateObject_BorderCourse(float posX, float posY, float posZ, int num_colour);
	uint size;
	uint numCourse;
	bool CreateCourse(float list[], uint size, uint courseNum);
	Cube* Course[400];//MIGHT NEED TO BE BIGGER

	////NUR
	//void createRamp(const vec3 i, const vec3 f);
	//cubePieces cube_circuit_pieces;
	//void angleAndAxisFromRotMat(mat4x4 m, float &angle, vec3 &axis);

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
