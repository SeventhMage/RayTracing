#include "tracer.h"

#include <ctime>

static const int FRAMES_PER_SECOND = 100;
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

using namespace se;
using namespace base;
using namespace math;
using namespace scene;
using namespace device;

int main(int argc, char *argv[])
{
	std::srand(time(0));
	CTracer tracer(100, 100, 768, 768);
	
	IDevice *device = tracer.GetDevice();	
	ISceneManager *sceneMgr = tracer.GetSceneManager();	
	IScene *scene = sceneMgr->GetCurrentScene();
	IObjectManager *objectMgr = tracer.GetObjectManager();
	IKeyEvent *pEvent = tracer.GetEventManager()->GetKeyEvent();

	ICamera *pCamera = scene->SetupCamera(math::CVector3(0, 5, 10), CVector3(0, -0.6, -1), CVector3(0, 1, 0), DEG_TO_RAD(30), 1 /*device->GetWindowWidth() * 1.f / device->GetWindowHeight()*/, 1, 1000);
	//ICamera *pCamera = scene->SetupCamera(math::CVector3(0, 0, 5), CVector3(0, 0, -1), CVector3(0, 1, 0), DEG_TO_RAD(30), 1 /*device->GetWindowWidth() * 1.f / device->GetWindowHeight()*/, 1, 1000);
	for (int i = 0; i < 1; ++i)
	{
		float a = MAX(rand() % 255 / 255.f, 0.1f);
		float r = MAX(rand() % 255 / 255.f, 0.2f);
		float g = MAX(rand() % 255 / 255.f, 0.2f);
		float b = MAX(rand() % 255 / 255.f, 0.2f);
		
		IObject *pObject = objectMgr->CreateSphere(1, Color(1.f, r, g, b));
		//pObject->SetAlbedo(0.5f);
		ISceneNode *pNode = scene->AddObject(pObject);
		float x = rand() % 10 - 5;
		float y = rand() % 10 - 5;
		float z = rand() % 10 - 5;
		pNode->SetPosition(CVector3(0, -4.f, -5.f));
		//pNode->SetPosition(CVector3(0, 0, -5));
	}
	
	std::vector<math::CVector3> vertices;
	vertices.push_back(CVector3(-10, -5, -10));
	vertices.push_back(CVector3(10, -5, -10));
	vertices.push_back(CVector3(0, -5, -2));

	std::vector<ushort>indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	std::vector<math::CVector3> normals;
	normals.push_back(CVector3(0, 1, 0));
	normals.push_back(CVector3(0, 1, 0));
	normals.push_back(CVector3(0, 1, 0));

	std::vector<math::CVector2> texCoords;
	texCoords.push_back(CVector2(0, 0));
	texCoords.push_back(CVector2(0, 1));
	texCoords.push_back(CVector2(1, 1));

	IObject *pTriObj = objectMgr->GreateTriangleMesh(vertices, indices, normals, texCoords);
	ISceneNode *pTriNode = scene->AddObject(pTriObj);
	float x = rand() % 10 - 5;
	float y = rand() % 10 - 5;
	float z = rand() % 10 - 5;
	//pTriNode->SetPosition(CVector3(x, y, z));
	pTriObj->SetAlbedo(.0f);

	long long next_game_tick = device->GetSystemRunTime();
	long long sleep_time = 0;
	int lastMouseX = -1;
	int lastMouseY = -1;
	IObject *pObject = nullptr;

	char buf[256] = { 0 };
	int delta = 0;
	bool bQuit = false;
	while (device->Run())
	{
		unsigned long long cur_time = device->GetSystemRunTime();
		sleep_time = next_game_tick - cur_time;
		if (sleep_time <= 0)
		{
			next_game_tick = device->GetSystemRunTime() + SKIP_TICKS;

			delta = SKIP_TICKS - sleep_time;

			sceneMgr->Update(delta);	

			sprintf_s(buf, "delta:%d frame:%d", delta, 1000 / delta);
			device->DrawString(0, 0, buf, strlen(buf));

			if (pEvent->IsPress(EKP_MOUSE_LBUTTON))
			{
				int x = pEvent->GetMousePositonX();
				int y = pEvent->GetMousePositionY();

				if (lastMouseX < 0)
				{
					lastMouseX = x;
				}
				if (lastMouseY < 0)
				{
					lastMouseY = y;
				}

				float deltaX = 15.f * (x - lastMouseX) / device->GetWindowWidth();
				float deltaY = 15.f * (y - lastMouseY) / device->GetWindowHeight();
				CRay ray = scene->GetCamera()->GetCameraRay(x, y, device->GetWindowWidth(), device->GetWindowHeight());
				 
				if (IObject *pObjectTemp = CTracer::GetObjectManager()->Trace(ray))
				{
					if (pObject == nullptr)
					{
						pObject = pObjectTemp;
					}
					CVector3 pos = pObject->GetSceneNode()->GetAbslutePosition();
					pos.x += deltaX;
					pos.y += -deltaY;
					pObject->GetSceneNode()->SetPosition(pos);

					lastMouseX = x;
					lastMouseY = y;
				}
			}
			else
			{
				pObject = nullptr;
				lastMouseX = -1;
				lastMouseY = -1;
			}

			CVector3 camPos = pCamera->GetPosition();
			float dt = 0.1f;
			if (pEvent->IsPress(EKP_KEYBOARD_W))
			{
				camPos.z -= dt;				
			}
			else if (pEvent->IsPress(EKP_KEYBOARD_A))
			{
				camPos.x -= dt;
			}
			else if (pEvent->IsPress(EKP_KEYBOARD_S))
			{
				camPos.z += dt;
			}
			else if (pEvent->IsPress(EKP_KEYBOARD_D))
			{
				camPos.x += dt;
			}

			pCamera->SetPosition(camPos);
		}
		else
		{
			device->Sleep(sleep_time);
		}
	}	
	return 0;
}