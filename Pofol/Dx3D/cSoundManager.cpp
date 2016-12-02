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
	//���� ����
	System_Create(&_system);

	//���� ä�μ� ����
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//����, ä�� �����Ҵ�
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	//�޸� �ʱ�ȭ
	memset(_sound, 0, sizeof(Sound*)* (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*)* (TOTALSOUNDBUFFER));

	return S_OK;
}

void cSoundManager::release(void)
{
	//���� �� ä�� ����
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

	//�޸� �����
	SAFE_DELETE(_channel);
	SAFE_DELETE(_sound);

	//�ý��� �ݱ�
	if (_system = NULL)
	{
		_system->release();
		_system->close();
	}

}

void cSoundManager::update(void)
{
	//���� �ý����� ��� ������Ʈ ����� ������ �ٲ�ų�,
	//����� ���� ���带 ü�ο��� �����µ� �پ��� �۾���
	//�̷�����.

	//���ΰ��ӿ��� ���� �Ŵ����� ��������
	_system->update();
}

void cSoundManager::render(void)
{

}

//���� �߰�(Ű��, �����̸�, bgm, loop)
void cSoundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)//��� or ����Ʈ
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

	//�ʿ� ���带 Ű���� �Բ�����ش�
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

//���� �÷���(Ű��, ����)0.0f~ 1.0f
void cSoundManager::play(string keyName, float volume)
{
	int count = 0;

	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second,
				false, &_channel[count]);
			//���� ����
			_channel[count]->setVolume(volume);
		}
	}
}

//���� ����
void cSoundManager::stop(string keyName)
{
	int count = 0;

	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[count]->stop();
			break;
		}
	}
}

//���� �Ͻ�����
void cSoundManager::pause(string keyName)
{
	int count = 0;

	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �Ͻ� ����
			_channel[count]->setPaused(true);
			break;
		}
	}
}

//���� �ٽ����
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

//�÷��� ���̳�?
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

//�Ͻ����� ���̳�?
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