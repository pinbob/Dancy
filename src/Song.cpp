#include <cstring>
#include "./Song.h"

Song::Song() {}

Song::~Song() {
  // if (alternatives_ != 0)
  //   delete[](alternatives_);
}

NoteData &Song::GetNote(int note_idx) {
  return alternatives_[note_idx];
}

Song &Song::operator=(const Song &right) {
  song_file_name_ = right.song_file_name_;
  main_title_ = right.main_title_;
  sub_title_ = right.sub_title_;
  artist_ = right.artist_;
  difficulty_ = right.difficulty_;
  genre_ = right.genre_;
  credit_ = right.credit_;
  this->time_ = right.time_;
  alternatives_.resize(right.alternatives_.size());
  memcpy(&alternatives_[0], &right.alternatives_[0], right.alternatives_.size() * sizeof(NoteData));
  return *this;
}
