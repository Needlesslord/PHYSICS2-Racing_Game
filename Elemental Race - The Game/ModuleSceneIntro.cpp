#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "DataForTheCourses.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	
	Mario_size = 1248;
	CreateCourse(Mario, Mario_size);

	checkpoints_list_size = 12;
	
	//add bridge
	AddBridge();
	//add fire archs
	AddFireArch();
	//add bushes
	AddBush();
	//add lake
	AddObstacles(4);
	//adding start line
	AddObstacles(0);
	currentStep = SelectVehicle;

	midActivated = true;
	startActivated = false;
	lap = 1;

	return true;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	for (uint i = 0; i < course_index; i++) {
		delete Course[i];
	}
	AddBridge();
	AddFireArch();
	AddBush();
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	for (uint i = 0; i < course_index; i++) {
		Course[i]->Render();
	}
	
	//bridge
	up->Render();
	down->Render();
	flat->Render();
	//lake
	water_lake->Render();
	start_line_cube->Render();
	//fire archs
	left_1->Render();
	top_1->Render();
	right_1->Render();
	left_2->Render();
	top_2->Render();
	right_2->Render();
	left_3->Render();
	top_3->Render();
	right_3->Render();
	left_4->Render();
	top_4->Render();
	right_4->Render();
	//bushes
	bush_1->Render();
	bush_2->Render();
	bush_3->Render();
	bush_4->Render();
	bush_5->Render();
	bush_6->Render();
	bush_7->Render();
	bush_8->Render();
	bush_9->Render();
	bush_10->Render();
	bush_11->Render();
	bush_12->Render();
	bush_13->Render();
	bush_14->Render();
	bush_15->Render();

	return UPDATE_CONTINUE;
}

Cube ModuleSceneIntro::CreateObject_BorderCourse(float posX, float posY, float posZ) {
	float mass = 0;
	float sizeX = 3;
	float sizeY = 3;
	float sizeZ = 3;
	Course[course_index] = new Cube(sizeX, sizeY, sizeZ);
	Course[course_index]->SetPos(posX, posY + sizeY / 2, posZ);
	App->physics->AddBody(*Course[course_index], this, mass);
	Course[course_index]->color = Blue2_T;
	
	course_index++;
	return *Course[course_index - 1];
}

bool ModuleSceneIntro::CreateCourse(float list[], uint size) {
	for (int i = 0; i < size; i += 3) {
		float x = list[i] * 300;
		float y = list[i + 1] * 300;
		float z = list[i + 2] * 300 - 75;
		CreateObject_BorderCourse(x, y, z);
	}
	
	return true;
}

void ModuleSceneIntro::AddCheckpoint(float posX, float posY, float posZ) {
	float sizeX = 5;
	float sizeY = 5;
	float sizeZ = 5;
	Cube checkpoint_cube(sizeX, sizeY, sizeZ);
	checkpoint_cube.SetPos(posX, posY + sizeY / 2, posZ);
	PhysBody3D*	Checkpoint = App->physics->AddBody(checkpoint_cube, this, 0.0f, false);
	Checkpoints.PushBack(Checkpoint);
}

bool ModuleSceneIntro::CreateCheckpoints(float list[], uint size) {
	for (int i = 0; i < size; i += 3) {
		float x = list[i];
		float y = list[i + 1];
		float z = list[i + 2];
		AddCheckpoint(x, y, z);
	}
	return true;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2) {
	
}

