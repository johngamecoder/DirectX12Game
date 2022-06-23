#include "pch.h"
#include "Game.h"
#include "Engine.h"

#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "CameraMovementScript.h"
#include "ParticleSystem.h"
#include "Terrain.h"
#include "SphereCollider.h"
#include "MeshData.h"
#include "PlanetMovement.h"

void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);

	GET_SINGLE(SceneManager)->SetActiveScene(SolarSystemScene());
	//GET_SINGLE(SceneManager)->SetActiveScene(LoadTestScene());
}

void Game::Update()
{
	GEngine->Update();
}

std::shared_ptr<Scene> Game::SolarSystemScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();

#pragma region Camera
	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		camera->SetName(L"Main_Camera");
		camera->AddComponent(make_shared<Transform>());
		camera->AddComponent(make_shared<Camera>()); // Near=1, Far=1000, FOV=45도
		camera->AddComponent(make_shared<CameraMovementScript>());
		camera->GetCamera()->SetFar(10000.f);
		camera->GetTransform()->SetLocalPosition(Vec3(0.f, 500.f, -500.f));
		camera->GetTransform()->SetLocalRotation(Vec3(0.8f, 0.f, 0.f));
		uint8 layerIndex = GET_SINGLE(SceneManager)->LayerNameToIndex(L"UI");
		camera->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, true); // UI는 안 찍음
		scene->AddGameObject(camera);
	}
#pragma endregion

#pragma region SkyBox
	{
		shared_ptr<GameObject> skybox = make_shared<GameObject>();
		skybox->SetName(L"Sky Box");
		skybox->AddComponent(make_shared<Transform>());
		skybox->SetCheckFrustum(false);
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Skybox");
			shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Sky01", L"..\\Resources\\Texture\\Sky01.jpg");
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		skybox->AddComponent(meshRenderer);
		scene->AddGameObject(skybox);
	}
#pragma endregion

#pragma region Directional Light
	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
		light->SetName(L"Directional Light");
		GET_SINGLE(Resources)->LoadRectangleMesh();
		light->AddComponent(make_shared<Transform>());
		light->GetTransform()->SetLocalPosition(Vec3(0, 1000, 500));
		light->AddComponent(make_shared<Light>());
		light->GetLight()->SetLightDirection(Vec3(0, -1, 1.f));
		light->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
		light->GetLight()->SetDiffuse(Vec3(1.f, 1.f, 1.f));
		light->GetLight()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));

		scene->AddGameObject(light);
	}
#pragma endregion

#pragma region Sun

	{
		shared_ptr<GameObject> obj = make_shared<GameObject>();
		obj->SetName(L"Sun");
		obj->AddComponent(make_shared<Transform>());
		obj->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		obj->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMeshAndMaterial(MeshType::SPHERE, obj->GetName());
		obj->AddComponent(make_shared<SphereCollider>());
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetRadius(0.5f);
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetCenter(Vec3(0.f, 0.f, 0.f));
		scene->AddGameObject(obj);
	}
#pragma endregion

	shared_ptr<Transform> sunTransform = scene->GetGameObjectByName(L"Sun")->GetTransform();

