#pragma once

class Voice{
public:

  Note getHighestRelatedNote() { return mRelatedHighestNote; };
  Note getLowestRelatedNote() { return mRelatedLowestNote; };
  void setHighestRelatedNote(Note note) { mRelatedHighestNote = note; };
  void setLowestRelatedNote(Note note) { mRelatedLowestNote = note; };

  Note getHighestNoteRange() { return mRangeHighestNote; };
  Note getLowestNoteRange() { return mRangeLowestNote; };
  void setHighestNoteRange(Note note) { mRangeHighestNote = note; };
  void setLowestNoteRange(Note note) { mRangeLowestNote = note; };

private:
  Note mRangeHighestNote;
  Note mRangeLowestNote;
  Note mRelatedHighestNote;
  Note mRelatedLowestNote;
};