void ModuleSceneIntro::AddBridge() {

	// up and down are actually swapped

	//offsets
	float offset_X = -244;
	float offset_Y = 0;
	float offset_Z = 24.15;
	// size of the bridge/mountain
	//up
	float size_X_up = 43;
	float size_Y_up = 1;
	float size_Z_up = 23;
	//flat
	float size_X_flat = 25;
	float size_Y_flat = 1;
	float size_Z_flat = 23;
	//down
	float size_X_down = 55; 
	float size_Y_down = 1;
	float size_Z_down = 23;
	// position of the bridge/mountain
	//up
	float pos_X_up = 347.5 + offset_X + 10.85;
	float pos_Y_up = 6.25;
	float pos_Z_up = 67.5 + offset_Z;
	//flat
	float pos_X_flat = 325 + offset_X;
	float pos_Y_flat = 13.25;
	float pos_Z_flat = 67.5 + offset_Z;
	//down
	float pos_X_down = 302.5 + offset_X - 17;
	float pos_Y_down = 6.25;
	float pos_Z_down = 67.5 + offset_Z;
	// rotation of the bridge/mountain
	//angle
	float angle_up = -20;
	float angle_flat = 0;
	float angle_down = 15;
	//up
	float rot_X_up = 0;
	float rot_Y_up = 0;
	float rot_Z_up = 1;
	//flat
	float rot_X_flat = 0;
	float rot_Y_flat = 1;
	float rot_Z_flat = 0;
	//down
	float rot_X_down = 0;
	float rot_Y_down = 0;
	float rot_Z_down = 1;

	//add cube, set the size
	up = new Cube		(		size_X_up,		size_Y_up,		size_Z_up		);
	flat = new Cube	(		size_X_flat,	size_Y_flat,	size_Z_flat		);
	down = new Cube	(		size_X_down,	size_Y_down,	size_Z_down		);
	//add location
	up->SetPos(			pos_X_up,		pos_Y_up,		pos_Z_up		);
	flat->SetPos(		pos_X_flat,		pos_Y_flat,		pos_Z_flat		);
	down->SetPos(		pos_X_down,		pos_Y_down,		pos_Z_down		);
	//add rotation
	up->SetRotation(		angle_up,	{	rot_X_up,		rot_Y_up,		rot_Z_up	});
	flat->SetRotation(		angle_flat, {	rot_X_flat,		rot_Y_flat,		rot_Z_flat	});
	down->SetRotation(		angle_down, {	rot_X_down,		rot_Y_down,		rot_Z_down	});
	//colouring
	up->color = Brown_T;
	flat->color = Brown_T;
	down->color = Brown_T;
	//add body
	App->physics->AddBody(*(up), this, 0.0f);
	App->physics->AddBody(*(flat), this, 0.0f);
	App->physics->AddBody(*(down), this, 0.0f);

}

void ModuleSceneIntro::AddObstacles(int zone) {

	num_trees = 10 + 11 + 10;
	num_rocks = 12;
	num_fire_archs = 2;
	num_fireballs = 6;
	num_people = 9;

	//zone 1 is spirit
	if (zone == 1) {
		for (int i = 0; i < num_people; i += 3) {
			//size of the people
		}
	}
	//zone 2 is fire
	else if (zone == 2) {
		for (int i = 0; i < num_fireballs; i += 3) {}
	}
	//zone 3 is earth
	else if (zone == 3) {
		for (int i = 0; i < num_rocks; i += 3) {}
	}
	//zone 4 is water
	else if (zone == 4) {
		// size of the bridge/mountain
		float size_X_water_lake = 130;
		float size_Y_water_lake = 0.5;
		float size_Z_water_lake = 150;
		// position of the bridge/mountain
		float pos_X_water_lake = -58;
		float pos_Y_water_lake = -0.5;
		float pos_Z_water_lake = 145;
		//add cube, set the size
		water_lake = new Cube(size_X_water_lake, size_Y_water_lake, size_Z_water_lake);
		//add location
		water_lake->SetPos(pos_X_water_lake, pos_Y_water_lake, pos_Z_water_lake);
		//colouring
		water_lake->color = Blue;
		//add body
		App->physics->AddBody(*(water_lake), this, 0.0f);

	}
	//zone 5 is air
	else if (zone == 5) {}
	//zone 6 is forest
	else if (zone == 6) {
		for (int i = 0; i < num_trees; i += 3) {
			//size of the trees
			float sizeLeaves_X = 2;
			float sizeLeaves_Y = 8;
			float sizeLeaves_Z = 2;
			float sizeLog_X = 1;
			float sizeLog_Y = 1;
			float sizeLog_Z = 1;
		}
	}
	//else is going to be used to create fire archs and start line
	else if (zone == 100) {
		float size_X_mid_line = 50;
		float size_Y_mid_line = 0.1;
		float size_Z_mid_line = 5;
		float  pos_X_mid_line = 173.75;
		float  pos_Y_mid_line = -0.01;
		float  pos_Z_mid_line = 10;
		mid_line_cube = new Cube(size_X_mid_line, size_Y_mid_line, size_Z_mid_line);
		mid_line_cube->SetPos(pos_X_mid_line, pos_Y_mid_line, pos_Z_mid_line);
		mid_line_cube->color = White;
		mid_line = App->physics->AddBody(*(mid_line_cube), this, 0.0f, false);
	}
	else {
		//start line
		// size of the start line
		float size_X_start_line = 50;
		float size_Y_start_line = 0.1;
		float size_Z_start_line = 5;
		// position of the bridge/mountain
		float pos_X_start_line = -73.75;
		float pos_Y_start_line = -0.01;
		float pos_Z_start_line = 10;
		//add cube, set the size
		start_line_cube = new Cube(size_X_start_line, size_Y_start_line, size_Z_start_line);
		//add location
		start_line_cube->SetPos(pos_X_start_line, pos_Y_start_line, pos_Z_start_line);
		//colouring
		start_line_cube->color = White;
		//add body
		start_line = App->physics->AddBody(*(start_line_cube), this, 0.0f, false);
	}

}

