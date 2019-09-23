#include "Graphics.h"
#include "UtilMesh.h"
#include "App.h"
#include "main.h"
#include "Util.h"
#include "shaders.h"

extern const char *VSString;
extern const char *FSString;

Model screenQuadModel;
GLuint rayMarchProgram;
static float globalTime;

void App::Init(Context *context)
{
	Graphics::InitScreenQuadModel(&screenQuadModel, UtilMesh::MakeScreenQuad());
	Graphics::CreateProgram(&rayMarchProgram, VSString, FSString);

	Graphics::SetUniform1f(rayMarchProgram, 0.0f, "iGlobalTime");
	Graphics::SetUniform2f(rayMarchProgram, float(SCREEN_X), float(SCREEN_Y), "iResolution");

	// Lake shot for 1366
	context->cameraPosition = Vector3(43.6f, 5.5f, 14.5f);
	context->cameraTarget = Vector3(43.1f, 5.3f, 13.7f);
	context->cameraMaxSpeed = 6.0f;
	context->cameraForwardSpeed = 0.0f;
	context->cameraAcceleration = 4.5f;

	context->yaw = 0.0f;
	context->pitch = 0.0f;
	context->lookingDown = false;
}

void UpdateCamera(Context *context, float dt)
{
	static Vector3 previousPos = context->cameraPosition;
	static Vector3 previousTarget = context->cameraTarget;

	float rotationSpeed = 0.0004f;
	Vector2 mouseDelta = context->mousePosition - context->previousMousePosition;
	if (!context->lookingDown)
	{
		context->yaw += (mouseDelta.x) * -rotationSpeed;
		context->pitch += (mouseDelta.y) * -rotationSpeed;
	}

	// Rotation
	Vector3 cameraToTargetVector = context->cameraTarget - context->cameraPosition;
	float cameraDistance = Math::Length(cameraToTargetVector);
	cameraToTargetVector = Math::Normalize(cameraToTargetVector);
	Vector3 forward = cameraToTargetVector;
	Vector3 right = Math::CrossProduct(forward, Vector3(0, 1, 0));
	right = Math::Normalize(right);
	Vector3 up = Math::CrossProduct(right, forward);
	up = Math::Normalize(up);

	if (context->sPressed && !context->lookingDown)
	{
		context->storedCameraDirection = forward;
		context->lookingDown = true;
	}

	if (context->lookingDown)
	{
		if (context->sPressed)
		{
			if (Math::Dot(forward, Vector3(0, -1, 0)) < 0.4f)
			{
				context->pitch += dt * -0.05f;
			}	
		}
		else
		{
			if (Math::Dot(context->storedCameraDirection, cameraToTargetVector) < 0.99f)
			{
				context->pitch += dt * 0.05f;
			}
			else
			{
				context->lookingDown = false;
			}
		}
	}

	if (context->wPressed)	// Accelerate
	{
		context->cameraForwardSpeed = MIN(context->cameraForwardSpeed + context->cameraAcceleration *dt, context->cameraMaxSpeed);
	}
	else					// Deccelerate
	{
		context->cameraForwardSpeed = MAX(context->cameraForwardSpeed - context->cameraAcceleration *dt, 0.0f);
	}

	if (context->lookingDown)
	{
		context->cameraPosition += context->storedCameraDirection * context->cameraForwardSpeed * dt;
		context->cameraTarget += context->storedCameraDirection * context->cameraForwardSpeed * dt;
	}
	else
	{
		context->cameraPosition += forward * context->cameraForwardSpeed * dt;
		context->cameraTarget += forward * context->cameraForwardSpeed * dt;
	}

		// Rotation again
	Vector4 rotatedCameraToTargetVector = Math::GetRotation(context->pitch, right) *
	Math::GetRotation(context->yaw, Vector3(0, 1, 0)) * Vector4(cameraToTargetVector, 0.0f);

	context->cameraTarget = context->cameraPosition + Math::Normalize(Vector3(rotatedCameraToTargetVector)) * cameraDistance;
	context->previousMousePosition = context->mousePosition;

	context->yaw *= 0.93f;
	context->pitch *= 0.93f;

#ifdef _DEBUG
	static int  i = 0;
	if (i++ % 100 == 0)
	{
		Util::DebugOutput("POSx:%.1f y:%.1f z:%.1f\n", context->cameraPosition.x, context->cameraPosition.y, context->cameraPosition.z);
		Util::DebugOutput("TARx:%.1f y:%.1f z:%.1f\n", context->cameraTarget.x, context->cameraTarget.y, context->cameraTarget.z);
	}
#endif
}

void App::Update(Context *context, float dt)
{
	globalTime += dt;
	UpdateCamera(context, dt);

	Graphics::ClearScreen();
	Graphics::UseProgram(rayMarchProgram);

	Graphics::SetUniform1f(rayMarchProgram, globalTime, "iGlobalTime");
	Graphics::SetUniform3f(rayMarchProgram, context->cameraPosition, "iCamPos");
	Graphics::SetUniform3f(rayMarchProgram, context->cameraTarget, "iCamTarget");

	Graphics::RenderModel(&screenQuadModel);
}