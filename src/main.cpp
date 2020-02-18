#include <gba_systemcalls.h>
#include "register.h"
#include "Engine.h"

#include "Palette.h"
#include "Scene.h"
#include "SceneAnimation.h"
#include "SceneFade.h"
#include "SceneWait.h"

EWRAM_DATA Engine engine;

void introTask()
{
	//engine.pushScene(new SceneFade(nullptr, BLACK, FadeType::REVERSE));
	//engine.pushScene(new SceneWait(20));
	//engine.pushScene(new SceneFade("intro1_fade", BLACK, FadeType::NORMAL));
	//engine.pushScene(new SceneAnimation("intro1_anim"));
	//engine.pushScene(new SceneWait(80));
	//engine.pushScene(new SceneFade(nullptr, BLANK, FadeType::REVERSE));
	engine.pushScene(new SceneAnimation("intro2_anim"));
	engine.pushScene(new SceneAnimation("intro3_anim"));
	engine.pushScene(new SceneAnimation("intro4_anim"));
}

int main(void)
{
	RegisterRamReset(RESET_PALETTE | RESET_OAM | RESET_VRAM | RESET_SOUND);
	SYS.WAITCNT = PREFETCH_ENABLE | WS0_S_1 | WS0_N_3;

	Palette::FillBuffer(BLANK);
	Palette::Flush();

	Engine::initOAM();
	Engine::initInterrupt();

	//engine.pushScene(new SceneFade("copyright", BLANK, FadeType::NORMAL));
	engine.pushScene(new SceneWait(10, introTask));
	engine.popScene();
		
	while(true)
	{
		VBlankIntrWait();
		if(Engine::scene)
		{
			Engine::scene->update();
			Sprite::sorter.sort();
			Engine::updater.update();
		}
	}
}