void ModuleSceneIntro::AddPerson(float posX, float posY, float posZ, int ethnicity) {

}

Cube ModuleSceneIntro::AddHead(int ethnicity){
	//size of the person's head
	float sizeHead_X = 0.5;
	float sizeHead_Y = 0.5;
	float sizeHead_Z = 0.5;
	Cube* Head = new Cube(sizeHead_X, sizeHead_Y, sizeHead_Z);

	App->physics->AddBody(*(Head), this, 0.0f);

	if (ethnicity == 1) Head->color = Skin2_T;
	else Head->color = Skin_T;

	return Cube{ 1,1,1 };

}

Cube ModuleSceneIntro::AddBody(int shirt){
	//size of the person's body
	float sizeBody_X = 1;
	float sizeBody_Y = 5;
	float sizeBody_Z = 1;
	Cube* Body = new Cube(sizeBody_X, sizeBody_Y, sizeBody_Z);
	
	App->physics->AddBody(*(Body), this, 0.0f);

	if (shirt == 1) Body->color = Red_T;
	else if (shirt == 2) Body->color = Yellow_T;
	else if (shirt == 3) Body->color = Green_T;
	else if (shirt == 4) Body->color = Blue2_T;
	else if (shirt == 5) Body->color = Black_T;
	else if (shirt == 6) Body->color = White_T;
	else Body->color = Blue2_T;

	return Cube{ 1,1,1 };
}