#pragma region Mercury
	{
		shared_ptr<GameObject> obj = make_shared<GameObject>();
		obj->SetName(L"Mercury");
		obj->AddComponent(make_shared<Transform>());
		obj->GetTransform()->SetLocalScale(Vec3(20.f, 20.f, 20.f));
		obj->GetTransform()->SetLocalPosition(Vec3(100.f, 0.f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMeshAndMaterial(MeshType::SPHERE, obj->GetName());
		obj->AddComponent(make_shared<SphereCollider>());
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetRadius(0.5f);
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetCenter(Vec3(0.f, 0.f, 0.f));
		
		shared_ptr<PlanetMovement> movement = dynamic_pointer_cast<PlanetMovement>(obj->AddComponent(make_shared<PlanetMovement>()));
		movement->SetPlanetRotationAndOrbit(0.1f, 0.1f);
		//scene->AddGameObject(obj);
	}
#pragma endregion

#pragma region Venus
	{
		shared_ptr<GameObject> obj = make_shared<GameObject>();
		obj->SetName(L"Venus");
		obj->AddComponent(make_shared<Transform>());
		obj->GetTransform()->SetLocalScale(Vec3(30.f, 30.f, 30.f));
		obj->GetTransform()->SetLocalPosition(Vec3(200.f, 0.f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMeshAndMaterial(MeshType::SPHERE, obj->GetName());
		obj->AddComponent(make_shared<SphereCollider>());
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetRadius(0.5f);
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetCenter(Vec3(0.f, 0.f, 0.f));
		//scene->AddGameObject(obj);
	}
#pragma endregion

#pragma region Earth
	{
		shared_ptr<GameObject> obj = make_shared<GameObject>();
		obj->SetName(L"Earth");
		obj->AddComponent(make_shared<Transform>());
		obj->GetTransform()->SetLocalScale(Vec3(50.f, 50.f, 50.f));
		obj->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -300.f));
		obj->GetTransform()->SetParent(sunTransform);
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMeshAndMaterial(MeshType::SPHERE, obj->GetName());
		obj->AddComponent(make_shared<SphereCollider>());
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetRadius(0.5f);
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetCenter(Vec3(0.f, 0.f, 0.f));
		
		shared_ptr<PlanetMovement> movement = dynamic_pointer_cast<PlanetMovement>(obj->AddComponent(make_shared<PlanetMovement>()));
		movement->SetPlanetRotationAndOrbit(0.1f, 0.6f);
		scene->AddGameObject(obj);
	}
#pragma endregion

	shared_ptr<Transform> earthTransform = scene->GetGameObjectByName(L"Earth")->GetTransform();

#pragma region Moon
	{
		shared_ptr<GameObject> obj = make_shared<GameObject>();
		obj->SetName(L"Moon");
		obj->AddComponent(make_shared<Transform>());
		obj->GetTransform()->SetLocalScale(Vec3(20.f, 20.f, 20.f));
		obj->GetTransform()->SetLocalPosition(Vec3(50.f, 0.f, 0.f));
		obj->GetTransform()->SetParent(earthTransform);
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMeshAndMaterial(MeshType::SPHERE, obj->GetName());
		obj->AddComponent(make_shared<SphereCollider>());
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetRadius(0.5f);
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetCenter(Vec3(0.f, 0.f, 0.f));
		
		//shared_ptr<PlanetMovement> movement = dynamic_pointer_cast<PlanetMovement>(obj->AddComponent(make_shared<PlanetMovement>()));
		//movement->SetPlanetRotationAndOrbit(0.1f, 0.6f);

		scene->AddGameObject(obj);
	}
#pragma endregion

#pragma region Mars
	{
		shared_ptr<GameObject> obj = make_shared<GameObject>();
		obj->SetName(L"Mars");
		obj->AddComponent(make_shared<Transform>());
		obj->GetTransform()->SetLocalScale(Vec3(50.f, 50.f, 50.f));
		obj->GetTransform()->SetLocalPosition(Vec3(400.f, 0.f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMeshAndMaterial(MeshType::SPHERE, obj->GetName());
		obj->AddComponent(make_shared<SphereCollider>());
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetRadius(0.5f);
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetCenter(Vec3(0.f, 0.f, 0.f));
		//scene->AddGameObject(obj);
	}
#pragma endregion

#pragma region Jupiter
	{
		shared_ptr<GameObject> obj = make_shared<GameObject>();
		obj->SetName(L"Jupiter");
		obj->AddComponent(make_shared<Transform>());
		obj->GetTransform()->SetLocalScale(Vec3(80.f, 80.f, 80.f));
		obj->GetTransform()->SetLocalPosition(Vec3(500.f, 0.f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMeshAndMaterial(MeshType::SPHERE, obj->GetName());
		obj->AddComponent(make_shared<SphereCollider>());
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetRadius(0.5f);
		dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetCenter(Vec3(0.f, 0.f, 0.f));
		//scene->AddGameObject(obj);
	}
#pragma endregion

	return scene;
}



//=============================================================================
//---------------------------Test----------------------------------------------
//=============================================================================

shared_ptr<Scene> Game::LoadTestScene()
{
#pragma region ComputeShader
	{
		shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"ComputeShader");

		// UAV 용 Texture 생성
		shared_ptr<Texture> texture = GET_SINGLE(Resources)->CreateTexture(L"UAVTexture",
			DXGI_FORMAT_R8G8B8A8_UNORM, 1024, 1024,
			CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE,
			D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);

		shared_ptr<Material> material = GET_SINGLE(Resources)->Get<Material>(L"ComputeShader");
		material->SetShader(shader);
		material->SetInt(0, 1);
		GEngine->GetComputeDescHeap()->SetUAV(texture->GetUAVHandle(), UAV_REGISTER::u0);

		// 쓰레드 그룹 (1 * 1024 * 1)
		material->Dispatch(1, 1024, 1);
	}
#pragma endregion

	shared_ptr<Scene> scene = make_shared<Scene>();

#pragma region Camera
	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		camera->SetName(L"Main_Camera");
		camera->AddComponent(make_shared<Transform>());
		camera->AddComponent(make_shared<Camera>()); // Near=1, Far=1000, FOV=45도
		camera->AddComponent(make_shared<CameraMovementScript>());
		camera->GetCamera()->SetFar(10000.f);
		camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 0.f));
		uint8 layerIndex = GET_SINGLE(SceneManager)->LayerNameToIndex(L"UI");
		camera->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, true); // UI는 안 찍음
		scene->AddGameObject(camera);
	}
#pragma endregion

#pragma region UI_Camera
	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		camera->SetName(L"Orthographic_Camera");
		camera->AddComponent(make_shared<Transform>());
		camera->AddComponent(make_shared<Camera>()); // Near=1, Far=1000, 800*600
		camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 0.f));
		camera->GetCamera()->SetProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC);
		uint8 layerIndex = GET_SINGLE(SceneManager)->LayerNameToIndex(L"UI");
		camera->GetCamera()->SetCullingMaskAll(); // 다 끄고
		camera->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, false); // UI만 찍음
		scene->AddGameObject(camera);
	}
