//External includes
#include "SDL.h"
#include "SDL_surface.h"

//Project includes
#include "ERenderer.h"
#include "ERGBColor.h"

// Ray include 
#include "Ray.h"

// Scene includes

#include "SceneGraph.h"

// camera include
#include "PerspectiveCamera.h"

using namespace Elite;
Elite::Renderer::Renderer(SDL_Window * pWindow)
{
	//Initialize
	m_pWindow = pWindow;
	m_pFrontBuffer = SDL_GetWindowSurface(pWindow);
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
}

void Elite::Renderer::Render()
{
	SDL_LockSurface(m_pBackBuffer);
	
	// camera values
	float fov = PerspectiveCamera::GetInstance()->GetFov();
	float aspectRatio = PerspectiveCamera::GetInstance()->GetAspectRatio();
	const auto& primitives = SceneGraph::GetInstance()->GetObjects();
	const auto& lights = SceneGraph::GetInstance()->GetLights();
	//Loop over all the pixels
	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			auto cameraPosition = PerspectiveCamera::GetInstance()->GetPosition();

			Elite::FPoint3 screenSpacePos{ GetScreenSpace(c, r, aspectRatio, fov),-1 };
			auto screenSpacePosTranslated{ PerspectiveCamera::GetInstance()->TranslatePosition(screenSpacePos) };
			Ray ray{ cameraPosition,Elite::GetNormalized(screenSpacePosTranslated - cameraPosition) };
			//Ray ray{ FPoint3{GetScreenSpace(c,r),-1}, FVector3{0,0,-1} };
			HitRecord hitrecord;
			RGBColor FinalPixelColor{};
			RGBColor lightColor{};
			bool isHit = false;

			for (auto * object : primitives )
			{
				

				HitRecord temp;
				if (object->Hit(ray, temp,false))
				{
					if (temp.t < hitrecord.t)
					{
						isHit = true;

						hitrecord = temp;
					}
				}
			}
			if (isHit)
			{
				for (auto * l :lights )
				{
					bool shadowHit{ false };

					FVector3 lightDirection{ l->GetDirection(hitrecord.intersectionPoint) };
					float lambertCosine = Elite::Dot(hitrecord.normal, lightDirection);
					float lightDistance{ l->GetDistance(hitrecord.intersectionPoint) };
					if (ShadowsOn)
					{
						for (auto* primitive : primitives)
						{
							Ray shadowRay{ hitrecord.intersectionPoint ,lightDirection,0.0001f,lightDistance };
							HitRecord temp;

							if (primitive->Hit(shadowRay, temp, true))
							{

								if (temp.t < hitrecord.t)
								{
									shadowHit = true;
								}
							}
						}
						if (shadowHit)
						{
							continue;
						}
					}
					
					if (lambertCosine > 0)
					{
						RGBColor BRDF;
						switch (m_LightToggle)
						{
						case all:
							 BRDF = hitrecord.m_pMaterial->Shade(hitrecord.normal, -ray.direction, lightDirection);
							lightColor = l->GetBiRadiance(hitrecord.intersectionPoint);
							//lightColor.MaxToOne();

							FinalPixelColor += lightColor * BRDF * lambertCosine;
							break;
						case irradiance:
							 BRDF = hitrecord.m_pMaterial->Shade(hitrecord.normal, -ray.direction, lightDirection);

							FinalPixelColor +=  BRDF * lambertCosine;
							break;
						case brdf:
							
							lightColor = l->GetBiRadiance(hitrecord.intersectionPoint);
							FinalPixelColor += lightColor  * lambertCosine;
							break;
					
						}
						//RGBColor BRDF = hitrecord.m_pMaterial->Shade(hitrecord.normal, -ray.direction, lightDirection);
						//lightColor = l->GetBiRadiance(hitrecord.intersectionPoint) ;
						////lightColor.MaxToOne();

						//FinalPixelColor += lightColor * BRDF * lambertCosine;
						
					}
					
				}
				FinalPixelColor.MaxToOne();
			}
			
			//Fill the pixels - pixel access demo
			float cw = (255.0f / m_Width) * c;
			float ch = (255.0f / m_Height) * r;
			uint8_t uColor = static_cast<uint8_t>((cw + ch) / 2.0f);
			m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				static_cast<uint8_t>(FinalPixelColor.r * 255),
				static_cast<uint8_t>(FinalPixelColor.g * 255),
				static_cast<uint8_t>(FinalPixelColor.b * 255));
		}
	}

	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}
FPoint2 Elite::Renderer::GetScreenSpace(float c, float r, float aspectratio, float fov)
{
	FPoint2 screenspace;

	screenspace.x = (2.f * ((c + 0.5f) / float(m_Width)) - 1.f) * aspectratio * fov /* * aspectratio * fov*/;
	screenspace.y = (1.f - 2.f * ((r + 0.5f) / float(m_Height))) * fov;

	return screenspace;
}
void Elite::Renderer::ToggleShadows()
{
	switch (ShadowsOn)
	{
	case true:
		ShadowsOn = false;
		break;
	case false:
		ShadowsOn = true;
		break;
	}
}
void Elite::Renderer::ToggleLights()
{
	switch (m_LightToggle)
	{
	case all:
		m_LightToggle = irradiance;
		break;
	case irradiance:
		m_LightToggle = brdf;
		break;
	case brdf:
		m_LightToggle = all;
		break;
	}
}
bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}