void ModuleSceneIntro::AddFireArch() {

	// size of the arch 
	//left
	float size_X_left = 2.5;
	float size_Y_left = 15;
	float size_Z_left = 2.5;
	//top
	float size_X_top = 2.5;
	float size_Y_top = 2.5;
	float size_Z_top = 30;
	//right
	float size_X_right = 2.5;
	float size_Y_right = 15;
	float size_Z_right = 2.5;
	// position of the arch 1
	//left
	float pos_X_left = 40;
	float pos_Y_left = 7.5;
	float pos_Z_left = 20;
	//top
	float pos_X_top = 40;
	float pos_Y_top = 18;
	float pos_Z_top = 30;
	//right
	float pos_X_right = 40;
	float pos_Y_right = 7.5;
	float pos_Z_right = 40;

	//add cube, set the size
	left_1 = new Cube(size_X_left, size_Y_left, size_Z_left);
	top_1 = new Cube(size_X_top, size_Y_top, size_Z_top);
	right_1 = new Cube(size_X_right, size_Y_right, size_Z_right);
	//add location
	left_1->SetPos(pos_X_left, pos_Y_left, pos_Z_left);
	top_1->SetPos(pos_X_top, pos_Y_top, pos_Z_top);
	right_1->SetPos(pos_X_right, pos_Y_right, pos_Z_right);
	//colouring
	left_1->color = Red;
	top_1->color = Red;
	right_1->color = Red;
	//add body
	App->physics->AddBody(*(left_1), this, 0.0f);
	App->physics->AddBody(*(top_1), this, 0.0f);
	App->physics->AddBody(*(right_1), this, 0.0f);

	// position of the arch 2
	//left
	pos_X_left = 15;
	pos_Y_left = 7.5;
	pos_Z_left = 30;
	//top
	pos_X_top = 15;
	pos_Y_top = 18;
	pos_Z_top = 40;
	//right
	pos_X_right = 15;
	pos_Y_right = 7.5;
	pos_Z_right = 50;

	//add cube, set the size
	left_2 = new Cube(size_X_left, size_Y_left, size_Z_left);
	top_2 = new Cube(size_X_top, size_Y_top, size_Z_top);
	right_2 = new Cube(size_X_right, size_Y_right, size_Z_right);
	//add location
	left_2->SetPos(pos_X_left, pos_Y_left, pos_Z_left);
	top_2->SetPos(pos_X_top, pos_Y_top, pos_Z_top);
	right_2->SetPos(pos_X_right, pos_Y_right, pos_Z_right);
	//colouring
	left_2->color = Red;
	top_2->color = Red;
	right_2->color = Red;
	//add body
	App->physics->AddBody(*(left_2), this, 0.0f);
	App->physics->AddBody(*(top_2), this, 0.0f);
	App->physics->AddBody(*(right_2), this, 0.0f);

	// position of the arch 3
	//left
	pos_X_left = -10;
	pos_Y_left = 7.5;
	pos_Z_left = 40;
	//top
	pos_X_top = -10;
	pos_Y_top = 18;
	pos_Z_top = 50;
	//right
	pos_X_right = -10;
	pos_Y_right = 7.5;
	pos_Z_right = 60;

	//add cube, set the size
	left_3 = new Cube(size_X_left, size_Y_left, size_Z_left);
	top_3 = new Cube(size_X_top, size_Y_top, size_Z_top);
	right_3 = new Cube(size_X_right, size_Y_right, size_Z_right);
	//add location
	left_3->SetPos(pos_X_left, pos_Y_left, pos_Z_left);
	top_3->SetPos(pos_X_top, pos_Y_top, pos_Z_top);
	right_3->SetPos(pos_X_right, pos_Y_right, pos_Z_right);
	//colouring
	left_3->color = Red;
	top_3->color = Red;
	right_3->color = Red;
	//add body
	App->physics->AddBody(*(left_3), this, 0.0f);
	App->physics->AddBody(*(top_3), this, 0.0f);
	App->physics->AddBody(*(right_3), this, 0.0f);

	// position of the arch 4
	//left
	pos_X_left = -35;
	pos_Y_left = 7.5;
	pos_Z_left = 40;
	//top
	pos_X_top = -35;
	pos_Y_top = 18;
	pos_Z_top = 50;
	//right
	pos_X_right = -35;
	pos_Y_right = 7.5;
	pos_Z_right = 60;

	//add cube, set the size
	left_4 = new Cube(size_X_left, size_Y_left, size_Z_left);
	top_4 = new Cube(size_X_top, size_Y_top, size_Z_top);
	right_4 = new Cube(size_X_right, size_Y_right, size_Z_right);
	//add location
	left_4->SetPos(pos_X_left, pos_Y_left, pos_Z_left);
	top_4->SetPos(pos_X_top, pos_Y_top, pos_Z_top);
	right_4->SetPos(pos_X_right, pos_Y_right, pos_Z_right);
	//colouring
	left_4->color = Red;
	top_4->color = Red;
	right_4->color = Red;
	//add body
	App->physics->AddBody(*(left_4), this, 0.0f);
	App->physics->AddBody(*(top_4), this, 0.0f);
	App->physics->AddBody(*(right_4), this, 0.0f);

}

