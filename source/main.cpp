//External includes
#include "vld.h"
#include "SDL.h"
#include "SDL_surface.h"
#undef main

//Standard includes
#include <iostream>

//Project includes
#include "ETimer.h"
#include "ERenderer.h"
// Scene include
#include "SceneGraph.h"
// object includes
#include "Primitive.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "TriangleMesh.h"
// Camera Include
#include "PerspectiveCamera.h"
// lights includes
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
// material includes
#include "Material.h"
#include "LambertMaterial.h"
#include "LambertPhongMaterial.h"
#include "PBRMaterial.h"

void ShutDown(SDL_Window* pWindow)
{
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}
//void BuildTestScene()
//{
//	RGBColor LighthColor = { 1.f, 1.f, 0.8f };
//	FPoint3 lightLocation = { 0,5,-5 };
//	FPoint3 lightLocation2 = { 0,2.5,5 };
//	FVector3 LightDirection = { 0,-1,0 };
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(-1.5f, 1, 0), 1, Elite::RGBColor{ 1,0,0 },std::make_unique<LambertPhongMaterial>(1.f, Elite::RGBColor{ 0.69f,0.60f,0.25f },1.0f,60)));
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(1.5f, 1, 0), 1, Elite::RGBColor{ 0,0,1 }, std::make_unique<LambertMaterial>(1.f, Elite::RGBColor{ 0.3f,0.5f,0.35f })));
//	
//
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0, 0, 0), Elite::FVector3(0.f,1.f,0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, std::make_unique<LambertMaterial>(1.f, Elite::RGBColor{ 0.3f,0.3f,0.3f })));
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0, 0, -5), Elite::FVector3(0.f, 1.f, 1.f), Elite::RGBColor{ 0.3f,0.3f,0.3f }, std::make_unique<LambertMaterial>(1.f, Elite::RGBColor{ 0.3f,0.3f,0.3f })));
//
//	SceneGraph::GetInstance()->AddLightsToGraph(new PointLight(LighthColor,25.f, lightLocation));
//	SceneGraph::GetInstance()->AddLightsToGraph(new PointLight(LighthColor, 25.f, lightLocation2));
//	SceneGraph::GetInstance()->AddLightsToGraph(new DirectionalLight(LighthColor, 2.f,LightDirection));
//	
//}
//void BuildPBRScene()
//{
//	RGBColor LighthColor = { 1.f, 1.f, 0.8f };
//	RGBColor LighthColor2 = { 0.8f, 1.f, 1.f };
//
//	FPoint3 lightLocation = { 0,5,-5 };
//	FPoint3 lightLocation2 = { 0,5.f,5 };
//	FVector3 LightDirection = { 0,-1,0 };
//
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(-3.f, 1.f, 0), 1, Elite::RGBColor{ 0,0,1 }, std::make_unique<PBRMaterial>(0.1f, Elite::RGBColor{ 0.972f,0.960f,0.915f }, true)));
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(0.f, 1.f, 0), 1, Elite::RGBColor{ 0,0,1 }, std::make_unique<PBRMaterial>(0.6f, Elite::RGBColor{ 0.972f,0.960f,0.915f }, true)));
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(3.f, 1.f, 0), 1, Elite::RGBColor{ 0,0,1 }, std::make_unique<PBRMaterial>(1.f, Elite::RGBColor{ 0.972f,0.960f,0.915f }, true)));
//
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(-3.f, 4.f, 0), 1, Elite::RGBColor{ 0,0,1 }, std::make_unique<PBRMaterial>(0.1f, Elite::RGBColor{ 0.972f,0.960f,0.915f }, false)));
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(0.f, 4.f, 0), 1, Elite::RGBColor{ 0,0,1 }, std::make_unique<PBRMaterial>(0.6f, Elite::RGBColor{ 0.972f,0.960f,0.915f }, false)));
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(3.f, 4.f, 0), 1, Elite::RGBColor{ 0,0,1 }, std::make_unique<PBRMaterial>(1.f, Elite::RGBColor{ 0.972f,0.960f,0.915f }, false)));
//
//	//SceneGraph::GetInstance()->AddObjectsToGraph(new Triangle(FPoint3(-0.25f, 0.5f, 4.f), FPoint3(-0.75f, 1.5f, 4.f), FPoint3(-0.75f, 0.f, 4.f), FPoint3(0.75f, 0.0f, 4.f), RGBColor(1.f, 1.f, 1.f), std::make_unique<PBRMaterial>(0.4f, RGBColor{ 0.04f,0.04f,0.04f }, false), CullMode::frontFace));
//
//	
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0, 0, 0), Elite::FVector3(0.f, 1.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, std::make_unique<LambertPhongMaterial>(1.f, Elite::RGBColor{ 0.3f,0.3f,0.3f }, 0.5f, 60)));
//	//SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0, 15, 0), Elite::FVector3(0.f, -1.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, std::make_unique<LambertMaterial>(1.f, Elite::RGBColor{ 0.3f,0.3f,0.3f })));
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0, 0, -10), Elite::FVector3(0.f, 0.f, 1.f), Elite::RGBColor{ 0.3f,0.3f,0.3f }, std::make_unique<LambertPhongMaterial>(1.f, Elite::RGBColor{ 0.6f,0.6f,0.6f }, 0.5f, 60)));
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(7, 0, 0), Elite::FVector3(-1.f, 0.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, std::make_unique<LambertPhongMaterial>(1.f, Elite::RGBColor{ 0.6f,0.6f,0.6f }, 0.5f, 60)));
//	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(-7, 0, -5), Elite::FVector3(1.f, 0.f, 0.f), Elite::RGBColor{ 0.3f,0.3f,0.3f }, std::make_unique<LambertPhongMaterial>(1.f, Elite::RGBColor{ 0.6f,0.6f,0.6f }, 0.5f, 60)));
//
//	SceneGraph::GetInstance()->AddLightsToGraph(new PointLight(LighthColor, 30.f, lightLocation));
//	SceneGraph::GetInstance()->AddLightsToGraph(new PointLight(LighthColor2, 30.f, lightLocation2));
//	//SceneGraph::GetInstance()->AddLightsToGraph(new DirectionalLight(LighthColor, 2.f, LightDirection));
//}
void RayTracer_Reference()
{
	PBRMaterial* PBR_RoughMetal = new PBRMaterial(1.f, RGBColor{.972f,.960f,.915f}, 1);
	PBRMaterial* PBR_MediumMetal = new PBRMaterial(.6f, RGBColor{ .972f,.960f,.915f }, 1);
	PBRMaterial* PBR_SmoothMetal =  new PBRMaterial(.1f, RGBColor{ .972f,.960f,.915f }, 1);
	PBRMaterial* PBR_RoughPlastic = new PBRMaterial(1.f, RGBColor{ .75f,.75f,.75f }, 0);
	PBRMaterial* PBR_MediumPlastic = new PBRMaterial(.4f, RGBColor{ .75f,.75f,.75f }, 0);
	PBRMaterial* PBR_SmoothPlastic = new PBRMaterial(.1f, RGBColor{ .75f,.75f,.75f }, 0);
	SceneGraph::GetInstance()->AddMaterialsToGraph(PBR_RoughMetal);
	SceneGraph::GetInstance()->AddMaterialsToGraph(PBR_MediumMetal);
	SceneGraph::GetInstance()->AddMaterialsToGraph(PBR_SmoothMetal);
	SceneGraph::GetInstance()->AddMaterialsToGraph(PBR_RoughPlastic);
	SceneGraph::GetInstance()->AddMaterialsToGraph(PBR_MediumPlastic);
	SceneGraph::GetInstance()->AddMaterialsToGraph(PBR_SmoothPlastic);
	 LambertMaterial* Lambert_GreyBlue = new LambertMaterial{ 1 ,RGBColor{.49f,.57f,.57f} };
	 LambertMaterial* Lambert_White = new LambertMaterial{ 1,RGBColor{ 1.f,1.f,1.f } };
	 SceneGraph::GetInstance()->AddMaterialsToGraph(Lambert_GreyBlue);
	 SceneGraph::GetInstance()->AddMaterialsToGraph(Lambert_White);

	// planes 
	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0.f, 0.f, 0.f), Elite::FVector3(0.f, 1.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f },Lambert_GreyBlue));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0.f, 0.f, -10.f), Elite::FVector3(0.f, 0.f, 1.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, Lambert_GreyBlue));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0.f, 10.f, 0.f), Elite::FVector3(0.f, -1.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, Lambert_GreyBlue));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(5.f, 0.f, 0.f), Elite::FVector3(-1.f, 0.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, Lambert_GreyBlue));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(-5.f, 0.f, 0.f), Elite::FVector3(1.f, 0.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, Lambert_GreyBlue));


	// Spheres
	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(-1.75f, 1, 0), .75f, Elite::RGBColor{ 0,0,1 },PBR_RoughMetal));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(0.f, 1.f, 0), .75f, Elite::RGBColor{ 0,0,1 }, PBR_MediumMetal));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(1.75f, 1.f, 0), .75f, Elite::RGBColor{ 0,0,1 }, PBR_SmoothMetal));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(-1.75f, 3.f, 0), .75f, Elite::RGBColor{ 0,0,1 }, PBR_RoughPlastic));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(0.f, 3.f, 0), .75f, Elite::RGBColor{ 0,0,1 }, PBR_MediumPlastic));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Sphere(Elite::FPoint3(1.75f, 3.f, 0), .75f, Elite::RGBColor{ 0,0,1 }, PBR_SmoothPlastic));

	// Triangles
	std::vector<FPoint3> relativePoints;
	FPoint3 vertex1{ -.75f,1.5f,0 };
	FPoint3 vertex2{ -.75f,0,0 };
	FPoint3 vertex3{ .75f,0,0 };
	relativePoints.push_back(vertex1);
	relativePoints.push_back(vertex2);
	relativePoints.push_back(vertex3);
	/*Triangle[Material{ Lambert_White }, Position{ -1.75f, 4.5f, 0.f }, CullMode{ BackFace }]
		Triangle[Material{ Lambert_White }, Position{ 0.f, 4.5f, 0.f }, CullMode{ FrontFace }]
		Triangle[Material{ Lambert_White }, Position{ 1.75f, 4.5f, 0.f }, CullMode{ No Culling }]*/
	
	SceneGraph::GetInstance()->AddObjectsToGraph(new Triangle(FPoint3(-1.75f, 4.5f, 0.f), relativePoints,RGBColor(1.f, 1.f, 1.f), Lambert_White, CullMode::backFace));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Triangle(FPoint3(0.f, 4.5f, 0.f), relativePoints, RGBColor(1.f, 1.f, 1.f), Lambert_White, CullMode::frontFace));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Triangle(FPoint3(1.75f, 4.5f, 0.f), relativePoints, RGBColor(1.f, 1.f, 1.f), Lambert_White, CullMode::none));


	// Lights

	SceneGraph::GetInstance()->AddLightsToGraph(new PointLight(RGBColor{ 1.f,0.61f,0.45f }, 50.f, FPoint3{0.f,5.f,-5.f}));
	SceneGraph::GetInstance()->AddLightsToGraph(new PointLight(RGBColor{ 1.f,0.8f,0.45f }, 70.f, FPoint3{ -2.5f,5.f,5.f }));
	SceneGraph::GetInstance()->AddLightsToGraph(new PointLight(RGBColor{ 0.34f,0.47f,0.68f }, 50.f, FPoint3{ 2.5f,2.5f,5.f }));



}
void RayTracer_Bunny()
{
	/*PBRMaterial * PBR_RoughMetal    = new PBRMaterial(1.f, RGBColor{ .972f,.960f,.915f }, 1);
	PBRMaterial * PBR_MediumMetal   = new PBRMaterial(.6f, RGBColor{ .972f,.960f,.915f }, 1);
	PBRMaterial * PBR_SmoothMetal   = new PBRMaterial(.1f, RGBColor{ .972f,.960f,.915f }, 1);
	PBRMaterial * PBR_RoughPlastic  = new PBRMaterial(1.f, RGBColor{ .75f,.75f,.75f }, 0);
	PBRMaterial * PBR_MediumPlastic = new PBRMaterial(.6f, RGBColor{ .75f,.75f,.75f }, 0);
	PBRMaterial * PBR_SmoothPlastic = new PBRMaterial(.1f, RGBColor{ .75f,.75f,.75f }, 0);*/

	 LambertMaterial *Lambert_GreyBlue = new LambertMaterial{ 1 ,RGBColor{.49f,.57f,.57f} };
	 LambertMaterial *Lambert_White = new LambertMaterial{ 1,RGBColor{ 1.f,1.f,1.f } };
	 SceneGraph::GetInstance()->AddMaterialsToGraph(Lambert_GreyBlue);
	 SceneGraph::GetInstance()->AddMaterialsToGraph(Lambert_White);



	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0.f, 0.f, 0.f), Elite::FVector3(0.f, 1.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f },Lambert_GreyBlue));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0.f, 0.f, -10.f), Elite::FVector3(0.f, 0.f, 1.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, Lambert_GreyBlue));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(0.f, 10.f, 0.f), Elite::FVector3(0.f, -1.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, Lambert_GreyBlue));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(5.f, 0.f, 0.f), Elite::FVector3(-1.f, 0.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f },Lambert_GreyBlue));
	SceneGraph::GetInstance()->AddObjectsToGraph(new Plane(Elite::FPoint3(-5.f, 0.f, 0.f), Elite::FVector3(1.f, 0.f, 0.f), Elite::RGBColor{ 0.5f,0.5f,0.5f }, Lambert_GreyBlue));

	TriangleMesh* pBunny = new TriangleMesh{ FPoint3{ 0,0,0 },Lambert_White, "Resources/lowpoly_bunny.obj" };
	SceneGraph::GetInstance()->AddObjectsToGraph(pBunny);

	SceneGraph::GetInstance()->AddLightsToGraph(new PointLight(RGBColor{ 1.f,0.61f,0.45f }, 50.f, FPoint3{ 0.f,5.f,-5.f }));
	SceneGraph::GetInstance()->AddLightsToGraph(new PointLight(RGBColor{ 1.f,0.8f,0.45f }, 70.f, FPoint3{ -2.5f,5.f,5.f }));
	SceneGraph::GetInstance()->AddLightsToGraph(new PointLight(RGBColor{ 0.34f,0.47f,0.68f }, 50.f, FPoint3{ 2.5f,2.5f,5.f }));
}

