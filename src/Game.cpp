#include <iostream>
#include <cmath>

#include "Tools.hpp"
#include "TN.hpp"

int main(int argc, char* argv[]){

    nx::gfxInit(150, 150, 8, 8);

    nx::Bitmap map, sky;

    map.load("data/texture/map.png");
    sky.load("data/texture/sky.png");

	float fWorldX = 1000.0f;
	float fWorldY = 1000.0f;
	float fWorldA = 0.1f;
	float fNear = 0.005f;
	float fFar = 0.03f;
	float fFoVHalf = 3.14159f / 4.0f;


    // int x = 0;
    // int y = 0;    
    // float angle = 0;

    // int r = ((nx::gfxSize().x + nx::gfxSize().y)/ 2)/2;

    while(nx::isRunning()){

        // x += std::cos(angle) * static_cast<float>(r);
        // y += std::sin(angle) * static_cast<float>(r);
        // angle += nx::Math::rads(45  * nx::gfxDelta());
        // printf("%f\n", nx::Math::rads(5));

        // nx::Draw::Line(nx::gfxSize().x / 2, nx::gfxSize().y / 2, x, y, nx::Pixel(255, 0, 0, 255));
        

        static const float speedo = 0.25f;
        static const float turnSpeedo = 1.0f;
        auto screenSize = nx::gfxSize();


		if (nx::kbCheck(nx::keyQ)) fNear += speedo * nx::gfxDelta();
		if (nx::kbCheck(nx::keyA)) fNear -= speedo * nx::gfxDelta();

		if (nx::kbCheck(nx::keyW)) fFar += speedo * nx::gfxDelta();
		if (nx::kbCheck(nx::keyS)) fFar -= speedo * nx::gfxDelta();

		if (nx::kbCheck(nx::keyZ)) fFoVHalf += speedo * nx::gfxDelta();
		if (nx::kbCheck(nx::keyX)) fFoVHalf -= speedo * nx::gfxDelta();
        

		float fFarX1 = fWorldX + std::cos(fWorldA - fFoVHalf) * fFar;
		float fFarY1 = fWorldY + std::sin(fWorldA - fFoVHalf) * fFar;

		float fNearX1 = fWorldX + std::cos(fWorldA - fFoVHalf) * fNear;
		float fNearY1 = fWorldY + std::sin(fWorldA - fFoVHalf) * fNear;

		float fFarX2 = fWorldX + std::cos(fWorldA + fFoVHalf) * fFar;
		float fFarY2 = fWorldY + std::sin(fWorldA + fFoVHalf) * fFar;

		float fNearX2 = fWorldX + std::cos(fWorldA + fFoVHalf) * fNear;
		float fNearY2 = fWorldY + std::sin(fWorldA + fFoVHalf) * fNear;

		for (int y = 0; y < screenSize.y / 2; y++)
		{
			// Take a sample point for depth linearly related to rows down screen
			float fSampleDepth = (float)y / ((float)screenSize.y / 2.0f);		

			// Use sample point in non-linear (1/x) way to enable perspective
			// and grab start and end points for lines across the screen
			float fStartX = (fFarX1 - fNearX1) / (fSampleDepth) + fNearX1;
			float fStartY = (fFarY1 - fNearY1) / (fSampleDepth) + fNearY1;
			float fEndX = (fFarX2 - fNearX2) / (fSampleDepth) + fNearX2;
			float fEndY = (fFarY2 - fNearY2) / (fSampleDepth) + fNearY2;

			// Linearly interpolate lines across the screen
			for (int x = 0; x < screenSize.x; x++)
			{
				float fSampleWidth = (float)x / (float)screenSize.x;
				float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
				float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;

				// Wrap sample coordinates to give "infinite" periodicity on maps
				fSampleX = std::fmod(fSampleX, 1.0f);
				fSampleY = std::fmod(fSampleY, 1.0f);

				// Sample symbol and colour from map sprite, and draw the
				// pixel to the screen
				// wchar_t sym = sprGround->SampleGlyph(fSampleX, fSampleY);
				// short col = sprGround->SampleColour(fSampleX, fSampleY);

                auto gspixel = map.sample(fSampleX * map.size.x, fSampleY * map.size.y);

				nx::Draw::Pixel(x, y + (screenSize.y / 2), gspixel);		

        


				// Sample symbol and colour from sky sprite, we can use same
				// coordinates, but we need to draw the "inverted" y-location
				// sym = sprSky->SampleGlyph(fSampleX, fSampleY);
				// col = sprSky->SampleColour(fSampleX, fSampleY);
                auto sspixel = sky.sample(fSampleX * sky.size.x, fSampleY * sky.size.y);

				nx::Draw::Pixel(x, (screenSize.y / 2) - y, sspixel);
			}
		}

        nx::Draw::Line(0, screenSize.y / 2.0f, screenSize.x, screenSize.y / 2.0f, nx::Pixel(0, 0, 0, 255));

		if (nx::kbCheck(nx::keyLEFT))

			fWorldA -= turnSpeedo * nx::gfxDelta();

		if (nx::kbCheck(nx::keyRIGHT))

			fWorldA += turnSpeedo * nx::gfxDelta();

		if (nx::kbCheck(nx::keyUP))
		{

			fWorldX += std::cos(fWorldA) * speedo * nx::gfxDelta();
			fWorldY += std::sin(fWorldA) * speedo * nx::gfxDelta();
		}

		if (nx::kbCheck(nx::keyDOWN))
		{
			fWorldX -= std::cos(fWorldA) * speedo * nx::gfxDelta();
			fWorldY -= std::sin(fWorldA) * speedo * nx::gfxDelta();
		}

        // nx::Draw::Bitmap(&map, nx::v2<int>(0), map.size, nx::v2<float>(0.5f), 0);


        nx::gfxDraw();
    }
    
    nx::gfxEnd();

    return 0;
}