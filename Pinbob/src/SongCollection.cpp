#include "./SongCollection.h"
#include "./Song.h"
#include "./NotesLoader.h"
#include "./NoteData.h"
#include <vector>
using std::vector;

SongCollection::SongCollection() {}

SongCollection::~SongCollection() {}

const vector<Song> &SongCollection::song_list() {
  return song_list_;
}
void SongCollection::LoadSongs(const char *path) {
  NotesLoader loader;
  loader.ListAllSongs(path, this);
}

NoteData &SongCollection::GetNote(int song_idx, int note_idx) {
  return song_list_[song_idx].GetNote(note_idx);
}

SongInfo SongCollection::GetSongInfo(int song_idx) {
  Song &song = song_list_[song_idx];
  return SongInfo{ song.main_title(),
      song.genre(),
      song.artist(),
      song.difficulty() };
}

Song &SongCollection::GetSong(int idx) {
  return song_list_[idx];
}