int main(int argc, char* args[])
{
	//Unreferenced parameters
	(void)argc;
	(void)args;
	// BuildScene
	
	//BuildTestScene();
	//BuildPBRScene();
	RayTracer_Reference();
	//RayTracer_Bunny();
	
	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	const uint32_t width = 640;
	const uint32_t height = 480;
	SDL_Window* pWindow = SDL_CreateWindow(
		"RayTracer - *Yannick Godeau*",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0);

	if (!pWindow)
		return 1;

	//Initialize "framework"
	Elite::Timer* pTimer = new Elite::Timer();
	Elite::Renderer* pRenderer = new Elite::Renderer(pWindow);
	// Camera and worldLocation initialization

	Elite::FPoint3 worldlocation{ 0.f,3.f,9.f };
	PerspectiveCamera::SetCamera(width, height, 45.f, worldlocation);

	//Start loop
	pTimer->Start();
	float printTimer = 0.f;
	bool isLooping = true;
	bool takeScreenshot = false;
	while (isLooping)
	{
		//--------- Get input events ---------
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isLooping = false;
				break;
			case SDL_KEYUP:
				if(e.key.keysym.scancode == SDL_SCANCODE_X)
					takeScreenshot = true;
				if (e.key.keysym.scancode == SDL_SCANCODE_Q)
				{
					pRenderer->ToggleShadows();
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_E)
				{
					pRenderer->ToggleLights();
				}
				break;
			}
		}
		PerspectiveCamera::GetInstance()->Update(pTimer->GetElapsed());
		//--------- Render ---------
		pRenderer->Render();

		//--------- Timer ---------
		pTimer->Update();
		printTimer += pTimer->GetElapsed();
		if (printTimer >= 1.f)
		{
			printTimer = 0.f;
			std::cout << "FPS: " << pTimer->GetFPS() << std::endl;
		}

		//Save screenshot after full render
		if (takeScreenshot)
		{
			if (!pRenderer->SaveBackbufferToImage())
				std::cout << "Screenshot saved!" << std::endl;
			else
				std::cout << "Something went wrong. Screenshot not saved!" << std::endl;
			takeScreenshot = false;
		}
	}
	pTimer->Stop();

	//Shutdown "framework"
	delete pRenderer;
	delete pTimer;

	ShutDown(pWindow);
	SceneGraph::Cleanup();
	PerspectiveCamera::Cleanup();
	return 0;
}