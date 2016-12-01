#pragma once

#define g_pSkinnedMeshManager cSkinnedMeshManager::GetInstance()

class cSkillManager
{
public:
	SINGLETONE(cSkinnedMeshManager);

	void Destroy()
};