#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <dirent.h>

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

#include "./note_config.h"
#include "./NotesLoader.h"
#include "./NoteData.h"
#include "./NoteTypes.h"
#include "./SongCollection.h"
#include "./Song.h"

using std::ifstream;
using std::string;
using std::vector;

///////////////////
// BMS encoding: //
// 5 panel       //
// Left :   11   //
// Down :   13   //
// Up   :   15   //
// Right:   16   //
// BPM  :  03/08 //
///////////////////

enum {
  BMS_NULL_COL = 0,
  BMS_LEFT,
  BMS_DOWN,
  BMS_UP,
  BMS_RIGHT,
  BMS_BPM
};

NotesLoader::NotesLoader(): song_num_(0) {}

NotesLoader::~NotesLoader() {
}


void NotesLoader::MapBMSToNote(int panel, int &panel_out, TapNote &tap_note_out) {
  if (panel  > 40) {
    tap_note_out = TAP_ORIGINAL_HOLD_HEAD;
    panel -= 40;
  } else {
    tap_note_out = TAP_ORIGINAL_TAP;
  }
  switch (panel) {
    case 3 :
    case 8 : panel_out = BMS_BPM;   break;
    case 11: panel_out = BMS_LEFT;  break;
    case 13: panel_out = BMS_DOWN;  break;
    case 15: panel_out = BMS_UP;    break;
    case 16: panel_out = BMS_RIGHT; break;
    default: panel_out = -1;        break;
  }
}


bool NotesLoader::LoadFromFile(const char *path, NoteData *note_data/*, Steps *output*/, struct SongInfo &info) {
  // NoteData *note_data = new NoteData;
  note_data->set_num_panels(MAX_NOTE_PANELS);
  // ResetPanelsMagic();

  ifstream file_reader;
  char *stop;
  // file_reader.open("OBLIVION_7a.bms", ifstream::in);
  // printf("%s\n", path);
  file_reader.open(path, ifstream::in);

  if (!file_reader.good()) {
    printf("fail to open file: %s\n", path);
    return false;
  }

  while (file_reader.good()) {
    string line;
    if (getline(file_reader, line).bad()) {
      delete note_data;
      return false;
    }

    string key;
    string value;

    /* find the first appearance of delimiter, otherwise string::npos */
    size_t first_colon = line.find(':');
    size_t first_space = line.find(' ');

    size_t index_of_separator = min(first_colon, first_space);

    if (index_of_separator != string::npos) {
      /* with separator */
      key = line.substr(0, index_of_separator);
      value = line.substr(index_of_separator + 1);
    } else {
      /* no separator */
      key = line;
    }
    // Done splitting 1 line

    if (line.find("#TITLE") != string::npos) {
      info.title_ = value;
    } else if (line.find("#GENRE") != string::npos) {
      info.genre_ = value;
    } else if (line.find("#ARTIST") != string::npos) {
      info.artist_ = value;
    } else if (line.find("#DIFFICULTY") != string::npos) {
      info.difficulty_ = atoi(value.c_str());
    } else if (line.find("#BPM") != string::npos) {
      // if (isint(key[4])
          // register preset bpm
          // && isint(key[5])
          // && first_space != string::npos) {
      if (key.length() > 4) {
        note_data->insert_preset_bpm(strtol(key.substr(4, 2).c_str(), &stop, 16),
                                     atof(value.c_str()));
      } else {
        // set default bpm
        note_data->set_bpm(atof(value.c_str()));
      }
    }

    // Main data field
    if (key.length() >= 6 && key[0] == '#'
        && isint(key[1]) && isint(key[2])
        && isint(key[3]) && isint(key[4])
        && isint(key[5])) {
      int measure_num = atoi(key.substr(1, 3).c_str());
      int panel_num = atoi(key.substr(4, 2).c_str());
      // PushPanelNumForMagic(panel_num);

      vector<bool> notes_array;      // split notes by 2 digits
      for (int i = 0; i < (int)value.length(); i += 2) {
        static bool is_note;
        string sub = value.substr(i, 2);
        is_note = (sub != "00");
        if (sub == "\r" || sub == "" || sub == "\n" || sub == "\n\r")
          continue;
        notes_array.push_back(is_note);
      }

      /* number of notes in a measure */
      const unsigned int note_num_in_this_measure = notes_array.size();

      for (int i = 0; i < (int)note_num_in_this_measure; i++) {
        if (notes_array[i]) {
          
          // If this is a valid note and not "00"
          // then calculate the percent of the note in this measure
          float percent = (float)i / (float)note_num_in_this_measure;

          /**
           * unify index to rows, leaving intervals TAP_EMPTY
           * - In this stage, variable BPM is not considered
           **/
          const int note_row = (int)((measure_num + percent) * BEATS_PER_MEASURE * ROWS_PER_BEAT);

          /* map panel_num [1-4] -> direction(1-4) */
          int direction;
          TapNote tap_note;

          MapBMSToNote(panel_num, direction, tap_note);

          // std::cout << note_num_in_this_measure << ' ' << i << ' ' <<  measure_num << ' ' << direction << ' ' << note_row << std::endl;
          if (direction == BMS_BPM) {
            if (panel_num == 3)
              note_data->set_cur_bpm(strtol(value.substr(2*i, 2).c_str(), &stop, 16));
            else {
              // when panel_num = 8
              // set the preset bpm
              int preset_num = strtol(value.substr(2*i, 2).c_str(), &stop, 16);
              note_data->set_cur_bpm(note_data->preset_bpm(preset_num));
            }
          } else {
            // set current bpm to default
            note_data->set_cur_bpm(note_data->cur_bpm());
          }
          if (direction != -1) {
            note_data->set_tap_note(direction - 1, note_row, tap_note);
          } 
        }
      }
    }
  }
  return true;
}

