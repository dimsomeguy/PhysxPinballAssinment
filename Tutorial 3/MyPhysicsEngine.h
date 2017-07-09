#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = { PxVec3(46.f / 255.f,9.f / 255.f,39.f / 255.f),PxVec3(217.f / 255.f,0.f / 255.f,0.f / 255.f),
		PxVec3(255.f / 255.f,45.f / 255.f,0.f / 255.f),PxVec3(255.f / 255.f,140.f / 255.f,54.f / 255.f),PxVec3(4.f / 255.f,117.f / 255.f,111.f / 255.f) };
	static int score = 0;

	////Bottom edges 
	//static PxVec3 btmEdges_verts[] = { PxVec3(2, 0, 0), PxVec3(0, 0, 0), PxVec3(0, 0, 0.5), PxVec3(0, 2, 0), PxVec3(0, 1, 0) };

	//static PxU32 btmEdges_trigs[] = { 0, 1, 3, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1 };

	//class btmEdges : public ConvexMesh
	//{
	//public:
	//	btmEdges(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
	//		ConvexMesh(vector<PxVec3>(begin(pyramid_verts), end(pyramid_verts)), pose, density)
	//	{
	//	}
	//};

	//class btmEdgesState : public TriangleMesh
	//{
	//public:
	//	btmEdgesState(PxTransform pose = PxTransform(PxIdentity)) :
	//		TriangleMesh(vector<PxVec3>(begin(pyramid_verts), end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs), end(pyramid_trigs)), pose)
	//	{
	//	}
	//};


	//pyramid vertices					//0					//1						//2					//3					//4						//5						//6					//7
	static PxVec3 pyramid_verts[] = { PxVec3(-1.75f,0.f,0.f), PxVec3(-1.75f,0.f,-1.5f), PxVec3(-1.75f,10.f,0.f), PxVec3(-1.75f,10.f,-1.5f),	PxVec3(6.f,3.f,-1.5f),	PxVec3(6.f,3.f,0.f), PxVec3(6.f,0.f,-1.5f), PxVec3(6.f,0.f,0.f) };
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = { 5, 7, 0, 2, 5, 4, 3, 2, 0, 1, 7, 6, 5 , 4 };


	static PxVec3 Paddle_Verts[] = { PxVec3(-1.f, -1.f, 0.f), PxVec3(1.f, -1.f, -1.f), PxVec3(1.f, -3.f, 0.f), PxVec3(-1.f, -3.f, 0.f), PxVec3(-1.f, -1.f, -1.f), PxVec3(1.f, -1.f, 0.f) };

	static PxU32 Paddle_trigs[] = { 5, 0, 2, 5, 4, 3, 2, 0, 1, 5 , 4};

	static PxVec3 Bouncer_Verts[] = { PxVec3(2.5f, 5.f, -2.f), PxVec3(4.f, -2.f, -2.f), PxVec3(4.f, -2.f, 0.f), PxVec3(2.5f,  5.f, 0.f), PxVec3(1.f, 1.5f, 0.f), PxVec3(1.f, 1.5f, -2.f) };

	static PxU32 Bouncer_trigs[] = { 5, 0, 2, 5, 4, 3, 2, 0, 1, 5 , 4 };

	class Bouncer : public ConvexMesh
	{
	public:
		//this works almost exactly as the original pyrimid class however this allows for different sets of verys and trigs
		Bouncer(const std::vector<PxVec3>& Vert, PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f ) :
			ConvexMesh(vector<PxVec3>(begin(Vert), end(Vert)), pose, density)
		{
		}
	};

	class BouncerStatic : public TriangleMesh
	{
	public:
		BouncerStatic(const std::vector<PxVec3>& Vert, const std::vector<PxU32> trig, PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(Vert), end(Vert)), vector<PxU32>(begin(trig), end(trig)), pose)
		{
		}
	};

	struct FilterGroup
	{
		enum Enum
		{
			ACTOR0		= (1 << 0),
			ACTOR1		= (1 << 1),
			ACTOR2		= (1 << 2)
			//add more if you need
		};
	};

	///An example class showing the use of springs (distance joints).
	class Trampoline
	{
		vector<DistanceJoint*> springs;
		Box *bottom, *top;

	public:
		Trampoline(const PxVec3& dimensions=PxVec3(.43f, 1.7f, .5f), PxReal stiffness=10.f, PxReal damping=12.f)
		{
			PxReal thickness = 0.2f;
			//PxVec3(25.65f, 7.f, -0.5f))
			bottom = new Box(PxTransform(PxVec3(25.56f,2.2f + thickness,-.5f)),PxVec3(dimensions.x,thickness,dimensions.z));
			top = new Box(PxTransform(PxVec3(25.56f, dimensions.y + 2.2f + thickness, -.5f)), PxVec3(dimensions.x, thickness, dimensions.z));
			bottom->SetKinematic(true, 1);
			//top->SetKinematic(true, 1);
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,-dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,-dimensions.z)));

			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
			}
		}

		void down()
		{
			springs[0]->Stiffness(physx::PxReal(10.f));
			springs[1]->Stiffness(physx::PxReal(10.f));
			springs[2]->Stiffness(physx::PxReal(10.f));
			springs[3]->Stiffness(physx::PxReal(10.f));

			top->GetShape()->getActor()->isRigidBody()->addForce(PxVec3(0.f, -60.f, 0.f));
			
		}

		void release()
		{
			springs[0]->Stiffness(physx::PxReal(300.f));
			springs[1]->Stiffness(physx::PxReal(300.f));
			springs[2]->Stiffness(physx::PxReal(300.f));
			springs[3]->Stiffness(physx::PxReal(300.f));
			/*top->GetShape()->getActor()->isRigidDynamic()->addForce(PxVec3(0.f, 30.f, 0.f));*/
		}
		void AddToScene(Scene* scene)
		{
			scene->Add(bottom);
			scene->Add(top);
		}

		~Trampoline()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
				delete springs[i];
		}
	};

	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		
		//PhysicsEngine::MyScene* scene;
		
		//an example variable that will be checked in the main simulation loop
		bool trigger;
		//represents if ball is in play or not 
		bool Dead = false;

		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						trigger = true;
						// if box is triggers=d ball is dead 
						Dead = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						trigger = false;
					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{


			//cerr << "Contact found between " << name1 << " " << name2 << endl;

			int i = 0;
			//when a filter group event ends 
			if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
			{
				
				//check which group just ended 
				switch (pairs[i].shapes[0]->getSimulationFilterData().word0)
				{
					//give score accordingly 
					//bouncer group
				case FilterGroup::ACTOR1:
					score += 5;
					break;
					//capsule group
				case FilterGroup::ACTOR2:
					score += 15;
					break;
				}

			}
			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{

		//actors
		Plane* plane;
		Box* box;
		MySimulationEventCallback* my_callback;
		Trampoline* trampoline;
		RevoluteJoint* Ljoint;
		RevoluteJoint* Rjoint;
		CompoundShape* board;
		Bouncer* Lpaddle;
		Bouncer* Rpaddle;
		Bouncer* RightSlant;
		Bouncer* LeftSlant;
		Sphere* sphere;
		Sphere* LPadBase;
		Sphere* RPadBase;
		Bouncer* LBouncer;
		Bouncer* Rbouncer;
		Bouncer* CBouncer;
		Capsule* BoardBit1;
		Capsule* BoardBit2;
		Capsule* BoardBit3;
		Capsule* BoardBit4;
		Capsule* BoardBit5;

		public:
		//specify your custom filter shader here
		//PxDefaultSimulationFilterShader by default
		MyScene() : Scene(CustomFilterShader) {};

		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			

			GetMaterial()->setDynamicFriction(.2f);

			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);			

			plane = new Plane();
			plane->Color(PxVec3(13.f/255.f,113.f/255.f,103.f/255.f));
			Add(plane);			

			//instantiate paddles based on a set of vectors 
			Lpaddle = new Bouncer(vector<PxVec3>(begin(Paddle_Verts), end(Paddle_Verts)), PxTransform(PxVec3(0.0f, 2.0f, -4.0f), (PxQuat(PxPi, PxVec3(0.f, 0.f, 1.f)))));
			//gives a colour to the Actor based on a Vec 3 
			//							R				G			B
			Lpaddle->Color(PxVec3(255.f / 255.f, 125.f / 255.f, 0.f / 255.f));
			//adds the object to scene 
			Add(Lpaddle);


			Rpaddle = new Bouncer(vector<PxVec3>(begin(Paddle_Verts), end(Paddle_Verts)), PxTransform(PxVec3(0.0f, 2.0f, -4.0f), (PxQuat(PxPi, PxVec3(0.f, 0.f, 1.f)))));
			Rpaddle->Color(PxVec3(255.f / 255.f, 125.f / 255.f, 0.f / 255.f));
			Add(Rpaddle);


			LPadBase = new Sphere(PxTransform(PxVec3(17.f, 8.3f, 0.f)), PxReal(0.01));
			//LPadBase->Get()->isRigidDynamic()->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);
			LPadBase->SetKinematic(true, 0);
			Add(LPadBase);

			RPadBase = new Sphere(PxTransform(PxVec3(13.3f, 8.3f, 0.f)), PxReal(0.01));
			//RPadBase->Get()->isRigidDynamic()->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);
			RPadBase->SetKinematic(true, 0);
			Add(RPadBase);


			//Boarder:

			//create instence of compundshape
			board = new CompoundShape();
			//set the position of each peace of the compound shape
			board->GetShape(0)->setLocalPose(PxTransform(PxVec3(5.5f, 15.f, -1.0f)));
			board->GetShape(1)->setLocalPose(PxTransform(PxVec3(26.6f, 15.f, -1.f)));
			board->GetShape(2)->setLocalPose(PxTransform(PxVec3(16.f, 28.4f, -1.f)));
			board->GetShape(3)->setLocalPose(PxTransform(PxVec3(16.f, 1.6f, -1.f)));
			board->GetShape(4)->setLocalPose(PxTransform(PxVec3(16.f, 15.6f, -1.5f)));
			board->Color(PxVec3(30.f / 255.f, 100.f / 255.f, 240.f / 255.f));
			//set the object to static
			board->SetKinematic(true, 0);
			//give the entive border a low friction & high restitution giving it a strong bounce 
			board->Material(CreateMaterial(0.08f,0.f, 1.2f));
			Add(board);

			//DeadZone:

			box = new Box(PxTransform(PxVec3(17.55f, 2.25f, -.5f)), PxVec3(4.6f, .5f, .3f));
			box->SetKinematic(true, 0);
			//set color using the color palette instead of base values
			box->Color(color_palette[3]);
			//placing a trigger over the box to call on contact ball
			box->SetTrigger(true, 0);
			Add(box);
			
			//Slants:

			RightSlant = new Bouncer(vector<PxVec3>(begin(pyramid_verts), end(pyramid_verts)), PxTransform(PxVec3(23.37f, 2.f, -1.59f)));
			RightSlant->SetKinematic(true, 0);
			RightSlant->Color(PxVec3(255.f / 255.f, 125.f / 255.f, 0.f / 255.f));
			//changing the geomatry so as to flip the slant around the Y-Axis 180 degrees/pi  radiens
			RightSlant->GetShape()->setLocalPose(PxTransform(PxQuat(PxPi, PxVec3(0.f, 1.f, 0.f))));
			RightSlant->Material(CreateMaterial(0.08f, 0));
			Add(RightSlant);

			LeftSlant = new Bouncer(vector<PxVec3>(begin(pyramid_verts), end(pyramid_verts)), PxTransform(PxVec3(7.9f, 2.f, -0.09f)));
			LeftSlant->SetKinematic(true, 0);
			LeftSlant->Color(PxVec3(255.f / 255.f, 125.f / 255.f, 0.f / 255.f));
			Add(LeftSlant);

			//Ball:

			sphere = new Sphere(PxTransform(PxVec3(25.56f, 15.f, -0.5f)));
			//based on values given for a steel ball 
			sphere->Material(CreateMaterial(0.f, 0.65f, .98f));
			//set up a filter for the sphere so as to notice when it collides with ether the actor1 or actor2 filter groups 
			sphere->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1 | FilterGroup::ACTOR2);
			Add(sphere);


			//bouncers 

			LBouncer = new Bouncer(vector<PxVec3>(begin(Bouncer_Verts), end(Bouncer_Verts)), PxTransform(PxVec3(8.f, 9.4f, 0.f)));
			LBouncer->Color(PxVec3(13.f / 255.f, 113.f / 255.f, 103.f / 255.f));
			LBouncer->SetKinematic(true, 0);
			LBouncer->GetShape()->setLocalPose(PxTransform(PxQuat((PxPi /4) - 0.2f, PxVec3(0.f, 0.f, 1.f))));
			LBouncer->Material(CreateMaterial(0.5f, 0.08f, 1.f));
			//make this interactable with the balls collider group 
			LBouncer->SetupFiltering(FilterGroup::ACTOR1, FilterGroup::ACTOR0);
			Add(LBouncer);


			Rbouncer = new Bouncer(vector<PxVec3>(begin(Bouncer_Verts), end(Bouncer_Verts)), PxTransform(PxVec3(23.57f, 10.f, 0.f)));
			Rbouncer->SetKinematic(true, 0);
			Rbouncer->Color(PxVec3(13.f / 255.f, 113.f / 255.f, 103.f / 255.f));
			Rbouncer->GetShape()->setLocalPose(PxTransform(PxQuat(PxPi, PxVec3(0.f, 1.f, 0.f))));
			Rbouncer->GetShape()->setLocalPose(PxTransform(PxQuat(PxPi/1.5, PxVec3(0.f, 0.f, 1.f))));
			Rbouncer->Material(CreateMaterial(0.5f, 0.08f, 1.f));
			Rbouncer->SetupFiltering(FilterGroup::ACTOR1, FilterGroup::ACTOR0);
			Add(Rbouncer);

			CBouncer = new Bouncer(vector<PxVec3>(begin(Bouncer_Verts), end(Bouncer_Verts)), PxTransform(PxVec3(26.f,28.f, -0.09f)));
			CBouncer->SetKinematic(true, 0);
			CBouncer->Color(PxVec3(255.f / 255.f, 125.f / 255.f, 0.f / 255.f));
			CBouncer->GetShape()->setLocalPose(PxTransform(PxQuat(PxPi+0.5f, PxVec3(0.f, 0.f, 1.f))));
			CBouncer->Material(CreateMaterial(0.f, 0.08f, 1.6f));
			CBouncer->SetupFiltering(FilterGroup::ACTOR1, FilterGroup::ACTOR0);
			Add(CBouncer);


			//board Peaces 



			BoardBit1 = new Capsule(PxTransform(PxVec3(15.65f, 20.f, -0.5f)));
			BoardBit1->SetKinematic(true, 0);
			BoardBit1->GetShape()->setLocalPose(PxTransform(PxQuat(PxPi/2, PxVec3(0.f,1.f,0.f))));
			BoardBit1->Material(CreateMaterial(0.f, 0.08f, 2.f));
			BoardBit1->SetupFiltering(FilterGroup::ACTOR2, FilterGroup::ACTOR0);
			BoardBit1->Color(PxVec3(113.f / 113.f, 45.f / 255.f, 13.f / 255.f));
			Add(BoardBit1);

			BoardBit2 = new Capsule(PxTransform(PxVec3(8.65f, 20.f, -0.5f)));
			BoardBit2->SetKinematic(true, 0);
			BoardBit2->GetShape()->setLocalPose(PxTransform(PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))));
			BoardBit2->Material(CreateMaterial(0.f, 0.08f, 2.f));
			BoardBit2->SetupFiltering(FilterGroup::ACTOR2, FilterGroup::ACTOR0);
			BoardBit2->Color(PxVec3(255.f / 255.f, 125.f / 255.f, 0.f / 255.f));
			Add(BoardBit2);

			BoardBit3 = new Capsule(PxTransform(PxVec3(22.65f, 20.f, -0.5f)));
			BoardBit3->SetKinematic(true, 0);
			BoardBit3->GetShape()->setLocalPose(PxTransform(PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))));
			BoardBit3->Material(CreateMaterial(0.f, 0.08f, 2.f));
			BoardBit3->SetupFiltering(FilterGroup::ACTOR2, FilterGroup::ACTOR0);
			BoardBit3->Color(PxVec3(255.f / 255.f, 125.f / 255.f, 0.f / 255.f));
			Add(BoardBit3);

			BoardBit4 = new Capsule(PxTransform(PxVec3(15.65f, 15.f, -0.5f)));
			BoardBit4->SetKinematic(true, 0);
			BoardBit4->GetShape()->setLocalPose(PxTransform(PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))));
			BoardBit4->Material(CreateMaterial(0.f, 0.08f, 2.f));
			BoardBit4->SetupFiltering(FilterGroup::ACTOR2, FilterGroup::ACTOR0);
			BoardBit4->Color(PxVec3(255.f / 255.f, 125.f / 255.f, 0.f / 255.f));
			Add(BoardBit4);

			BoardBit5 = new Capsule(PxTransform(PxVec3(15.65f, 25.f, -0.5f)));
			BoardBit5->SetKinematic(true, 0);
			BoardBit5->GetShape()->setLocalPose(PxTransform(PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))));
			BoardBit5->Material(CreateMaterial(0.f, 0.08f, 2.f));
			BoardBit5->SetupFiltering(FilterGroup::ACTOR2, FilterGroup::ACTOR0);
			BoardBit5->Color(PxVec3(255.f / 255.f, 125.f / 255.f, 0.f / 255.f));
			Add(BoardBit5);


			//create a new instence f the trampoline 
			trampoline = new Trampoline();		
			//add this instence of trampoline to the scene
			trampoline->AddToScene(this);


			/*
			//joint two boxes together
			//the joint is fixed to the centre of the first box, oriented by 90 degrees around the Y axis
			//and has the second object attached 5 meters away along the Y axis from the first object.
			*/

			//joints:

			//place a revolving joint at the base point with the paddle attached to it  
			Ljoint = new RevoluteJoint(LPadBase, PxTransform(PxVec3(0.f, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))), Lpaddle, PxTransform(PxVec3(0.f, -1.5f,-.5f)));
			//gives an uper and lower bound to the joint 
			Ljoint->SetLimits(PxReal(0.3f),PxReal(1.9f));
			// gives a base velocity to the joint motor 
			Ljoint->DriveVelocity(PxReal(-10.0f));

			Rjoint = new RevoluteJoint(RPadBase, PxTransform(PxVec3(0.f, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, -1.f, 0.f))), Rpaddle, PxTransform(PxVec3(0.f, -1.5f, -.5f)));
			Rjoint->SetLimits(PxReal(0.5f), PxReal(1.9f));

			Rjoint->DriveVelocity(PxReal(-10.0f));

		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
			//if ball is dead 
			if (my_callback->Dead == true)
			{
				//move ball back to origin 
				sphere->GetShape()->getActor()->setGlobalPose(PxTransform(PxVec3(25.56f, 9.f, -1.f)));
				//reset dead flag 
				my_callback->Dead = false;
			}
			//keeps the ball from flying out of the bard assuming gravity isn't strong enough 
			sphere->GetShape()->setLocalPose(PxTransform(PxVec3(NULL, NULL, 0.f)));
			
		}

		virtual int GetScore()
		{
			return score;
		}
		void Fire()
		{
			trampoline->down();
		}
		void Release()
		{
			trampoline->release();
		}
		// An example use of key release handling
		void LeftRelease()
		{
			//if P is released give the motor a downward force 
				Ljoint->DriveVelocity(-30.0f);
			//cerr << "I am realeased!" << endl;
		}

		/// An example use of key presse handling
		void LeftPress()
		{
			//if P is pressed give the motor a strong upward force
				Ljoint->DriveVelocity(50.0f);
			//cerr << "I am pressed!" << endl;
		}

		void RightRelease()
		{
	
				Rjoint->DriveVelocity(-40.0f);
			//cerr << "I am realeased!" << endl;
		}

		/// An example use of key presse handling
		void RightPress()
		{

		
				Rjoint->DriveVelocity(40.0f);
			//cerr << "I am pressed!" << endl;
		}
	};
}
