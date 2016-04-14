#pragma once
#include "Variables.h"

float shoft_loud = 0.5f;
int major_minor = 0;
float staccato_legato = 0.5f;
int phrase_length = 12;
int voice_melody = 0;
int time_signature = 1;
int BPM = 80;
float happiness = 0.5f;
float peacefulness = 0.5f;
float heart = 0.5f;
float relax = 0.5f;

float* GetSoftness() { return &shoft_loud; }
int* GetMajor() { return &major_minor; }
float* GetStaccato() { return &staccato_legato; }
int* GetPhraseLength() { return &phrase_length; }
int* GetVoiceMelody() { return &voice_melody; }
int* GetTimeSignature() { return &time_signature; }
int* GetBPM() { return &BPM; }
float* GetHappiness() { return &happiness; }
float* GetPeacefulness() { return &peacefulness; }
float* GetHeartness() { return &heart; }
float* GetRelax() { return &relax; }