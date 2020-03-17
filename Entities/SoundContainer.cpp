#include "SoundContainer.h"
#include "RTETools.h"

namespace RTE {

	CONCRETECLASSINFO(SoundContainer, Entity, 0);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void SoundContainer::Clear() {
		m_Sounds.clear();
		m_CurrentSound = 0;
		m_PlayingChannels.clear();
		m_Loops = 0;
		m_Priority = AudioMan::PRIORITY_LOW;
		m_AffectedByPitch = true;
		m_Hash = 0;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int SoundContainer::Create(const SoundContainer &reference) {
		Entity::Create(reference);

		for (std::vector<std::pair<ContentFile, FMOD::Sound *>>::const_iterator itr = reference.m_Sounds.begin(); itr != reference.m_Sounds.end(); ++itr) {
			m_Sounds.push_back(*itr);
		}

		m_CurrentSound = reference.m_CurrentSound;
		m_PlayingChannels.clear();
		m_Loops = reference.m_Loops;
		m_Priority = reference.m_Priority;
		m_AffectedByPitch = reference.m_AffectedByPitch;
		m_Hash = reference.m_Hash;

		return 0;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int SoundContainer::Create(std::string samplePath, bool affectedByPitch, int loops) {
		AddSound(samplePath);
		m_AffectedByPitch = affectedByPitch;
		m_Loops = loops;

		return 0;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int SoundContainer::ReadProperty(std::string propName, Reader &reader) {
		if (propName == "AddSample" || propName == "AddSound") {
			ContentFile newFile;
			reader >> newFile;
			m_Hash = newFile.GetHash();

			FMOD::Sound *pNewSample = newFile.GetAsSample();
			if (!pNewSample) {
				reader.ReportError(std::string("Failed to load the sample from the file"));
			}
			m_Sounds.push_back(std::pair<ContentFile, FMOD::Sound *>(newFile, pNewSample));
		} else if (propName == "LoopSetting")
			reader >> m_Loops;
		else if (propName == "Priority")
			reader >> m_Priority;
		else if (propName == "AffectedByPitch")
			reader >> m_AffectedByPitch;
		else
			// See if the base class(es) can find a match instead
			return Entity::ReadProperty(propName, reader);

		return 0;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int SoundContainer::Save(Writer &writer) const {
		return 0;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void SoundContainer::Destroy(bool notInherited) {
		// Don't delete Sounds since they are owned in the ContentFile static maps
		if (!notInherited) {
			Entity::Destroy();
		}
		Clear();
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void SoundContainer::AddSound(std::string soundPath) {
		ContentFile newFile(soundPath.c_str());
		m_Hash = newFile.GetHash();

		FMOD::Sound *pNewSample = newFile.GetAsSample();
		RTEAssert(pNewSample, "Failed to load the sample from the file");
		m_Sounds.push_back(std::pair<ContentFile, FMOD::Sound *>(newFile, pNewSample));
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void SoundContainer::SetLoopSetting(int loops) {
		for (std::vector<std::pair<ContentFile, FMOD::Sound * >>::const_iterator itr = m_Sounds.begin(); itr != m_Sounds.end(); ++itr) {
			FMOD_RESULT result = itr->second->setMode((loops == 0 || loops == 1) ? FMOD_LOOP_OFF : FMOD_LOOP_NORMAL);
			result = itr->second->setLoopCount(loops);
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	FMOD::Sound *SoundContainer::SelectNextSound() {
		int soundCount = GetSoundCount();
		if (soundCount == 2) {
			m_CurrentSound = m_CurrentSound == 0 ? 1 : 0; // Alternate between 2 sounds
		} else if (soundCount > 2) {
			int lastSound = m_CurrentSound;
			m_CurrentSound = floorf((float)soundCount * PosRand());
			// Mix it up again if we got the same sound twice
			while (m_CurrentSound == lastSound) {
				m_CurrentSound = floorf((float)soundCount * PosRand());
			}
		}
		RTEAssert(m_CurrentSound >= 0 && m_CurrentSound < soundCount, "Sample index is out of bounds!");
		
		FMOD::Sound *soundToStart;
		return m_Sounds[m_CurrentSound].second;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void SoundContainer::FadeOut(int fadeOutTime) {
		if (HasAnySounds()) {
			return g_AudioMan.FadeOutSound(this, fadeOutTime);
		}
	}
}
