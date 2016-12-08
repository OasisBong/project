#include "stdafx.h"
#include "cSoundManager.h"



cSoundManager::cSoundManager()
{
}


cSoundManager::~cSoundManager()
{
}

HRESULT cSoundManager::init(void)
{
	//사운드 생성
	System_Create(&_system);

	//사운드 채널수 생성
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//사운드, 채널 동적할당
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	//메모리 초기화
	memset(_sound, 0, sizeof(Sound*)* (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*)* (TOTALSOUNDBUFFER));

	return S_OK;
}

void cSoundManager::release(void)
{
	//사운드 및 채널 삭제
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	//메모리 지우기
	SAFE_DELETE(_channel);
	SAFE_DELETE(_sound);

	//시스템 닫기
	if (_system = NULL)
	{
		_system->release();
		_system->close();
	}

}

void cSoundManager::update(void)
{
	//사운드 시스템을 계속 업데이트 해줘야 볼륨이 바뀌거나,
	//재생이 끝난 사우드를 체널에서 빼내는등 다양한 작업이
	//이뤄진다.

	//매인게임에서 사운드 매니져를 업뎃하자
	_system->update();
}

void cSoundManager::render(void)
{

}

//사운드 추가(키값, 파일이름, bgm, loop)
void cSoundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)//브금 or 이펙트
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(),
				FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(),
				FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		_system->createSound(soundName.c_str(),
			FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	//맵에 사운드를 키값과 함께담아준다
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

//사운드 플레이(키값, 볼륨)0.0f~ 1.0f
void cSoundManager::play(string keyName, float volume)
{
	int count = 0;

	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second,
				false, &_channel[count]);
			//볼륨 세팅
			_channel[count]->setVolume(volume);
		}
	}
}

//사운드 정지
void cSoundManager::stop(string keyName)
{
	int count = 0;

	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			_channel[count]->stop();
			break;
		}
	}
}

//사운드 일시정지
void cSoundManager::pause(string keyName)
{
	int count = 0;

	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 일시 정지
			_channel[count]->setPaused(true);
			break;
		}
	}
}

//사운드 다시재생
void cSoundManager::resume(string keyName)
{
	int count = 0;

	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
		}
	}
}

//플레이 중이냐?
bool cSoundManager::isPlaySound(string keyName)
{
	int count = 0;
	bool isPlay;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

//일시정지 중이냐?
bool cSoundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;

	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPause); 
			break;
		}
	}

	return isPause;
}