#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>
using std::vector;
using std::string;

#include "NoteData.h"

class NotesLoader;

class Song {
public:
  friend class NotesLoader;

  Song();
  ~Song();

  string song_file_name() const { return song_file_name_; }
  void   set_song_file_name(string song_file_name) { song_file_name_ = song_file_name; }
  string main_title() const { return main_title_; }
  void   set_main_title(string main_title) { main_title_ = main_title; }
  string sub_title() const { return sub_title_; }
  void   set_sub_title(string sub_title) { sub_title_ = sub_title; }
  string artist() const { return artist_; }
  void   set_artist(string artist) { artist_ = artist; }
  string credit() const { return credit_; }
  void   set_credit(string credit) { credit_ = credit; }
  int    difficulty() { return difficulty_; }
  void   set_difficulty(int difficulty) { difficulty_ = difficulty; }
  string genre() { return genre_; }
  void   set_genre(string genre) { genre_ = genre; }

  NoteData &GetNote(int note_idx);
  NotesLoader *MakeLoader(const char *dir) const;

  Song &operator=(const Song &right);

private:
  /* depreciated */
  string song_file_name_;

  string main_title_;
  string sub_title_;
  string artist_;

  int    difficulty_;
  string genre_;
  /* This is read and saved, but never actually used. */
  string credit_;
  /* vector<Steps*> steps_; */
  /* vector<Steps*> steps_by_type_[NUM_STEPS_TYPES] */

  /* notes from files under the same song folder */
  vector<NoteData> alternatives_;
  /* int       alter_num_; */
};

#endif /* SONG_H */
