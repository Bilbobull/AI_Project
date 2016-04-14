#pragma once

#include <vector>
#include <deque>
#include "NoteFrequency.h"

typedef std::vector<Note> MajorScale;
typedef std::vector<Note> MinorScale;

static MajorScale Abmajor = {F2, G2, A2b, B2b, C3, D3b, E3b, F3, G3, A3b, B3b, C4, D4b, E4b, F4, G4, A4b, B4b, C5, D5b, E5b, F5, G5, A5b, B5b };
static MajorScale Amajor  = {F2f, G2f, A2, B2, C3f, D3, E3, F3f, G3f, A3, B3, C4f, D4, E4, F4f, G4f, A4, B4, C5f, D5, E5, F5f, G5f, A5, B5};
static MajorScale Bbmajor = {F2, G2, A2, B2b, C3, D3, E3b, F3, G3, A3, B3b, C4, D4, E4b, F4, G4, A4, B4b, C5, D5, E5b, F5, G5, A5, B5b };
static MajorScale Bmajor  = {F2f, G2f, A2f, B2, C3f, D3f, E3, F3f, G3f, A3f, B3, C4f, D4f, E4, F4f, G4f, A4f, B4, C5f, D5f, E5, F5f, G5f, A5f, B5 };
static MajorScale Cbmajor = {F2b, G2b, A2b, B2b, C3b, D3b, E3b, F3b, G3b, A3b, B3b, C4b, D4b, E4b, F4b, G4b, A4b, B4b, C5b, D5b, E5b, F5b, G5b, A5b, B5b };
static MajorScale Cmajor  = {F2, G2, A2, B2, C3, D3, E3, F3, G3, A3, B3, C4, D4, E4, F4, G4, A4, B4, C5, D5, E5, F5, G5, A5, B5 };
static MajorScale Cfmajor = {F2f, G2f, A2f, B2f, C3f, D3f, E3f, F3f, G3f, A3f, B3f, C4f, D4f, E4f, F4f, G4f, A4f, B4f, C5f, D5f, E5f, F5f, G5f, A5f, B5f };
static MajorScale Dbmajor = {F2, G2b, A2b, B2b, C3, D3b, E3b, F3, G3b, A3b, B3b, C4, D4b, E4b, F4, G4b, A4b, B4b, C5, D5b, E5b, F5, G5b, A5b, B5b };
static MajorScale Dmajor  = {F2f, G2, A2, B2, C3f, D3, E3, F3f, G3, A3, B3, C4f, D4, E4, F4f, G4, A4, B4, C5f, D5, E5, F5f, G5, A5, B5 };
static MajorScale Ebmajor = {F2, G2, A2b, B2b, C3, D3, E3b, F3, G3, A3b, B3b, C4, D4, E4b, F4, G4, A4b, B4b, C5, D5, E5b, F5, G5, A5b, B5b };
static MajorScale Emajor  = {F2f, G2f, A2, B2, C3f, D3f, E3, F3f, G3f, A3, B3, C4f, D4f, E4, F4f, G4f, A4, B4, C5f, D5f, E5, F5f, G5f, A5, B5 };
static MajorScale Fmajor  = {F2, G2, A2, B2b, C3, D3, E3, F3, G3, A3, B3b, C4, D4, E4, F4, G4, A4, B4b, C5, D5, E5, F5, G5, A5, B5b };
static MajorScale Ffmajor = {F2f, G2f, A2f, B2, C3f, D3f, E3f, F3f, G3f, A3f, B3, C4f, D4f, E4f, F4f, G4f, A4f, B4, C5f, D5f, E5f, F5f, G5f, A5f, B5 };
static MajorScale Gbmajor = {F2, G2b, A2b, B2b, C3b, D3b, E3b, F3, G3b, A3b, B3b, C4b, D4b, E4b, F4, G4b, A4b, B4b, C5b, D5b, E5b, F5, G5b, A5b, B5b };
static MajorScale Gmajor  = {F2f, G2, A2, B2, C3, D3, E3, F3f, G3, A3, B3, C4, D4, E4, F4f, G4, A4, B4, C5, D5, E5, F5f, G5, A5, B5 };

static MinorScale Abminor = Cbmajor;
static MinorScale Aminor  = Cmajor;
static MinorScale Afminor = Cfmajor;
static MinorScale Bbminor = Dbmajor;
static MinorScale Bminor  = Dmajor;
static MinorScale Cminor  = Ebmajor;
static MinorScale Cfminor = Emajor;
static MinorScale Dminor  = Fmajor;
static MinorScale Dfminor = Ffmajor;
static MinorScale Ebminor = Gbmajor;
static MinorScale Eminor  = Gmajor;
static MinorScale Fminor  = Abmajor;
static MinorScale Ffminor = Amajor;
static MinorScale Gminor  = Bmajor;
static MinorScale Gbminor = Bbmajor;

static int GetDistanceBetweenNotes(std::vector<Note>& scale, Note a1, Note a2) {
	// Make a1 the lowest
	if (a1 > a2) {
		auto a3 = a2;
		a2 = a1;
		a1 = a3;
	}
	
	auto it1 = std::find(scale.begin(), scale.end(), a1);
	auto it2 = std::find(scale.begin(), scale.end(), a2);

	_ASSERT(it1 != scale.end());
	_ASSERT(it2 != scale.end());

	return std::distance(it1, it2);
}

static std::deque<Note> GetNotesBetweenVoices(std::vector<Note>& scale, Note a1, Note a2) {
	std::deque<Note> list;

	// Make a1 the lowest
	if (a1 > a2) {
		auto a3 = a2;
		a2 = a1;
		a1 = a3;
	}

	auto it1 = std::find(scale.begin(), scale.end(), a1);
	auto it2 = std::find(scale.begin(), scale.end(), a2);

	_ASSERT(it1 != scale.end());
	_ASSERT(it2 != scale.end());

	if (it1 == it2) {
		return list;
	}

	// Add all notes in range to the list
	while (it1 < it2) {
		list.push_back(*it1);
		++it1;
	}

	return list;
}