void NotesLoader::ListAllSongs(const char *path, SongCollection *collection) {
  DIR           *d;                     // directory file descriptor
  struct dirent *dir;                   // directory struct
  NoteData       data;                  // temporary data to hole note data

  // Look for song folders in the given directory
  d = opendir(path);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type == DT_DIR
          && strcmp(dir->d_name, "..") != 0
          && strcmp(dir->d_name, ".") != 0) {
        strncpy(song_list_[song_num_], dir->d_name, FILE_NAME_MAX_LEN - 1);
        ++song_num_;
      }
    }
    closedir(d);
  } else {
    perror(path);
    return;
  }
  
  char *sub_dir;
  
  // For every song folder, search for its different bms files
  // and add them to the NoteData array in Class Song
  // +2 BECAUSE strlen doesn't include the empty char
  for (int i = 0; i < song_num_; ++i) {
    int len = strlen(path) + strlen(song_list_[i]) + 2;
    sub_dir = new char[len];
    memset(sub_dir, 0, sizeof(char) * len);
    strncpy(sub_dir, path, strlen(path));
    strncat(sub_dir, "/", 1);
    d = opendir(strncat(sub_dir, song_list_[i], strlen(song_list_[i])));

    // count total files in the folder
    int bms_file_count = 0;

    // temp array to store NoteData
    NoteData notes_of_a_song[10];
    struct SongInfo info;
    // Load bms files(regular file REG) in the same song folder
    if (d) {
      while ((dir = readdir(d)) != NULL) {
        // readin *.bms 
        if (dir->d_type == DT_REG
            && strcmp(dir->d_name + strlen(dir->d_name) - 4, ".bms") == 0) {
          char *file_dir = new char[len + strlen(dir->d_name) + 1];
          memset(file_dir, 0, sizeof(char) * (len + strlen(dir->d_name) + 1));
          strncpy(file_dir, sub_dir, strlen(sub_dir));
          strncat(file_dir, "/", 1);
          strncat(file_dir, dir->d_name, strlen(dir->d_name));

          LoadFromFile(file_dir, &notes_of_a_song[bms_file_count], info);
          delete[](file_dir);
          ++bms_file_count;
        }
      }
    }

    closedir(d);
    
    Song song;
    
    // copy temp note data into song object
    for (int i = 0; i < bms_file_count; ++i) {
      song.alternatives_.push_back(notes_of_a_song[i]);
    }
    song.main_title_ = info.title_;
    song.artist_ = info.artist_;
    song.genre_ = info.genre_;
    song.difficulty_ = info.difficulty_;

    // MUST HAVE AT LEAST ONE SONG
    OggVorbis_File ov;
    FILE *fd;

    char *song_name = new char[strlen(sub_dir) + 8];
    memset(song_name, 0, sizeof(char) * (strlen(sub_dir) + 8));
    strncpy(song_name, sub_dir, strlen(sub_dir));
    fd = fopen(strncat(song_name, "/01.ogg", 7), "rb");
    if (ov_open_callbacks(fd, &ov, NULL, -1, OV_CALLBACKS_NOCLOSE) < 0) {
      perror("Could not open input as an OggVorbis file.\n:");
      perror(song_name);
      delete[](song_name);
      return;
    }
    delete[](song_name);

    song.set_time(ov_time_total(&ov, -1));
    fclose(fd);
    ov_clear(&ov);
    
    // printf("time total: %f", ov_time_total(&ov, -1));

    // add one song to the song collection
    collection->song_list_.push_back(song);
    // printf("%d\n", collection->song_list().size());
    delete[](sub_dir);
  }
}

