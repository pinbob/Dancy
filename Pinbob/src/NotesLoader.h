#ifndef NOTES_LOADER_H
#define NOTES_LOADER_H

const int MAX_SONGS         = 10;
const int FILE_NAME_MAX_LEN = 256;

/* class Song; */
/* class Steps; */

struct TapNote;
class NoteData;
class SongCollection;

class NotesLoader {
public:
  NotesLoader();
  ~NotesLoader();
  /* bool loadFromDir(const char *path, Song *output); */
  
  /**
   * Load notes from a .bms file, and store notes into output object
   * @param path path of the bms file
   * @param output the Steps object to be filled with notes info
   * @return true if succeeded, false otherwise
   **/
  bool LoadFromFile(const char *path, NoteData *note_data, struct SongInfo &info);

  /**
   * List all available BMS file recursively in the given dir
   * @param path the Song directory which stores song folders
   */
  void ListAllSongs(const char *path, SongCollection *collection);
private:
  void MapBMSToNote(int panel, int &panel_out, TapNote &tap_note_out);

  /* store the song name of each song */
  char song_list_[MAX_SONGS][FILE_NAME_MAX_LEN];
  int  song_num_;
};

#endif /* NOTES_LOADER_H */
