#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "./note_config.h"
#include "./NotesLoader.h"
#include "./NoteData.h"
#include "./NoteTypes.h"

using std::ifstream;
using std::string;
using std::vector;

///////////////////
// BMS encoding: //
// 4 panel       //
// Left :    11  //
// Down :    13  //
// Up   :    15  //
// Right:    16  //
///////////////////

enum {
  BMS_NULL_COL = 0,
  BMS_LEFT,
  BMS_DOWN,
  BMS_UP,
  BMS_RIGHT
};



void NotesLoader::MapBMSToNote(int panel, int &panel_out, TapNote &tap_note_out) {
  if (panel  > 40) {
    tap_note_out = TAP_ORIGINAL_HOLD_HEAD;
    panel -= 40;
  } else {
    tap_note_out = TAP_ORIGINAL_TAP;
  }
  switch (panel) {
    case 11: panel_out = BMS_LEFT;  break;
    case 13: panel_out = BMS_DOWN;  break;
    case 15: panel_out = BMS_UP;    break;
    case 16: panel_out = BMS_RIGHT; break;
    default: panel_out = -1;        break;
  }
}


bool NotesLoader::LoadFromFile(const char *path, NoteData *note_data/*, Steps *output*/) {
  // NoteData *note_data = new NoteData;
  note_data->set_num_panels(MAX_NOTE_PANELS);
  // ResetPanelsMagic();

  ifstream file_reader;
// #ifdef DEBUG__
  file_reader.open("OBLIVION_7a.bms", ifstream::in);
// #else
//   file_reader.open(path, ifstream::in);
// #endif /* DEBUG__ */

  if (!file_reader.good())
    return false;

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

    if (line.find("#PLAYER") != string::npos) {}
    if (line.find("#TITLE") != string::npos) {}
    if (line.find("#PLAYLEVEL") != string::npos) {}
    if (line.find("#BPM") != string::npos) {
      note_data->set_bpm(atoi(value.c_str()));
    }
    if (key.length() >= 6 &&  key[0] == '#'
        && isint(key[1]) && isint(key[2])
        && isint(key[3]) && isint(key[4])
        && isint(key[5])) {
      int measure_num = atoi(key.substr(1, 3).c_str());
      int panel_num = atoi(key.substr(4, 2).c_str());
      // PushPanelNumForMagic(panel_num);

      vector<bool> notes_array;      // split notes by 2
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
          float percent = (float)i / (float)note_num_in_this_measure;

          /* unify index to rows, leaving intervals TAP_EMPTY */
          const int note_row = (int)((measure_num + percent) * BEATS_PER_MEASURE * ROWS_PER_BEAT);

          /* col_num ~ panel_num */
          int col_num;
          TapNote tap_note;

          MapBMSToNote(panel_num, col_num, tap_note);

          // std::cout << note_num_in_this_measure << ' ' << i << ' ' <<  measure_num << ' ' << col_num << ' ' << note_row << std::endl;
          if (col_num != -1) {
            note_data->set_tap_note(col_num - 1, note_row, tap_note);
          }
        }
      }
    }
  }

// #ifdef DEBUG__
//   for (int i = 0; i < note_data->num_panels(); i++) {
//     for (int j = 0; j < (int)note_data->get_panel(i).size(); j++)
//       // std::cout<< note_data->tap_note(i, j).type << "\n";
//       // if (note_data->tap_note(i, j).type_ == TAP_EMPTY.type_
//       //     && note_data->tap_note(i, j).source_ == TAP_EMPTY.source_
//       //     && note_data->tap_note(i, j).attackIndex_ == TAP_EMPTY.attackIndex_)
//       //   std::cout << "1";
//       if (note_data->tap_note(i, j).type_ != 0)
//         std::cout << note_data->tap_note(i, j).type_;
//     std::cout << note_data->get_panel(i).size() << std::endl;
//   }
// #endif /* DEBUG__ */
  // delete note_data;
  return true;
}