#pragma endregion

#pragma region SkyBox
	{
		shared_ptr<GameObject> skybox = make_shared<GameObject>();
		skybox->AddComponent(make_shared<Transform>());
		skybox->SetCheckFrustum(false);
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Skybox");
			shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Sky01", L"..\\Resources\\Texture\\Sky01.jpg");
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		skybox->AddComponent(meshRenderer);
		scene->AddGameObject(skybox);
	}
#pragma endregion

#pragma region Object
	//{
	//	shared_ptr<GameObject> obj = make_shared<GameObject>();
	//	obj->SetName(L"OBJ");
	//	obj->AddComponent(make_shared<Transform>());
	//	obj->AddComponent(make_shared<SphereCollider>());
	//	obj->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
	//	obj->GetTransform()->SetLocalPosition(Vec3(0, 0.f, 500.f));
	//	obj->SetStatic(false);
	//	shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
	//	{
	//		shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
	//		meshRenderer->SetMesh(sphereMesh);
	//	}
	//	{
	//		shared_ptr<Material> material = GET_SINGLE(Resources)->Get<Material>(L"GameObject");
	//		meshRenderer->SetMaterial(material->Clone());
	//	}
	//	dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetRadius(0.5f);
	//	dynamic_pointer_cast<SphereCollider>(obj->GetCollider())->SetCenter(Vec3(0.f, 0.f, 0.f));
	//	obj->AddComponent(meshRenderer);
	//	scene->AddGameObject(obj);
	//}
#pragma endregion

#pragma region Terrain
	//{
	//	shared_ptr<GameObject> obj = make_shared<GameObject>();
	//	obj->AddComponent(make_shared<Transform>());
	//	obj->AddComponent(make_shared<Terrain>());
	//	obj->AddComponent(make_shared<MeshRenderer>());

	//	obj->GetTransform()->SetLocalScale(Vec3(50.f, 250.f, 50.f));
	//	obj->GetTransform()->SetLocalPosition(Vec3(-100.f, -200.f, 300.f));
	//	obj->SetStatic(true);
	//	obj->GetTerrain()->Init(64, 64);
	//	obj->SetCheckFrustum(false);

	//	scene->AddGameObject(obj);
	//}
#pragma endregion

#pragma region UI_Test
	for (int32 i = 0; i < 6; i++)
	{
		shared_ptr<GameObject> obj = make_shared<GameObject>();
		obj->SetLayerIndex(GET_SINGLE(SceneManager)->LayerNameToIndex(L"UI")); // UI
		obj->AddComponent(make_shared<Transform>());
		obj->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		obj->GetTransform()->SetLocalPosition(Vec3(-350.f + (i * 120), 250.f, 500.f));
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectangleMesh();
			meshRenderer->SetMesh(mesh);
		}
		{
			shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Texture");

			shared_ptr<Texture> texture;
			if (i < 3)
				texture = GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->GetRTTexture(i);
			else if (i < 5)
				texture = GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->GetRTTexture(i - 3);
			else
				texture = GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SHADOW)->GetRTTexture(0);

			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		obj->AddComponent(meshRenderer);
		scene->AddGameObject(obj);
	}
#pragma endregion

#pragma region Directional Light
	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
		light->AddComponent(make_shared<Transform>());
		light->GetTransform()->SetLocalPosition(Vec3(0, 1000, 500));
		light->AddComponent(make_shared<Light>());
		light->GetLight()->SetLightDirection(Vec3(0, -1, 1.f));
		light->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
		light->GetLight()->SetDiffuse(Vec3(1.f, 1.f, 1.f));
		light->GetLight()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));

		scene->AddGameObject(light);
	}
#pragma endregion


//#pragma region FBX
//	{
//		shared_ptr<MeshData> meshData = GET_SINGLE(Resources)->LoadFBX(L"..\\Resources\\FBX\\Dragon.fbx");
//
//		vector<shared_ptr<GameObject>> gameObjects = meshData->Instantiate();
//
//		for (auto& gameObject : gameObjects)
//		{
//			gameObject->SetName(L"Dragon");
//			gameObject->SetCheckFrustum(false);
//			gameObject->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 300.f));
//			gameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
//			scene->AddGameObject(gameObject);
//			gameObject->AddComponent(make_shared<TestDragon>());
//		}
//	}
//#pragma endregion

	return scene;
}