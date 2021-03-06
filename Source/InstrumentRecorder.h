/*
** FamiTracker - NES/Famicom sound tracker
** Copyright (C) 2005-2014  Jonathan Liss
**
** 0CC-FamiTracker is (C) 2014-2018 HertzDevil
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Library General Public License for more details.  To obtain a
** copy of the GNU Library General Public License, write to the Free
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
*/


#pragma once

#include "FamiTrackerDefines.h"
#include "APU/Types.h"
#include <memory>
#include <array>
#include <unordered_map>

class CSequence;
class CInstrument;
class CFamiTrackerModule;
class CSoundGen;
class CWnd;
enum class sequence_t : unsigned;

struct stRecordSetting {
	int Interval;
	int InstCount;
	bool Reset;
};

class CInstrumentRecorder
{
public:
	explicit CInstrumentRecorder(CSoundGen *pSG);
	~CInstrumentRecorder();

public:
	void			AssignModule(CFamiTrackerModule &modfile);

	void			StartRecording();
	void			StopRecording(CWnd *pView);
	void			RecordInstrument(const unsigned Tick, CWnd *pView);

	std::unique_ptr<CInstrument> GetRecordInstrument(unsigned Tick);
	stChannelID		GetRecordChannel() const;
	void			SetRecordChannel(stChannelID Channel);
	const stRecordSetting &GetRecordSetting() const;
	void			SetRecordSetting(const stRecordSetting &Setting);
	void			SetDumpCount(int Count) { m_iDumpCount = Count; }

	void			ResetDumpInstrument();
	void			ResetRecordCache();
	void			ReleaseCurrent();

private:
	void			InitRecordInstrument();
	void			FinalizeRecordInstrument();

	CFamiTrackerModule *m_pModule = nullptr;
	CSoundGen		*m_pSoundGen = nullptr;
	stChannelID		m_iRecordChannel;
	int				m_iDumpCount;
	std::unique_ptr<CInstrument> *m_pDumpInstrument = nullptr;
	std::array<std::unique_ptr<CInstrument>, MAX_INSTRUMENTS> m_pDumpCache = { };
	std::unordered_map<sequence_t, std::shared_ptr<CSequence>> m_pSequenceCache;
	stRecordSetting	m_stRecordSetting;
	std::unique_ptr<char[]> m_iRecordWaveCache;
	int				m_iRecordWaveSize;
	int				m_iRecordWaveCount;
};
