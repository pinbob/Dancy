#ifndef NOTES_LOADER_H
#define NOTES_LOADER_H

/* class Song; */
/* class Steps; */
struct TapNote;
class NoteData;

class NotesLoader {
public:
  /* bool loadFromDir(const char *path, Song *output); */
  /**
   * Load notes from a .bms file, and store notes into output object
   * @param path path of the bms file
   * @param output the Steps object to be filled with notes info
   * @return true if succeeded, false otherwise
   **/
  bool LoadFromFile(const char *path, NoteData *note_data/*, Steps *output*/);

private:

  void MapBMSToNote(int panel, int &panel_out, TapNote &tap_note_out);
};

#endif /* NOTES_LOADER_H */
