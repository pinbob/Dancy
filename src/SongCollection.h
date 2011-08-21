#ifndef SONG_COLLECTION_H
#define SONG_COLLECTION_H

#include <vector>
using std::vector;

#include "NoteData.h"


class Song;
class NoteData;
class NotesLoader;

class SongCollection {
public:
  friend class NotesLoader;
  SongCollection();
  ~SongCollection();

  const vector<Song> &song_list();
  void LoadSongs(const char *path);
  
  NoteData &GetNote(int song_idx, int note_idx);
  SongInfo  GetSongInfo(int song_idx);
  Song     &GetSong(int idx);
private:
  vector<Song> song_list_;
  int          song_num_;
};

#endif /* SONG_COLLECTION_H */
