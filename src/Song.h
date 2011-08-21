#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>
using std::vector;

#include "NoteData.h"

class NotesLoader;

class Song {
public:
  friend class NotesLoader;

  Song();
  ~Song();

  std::string song_file_name() const { return song_file_name_; }
  void   set_song_file_name(std::string song_file_name) { song_file_name_ = song_file_name; }
  std::string main_title() const { return main_title_; }
  void   set_main_title(std::string main_title) { main_title_ = main_title; }
  std::string sub_title() const { return sub_title_; }
  void   set_sub_title(std::string sub_title) { sub_title_ = sub_title; }
  std::string artist() const { return artist_; }
  void   set_artist(std::string artist) { artist_ = artist; }
  std::string credit() const { return credit_; }
  void   set_credit(std::string credit) { credit_ = credit; }
  int    difficulty() { return difficulty_; }
  void   set_difficulty(int difficulty) { difficulty_ = difficulty; }
  std::string genre() { return genre_; }
  void   set_genre(std::string genre) { genre_ = genre; }
  double time() { return time_; }
  void   set_time(double time) { time_ = time; }
  NoteData &GetNote(int note_idx);
  NotesLoader *MakeLoader(const char *dir) const;

  Song &operator=(const Song &right);

private:
  /* depreciated */
  std::string song_file_name_;

  std::string main_title_;
  std::string sub_title_;
  std::string artist_;

  int    difficulty_;
  std::string genre_;
  /* This is read and saved, but never actually used. */
  std::string credit_;
  /* vector<Steps*> steps_; */
  /* vector<Steps*> steps_by_type_[NUM_STEPS_TYPES] */

  double time_;
  /* notes from files under the same song folder */
  vector<NoteData> alternatives_;
  /* int       alter_num_; */
};

#endif /* SONG_H */