void ModuleSceneIntro::AddBush() {

	// size of the bush 
	float size_X = 1.5;
	float size_Y = 2;
	float size_Z = 1.5;

	// position of the bush 1
	float pos_X = -25;
	float pos_Y = 1;
	float pos_Z = -65;
	//add cube, set the size
	bush_1 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_1->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_1->color = Green2_T;
	//add body
	App->physics->AddBody(*(bush_1), this, 0.0f);

	// position of the bush 2
	pos_X = -13;
	pos_Y = 1;
	pos_Z = -80;
	//add cube, set the size
	bush_2 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_2->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_2->color = Green;
	//add body
	App->physics->AddBody(*(bush_2), this, 0.0f);

	// position of the bush 3
	pos_X = 35;
	pos_Y = 1;
	pos_Z = -65;
	//add cube, set the size
	bush_3 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_3->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_3->color = Green;
	//add body
	App->physics->AddBody(*(bush_3), this, 0.0f);

	// position of the bush 4
	pos_X = 25;
	pos_Y = 1;
	pos_Z = -75;
	//add cube, set the size
	bush_4 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_4->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_4->color = Green;
	//add body
	App->physics->AddBody(*(bush_4), this, 0.0f);

	// position of the bush 5
	pos_X = 0;
	pos_Y = 1;
	pos_Z = -75;
	//add cube, set the size
	bush_5 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_5->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_5->color = Green2_T;
	//add body
	App->physics->AddBody(*(bush_5), this, 0.0f);

	// position of the bush 6
	pos_X = 50;
	pos_Y = 1;
	pos_Z = -80;
	//add cube, set the size
	bush_6 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_6->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_6->color = Green2_T;
	//add body
	App->physics->AddBody(*(bush_6), this, 0.0f);

	// position of the bush 7
	pos_X = 45;
	pos_Y = 1;
	pos_Z = -80;
	//add cube, set the size
	bush_7 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_7->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_7->color = Green;
	//add body
	App->physics->AddBody(*(bush_7), this, 0.0f);

	// position of the bush 8
	pos_X = -45;
	pos_Y = 1;
	pos_Z = -80;
	//add cube, set the size
	bush_8 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_8->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_8->color = Green2_T;
	//add body
	App->physics->AddBody(*(bush_8), this, 0.0f);

	// position of the bush 9
	pos_X = -40;
	pos_Y = 1;
	pos_Z = -60;
	//add cube, set the size
	bush_9 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_9->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_9->color = Green;
	//add body
	App->physics->AddBody(*(bush_9), this, 0.0f);

	//outside the road
	// position of the bush 10
	pos_X = -80;
	pos_Y = 1;
	pos_Z = -50;
	//add cube, set the size
	bush_10 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_10->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_10->color = Green;
	//add body
	App->physics->AddBody(*(bush_10), this, 0.0f);

	// position of the bush 11
	pos_X = -90;
	pos_Y = 1;
	pos_Z = -40;
	//add cube, set the size
	bush_11 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_11->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_11->color = Green2_T;
	//add body
	App->physics->AddBody(*(bush_11), this, 0.0f);

	// position of the bush 12
	pos_X = -30;
	pos_Y = 1;
	pos_Z = -90;
	//add cube, set the size
	bush_12 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_12->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_12->color = Green;
	//add body
	App->physics->AddBody(*(bush_12), this, 0.0f);

	// position of the bush 13
	pos_X = -60;
	pos_Y = 1;
	pos_Z = -100;
	//add cube, set the size
	bush_13 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_13->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_13->color = Green;
	//add body
	App->physics->AddBody(*(bush_13), this, 0.0f);

	// position of the bush 14
	pos_X = -40;
	pos_Y = 1;
	pos_Z = -50;
	//add cube, set the size
	bush_14 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_14->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_14->color = Green2_T;
	//add body
	App->physics->AddBody(*(bush_14), this, 0.0f);

	// position of the bush 15
	pos_X = -50;
	pos_Y = 1;
	pos_Z = -110;
	//add cube, set the size
	bush_15 = new Cube(size_X, size_Y, size_Z);
	//add location
	bush_15->SetPos(pos_X, pos_Y, pos_Z);
	//colouring
	bush_15->color = Green;
	//add body
	App->physics->AddBody(*(bush_15), this, 0.0f);

}
